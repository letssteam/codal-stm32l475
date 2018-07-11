/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
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

#include "PeripheralPins.h"

//==============================================================================
// Notes
//
// - The pins mentioned Px_y_ALTz are alternative possibilities which use other
//   HW peripheral instances. You can use them the same way as any other "normal"
//   pin (i.e. PwmOut pwm(PA_7_ALT0);). These pins are not displayed on the board
//   pinout image on mbed.org.
//
// - The pins which are connected to other components present on the board have
//   the comment "Connected to xxx". The pin function may not work properly in this
//   case. These pins may not be displayed on the board pinout image on mbed.org.
//   Please read the board reference manual and schematic for more information.
//
// - Warning: pins connected to the default STDIO_UART_TX and STDIO_UART_RX pins are commented
//   See https://os.mbed.com/teams/ST/wiki/STDIO for more information.
//
//==============================================================================


//*** ADC ***

__attribute__((weak)) extern const PinMap PinMap_ADC[] = {
    {codal::PinNumber::PA_0,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 5, 0)}, // ADC1_IN5 // Connected to ARD_D1 [UART4_TX]
    {codal::PinNumber::PA_1,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 6, 0)}, // ADC1_IN6 // Connected to ARD_D0 [UART4_RX]
    {codal::PinNumber::PA_2,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 7, 0)}, // ADC1_IN7 // Connected to ARD_D10 [SPI_SSN]
    {codal::PinNumber::PA_3,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 8, 0)}, // ADC1_IN8 // Connected to ARD_D4
    {codal::PinNumber::PA_4,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 9, 0)}, // ADC1_IN9 // Connected to ARD_D7
    {codal::PinNumber::PA_5,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 10, 0)}, // ADC1_IN10 // Connected to ARD_D13 [SPI1_SCK]
    {codal::PinNumber::PA_6,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 11, 0)}, // ADC1_IN11 // Connected to ARD_D12 [SPI1_MISO]
    {codal::PinNumber::PA_7,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 12, 0)}, // ADC1_IN12 // Connected to ARD_D11 [SPI1_MOSI]
    {codal::PinNumber::PB_0,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 15, 0)}, // ADC1_IN15 // Connected to ARD_D3 [INT_EXT10]
    {codal::PinNumber::PB_1,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 16, 0)}, // ADC1_IN16 // Connected to ARD_D6 [ADC1_IN6]
    {codal::PinNumber::PC_0,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 1, 0)}, // ADC1_IN1 // Connected to ARD_A5 [ADC]
    {codal::PinNumber::PC_1,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 2, 0)}, // ADC1_IN2 // Connected to ARD_A4 [ADC]
    {codal::PinNumber::PC_2,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 3, 0)}, // ADC1_IN3 // Connected to ARD_A3 [ADC]
    {codal::PinNumber::PC_3,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 4, 0)}, // ADC1_IN4 // Connected to ARD_A2 [ADC]
    {codal::PinNumber::PC_4,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 13, 0)}, // ADC1_IN13 // Connected to ARD_A1 [ADC]
    {codal::PinNumber::PC_5,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 14, 0)}, // ADC1_IN14 // Connected to ARD_A0 [ADC]
    {codal::PinNumber::NC, -1, 0}
};

__attribute__((weak)) extern const PinMap PinMap_ADC_Internal[] = {
    {codal::PinNumber::ADC_TEMP,   ADC_1,    STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 17, 0)},
    {codal::PinNumber::ADC_VREF,   ADC_1,    STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0,  0, 0)},
    {codal::PinNumber::ADC_VBAT,   ADC_1,    STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 18, 0)},
    {codal::PinNumber::NC, -1, 0}
};

//*** DAC ***

__attribute__((weak)) extern const PinMap PinMap_DAC[] = {
    {codal::PinNumber::PA_4,       DAC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 1, 0)}, // DAC1_OUT1 // Connected to ARD_D7
    {codal::PinNumber::PA_5,       DAC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 2, 0)}, // DAC1_OUT2 // Connected to ARD_D13 [SPI1_SCK]
    {codal::PinNumber::NC, -1, 0}
};

//*** I2C ***

__attribute__((weak)) extern const PinMap PinMap_I2C_SDA[] = {
//  {PB_7,       I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)}, // Connected to STDIO_UART_RX
    {codal::PinNumber::PB_9,       I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)}, // Connected to ARD_D14 [I2C1_SDA]
    {codal::PinNumber::PB_11,      I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)}, // Connected to INTERNAL_I2C2_SDA [VL53L0X_SDA]
    {codal::PinNumber::PB_14,      I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)}, // Connected to LED2 [LED_GREEN]
    {codal::PinNumber::PC_1,       I2C_3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3)}, // Connected to ARD_A4 [ADC]
    {codal::PinNumber::NC, -1, 0}
};

