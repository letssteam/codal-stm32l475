#ifndef CODAL_STM32L4XX_SPI_H
#define CODAL_STM32L4XX_SPI_H

#include "CodalConfig.h"
#include "codal-core/inc/driver-models/SPI.h"
#include "Pin.h"

namespace codal
{
class STM32L4xxSPI;

struct SPI_HandleWithParent : public SPI_HandleTypeDef
{
    STM32L4xxSPI *spi_parent;
};

/**
 * Class definition for SPI service, derived from ARM mbed.
 */
class STM32L4xxSPI : public codal::SPI
{
protected:
    Pin& mosi; 
    Pin& miso; 
    Pin& sclk;
    
    uint32_t freq;

    SPI_HandleWithParent spi;

    PVoidCallback doneHandler;
    void *doneHandlerArg;

    bool needsInit;
    uint8_t rxCh, txCh;
    uint16_t transferCompleteEventCode;



public:
    void complete();
    void init();

    static void _complete(uint32_t instance);
    static void _irq(uint32_t instance);

    /**
     * Initialize SPI instance with given pins.
     *
     * Default setup is 1 MHz, 8 bit, mode 0.
     */
    STM32L4xxSPI(codal::Pin &mosi, codal::Pin &miso, codal::Pin &sclk);

    virtual ~STM32L4xxSPI();

    /** Set the frequency of the SPI interface
     *
     * @param frequency The bus frequency in hertz
     */
    virtual int setFrequency(uint32_t frequency);

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
    virtual int setMode(int mode, int bits = 8);

    /**
     * Writes the given byte to the SPI bus.
     *
     * The CPU will wait until the transmission is complete.
     *
     * @param data The data to write.
     * @return Response from the SPI slave or DEVICE_SPI_ERROR if the the write request failed.
     */
    virtual int write(int data);

    /**
     * Writes and reads from the SPI bus concurrently. Waits un-scheduled for transfer to finish.
     *
     * Either buffer can be NULL.
     */
    virtual int transfer(const uint8_t *txBuffer, uint32_t txSize, uint8_t *rxBuffer,
                         uint32_t rxSize);

    virtual int startTransfer(const uint8_t *txBuffer, uint32_t txSize, uint8_t *rxBuffer,
                              uint32_t rxSize, PVoidCallback doneHandler, void *arg);
};
} // namespace codal

#endif