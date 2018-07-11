#include "stm32l4xxSPI.h"

using namespace codal;

STM32L4xxSPI::~STM32L4xxSPI(){

}

/** Set the frequency of the SPI interface
 *
 * @param frequency The bus frequency in hertz
 */
int STM32L4xxSPI::setFrequency(uint32_t frequency){
    return 0;
}

/** Set the mode of the SPI interface
 *
 * @param mode Clock polarity and phase mode (0 - 3)
 * @param bits Number of bits per SPI frame (4 - 16)
 *
 * @code
 * mode | POL PHA
 * -----+--------
 *   0  |  0   0
 *   1  |  0   1
 *   2  |  1   0
 *   3  |  1   1
 * @endcode
 */
int STM32L4xxSPI::setMode(int mode, int bits){
    return 0;
}

/**
 * Writes the given byte to the SPI bus.
 *
 * The CPU will wait until the transmission is complete.
 *
 * @param data The data to write.
 * @return Response from the SPI slave or DEVICE_SPI_ERROR if the the write request failed.
 */
int STM32L4xxSPI::write(int data){
    return 0;
}

/**
 * Writes and reads from the SPI bus concurrently. Waits un-scheduled for transfer to finish.
 *
 * Either buffer can be NULL.
 */
int STM32L4xxSPI::transfer(const uint8_t *txBuffer, uint32_t txSize, uint8_t *rxBuffer, uint32_t rxSize){
    return 0;
}

int STM32L4xxSPI::startTransfer(const uint8_t *txBuffer, uint32_t txSize, uint8_t *rxBuffer, uint32_t rxSize, PVoidCallback doneHandler, void *arg){
    return 0;
}