__attribute__((weak)) extern const PinMap PinMap_I2C_SCL[] = {
//  {PB_6,       I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)}, // Connected to STDIO_UART_TX
    {codal::PinNumber::PB_8,       I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)}, // Connected to ARD_D15 [I2C1_SCL]
    {codal::PinNumber::PB_10,      I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)}, // Connected to INTERNAL_I2C2_SCL [VL53L0X_SCL]
    {codal::PinNumber::PB_13,      I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)}, // Connected to ISM43362_WAKEUP [ISM43362_WKUP]
    {codal::PinNumber::PC_0,       I2C_3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3)}, // Connected to ARD_A5 [ADC]
    {codal::PinNumber::NC, -1, 0}
};

//*** PWM ***

// TIM5 cannot be used because already used by the us_ticker
__attribute__((weak)) extern const PinMap PinMap_PWM[] = {
    {codal::PinNumber::PA_0,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 1, 0)}, // TIM2_CH1 // Connected to ARD_D1 [UART4_TX]
//  {PA_0,       PWM_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM5, 1, 0)}, // TIM5_CH1 // Connected to ARD_D1 [UART4_TX]
    {codal::PinNumber::PA_1,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 2, 0)}, // TIM2_CH2 // Connected to ARD_D0 [UART4_RX]
//  {PA_1,       PWM_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM5, 2, 0)}, // TIM5_CH2 // Connected to ARD_D0 [UART4_RX]
    {codal::PinNumber::PA_2,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 3, 0)}, // TIM2_CH3 // Connected to ARD_D10 [SPI_SSN]
//  {PA_2,       PWM_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM5, 3, 0)}, // TIM5_CH3 // Connected to ARD_D10 [SPI_SSN]
    {codal::PinNumber::PA_3,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 4, 0)}, // TIM2_CH4 // Connected to ARD_D4
//  {PA_3,       PWM_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM5, 4, 0)}, // TIM5_CH4 // Connected to ARD_D4
    {codal::PinNumber::PA_5,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 1, 0)}, // TIM2_CH1 // Connected to ARD_D13 [SPI1_SCK]
    {codal::PinNumber::PA_6,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 1, 0)}, // TIM3_CH1 // Connected to ARD_D12 [SPI1_MISO]
    {codal::PinNumber::PA_7,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 1)}, // TIM1_CH1N // Connected to ARD_D11 [SPI1_MOSI]
    {codal::PinNumber::PA_8,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 0)}, // TIM1_CH1 // Connected to SPBTLE_RF_RST
    {codal::PinNumber::PA_9,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 0)}, // TIM1_CH2 // Connected to USB_OTG_FS_VBUS [STMPS2141STR_OUT]
    {codal::PinNumber::PA_10,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 0)}, // TIM1_CH3 // Connected to USB_OTG_FS_ID
    {codal::PinNumber::PA_11,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 4, 0)}, // TIM1_CH4 // Connected to USB_OTG_FS_DM
    {codal::PinNumber::PA_15,      PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 1, 0)}, // TIM2_CH1
    {codal::PinNumber::PB_0,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 1)}, // TIM1_CH2N // Connected to ARD_D3 [INT_EXT10]
    {codal::PinNumber::PB_1,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 1)}, // TIM1_CH3N // Connected to ARD_D6 [ADC1_IN6]
    {codal::PinNumber::PB_3,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 2, 0)}, // TIM2_CH2
    {codal::PinNumber::PB_4,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 1, 0)}, // TIM3_CH1
    {codal::PinNumber::PB_5,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 2, 0)}, // TIM3_CH2 // Connected to SPSGRF_915_SPI3_CSN [SPSGRF_SPI_CS]
