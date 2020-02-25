/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include "CodalDmesg.h"
#include "pinmap.h"
#include "pin_device.h"
#define LOG DMESG

const uint32_t ll_pin_defines[16] = {
    LL_GPIO_PIN_0,  LL_GPIO_PIN_1,  LL_GPIO_PIN_2,  LL_GPIO_PIN_3, LL_GPIO_PIN_4,  LL_GPIO_PIN_5,
    LL_GPIO_PIN_6,  LL_GPIO_PIN_7,  LL_GPIO_PIN_8,  LL_GPIO_PIN_9, LL_GPIO_PIN_10, LL_GPIO_PIN_11,
    LL_GPIO_PIN_12, LL_GPIO_PIN_13, LL_GPIO_PIN_14, LL_GPIO_PIN_15};

typedef enum
{
    PortA = 0,
    PortB = 1,
    PortC = 2,
    PortD = 3,
    PortE = 4,
    PortF = 5,
    PortG = 6,
    PortH = 7,
    PortI = 8,
    PortJ = 9,
    PortK = 10
} PortName;

// Enable GPIO clock and return GPIO base address
extern "C" GPIO_TypeDef *Set_GPIO_Clock(uint32_t port_idx)
{
    uint32_t gpio_add = 0;
    switch (port_idx)
    {
    case PortA:
        gpio_add = GPIOA_BASE;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        break;
    case PortB:
        gpio_add = GPIOB_BASE;
        __HAL_RCC_GPIOB_CLK_ENABLE();
        break;
#if defined(GPIOC_BASE)
    case PortC:
        gpio_add = GPIOC_BASE;
        __HAL_RCC_GPIOC_CLK_ENABLE();
        break;
#endif
#if defined GPIOD_BASE
    case PortD:
        gpio_add = GPIOD_BASE;
        __HAL_RCC_GPIOD_CLK_ENABLE();
        break;
#endif
#if defined GPIOE_BASE
    case PortE:
        gpio_add = GPIOE_BASE;
        __HAL_RCC_GPIOE_CLK_ENABLE();
        break;
#endif
#if defined GPIOF_BASE
    case PortF:
        gpio_add = GPIOF_BASE;
        __HAL_RCC_GPIOF_CLK_ENABLE();
        break;
#endif
#if defined GPIOG_BASE
    case PortG:
#if defined TARGET_STM32L4
        __HAL_RCC_PWR_CLK_ENABLE();
        HAL_PWREx_EnableVddIO2();
#endif
        gpio_add = GPIOG_BASE;
        __HAL_RCC_GPIOG_CLK_ENABLE();
        break;
#endif
#if defined GPIOH_BASE
    case PortH:
        gpio_add = GPIOH_BASE;
        __HAL_RCC_GPIOH_CLK_ENABLE();
        break;
#endif
#if defined GPIOI_BASE
    case PortI:
        gpio_add = GPIOI_BASE;
        __HAL_RCC_GPIOI_CLK_ENABLE();
        break;
#endif
#if defined GPIOJ_BASE
    case PortJ:
        gpio_add = GPIOJ_BASE;
        __HAL_RCC_GPIOJ_CLK_ENABLE();
        break;
#endif
#if defined GPIOK_BASE
    case PortK:
        gpio_add = GPIOK_BASE;
        __HAL_RCC_GPIOK_CLK_ENABLE();
        break;
#endif
    default:
        LOG("Pinmap error: wrong port number.");
        break;
    }
    return (GPIO_TypeDef *)gpio_add;
}

// return GPIO base address
extern "C" GPIO_TypeDef *Get_GPIO_Port(uint32_t port_idx)
{
    uint32_t gpio_add = 0;
    switch (port_idx)
    {
    case PortA:
        gpio_add = GPIOA_BASE;
        break;
    case PortB:
        gpio_add = GPIOB_BASE;
        break;
#if defined(GPIOC_BASE)
    case PortC:
        gpio_add = GPIOC_BASE;
        break;
#endif
#if defined GPIOD_BASE
    case PortD:
        gpio_add = GPIOD_BASE;
        break;
#endif
#if defined GPIOE_BASE
    case PortE:
        gpio_add = GPIOE_BASE;
        break;
#endif
#if defined GPIOF_BASE
    case PortF:
        gpio_add = GPIOF_BASE;
        break;
#endif
#if defined GPIOG_BASE
    case PortG:
        gpio_add = GPIOG_BASE;
        break;
#endif
#if defined GPIOH_BASE
    case PortH:
        gpio_add = GPIOH_BASE;
        break;
#endif
#if defined GPIOI_BASE
    case PortI:
        gpio_add = GPIOI_BASE;
        break;
#endif
#if defined GPIOJ_BASE
    case PortJ:
        gpio_add = GPIOJ_BASE;
        break;
#endif
#if defined GPIOK_BASE
    case PortK:
        gpio_add = GPIOK_BASE;
        break;
#endif
    default:
        LOG("Pinmap error: wrong port number.");
        break;
    }
    return (GPIO_TypeDef *)gpio_add;
}

