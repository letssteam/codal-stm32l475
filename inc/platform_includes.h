#ifndef PLATFORM_INCLUDES
#define PLATFORM_INCLUDES

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#include "stm32.h"
#include "stm32l4xx_it.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_cortex.h"
#include "i2c.h"
#include "spi.h"

#define PROCESSOR_WORD_TYPE uint32_t

#ifdef __cplusplus
extern "C" {
#endif

void target_panic(int statusCode);
void wait_us(uint32_t us);

#ifdef __cplusplus
}
#endif
#endif
