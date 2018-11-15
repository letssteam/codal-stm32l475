#include "stm32l4xxI2C.h"
#include "pinmap.h"
#include "PeripheralPins.h"
using namespace codal;


#define I2C_TIMEOUT_TICK        100

void STM32L4xxI2C::init()
{
    if (!needsInit)
        return;
    needsInit = false;

    if (!i2c.Instance)
    {
        uint32_t inst = 0;
        inst = codal_setup_pin(sda, inst, PinMap_I2C_SDA);
        inst = codal_setup_pin(scl, inst, PinMap_I2C_SCL);

        i2c.Instance = (I2C_TypeDef *)inst;

        switch (inst)
        {
            case I2C1_BASE:
                __HAL_RCC_I2C1_CLK_ENABLE();
            break;
            case I2C2_BASE:
                __HAL_RCC_I2C2_CLK_ENABLE();
            break;
            case I2C3_BASE:
            __HAL_RCC_I2C3_CLK_ENABLE();
            break;
        }
    }

    int res = HAL_I2C_Init(&i2c);
    CODAL_ASSERT(res == HAL_OK);
}

typedef enum {
  I2C_10KHz =   0xF010F3FE,
  I2C_50KHz =   0x30608CFF,
  I2C_100KHz =  0x10D0A4E4,
  I2C_200KHz =  0x00F082FF,
  I2C_400KHz =  0x00F02E8B,
  I2C_600KHz =  0x00B01265,
  I2C_800KHz =  0x00B01243,
  I2C_1000KHz = 0x00B0122F
}i2c_timing_e;


STM32L4xxI2C::STM32L4xxI2C(Pin &sda, Pin &scl):I2C(sda, scl),
    i2c(),
    sda(sda),
    scl(scl), 
    needsInit(true)
{
    i2c.Init.Timing = 0x10909CEC;
    i2c.Init.OwnAddress1 = 0xFE;
    i2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    i2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2c.Init.OwnAddress2 = 0xFE;
    i2c.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    i2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
}


STM32L4xxI2C::~STM32L4xxI2C(){
}

/** Set the frequency of the I2C interface
 *
 * @param frequency The bus frequency in hertz
 */
int STM32L4xxI2C::setFrequency(uint32_t frequency){
  uint32_t f = I2C_10KHz;
  __HAL_I2C_DISABLE(&i2c);

  if(frequency <= 10000)
    f = I2C_10KHz;
  else if(frequency <= 50000)
    f = I2C_50KHz;
  else if(frequency <= 100000)
    f = I2C_100KHz;
  else if(frequency <= 200000)
    f = I2C_200KHz;
  else if(frequency <= 400000)
    f = I2C_400KHz;

  i2c.Init.Timing = f;
  HAL_I2C_Init(&i2c);
  __HAL_I2C_ENABLE(&i2c);
  return DEVICE_OK;
}

/**
* Issues a standard, I2C command write to the I2C bus.
* This consists of:
*  - Asserting a Start condition on the bus
*  - Selecting the Slave address (as an 8 bit address)
*  - Writing a number of raw data bytes provided
*  - Asserting a Stop condition on the bus
*
* The CPU will busy wait until the transmission is complete.
*
* @param address The 8bit I2C address of the device to write to
* @param data pointer to the bytes to write
* @param len the number of bytes to write
* @param repeated Suppresses the generation of a STOP condition if set. Default: false;
*
* @return DEVICE_OK on success, DEVICE_I2C_ERROR if the the write request failed.
*/
int STM32L4xxI2C::write(uint16_t address, uint8_t *data, int len, bool repeated){
    if (data == NULL || len <= 0)
        return DEVICE_INVALID_PARAMETER;

    CODAL_ASSERT(!repeated);

    init();

    int ret = DEVICE_I2C_ERROR;
    uint32_t tickstart = HAL_GetTick();
    uint32_t delta = 0;

    do{
        if(HAL_I2C_Master_Transmit_IT(&(i2c), address, data, len) == HAL_OK){
            ret = DEVICE_OK;
            // wait for transfer completion
            while((HAL_I2C_GetState(&(i2c)) != HAL_I2C_STATE_READY) && (ret == DEVICE_OK)){
                delta = (HAL_GetTick() - tickstart);
                if(delta > I2C_TIMEOUT_TICK) {
                    ret = DEVICE_I2C_ERROR;
                } else if(HAL_I2C_GetError(&(i2c)) != HAL_I2C_ERROR_NONE) {
                    ret = DEVICE_I2C_ERROR;
                }
            }
    }
    /* When Acknowledge failure occurs (Slave don't acknowledge it's address)
        Master restarts communication */
    }while(HAL_I2C_GetError(&(i2c)) == HAL_I2C_ERROR_AF && delta < I2C_TIMEOUT_TICK);

    return ret;
}

