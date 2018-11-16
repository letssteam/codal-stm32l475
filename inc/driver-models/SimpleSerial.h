#ifndef CODAL_SIMPLE_SERIAL_H
#define CODAL_SIMPLE_SERIAL_H

#include "Pin.h"

#define CODAL_SERIAL_DEFAULT_BAUD_RATE 115200


namespace codal
{
    /**
     * Class definition for an Simple serial interface.
     */
    class SimpleSerial
    {
        public:

        SimpleSerial(Pin& tx, Pin& rx, int baudRate = CODAL_SERIAL_DEFAULT_BAUD_RATE)
        {
        }

        virtual ~SimpleSerial()
        {
        }

        /**
          * Sends a single character over the serial line.
          *
          * @param c the character to send
          *
          * @return the number of bytes written, or CODAL_SERIAL_IN_USE if another fiber
          *         is using the serial instance for transmission.
          */
        virtual int sendChar(char c) = 0;

        /**
          * Reads a single character from the serial line
          *
          * @return a character, CODAL_SERIAL_IN_USE if another fiber is using the serial instance for reception,
          *         DEVICE_NO_RESOURCES if buffer allocation did not complete successfully.
          */
        virtual int read() = 0;

        /**
          * Determines whether there is any data waiting in the buffer.
          *
          * @return 1 if we have space, 0 if we do not.
          *
          */
        virtual int isReadable() = 0;

        /**
          * Determines if we have space in our writing buffer.
          *
          * @return 1 if we have space, 0 if we do not.
          *
          */
        virtual int isWriteable() = 0;

    };
}

#endif