/**
 * Configure pin (mode, speed, output type and pull-up/pull-down)
 */
extern "C" void pin_function(PinNumber pin, int data)
{
    CODAL_ASSERT(pin != PinNumber::NC, 99);

    // LOG("pin_function(%x, %x)\n",(uint8_t)pin, data);
    // Get the pin informations
    uint32_t mode = STM_PIN_FUNCTION(data);
    uint32_t afnum = STM_PIN_AFNUM(data);
    uint32_t port = STM_PORT(pin);
    uint32_t ll_pin = ll_pin_defines[STM_PIN(pin)];
    uint32_t ll_mode = 0;

    // Enable GPIO clock
    GPIO_TypeDef *gpio = Set_GPIO_Clock(port);

    /*  Set default speed to high.
     *  For most families there are dedicated registers so it is
     *  not so important, register can be set at any time.
     *  But for families like F1, speed only applies to output.
     */
    #ifdef LL_GPIO_SPEED_FREQ_VERY_HIGH
    LL_GPIO_SetPinSpeed(gpio, ll_pin, LL_GPIO_SPEED_FREQ_VERY_HIGH);
    #else
    LL_GPIO_SetPinSpeed(gpio, ll_pin, LL_GPIO_SPEED_FREQ_HIGH);
    #endif

    switch (mode)
    {
    case STM_PIN_INPUT:
        ll_mode = LL_GPIO_MODE_INPUT;
        break;
    case STM_PIN_OUTPUT:
        ll_mode = LL_GPIO_MODE_OUTPUT;
        break;
    case STM_PIN_ALTERNATE:
        ll_mode = LL_GPIO_MODE_ALTERNATE;
        // In case of ALT function, also set he afnum
        stm_pin_SetAFPin(gpio, pin, afnum);
        break;
    case STM_PIN_ANALOG:
        ll_mode = LL_GPIO_MODE_ANALOG;
        break;
    default:
        LOG("incorect pin mode !");
        break;
    }
    LL_GPIO_SetPinMode(gpio, ll_pin, ll_mode);

#if defined(GPIO_ASCR_ASC0)
    /*  For families where Analog Control ASC0 register is present */
    if (STM_PIN_ANALOG_CONTROL(data))
    {
        LL_GPIO_EnablePinAnalogControl(gpio, ll_pin);
    }
    else
    {
        LL_GPIO_DisablePinAnalogControl(gpio, ll_pin);
    }
#endif

    /*  For now by default use Speed HIGH for output or alt modes */
    if ((mode == STM_PIN_OUTPUT) || (mode == STM_PIN_ALTERNATE))
    {
        if (STM_PIN_OD(data))
        {
            LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_OPENDRAIN);
        }
        else
        {
            LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_PUSHPULL);
        }
    }

    stm_pin_PullConfig(gpio, ll_pin, STM_PIN_PUPD(data));

    stm_pin_DisconnectDebug(pin);
}

/**
 * Configure pin pull-up/pull-down
 */
extern "C" void pin_mode(PinNumber pin, PinMode mode)
{
    CODAL_ASSERT(pin != PinNumber::NC, 99);

    uint32_t port_index = STM_PORT(pin);
    uint32_t ll_pin = ll_pin_defines[STM_PIN(pin)];
    // Enable GPIO clock
    GPIO_TypeDef *gpio = Set_GPIO_Clock(port_index);
    uint32_t function = LL_GPIO_GetPinMode(gpio, ll_pin);

    if ((function == LL_GPIO_MODE_OUTPUT) || (function == LL_GPIO_MODE_ALTERNATE))
    {
        if ((mode == OpenDrainNoPull) || (mode == OpenDrainPullUp) || (mode == OpenDrainPullDown))
        {
            LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_OPENDRAIN);
        }
        else
        {
            LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_PUSHPULL);
        }
    }

    if ((mode == OpenDrainPullUp) || (mode == PullUp))
    {
        stm_pin_PullConfig(gpio, ll_pin, GPIO_PULLUP);
    }
    else if ((mode == OpenDrainPullDown) || (mode == PullDown))
    {
        stm_pin_PullConfig(gpio, ll_pin, GPIO_PULLDOWN);
    }
    else
    {
        stm_pin_PullConfig(gpio, ll_pin, GPIO_NOPULL);
    }
}

