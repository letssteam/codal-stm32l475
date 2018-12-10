#include "stm32l4xxI2C.h"
#include "i2c.h"
#include "pinmap.h"
#include "PeripheralPins.h"

#define DMESG(x)  printf("%s\n",x)
#define DMESGF  printf

using namespace codal;

#define I2C_TIME_OUT_BASE   10
#define I2C_TIME_OUT_BYTE   1

I2C_HandleTypeDef* codal::default_i2c_sensors_bus = nullptr;

#define I2C_TIMEOUT_TICK        100

void STM32L4xxI2C::init()
{
    DMESG("STM32L4xxI2C::init()");
    DMESGF("I2C%d Initialisation\n", i2c.Instance == I2C2 ? 2 : i2c.Instance == I2C1 ? 1 : 0 );

    if (!needsInit)
        return;
    needsInit = false;

    if (!i2c.Instance)
    {
        uint32_t inst = 0;
        inst = codal_setup_pin(sda, inst, PinMap_I2C_SDA);
        inst = codal_setup_pin(scl, inst, PinMap_I2C_SCL);
        i2c.Instance = (I2C_TypeDef *)inst;
    }

    I2Cx_Init(&i2c);
    DMESGF("I2C%d Initialized !\n", i2c.Instance == I2C2 ? 2 : i2c.Instance == I2C1 ? 1 : 0);
}

STM32L4xxI2C::STM32L4xxI2C(STM32L4xxPin &sda, STM32L4xxPin &scl):I2C(sda, scl),
    i2c(),
    sda(sda),
    scl(scl), 
    needsInit(true)
{
    IC2x_Init_Handler(&i2c);
}


STM32L4xxI2C::~STM32L4xxI2C(){
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

    auto res = HAL_I2C_Master_Transmit(&i2c, address, data, len, HAL_MAX_DELAY);
    if (res == HAL_OK)
        return DEVICE_OK;
    
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

    auto res = HAL_I2C_Master_Receive(&i2c, address, data, len, HAL_MAX_DELAY);

    if (res == HAL_OK)
        return DEVICE_OK;

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

    CODAL_ASSERT(!repeated);

    init();

    auto ret = I2Cx_ReadMultiple(&i2c, address, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, data, length);
    return ret == HAL_OK ? DEVICE_OK : DEVICE_I2C_ERROR;
}

/**
  * Performs a typical register write operation to the I2C slave device provided.
  * This consists of:
  *  - Asserting a Start condition on the bus
  *  - Selecting the Slave address (as an 8 bit address)
  *  - Writing the 8 bit register address provided
  *  - Writing the 8 bit value provided
  *  - Asserting a Stop condition on the bus
  *
  * The CPU will busy wait until the transmission is complete..
  *
  * @param address 8bit address of the device to write to
  * @param reg The 8bit address of the register to write to.
  * @param value The value to write.
  *
  * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the the write request failed.
  */
int STM32L4xxI2C::writeRegister(uint16_t address, uint8_t reg, uint8_t value){
    init();

    int ret = I2Cx_WriteMultiple(&i2c, address, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT,(uint8_t*)&value, 1);
    return ret == HAL_OK ? DEVICE_OK : DEVICE_I2C_ERROR;
}

 /**
  * Performs a typical register write operation to the I2C slave device provided.
  * This consists of:
  *  - Asserting a Start condition on the bus
  *  - Selecting the Slave address (as an 8 bit address)
  *  - Writing the 8 bit register address provided
  *  - Writing the 8 bit value provided
  *  - Asserting a Stop condition on the bus
  *
  * The CPU will busy wait until the transmission is complete..
  *
  * @param address 8bit address of the device to write to
  * @param reg The 8bit address of the register to write to.
  * @param data A pointer to a memory location of data to be write on bus
  * @param length The number of mytes to read
  *
  * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the the write request failed.
  */
int STM32L4xxI2C::writeRegister(uint16_t address, uint8_t reg, uint8_t *data, int length){
    if (data == NULL || length <= 0)
        return DEVICE_INVALID_PARAMETER;

    init();

    int ret = I2Cx_WriteMultiple(&i2c, address, reg, I2C_MEMADD_SIZE_8BIT, data, length);
    return ret == HAL_OK ? DEVICE_OK : DEVICE_I2C_ERROR;
}

extern "C"{
    void SENSOR_IO_Init(void){
        if(default_i2c_sensors_bus == nullptr){
            default_i2c_sensors_bus = new I2C_HandleTypeDef;
            IC2x_Init_Handler(default_i2c_sensors_bus);
            DMESG("SENSOR_IO_Init()");
            DMESGF("I2C%d Initialisation\n", default_i2c_sensors_bus->Instance == I2C2 ? 2 : default_i2c_sensors_bus->Instance == I2C1 ? 1 : 0 );

            default_i2c_sensors_bus->Instance = I2C2;

            I2Cx_Init(default_i2c_sensors_bus);
            DMESGF("I2C%d Initialized !\n", default_i2c_sensors_bus->Instance == I2C2 ? 2 : default_i2c_sensors_bus->Instance == I2C1 ? 1 : 0 );
        }
    }

    void SENSOR_IO_DeInit(void){
        if(default_i2c_sensors_bus != nullptr){
            I2Cx_DeInit(default_i2c_sensors_bus);
            delete default_i2c_sensors_bus;
        }
    }

    uint16_t SENSOR_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value){
        return I2Cx_WriteMultiple(default_i2c_sensors_bus, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT,(uint8_t*)&Value, 1);
    }

    uint8_t  SENSOR_IO_Read(uint8_t Addr, uint8_t Reg){
      uint8_t read_value = 0;
      I2Cx_ReadMultiple(default_i2c_sensors_bus, Addr, Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&read_value, 1);
      return read_value;
    }

    uint16_t SENSOR_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length){
        SENSOR_IO_Init();
        //printf("SENSOR_IO_ReadMultiple(%x, %x, %lx, %d)\n", Addr, Reg, (uint32_t)Buffer, Length);
        return I2Cx_ReadMultiple(default_i2c_sensors_bus, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
    }
    uint16_t SENSOR_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length){
        SENSOR_IO_Init();
        //printf("SENSOR_IO_WriteMultiple(%x, %x, %lx, %d)\n", Addr, Reg, (uint32_t)Buffer, Length);
        return I2Cx_WriteMultiple(default_i2c_sensors_bus, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
    }

    HAL_StatusTypeDef SENSOR_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials){
        SENSOR_IO_Init();
        return I2Cx_IsDeviceReady(default_i2c_sensors_bus, DevAddress, Trials);
    }

    void SENSOR_IO_Delay(uint32_t Delay){
        HAL_Delay(Delay);
    }

    uint32_t SENSOR_IO_Error(){
        SENSOR_IO_Init();
        return default_i2c_sensors_bus->ErrorCode;
    }
}