//  {PB_6,       PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 1, 0)}, // TIM4_CH1 // Connected to STDIO_UART_TX
//  {PB_6,       PWM_16, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM16, 1, 1)}, // TIM16_CH1N // Connected to STDIO_UART_TX
//  {PB_7,       PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 2, 0)}, // TIM4_CH2 // Connected to STDIO_UART_RX
//  {PB_7,       PWM_17, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM17, 1, 1)}, // TIM17_CH1N // Connected to STDIO_UART_RX
    {codal::PinNumber::PB_8,       PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 3, 0)}, // TIM4_CH3 // Connected to ARD_D15 [I2C1_SCL]
    {codal::PinNumber::PB_9,       PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 4, 0)}, // TIM4_CH4 // Connected to ARD_D14 [I2C1_SDA]
    {codal::PinNumber::PB_10,      PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 3, 0)}, // TIM2_CH3 // Connected to INTERNAL_I2C2_SCL [VL53L0X_SCL]
    {codal::PinNumber::PB_11,      PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 4, 0)}, // TIM2_CH4 // Connected to INTERNAL_I2C2_SDA [VL53L0X_SDA]
    {codal::PinNumber::PB_13,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 1)}, // TIM1_CH1N // Connected to ISM43362_WAKEUP [ISM43362_WKUP]
    {codal::PinNumber::PB_14,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 1)}, // TIM1_CH2N // Connected to LED2 [LED_GREEN]
    {codal::PinNumber::PB_15,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 1)}, // TIM1_CH3N // Connected to SPSGRF_915_SDN [SPSGRF_SDN]
    {codal::PinNumber::PC_6,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 1, 0)}, // TIM3_CH1 // Connected to VL53L0X_XSHUT [Read_XSHUT]
    {codal::PinNumber::PC_7,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 2, 0)}, // TIM3_CH2 // Connected to VL53L0X_GPIO1_EXTI7 [VL53L0X_GPIO1]
    {codal::PinNumber::PC_8,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 3, 0)}, // TIM3_CH3 // Connected to LSM3MDL_DRDY_EXTI8 [LIS3MDL_DRDY]
    {codal::PinNumber::PC_9,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 4, 0)}, // TIM3_CH4 // Connected to LED3_WIFI_ LED4_BLE
    {codal::PinNumber::PD_12,      PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 1, 0)}, // TIM4_CH1 // Connected to USB_OTG_FS_PWR_EN [STMPS2141STR_EN]
    {codal::PinNumber::PD_13,      PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 2, 0)}, // TIM4_CH2 // Connected to SPBTLE_RF_SPI3_CSN [BT module_SPI_CS]
    {codal::PinNumber::PD_14,      PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 3, 0)}, // TIM4_CH3 // Connected to ARD_D2 [INT0_EXTI14]
    {codal::PinNumber::PD_15,      PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 4, 0)}, // TIM4_CH4 // Connected to HTS221_DRDY_EXTI15 [HTS221_DRDY]
    {codal::PinNumber::PE_0,       PWM_16, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM16, 1, 0)}, // TIM16_CH1 // Connected to ISM43362_SPI3_CSN [ISM43362_SSN]
    {codal::PinNumber::PE_1,       PWM_17, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM17, 1, 0)}, // TIM17_CH1 // Connected to ISM43362_DRDY_EXTI1 [ISM43362_DATARDY]
    {codal::PinNumber::PE_3,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 1, 0)}, // TIM3_CH1 // Connected to USB_OTG_FS_OVRCR_EXTI3 [STMPS2141STR_FAULT]
    {codal::PinNumber::PE_4,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 2, 0)}, // TIM3_CH2 // Connected to M24SR64_Y_GPO [M24SR64_GPO]
    {codal::PinNumber::PE_5,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 3, 0)}, // TIM3_CH3 // Connected to SPSGRF_915_GPIO3_EXTI5 [SPSGRF_GPIO_3]
    {codal::PinNumber::PE_6,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 4, 0)}, // TIM3_CH4 // Connected to SPBTLE_RF_IRQ_EXTI6 [BT module_SPI_IRQ]
    {codal::PinNumber::PE_8,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 1)}, // TIM1_CH1N // Connected to ISM43362_RST [ISM43362_RSTN]
    {codal::PinNumber::PE_9,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 0)}, // TIM1_CH1 // Connected to DFSDM1_CKOUT [MP34DT01_CLK]
    {codal::PinNumber::PE_10,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 1)}, // TIM1_CH2N // Connected to QUADSPI_CLK [MX25R6435F_SCLK]
    {codal::PinNumber::PE_11,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 0)}, // TIM1_CH2 // Connected to QUADSPI_NCS [MX25R6435F_SCLK]
    {codal::PinNumber::PE_12,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 1)}, // TIM1_CH3N // Connected to OQUADSPI_BK1_IO0 [MX25R6435F_IO0]
    {codal::PinNumber::PE_13,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 0)}, // TIM1_CH3 // Connected to QUADSPI_BK1_IO1 [MX25R6435F_IO1]
    {codal::PinNumber::PE_14,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 4, 0)}, // TIM1_CH4 // Connected to QUAD_SPI_BK1_IO2 [MX25R6435F_IO2]
    {codal::PinNumber::NC, -1, 0}
};

//*** SERIAL ***

