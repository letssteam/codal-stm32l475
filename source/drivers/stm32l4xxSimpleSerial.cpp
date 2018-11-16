#include "stm32l4xxSimpleSerial.h"

using namespace codal;

//
// Default system wide serial port used by printf function, if created.
//
SimpleSerial* codal::default_serial_debug = nullptr;

namespace{
  USART_TypeDef* COM_USART[COMn] = {DISCOVERY_COM1};
  GPIO_TypeDef* COM_TX_PORT[COMn] = {DISCOVERY_COM1_TX_GPIO_PORT};
  GPIO_TypeDef* COM_RX_PORT[COMn] = {DISCOVERY_COM1_RX_GPIO_PORT};
  const uint16_t COM_TX_PIN[COMn] = {DISCOVERY_COM1_TX_PIN};
  const uint16_t COM_RX_PIN[COMn] = {DISCOVERY_COM1_RX_PIN};
  const uint16_t COM_TX_AF[COMn] = {DISCOVERY_COM1_TX_AF};
  const uint16_t COM_RX_AF[COMn] = {DISCOVERY_COM1_RX_AF};
}
/**
  * @brief  Configures COM port.
  * @param  COM: COM port to be configured.
  *          This parameter can be one of the following values:
  *            @arg  COM1 
  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains the
  *                configuration information for the specified USART peripheral.
  */
void COM_Init(COM_TypeDef COM, UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef gpio_init_structure;

  /* Enable GPIO clock */
  DISCOVERY_COMx_TX_GPIO_CLK_ENABLE(COM);
  DISCOVERY_COMx_RX_GPIO_CLK_ENABLE(COM);

  /* Enable USART clock */
  DISCOVERY_COMx_CLK_ENABLE(COM);

  /* Configure USART Tx as alternate function */
  gpio_init_structure.Pin = COM_TX_PIN[(uint8_t)COM];
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Alternate = COM_TX_AF[(uint8_t)COM];
  HAL_GPIO_Init(COM_TX_PORT[(uint8_t)COM], &gpio_init_structure);

  /* Configure USART Rx as alternate function */
  gpio_init_structure.Pin = COM_RX_PIN[(uint8_t)COM];
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Alternate = COM_RX_AF[(uint8_t)COM];
  HAL_GPIO_Init(COM_RX_PORT[(uint8_t)COM], &gpio_init_structure);

  /* USART configuration */
  huart->Instance = COM_USART[(uint8_t)COM];
  HAL_UART_Init(huart);
}

/**
  * @brief  DeInit COM port.
  * @param  COM: COM port to be configured.
  *          This parameter can be one of the following values:
  *            @arg  COM1 
  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains the
  *                configuration information for the specified USART peripheral.
  */
void COM_DeInit(COM_TypeDef COM, UART_HandleTypeDef *huart)
{
  /* USART configuration */
  huart->Instance = COM_USART[(uint8_t)COM];
  HAL_UART_DeInit(huart);

  /* Enable USART clock */
  DISCOVERY_COMx_CLK_DISABLE(COM);
}

void STM32L4xxSimpleSerial::init(){
    COM_Init(COM1, &hDiscoUart);
}

void STM32L4xxSimpleSerial::deInit(){
    COM_DeInit(COM1, &hDiscoUart);
}

/**
 * Sends a single character over the serial line.
 *
 * @param c the character to send
 *
 * @return the number of bytes written, or CODAL_SERIAL_IN_USE if another fiber
 *         is using the serial instance for transmission.
 */
int STM32L4xxSimpleSerial::sendChar(char c){
  /* write a character to the serial port and Loop until the end of transmission */
  while (HAL_OK != HAL_UART_Transmit(&hDiscoUart, (uint8_t *) &c, 1, 30000))
  {
    ;
  }
  return 1;
}

/**
 * Reads a single character from the serial line
 *
 * @return a character, CODAL_SERIAL_IN_USE if another fiber is using the serial instance for reception,
 *         DEVICE_NO_RESOURCES if buffer allocation did not complete successfully.
 */
int STM32L4xxSimpleSerial::read(){
/* read a character to the USART and Loop until the end of transmission */
  uint8_t ch = 0;
  while (HAL_OK != HAL_UART_Receive(&hDiscoUart, (uint8_t *)&ch, 1, 30000))
  {
    ;
  }
  return ch;
}

/**
 * Determines whether there is any data waiting in the buffer.
 *
 * @return 1 if we have space, 0 if we do not.
 *
 */
int STM32L4xxSimpleSerial::isReadable(){
    return hDiscoUart.RxState == HAL_UART_STATE_READY;
}

/**
 * Determines if we have space in our writing buffer.
 *
 * @return 1 if we have space, 0 if we do not.
 *
 */
int STM32L4xxSimpleSerial::isWriteable(){
    return (hDiscoUart.gState != HAL_UART_STATE_BUSY_TX) && (hDiscoUart.gState != HAL_UART_STATE_BUSY_TX_RX);
}

#ifdef __GNUC__
/* With GCC/RAISONANCE, small msg_info (option LD Linker->Libraries->Small msg_info
   set to 'Yes') calls __io_putchar() */

#if !defined(PUTCHAR_PROTOTYPE)
#define PUTCHAR_PROTOTYPE WEAK int __io_putchar(int ch)
/**
  * @brief Retargets the C library msg_info function to the USART.
  * @param None
  * @retval None
  */
extern "C" PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the serial port and Loop until the end of transmission */
  if(default_serial_debug != nullptr){
    return default_serial_debug->sendChar(ch);
  }
  return 0;
}
#endif

#if !defined(GETCHAR_PROTOTYPE)
#define GETCHAR_PROTOTYPE WEAK int __io_getchar(void)
/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval None
  */
extern "C" GETCHAR_PROTOTYPE
{
  /* Place your implementation of fgetc here */
  /* e.g. readwrite a character to the USART2 and Loop until the end of transmission */
  uint8_t ch = 0;
  if(default_serial_debug != nullptr){
    ch = default_serial_debug->read();
  }
  return ch;
}
#endif
#endif /* __GNUC__ */


