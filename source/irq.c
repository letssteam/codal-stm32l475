#include "stm32.h"

extern "C" void init_irqs() {}

extern "C" void NMI_Handler(void) {}

extern "C" void SVC_Handler(void) {}

extern "C" void DebugMon_Handler(void) {}

extern "C" void PendSV_Handler(void) {}

extern "C" void SysTick_Handler(void)
{
    HAL_IncTick();
}