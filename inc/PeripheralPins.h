#ifndef CODAL_PERIPHERALPINS_H
#define CODAL_PERIPHERALPINS_H

#include "pinmap.h"
#include "PeripheralNames.h"
#ifdef __cplusplus
extern "C" {
#endif
//*** ADC ***

extern const PinMap PinMap_ADC[];
extern const PinMap PinMap_ADC_Internal[];
//*** DAC ***
extern const PinMap PinMap_DAC[];

//*** I2C ***
extern const PinMap PinMap_I2C_SDA[];
extern const PinMap PinMap_I2C_SCL[];

//*** PWM ***
extern const PinMap PinMap_PWM[];

//*** SERIAL ***
extern const PinMap PinMap_UART_TX[];
extern const PinMap PinMap_UART_RX[];
extern const PinMap PinMap_UART_RTS[];
extern const PinMap PinMap_UART_CTS[];

//*** SPI ***
extern const PinMap PinMap_SPI_MOSI[];
extern const PinMap PinMap_SPI_MISO[];
extern const PinMap PinMap_SPI_SCLK[];
extern const PinMap PinMap_SPI_SSEL[];

//*** CAN ***
extern const PinMap PinMap_CAN_RD[];
extern const PinMap PinMap_CAN_TD[];
#ifdef __cplusplus
}
#endif
#endif