/**
 * Issues a standard, 2 byte I2C command read to the I2C bus.
 * This consists of:
 *  - Asserting a Start condition on the bus
 *  - Selecting the Slave address (as an 8 bit address)
 *  - reading "len" bytes of raw 8 bit data into the buffer provided
 *  - Asserting a Stop condition on the bus
 *
 * The CPU will busy wait until the transmission is complete.
 *
 * @param address The 8bit I2C address of the device to read from
 * @param data pointer to store the the bytes read
 * @param len the number of bytes to read into the buffer
 * @param repeated Suppresses the generation of a STOP condition if set. Default: false;
 *
 * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the the read request failed.
 */
int STM32L4xxI2C::read(uint16_t address, uint8_t *data, int len, bool repeated)
{
    if (data == NULL || len <= 0)
        return DEVICE_INVALID_PARAMETER;
    CODAL_ASSERT(!repeated);

    init();

    int ret = DEVICE_I2C_ERROR;
    uint32_t tickstart = HAL_GetTick();
    uint32_t delta = 0;

    do{
        if(HAL_I2C_Master_Receive_IT(&(i2c), address, data, len) == HAL_OK) {
            ret = DEVICE_OK;
            // wait for transfer completion
            while((HAL_I2C_GetState(&(i2c)) != HAL_I2C_STATE_READY) && (ret == DEVICE_OK)){
                delta = (HAL_GetTick() - tickstart);
                if( delta > I2C_TIMEOUT_TICK) {
                    ret = DEVICE_I2C_ERROR;
                } else if(HAL_I2C_GetError(&(i2c)) != HAL_I2C_ERROR_NONE) {
                    ret = DEVICE_I2C_ERROR;
                }
            }
        }
        /* When Acknowledge failure occurs (Slave don't acknowledge it's address)
            Master restarts communication */
    }while(HAL_I2C_GetError(&(i2c)) == HAL_I2C_ERROR_AF && delta < I2C_TIMEOUT_TICK);

return ret;
}

/**
 * Performs a typical register read operation to the I2C slave device provided.
 * This consists of:
 *  - Asserting a Start condition on the bus
 *  - Selecting the Slave address (as an 8 bit address, I2C WRITE)
 *  - Selecting a RAM register address in the slave
 *  - Asserting a Stop condition on the bus
 *  - Asserting a Start condition on the bus
 *  - Selecting the Slave address (as an 8 bit address, I2C READ)
 *  - Performing an 8 bit read operation (of the requested register)
 *  - Asserting a Stop condition on the bus
 *
 * The CPU will busy wait until the transmission is complete..
 *
 * @param address 8bit I2C address of the device to read from
 * @param reg The 8bit register address of the to read.
 * @param data A pointer to a memory location to store the result of the read operation
 * @param length The number of mytes to read
 * @param repeated Use a repeated START/START/STOP transaction if true, or independent START/STOP/START/STOP transactions if fasle. Default: true
 *
 * @return DEVICE_OK or DEVICE_I2C_ERROR if the the read request failed.
 */
int STM32L4xxI2C::readRegister(uint16_t address, uint8_t reg, uint8_t *data, int length, bool repeated){
    
    if (data == NULL || length <= 0)
        return DEVICE_INVALID_PARAMETER;

    CODAL_ASSERT(!repeated);CODAL_ASSERT(!repeated);

    init();

    auto res = HAL_I2C_Mem_Read(&i2c, address, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY);

    if (res == HAL_OK)
        return DEVICE_OK;
    else
        return DEVICE_I2C_ERROR;
}