__attribute__((weak)) extern const PinMap PinMap_UART_TX[] = {
    {codal::PinNumber::PA_0,       UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)}, // Connected to ARD_D1 [UART4_TX]
    {codal::PinNumber::PA_2,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)}, // Connected to ARD_D10 [SPI_SSN]
    {codal::PinNumber::PA_9,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)}, // Connected to USB_OTG_FS_VBUS [STMPS2141STR_OUT]
    {codal::PinNumber::PB_6,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)}, // Connected to STDIO_UART_TX
    {codal::PinNumber::PB_10,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to INTERNAL_I2C2_SCL [VL53L0X_SCL]
    {codal::PinNumber::PB_11,      LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // Connected to INTERNAL_I2C2_SDA [VL53L0X_SDA]
    {codal::PinNumber::PC_1,       LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // Connected to ARD_A4 [ADC]
    {codal::PinNumber::PC_4,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to ARD_A1 [ADC]
    {codal::PinNumber::PC_10,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to INTERNAL_SPI3_SCK [BT module_SPI_SCLK]
    {codal::PinNumber::PC_12,      UART_5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)}, // Connected to INTERNAL_SPI3_MOSI [BT module_SPI_MOSI]
    {codal::PinNumber::PD_5,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)}, // Connected to PMOD_UART2_TX
    {codal::PinNumber::PD_8,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to INTERNAL_UART3_TX [ISM43362_RX]
    {codal::PinNumber::NC, -1, 0}
};
__attribute__((weak)) extern const PinMap PinMap_UART_RX[] = {
    {codal::PinNumber::PA_1,       UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)}, // Connected to ARD_D0 [UART4_RX]
    {codal::PinNumber::PA_3,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)}, // Connected to ARD_D4
    {codal::PinNumber::PA_10,      UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)}, // Connected to USB_OTG_FS_ID
    {codal::PinNumber::PB_7,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)}, // Connected to STDIO_UART_RX
    {codal::PinNumber::PB_10,      LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // Connected to INTERNAL_I2C2_SCL [VL53L0X_SCL]
    {codal::PinNumber::PB_11,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to INTERNAL_I2C2_SDA [VL53L0X_SDA]
    {codal::PinNumber::PC_0,       LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // Connected to ARD_A5 [ADC]
    {codal::PinNumber::PC_5,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to ARD_A0 [ADC]
    {codal::PinNumber::PC_11,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to INTERNAL_SPI3_MISO [BT module_SPI_MISO]
    {codal::PinNumber::PD_2,       UART_5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)}, // Connected to PMOD_IRQ_EXTI12
    {codal::PinNumber::PD_6,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)}, // Connected to PMOD_UART2_RX
    {codal::PinNumber::PD_9,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to INTERNAL_UART3_RX [ISM43362_TX]
    {codal::PinNumber::NC, -1, 0}
};

__attribute__((weak)) extern const PinMap PinMap_UART_RTS[] = {
    {codal::PinNumber::PA_1,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)}, // Connected to ARD_D0 [UART4_RX]
    {codal::PinNumber::PA_12,      UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)}, // Connected to USB_OTG_FS_DP
    {codal::PinNumber::PA_15,      UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)},
    {codal::PinNumber::PB_1,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to ARD_D6 [ADC1_IN6]
    {codal::PinNumber::PB_3,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
    {codal::PinNumber::PB_4,       UART_5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)},
    {codal::PinNumber::PB_12,      LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // Connected to ISM43362_BOOT0 [ISM43362_BOOT]
    {codal::PinNumber::PB_14,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to LED2 [LED_GREEN]
    {codal::PinNumber::PD_2,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to PMOD_IRQ_EXTI12
    {codal::PinNumber::PD_4,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)}, // Connected to PMOD_UART2_RTS
    {codal::PinNumber::PD_12,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to USB_OTG_FS_PWR_EN [STMPS2141STR_EN]
    {codal::PinNumber::NC, -1, 0}
};

__attribute__((weak)) extern const PinMap PinMap_UART_CTS[] = {
    {codal::PinNumber::PA_0,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)}, // Connected to ARD_D1 [UART4_TX]
    {codal::PinNumber::PA_6,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to ARD_D12 [SPI1_MISO]
    {codal::PinNumber::PA_11,      UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)}, // Connected to USB_OTG_FS_DM
    {codal::PinNumber::PB_4,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
    {codal::PinNumber::PB_5,       UART_5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)}, // Connected to SPSGRF_915_SPI3_CSN [SPSGRF_SPI_CS]
    {codal::PinNumber::PB_7,       UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)}, // Connected to STDIO_UART_RX
    {codal::PinNumber::PB_13,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to ISM43362_WAKEUP [ISM43362_WKUP]
    {codal::PinNumber::PD_3,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)}, // Connected to PMOD_UART2_CTS
    {codal::PinNumber::PD_11,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)}, // Connected to LSM6DSL_INT1_EXTI11 [LSM6DSL_INT1]
    {codal::PinNumber::NC, -1, 0}
};

//*** SPI ***

__attribute__((weak)) extern const PinMap PinMap_SPI_MOSI[] = {
    {codal::PinNumber::PA_7,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // Connected to ARD_D11 [SPI1_MOSI]
    {codal::PinNumber::PB_5,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // Connected to SPSGRF_915_SPI3_CSN [SPSGRF_SPI_CS]
    {codal::PinNumber::PB_15,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to SPSGRF_915_SDN [SPSGRF_SDN]
    {codal::PinNumber::PC_3,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to ARD_A2 [ADC]
    {codal::PinNumber::PC_12,      SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // Connected to INTERNAL_SPI3_MOSI [BT module_SPI_MOSI]
    {codal::PinNumber::PD_4,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to PMOD_UART2_RTS
    {codal::PinNumber::PE_15,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // Connected to QUAD_SPI_BK1_IO3 [MX25R6435F_IO3]
    {codal::PinNumber::NC, -1, 0}
};

__attribute__((weak)) extern const PinMap PinMap_SPI_MISO[] = {
    {codal::PinNumber::PA_6,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // Connected to ARD_D12 [SPI1_MISO]
    {codal::PinNumber::PB_4,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)},
    {codal::PinNumber::PB_14,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to LED2 [LED_GREEN]
    {codal::PinNumber::PC_2,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to ARD_A3 [ADC]
    {codal::PinNumber::PC_11,      SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // Connected to INTERNAL_SPI3_MISO [BT module_SPI_MISO]
    {codal::PinNumber::PD_3,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to PMOD_UART2_CTS
    {codal::PinNumber::PE_14,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // Connected to QUAD_SPI_BK1_IO2 [MX25R6435F_IO2]
    {codal::PinNumber::NC, -1, 0}
};

__attribute__((weak)) extern const PinMap PinMap_SPI_SCLK[] = {
    {codal::PinNumber::PA_5,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // Connected to ARD_D13 [SPI1_SCK]
    {codal::PinNumber::PB_3,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)},
    {codal::PinNumber::PB_10,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to INTERNAL_I2C2_SCL [VL53L0X_SCL]
    {codal::PinNumber::PB_13,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to ISM43362_WAKEUP [ISM43362_WKUP]
    {codal::PinNumber::PC_10,      SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // Connected to INTERNAL_SPI3_SCK [BT module_SPI_SCLK]
    {codal::PinNumber::PD_1,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to PMOD_SPI2_SCK
    {codal::PinNumber::PE_13,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // Connected to QUADSPI_BK1_IO1 [MX25R6435F_IO1]
    {codal::PinNumber::NC, -1, 0}
};

__attribute__((weak)) extern const PinMap PinMap_SPI_SSEL[] = {
    {codal::PinNumber::PA_4,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // Connected to ARD_D7
    {codal::PinNumber::PA_15,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)},
    {codal::PinNumber::PB_9,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to ARD_D14 [I2C1_SDA]
    {codal::PinNumber::PB_12,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to ISM43362_BOOT0 [ISM43362_BOOT]
    {codal::PinNumber::PD_0,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // Connected to PMOD_RESET
    {codal::PinNumber::PE_12,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // Connected to OQUADSPI_BK1_IO0 [MX25R6435F_IO0]
    {codal::PinNumber::NC, -1, 0}
};

//*** CAN ***

__attribute__((weak)) extern const PinMap PinMap_CAN_RD[] = {
    {codal::PinNumber::PA_11,      CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // Connected to USB_OTG_FS_DM
    {codal::PinNumber::PB_8,       CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // Connected to ARD_D15 [I2C1_SCL]
    {codal::PinNumber::PD_0,       CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // Connected to PMOD_RESET
    {codal::PinNumber::NC, -1, 0}
};

__attribute__((weak)) extern const PinMap PinMap_CAN_TD[] = {
    {codal::PinNumber::PA_12,      CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // Connected to USB_OTG_FS_DP
    {codal::PinNumber::PB_9,       CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // Connected to ARD_D14 [I2C1_SDA]
    {codal::PinNumber::PD_1,       CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // Connected to PMOD_SPI2_SCK
    {codal::PinNumber::NC, -1, 0}
};