extern "C" void pinmap_pinout(PinNumber pin, const PinMap *map)
{
    if (pin == PinNumber::NC)
        return;

    while (map->pin != PinNumber::NC)
    {
        if (map->pin == pin)
        {
            pin_function(pin, map->function);
            return;
        }
        map++;
    }
    LOG("could not pinout");
}

extern "C" uint32_t pinmap_merge(uint32_t a, uint32_t b)
{
    // both are the same (inc both NC)
    if (a == b)
        return a;

    // one (or both) is not connected
    if (a == (uint32_t)NC)
        return b;
    if (b == (uint32_t)NC)
        return a;

    // mis-match error case
    codal_error("pinmap mis-match");
    return (uint32_t)NC;
}

extern "C" bool pin_in_pinmap(PinNumber pin, const PinMap *map)
{
  if (pin != (PinNumber)PinNumber::NC) {
    while (map->pin != PinNumber::NC) {
      if (map->pin == pin) {
        return true;
      }
      map++;
    }
  }
  return false;
}

extern "C" uint32_t pinmap_find_peripheral(PinNumber pin, const PinMap *map)
{
    while (map->pin != PinNumber::NC)
    {
        if (map->pin == pin)
            return map->peripheral;
        map++;
    }
    return (uint32_t)NC;
}

extern "C" uint32_t pinmap_peripheral(PinNumber pin, const PinMap *map)
{
    uint32_t peripheral = (uint32_t)NC;

    if (pin == PinNumber::NC)
        return (uint32_t)NC;
    peripheral = pinmap_find_peripheral(pin, map);
    if ((uint32_t)NC == peripheral) // no mapping available
        LOG("pinmap not found for peripheral");
    return peripheral;
}

extern "C" PinNumber pinmap_find_pin(void *peripheral, const PinMap *map)
{
  while (map->peripheral != NP) {
    if (map->peripheral == (uint32_t)peripheral) {
      return map->pin;
    }
    map++;
  }
  return PinNumber::NC;
}

extern "C" PinNumber pinmap_pin(void *peripheral, const PinMap *map)
{
  PinNumber pin = PinNumber::NC;

  if ((uint32_t)peripheral != NP) {
    pin = pinmap_find_pin(peripheral, map);
  }
  return pin;
}

extern "C" uint32_t pinmap_find_function(PinNumber pin, const PinMap *map)
{
    while (map->pin != PinNumber::NC)
    {
        if (map->pin == pin)
            return map->function;
        map++;
    }
    return (uint32_t)NC;
}

extern "C" uint32_t pinmap_function(PinNumber pin, const PinMap *map)
{
    uint32_t function = (uint32_t)NC;

    if (pin == PinNumber::NC)
        return (uint32_t)NC;
    function = pinmap_find_function(pin, map);
    if ((uint32_t)NC == function) // no mapping available
        codal_error("pinmap not found for function");
    return function;
}

extern "C" void digital_io_init(PinNumber pin, uint32_t mode, uint32_t pull)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_TypeDef *port = Set_GPIO_Clock(STM_PORT(pin));
    GPIO_InitStructure.Pin = STM_PIN(pin);
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode = mode;
    GPIO_InitStructure.Pull = pull;
#ifdef STM32F1xx
    pinF1_DisconnectDebug(pin);
#endif /* STM32F1xx */
    HAL_GPIO_Init(port, &GPIO_InitStructure);
}

extern "C" void digital_io_write(GPIO_TypeDef *port, uint32_t pin, uint32_t val)
{
    if (val)
    {
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
    }
}

extern "C" void digitalWrite(PinNumber pin, uint32_t ulVal)
{
    if (pin != codal::PinNumber::NC)
    {
        digital_io_write(Get_GPIO_Port(STM_PORT(pin)), STM_PIN(pin), ulVal);
    }
}

uint32_t codal_setup_pin(codal::Pin &p, uint32_t prev, const PinMap *map)
{
    auto pin = p.name;
    uint32_t tmp = pinmap_peripheral(pin, map);
    pin_function(pin, pinmap_function(pin, map));
    pin_mode(pin, PullNone);
    CODAL_ASSERT(!prev || prev == tmp, 99);
    return tmp;
}
