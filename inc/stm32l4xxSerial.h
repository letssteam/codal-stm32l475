#ifndef CODAL_STM32L4XX_SERIAL_H
#define CODAL_STM32L4XX_SERIAL_H
#include "CodalConfig.h"
#include "codal-core/inc/driver-models/Serial.h"
namespace codal
{
class STM32L4xxSerial : public codal::Serial
{
    public:
    /**
         * Constructor.
         * Create an instance of DeviceSerial
         *
         * @param tx the Pin to be used for transmission
         *
         * @param rx the Pin to be used for receiving data
         *
         * @param rxBufferSize the size of the buffer to be used for receiving bytes
         *
         * @param txBufferSize the size of the buffer to be used for transmitting bytes
         *
         * @code
         * DeviceSerial serial(USBTX, USBRX);
         * @endcode
         * @note the default baud rate is 115200. More API details can be found:
         *       -https://github.com/mbedmicro/mbed/blob/master/libraries/mbed/api/SerialBase.h
         *       -https://github.com/mbedmicro/mbed/blob/master/libraries/mbed/api/RawSerial.h
         *
         *       Buffers aren't allocated until the first send or receive respectively.
         */
    STM32L4xxSerial(Pin tx, Pin rx, uint8_t rxBufferSize = CODAL_SERIAL_DEFAULT_BUFFER_SIZE, uint8_t txBufferSize = CODAL_SERIAL_DEFAULT_BUFFER_SIZE):Serial(tx, rx, rxBufferSize, txBufferSize)
    {
    }
};
}
#endif