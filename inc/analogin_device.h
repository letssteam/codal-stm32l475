#ifndef ANALOGIN_API_H
#define ANALOGIN_API_H

#include "PinNumber.h"
#include "platform_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

struct analogin_s {
    ADC_HandleTypeDef handle;
    PinName pin;
    uint8_t channel;
};

/** Analogin hal structure. analogin_s is declared in the target's hal
 */
typedef struct analogin_s analogin_t;

/**
 * \defgroup hal_analogin Analogin hal functions
 * @{
 */

/** Initialize the analogin peripheral
 *
 * Configures the pin used by analogin.
 * @param obj The analogin object to initialize
 * @param pin The analogin pin name
 */
void analogin_init(analogin_t *obj, PinNumber pin);

/** Read the input voltage, represented as a float in the range [0.0, 1.0]
 *
 * @param obj The analogin object
 * @return A floating value representing the current input voltage
 */
float analogin_read(analogin_t *obj);

/** Read the value from analogin pin, represented as an unsigned 16bit value
 *
 * @param obj The analogin object
 * @return An unsigned 16bit value representing the current input voltage
 */
uint16_t analogin_read_u16(analogin_t *obj);


#ifdef __cplusplus
}
#endif

#endif
