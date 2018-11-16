#ifndef CODAL_STM32L4XX_TIMER_H
#define CODAL_STM32L4XX_TIMER_H

#include "codal-core/inc/types/Event.h"
#include "codal-core/inc/driver-models/Timer.h"
#include "CodalConfig.h"

namespace codal
{
class STM32L4xxTimer : public codal::Timer
{
    uint32_t prev;
public:
    TIM_HandleTypeDef TimHandle;
    
    STM32L4xxTimer();
    static STM32L4xxTimer *instance;
    void init();
    virtual void triggerIn(CODAL_TIMESTAMP t);
    virtual void syncRequest();
};
} // namespace codal

#endif