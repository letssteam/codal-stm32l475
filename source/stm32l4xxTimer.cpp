#include "stm32l4xxTimer.h"
#include "CodalConfig.h"
#include "codal_target_hal.h"

#include "CodalDmesg.h"

using namespace codal;


STM32L4xxTimer *STM32L4xxTimer::instance;

STM32L4xxTimer::STM32L4xxTimer() : codal::Timer()
{
    memset(&TimHandle, 0, sizeof(TimHandle));
    instance = this;
    this->prev = 0;
}

extern "C" void TIM5_IRQHandler()
{
    auto h = &STM32L4xxTimer::instance->TimHandle;

    if (__HAL_TIM_GET_FLAG(h, TIM_FLAG_CC1) == SET)
    {
        if (__HAL_TIM_GET_IT_SOURCE(h, TIM_IT_CC1) == SET)
        {
            __HAL_TIM_CLEAR_IT(h, TIM_IT_CC1);
            __HAL_TIM_CLEAR_FLAG(h, TIM_FLAG_CC1);
            STM32L4xxTimer::instance->trigger();
        }
    }
}

void STM32L4xxTimer::init()
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    uint32_t PclkFreq;

    // Get clock configuration
    // Note: PclkFreq contains here the Latency (not used after)
    HAL_RCC_GetClockConfig(&RCC_ClkInitStruct, &PclkFreq);

    PclkFreq = HAL_RCC_GetPCLK1Freq();

    // Enable timer clock
    __HAL_RCC_TIM5_CLK_ENABLE(); 

    __HAL_RCC_TIM5_FORCE_RESET();
    __HAL_RCC_TIM5_RELEASE_RESET();

    TimHandle.Instance = TIM5;

    TimHandle.Init.Period = 0xFFFFFFFF;

    if (RCC_ClkInitStruct.APB1CLKDivider == RCC_HCLK_DIV1) {
        TimHandle.Init.Prescaler   = (uint16_t)((PclkFreq) / 1000000) - 1; // 1 us tick
    } else {
        TimHandle.Init.Prescaler   = (uint16_t)((PclkFreq * 2) / 1000000) - 1; // 1 us tick
    }

    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;

    if (HAL_TIM_OC_Init(&TimHandle) != HAL_OK)
        CODAL_ASSERT(0);

    NVIC_SetPriority(TIM5_IRQn, 0);
    NVIC_EnableIRQ(TIM5_IRQn);
    HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_1);

    this->prev = __HAL_TIM_GET_COUNTER(&TimHandle);
}

void STM32L4xxTimer::triggerIn(CODAL_TIMESTAMP t)
{
    if (t < 20)
        t = 20;

    this->syncRequest(); // is this needed?

    target_disable_irq();
    __HAL_TIM_DISABLE_IT(&TimHandle, TIM_IT_CC1);
    __HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_1,
                          (uint32_t)(__HAL_TIM_GET_COUNTER(&TimHandle) + t));
    __HAL_TIM_ENABLE_IT(&TimHandle, TIM_IT_CC1);
    target_enable_irq();
}

extern "C" uint32_t uwTick;

void STM32L4xxTimer::syncRequest()
{
    target_disable_irq();
    uint32_t curr = __HAL_TIM_GET_COUNTER(&TimHandle);
    uint32_t delta = curr - this->prev;

    // update the hal...
    uwTick += delta / 1000;

    this->prev = curr;
    this->sync(delta);
    target_enable_irq();
}

extern "C" void wait_us(uint32_t us)
{
    auto end = STM32L4xxTimer::instance->getTimeUs() + us;

    while (STM32L4xxTimer::instance->getTimeUs() < end)
    {
        // busy wait
    }
}