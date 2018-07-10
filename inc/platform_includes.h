#ifndef PLATFORM_INCLUDES
#define PLATFORM_INCLUDES

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include "stm32.h"
#include "stm32l4xx_it.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_cortex.h"
#include "dfsdm.h"
#include "i2c.h"
#include "quadspi.h"
#include "spi.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

#define PROCESSOR_WORD_TYPE uint32_t

#ifdef __cplusplus
extern "C" {
#endif

void target_panic(int statusCode);
void wait_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#define CODAL_ASSERT(cond)                                                                         \
    if (!(cond))                                                                                   \
    target_panic(909)
#endif
