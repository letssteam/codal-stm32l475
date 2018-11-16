#ifndef CODAL_STM32L4XX_SIMPLE_SERIAL_H
#define CODAL_STM32L4XX_SIMPLE_SERIAL_H

#include "CodalConfig.h"
#include "SimpleSerial.h"

namespace codal {
    class STM32L4xxSimpleSerial : public SimpleSerial
    {
        Pin& tx;
        Pin& rx;
        int baudRate;

        UART_HandleTypeDef hDiscoUart;

        public:
        STM32L4xxSimpleSerial(Pin& tx, Pin& rx, int baudRate = CODAL_SERIAL_DEFAULT_BAUD_RATE)
            :SimpleSerial(tx, rx, baudRate), 
            tx(tx), 
            rx(rx), 
            baudRate(baudRate)
        {
            memset(&hDiscoUart, 0, sizeof(hDiscoUart));
            hDiscoUart.Instance = DISCOVERY_COM1; 
            hDiscoUart.Init.BaudRate = baudRate;
            hDiscoUart.Init.WordLength = UART_WORDLENGTH_8B;
            hDiscoUart.Init.StopBits = UART_STOPBITS_1;
            hDiscoUart.Init.Parity = UART_PARITY_NONE;
            hDiscoUart.Init.Mode = UART_MODE_TX_RX;
            hDiscoUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
            hDiscoUart.Init.OverSampling = UART_OVERSAMPLING_16;
            hDiscoUart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
            hDiscoUart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
        }

        virtual ~STM32L4xxSimpleSerial(){
            deInit();
        }

        void init();

        void deInit();

        /**
          * Sends a single character over the serial line.
          *
          * @param c the character to send
          *
          * @return the number of bytes written, or CODAL_SERIAL_IN_USE if another fiber
          *         is using the serial instance for transmission.
          */
        virtual int sendChar(char c);

        /**
          * Reads a single character from the serial line
          *
          * @return a character, CODAL_SERIAL_IN_USE if another fiber is using the serial instance for reception,
          *         DEVICE_NO_RESOURCES if buffer allocation did not complete successfully.
          */
        virtual int read();

        /**
          * Determines whether there is any data waiting in the buffer.
          *
          * @return 1 if we have space, 0 if we do not.
          *
          */
        virtual int isReadable();

        /**
          * Determines if we have space in our writing buffer.
          *
          * @return 1 if we have space, 0 if we do not.
          *
          */
        virtual int isWriteable();
    };

    extern SimpleSerial* default_serial_debug;
}


#endif