

/**
 * Class definition for STM32L4xxPin.
 *
 * Commonly represents an I/O pin on the edge connector.
 */
#include "stm32l4xxPin.h"
#include "Timer.h"
#include "codal_target_hal.h"
#include "codal-core/inc/types/Event.h"
#include "pwmout_api.h"
#include "pinmap.h"

#define IO_STATUS_CAN_READ                                                                         \
    (IO_STATUS_DIGITAL_IN | IO_STATUS_EVENT_ON_EDGE | IO_STATUS_EVENT_PULSE_ON_EDGE)

#define PORTPINS 16
#define PINMASK (PORTPINS - 1)

#define GPIO_PORT() ((GPIO_TypeDef *)(GPIOA_BASE + 0x400 * ((int)name >> 4)))
#define GPIO_PIN() (1 << ((uint32_t)name & 0xf))

namespace codal
{

static STM32L4xxPin *eventPin[16];

struct STM32L4xxEventConfig
{
    CODAL_TIMESTAMP prevPulse;
};

inline int map(codal::PullMode pinMode)
{
    switch (pinMode)
    {
    case PullMode::Up:
        return GPIO_PULLUP;
    case PullMode::Down:
        return GPIO_PULLDOWN;
    case PullMode::None:
        return GPIO_NOPULL;
    }

    return GPIO_NOPULL;
}

/**
 * Constructor.
 * Create a STM32L4xxPin instance, generally used to represent a pin on the edge connector.
 *
 * @param id the unique EventModel id of this component.
 *
 * @param name the mbed PinNumber for this STM32L4xxPin instance.
 *
 * @param capability the capabilities this STM32L4xxPin instance should have.
 *                   (PIN_CAPABILITY_DIGITAL, PIN_CAPABILITY_ANALOG, PIN_CAPABILITY_AD,
 * PIN_CAPABILITY_ALL)
 *
 * @code
 * STM32L4xxPin P0(DEVICE_ID_IO_P0, DEVICE_PIN_P0, PIN_CAPABILITY_ALL);
 * @endcode
 */
STM32L4xxPin::STM32L4xxPin(int id, PinNumber name, PinCapability capability) : codal::Pin(id, name, capability)
{
    this->pullMode = DEVICE_DEFAULT_PULLMODE;

    // Power up in a disconnected, low power state.
    // If we're unused, this is how it will stay...
    this->status = 0x00;

    this->pwmCfg = NULL;
}

void STM32L4xxPin::disconnect()
{
    if (this->status & IO_STATUS_ANALOG_OUT)
    {
        if (this->pwmCfg)
            delete this->pwmCfg;
        this->pwmCfg = NULL;
    }

    if (this->status & (IO_STATUS_EVENT_ON_EDGE | IO_STATUS_EVENT_PULSE_ON_EDGE))
    {
        EXTI->IMR1 &= ~GPIO_PIN();
        if (this->evCfg)
            delete this->evCfg;
        this->evCfg = NULL;
    }

    if (this->status & IO_STATUS_TOUCH_IN)
    {
        if (this->btn)
            delete this->btn;
        this->btn = NULL;
    }

    status = 0;
}

// void STM32L4xxPin::config(int status)
// {
//     disconnect();

//     int mode = STM_PIN_INPUT;
//     int pull = GPIO_NOPULL;

//     if (status & IO_STATUS_DIGITAL_OUT)
//         mode = STM_PIN_OUTPUT;
//     else if (this->status & IO_STATUS_ANALOG_IN)
//         mode = STM_PIN_ANALOG;

//     if (status & IO_STATUS_CAN_READ)
//         pull = map(this->pullMode);

//     pin_function(name, STM_PIN_DATA(mode, pull, 0));
// }

/**
 * Configures this IO pin as a digital output (if necessary) and sets the pin to 'value'.
 *
 * @param value 0 (LO) or 1 (HI)
 *
 * @return DEVICE_OK on success, DEVICE_INVALID_PARAMETER if value is out of range, or
 * DEVICE_NOT_SUPPORTED if the given pin does not have digital capability.
 *
 * @code
 * STM32L4xxPin P0(DEVICE_ID_IO_P0, DEVICE_PIN_P0, PIN_CAPABILITY_BOTH);
 * P0.setDigitalValue(1); // P0 is now HI
 * @endcode
 */
int STM32L4xxPin::setDigitalValue(int value)
{
    // Ensure we have a valid value.
    if (value < 0 || value > 1)
        return DEVICE_INVALID_PARAMETER;

    // Move into a Digital input state if necessary.
    if (!(status & IO_STATUS_DIGITAL_OUT))
    {
        disconnect();
        pin_function(name, STM_PIN_DATA(STM_PIN_OUTPUT, GPIO_NOPULL, 0));
        status |= IO_STATUS_DIGITAL_OUT;
    }

    HAL_GPIO_WritePin(GPIO_PORT(), GPIO_PIN(), (GPIO_PinState)value);

    return DEVICE_OK;
}

/**
 * Configures this IO pin as a digital input (if necessary) and tests its current value.
 *
 *
 * @return 1 if this input is high, 0 if input is LO, or DEVICE_NOT_SUPPORTED
 *         if the given pin does not have digital capability.
 *
 * @code
 * STM32L4xxPin P0(DEVICE_ID_IO_P0, DEVICE_PIN_P0, PIN_CAPABILITY_BOTH);
 * P0.getDigitalValue(); // P0 is either 0 or 1;
 * @endcode
 */
int STM32L4xxPin::getDigitalValue()
{
    // Move into a Digital input state if necessary.
    if (!(status & (IO_STATUS_DIGITAL_IN | IO_STATUS_EVENT_ON_EDGE | IO_STATUS_EVENT_PULSE_ON_EDGE)))
    {
        disconnect();
        pin_function(name, STM_PIN_DATA(STM_PIN_INPUT, map(this->pullMode), 0));
        status |= IO_STATUS_DIGITAL_IN;
    }

    return HAL_GPIO_ReadPin(GPIO_PORT(), GPIO_PIN());
}

/**
 * Configures this IO pin as a digital input with the specified internal pull-up/pull-down
 * configuraiton (if necessary) and tests its current value.
 *
 * @param pull one of the mbed pull configurations: PullUp, PullDown, PullNone
 *
 * @return 1 if this input is high, 0 if input is LO, or DEVICE_NOT_SUPPORTED
 *         if the given pin does not have digital capability.
 *
 * @code
 * STM32L4xxPin P0(DEVICE_ID_IO_P0, DEVICE_PIN_P0, PIN_CAPABILITY_BOTH);
 * P0.getDigitalValue(PullUp); // P0 is either 0 or 1;
 * @endcode
 */
int STM32L4xxPin::getDigitalValue(PullMode pull)
{
    setPull(pull);
    return getDigitalValue();
}

int STM32L4xxPin::obtainAnalogChannel()
{
    // Move into an analogue output state if necessary
    if (!(status & IO_STATUS_ANALOG_OUT))
    {
        disconnect();
        pin_function(name, STM_PIN_DATA(STM_PIN_OUTPUT, map(this->pullMode), 0));
        auto cfg = this->pwmCfg = new pwmout_t;
        pwmout_init(cfg, name);
        status = IO_STATUS_ANALOG_OUT;
    }

    return DEVICE_OK;
}

int STM32L4xxPin::setPWM(uint32_t value, uint32_t period)
{
    // sanitise the level value
    if (value > period)
        value = period;

    if (obtainAnalogChannel())
        return DEVICE_INVALID_PARAMETER;

    auto cfg = this->pwmCfg;

    if (cfg->period != period)
        pwmout_period_us(cfg, period);
    pwmout_write(cfg, value);

    return DEVICE_OK;
}

/**
 * Configures this IO pin as an analog/pwm output, and change the output value to the given level.
 *
 * @param value the level to set on the output pin, in the range 0 - 1024
 *
 * @return DEVICE_OK on success, DEVICE_INVALID_PARAMETER if value is out of range, or
 * DEVICE_NOT_SUPPORTED if the given pin does not have analog capability.
 */
int STM32L4xxPin::setAnalogValue(int value)
{
    // sanitise the level value
    if (value < 0 || value > DEVICE_PIN_MAX_OUTPUT)
        return DEVICE_INVALID_PARAMETER;

    uint32_t period = 20000;
    if (status & IO_STATUS_ANALOG_OUT)
        period = this->pwmCfg->period;

    return setPWM((uint64_t)value * period / DEVICE_PIN_MAX_OUTPUT, period);
}

/**
 * Configures this IO pin as an analog/pwm output (if necessary) and configures the period to be
 * 20ms, with a duty cycle between 500 us and 2500 us.
 *
 * A value of 180 sets the duty cycle to be 2500us, and a value of 0 sets the duty cycle to be 500us
 * by default.
 *
 * This range can be modified to fine tune, and also tolerate different servos.
 *
 * @param value the level to set on the output pin, in the range 0 - 180.
 *
 * @param range which gives the span of possible values the i.e. the lower and upper bounds (center
 * +/- range/2). Defaults to DEVICE_PIN_DEFAULT_SERVO_RANGE.
 *
 * @param center the center point from which to calculate the lower and upper bounds. Defaults to
 * DEVICE_PIN_DEFAULT_SERVO_CENTER
 *
 * @return DEVICE_OK on success, DEVICE_INVALID_PARAMETER if value is out of range, or
 * DEVICE_NOT_SUPPORTED if the given pin does not have analog capability.
 */
int STM32L4xxPin::setServoValue(int value, int range, int center)
{
    // check if this pin has an analogue mode...
    if (!(PIN_CAPABILITY_ANALOG & capability))
        return DEVICE_NOT_SUPPORTED;

    // sanitise the servo level
    if (value < 0 || range < 1 || center < 1)
        return DEVICE_INVALID_PARAMETER;

    // clip - just in case
    if (value > DEVICE_PIN_MAX_SERVO_RANGE)
        value = DEVICE_PIN_MAX_SERVO_RANGE;

    // calculate the lower bound based on the midpoint
    int lower = (center - (range / 2)) * 1000;

    value = value * 1000;

    // add the percentage of the range based on the value between 0 and 180
    int scaled = lower + (range * (value / DEVICE_PIN_MAX_SERVO_RANGE));

    return setServoPulseUs(scaled / 1000);
}

/**
 * Configures this IO pin as an analogue input (if necessary), and samples the STM32L4xxPin for its analog
 * value.
 *
 * @return the current analogue level on the pin, in the range 0 - 1024, or
 *         DEVICE_NOT_SUPPORTED if the given pin does not have analog capability.
 *
 * @code
 * STM32L4xxPin P0(DEVICE_ID_IO_P0, DEVICE_PIN_P0, PIN_CAPABILITY_BOTH);
 * P0.getAnalogValue(); // P0 is a value in the range of 0 - 1024
 * @endcode
 */
int STM32L4xxPin::getAnalogValue()
{
    // check if this pin has an analogue mode...
    //    if (!(PIN_CAPABILITY_ANALOG & capability))
    return DEVICE_NOT_SUPPORTED;
}

/**
 * Determines if this IO pin is currently configured as an input.
 *
 * @return 1 if pin is an analog or digital input, 0 otherwise.
 */
int STM32L4xxPin::isInput()
{
    return (status & (IO_STATUS_DIGITAL_IN | IO_STATUS_ANALOG_IN)) == 0 ? 0 : 1;
}

/**
 * Determines if this IO pin is currently configured as an output.
 *
 * @return 1 if pin is an analog or digital output, 0 otherwise.
 */
int STM32L4xxPin::isOutput()
{
    return (status & (IO_STATUS_DIGITAL_OUT | IO_STATUS_ANALOG_OUT)) == 0 ? 0 : 1;
}

/**
 * Determines if this IO pin is currently configured for digital use.
 *
 * @return 1 if pin is digital, 0 otherwise.
 */
int STM32L4xxPin::isDigital()
{
    return (status & (IO_STATUS_DIGITAL_IN | IO_STATUS_DIGITAL_OUT)) == 0 ? 0 : 1;
}

/**
 * Determines if this IO pin is currently configured for analog use.
 *
 * @return 1 if pin is analog, 0 otherwise.
 */
int STM32L4xxPin::isAnalog()
{
    return (status & (IO_STATUS_ANALOG_IN | IO_STATUS_ANALOG_OUT)) == 0 ? 0 : 1;
}

/**
 * Configures this IO pin as a "makey makey" style touch sensor (if necessary)
 * and tests its current debounced state.
 *
 * Users can also subscribe to Button events generated from this pin.
 *
 * @return 1 if pin is touched, 0 if not, or DEVICE_NOT_SUPPORTED if this pin does not support touch
 * capability.
 *
 * @code
 * DeviceMessageBus bus;
 *
 * STM32L4xxPin P0(DEVICE_ID_IO_P0, DEVICE_PIN_P0, PIN_CAPABILITY_ALL);
 * if(P0.isTouched())
 * {
 *     //do something!
 * }
 *
 * // subscribe to events generated by this pin!
 * bus.listen(DEVICE_ID_IO_P0, DEVICE_BUTTON_EVT_CLICK, someFunction);
 * @endcode
 */
int STM32L4xxPin::isTouched()
{
    // check if this pin has a touch mode...
    if (!(PIN_CAPABILITY_DIGITAL & capability))
        return DEVICE_NOT_SUPPORTED;

    // Move into a touch input state if necessary.
    if (!(status & IO_STATUS_TOUCH_IN))
    {
        disconnect();
        this->btn = new Button(*this, id);
        status |= IO_STATUS_TOUCH_IN;
    }

    return this->btn->isPressed();
}

/**
 * Configures this IO pin as an analog/pwm output if it isn't already, configures the period to be
 * 20ms, and sets the pulse width, based on the value it is given.
 *
 * @param pulseWidth the desired pulse width in microseconds.
 *
 * @return DEVICE_OK on success, DEVICE_INVALID_PARAMETER if value is out of range, or
 * DEVICE_NOT_SUPPORTED if the given pin does not have analog capability.
 */
int STM32L4xxPin::setServoPulseUs(int pulseWidth)
{
    // check if this pin has an analogue mode...
    if (!(PIN_CAPABILITY_ANALOG & capability))
        return DEVICE_NOT_SUPPORTED;

    // sanitise the pulse width
    if (pulseWidth < 0)
        return DEVICE_INVALID_PARAMETER;

    return setPWM(pulseWidth, DEVICE_DEFAULT_PWM_PERIOD);
}

/**
 * Configures the PWM period of the analog output to the given value.
 *
 * @param period The new period for the analog output in microseconds.
 *
 * @return DEVICE_OK on success.
 */
int STM32L4xxPin::setAnalogPeriodUs(int period)
{
    if (status & IO_STATUS_ANALOG_OUT)
        // keep the % of duty cycle
        return setPWM((uint64_t)this->pwmCfg->pulse * period / this->pwmCfg->period, period);
    else
        return setPWM(0, period);
}

/**
 * Configures the PWM period of the analog output to the given value.
 *
 * @param period The new period for the analog output in milliseconds.
 *
 * @return DEVICE_OK on success, or DEVICE_NOT_SUPPORTED if the
 *         given pin is not configured as an analog output.
 */
int STM32L4xxPin::setAnalogPeriod(int period)
{
    return setAnalogPeriodUs(period * 1000);
}

/**
 * Obtains the PWM period of the analog output in microseconds.
 *
 * @return the period on success, or DEVICE_NOT_SUPPORTED if the
 *         given pin is not configured as an analog output.
 */
uint32_t STM32L4xxPin::getAnalogPeriodUs()
{
    if (!(status & IO_STATUS_ANALOG_OUT))
        return DEVICE_NOT_SUPPORTED;

    return this->pwmCfg->period;
}

/**
 * Obtains the PWM period of the analog output in milliseconds.
 *
 * @return the period on success, or DEVICE_NOT_SUPPORTED if the
 *         given pin is not configured as an analog output.
 */
int STM32L4xxPin::getAnalogPeriod()
{
    return getAnalogPeriodUs() / 1000;
}

/**
 * Configures the pull of this pin.
 *
 * @param pull one of the mbed pull configurations: PullUp, PullDown, PullNone
 *
 * @return DEVICE_NOT_SUPPORTED if the current pin configuration is anything other
 *         than a digital input, otherwise DEVICE_OK.
 */
int STM32L4xxPin::setPull(PullMode pull)
{
    if (pullMode == pull)
        return DEVICE_OK;

    pullMode = pull;

    // have to disconnect to flush the change to the hardware
    disconnect();
    getDigitalValue();

    return DEVICE_OK;
}

/**
 * This member function manages the calculation of the timestamp of a pulse detected
 * on a pin whilst in IO_STATUS_EVENT_PULSE_ON_EDGE or IO_STATUS_EVENT_ON_EDGE modes.
 *
 * @param eventValue the event value to distribute onto the message bus.
 */
void STM32L4xxPin::pulseWidthEvent(int eventValue)
{
    Event evt(id, eventValue, CREATE_ONLY);
    auto now = evt.timestamp;
    auto previous = this->evCfg->prevPulse;

    if (previous != 0)
    {
        evt.timestamp -= previous;
        evt.fire();
    }

    this->evCfg->prevPulse = now;
}

void STM32L4xxPin::eventCallback()
{
    bool isRise = HAL_GPIO_ReadPin(GPIO_PORT(), GPIO_PIN());

    if (status & IO_STATUS_EVENT_PULSE_ON_EDGE)
        pulseWidthEvent(isRise ? DEVICE_PIN_EVT_PULSE_LO : DEVICE_PIN_EVT_PULSE_HI);

    if (status & IO_STATUS_EVENT_ON_EDGE)
        Event(id, isRise ? DEVICE_PIN_EVT_RISE : DEVICE_PIN_EVT_FALL);
}

static void irq_handler()
{
    int pr = EXTI->PR1;
    EXTI->PR1 = pr; // clear all pending bits

    for (int i = 0; i < 16; ++i)
    {
        if ((pr & (1 << i)) && eventPin[i])
            eventPin[i]->eventCallback();
    }
}

#define DEF(nm)                                                                                    \
    extern "C" void nm() { irq_handler(); }

DEF(EXTI0_IRQHandler)
DEF(EXTI1_IRQHandler)
DEF(EXTI2_IRQHandler)
DEF(EXTI3_IRQHandler)
DEF(EXTI4_IRQHandler)
DEF(EXTI9_5_IRQHandler)
DEF(EXTI15_10_IRQHandler)

static void enable_irqs()
{
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI2_IRQn);
    NVIC_EnableIRQ(EXTI3_IRQn);
    NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/**
 * This member function will construct an TimedInterruptIn instance, and configure
 * interrupts for rise and fall.
 *
 * @param eventType the specific mode used in interrupt context to determine how an
 *                  edge/rise is processed.
 *
 * @return DEVICE_OK on success
 */
int STM32L4xxPin::enableRiseFallEvents(int eventType)
{
    // if we are in neither of the two modes, configure pin as a TimedInterruptIn.
    if (!(status & (IO_STATUS_EVENT_ON_EDGE | IO_STATUS_EVENT_PULSE_ON_EDGE)))
    {
        if (!(status & IO_STATUS_DIGITAL_IN))
            getDigitalValue();

        enable_irqs();

        int pin = (int)name & PINMASK;

        eventPin[pin] = this;

        volatile uint32_t *ptr = &SYSCFG->EXTICR[pin >> 2];
        int shift = (pin & 3) * 4;
        int port = (int)name >> 4;

        // take over line for ourselves
        *ptr = (*ptr & ~(0xf << shift)) | (port << shift);

        EXTI->EMR1 &= ~GPIO_PIN();
        EXTI->IMR1 |= GPIO_PIN();
        EXTI->RTSR1 |= GPIO_PIN();
        EXTI->FTSR1 |= GPIO_PIN();

        if (this->evCfg == NULL)
            this->evCfg = new STM32L4xxEventConfig;

        auto cfg = this->evCfg;
        cfg->prevPulse = 0;
    }

    status &= ~(IO_STATUS_EVENT_ON_EDGE | IO_STATUS_EVENT_PULSE_ON_EDGE);

    // set our status bits accordingly.
    if (eventType == DEVICE_PIN_EVENT_ON_EDGE)
        status |= IO_STATUS_EVENT_ON_EDGE;
    else if (eventType == DEVICE_PIN_EVENT_ON_PULSE)
        status |= IO_STATUS_EVENT_PULSE_ON_EDGE;

    return DEVICE_OK;
}

/**
 * If this pin is in a mode where the pin is generating events, it will destruct
 * the current instance attached to this STM32L4xxPin instance.
 *
 * @return DEVICE_OK on success.
 */
int STM32L4xxPin::disableEvents()
{
    if (status & (IO_STATUS_EVENT_ON_EDGE | IO_STATUS_EVENT_PULSE_ON_EDGE | IO_STATUS_TOUCH_IN))
    {
        disconnect();
        getDigitalValue();
    }

    return DEVICE_OK;
}

/**
 * Configures the events generated by this STM32L4xxPin instance.
 *
 * DEVICE_PIN_EVENT_ON_EDGE - Configures this pin to a digital input, and generates events whenever
 * a rise/fall is detected on this pin. (DEVICE_PIN_EVT_RISE, DEVICE_PIN_EVT_FALL)
 * DEVICE_PIN_EVENT_ON_PULSE - Configures this pin to a digital input, and generates events where
 * the timestamp is the duration that this pin was either HI or LO. (DEVICE_PIN_EVT_PULSE_HI,
 * DEVICE_PIN_EVT_PULSE_LO) DEVICE_PIN_EVENT_ON_TOUCH - Configures this pin as a makey makey style
 * touch sensor, in the form of a Button. Normal button events will be generated using the ID of
 * this pin. DEVICE_PIN_EVENT_NONE - Disables events for this pin.
 *
 * @param eventType One of: DEVICE_PIN_EVENT_ON_EDGE, DEVICE_PIN_EVENT_ON_PULSE,
 * DEVICE_PIN_EVENT_ON_TOUCH, DEVICE_PIN_EVENT_NONE
 *
 * @code
 * DeviceMessageBus bus;
 *
 * STM32L4xxPin P0(DEVICE_ID_IO_P0, DEVICE_PIN_P0, PIN_CAPABILITY_BOTH);
 * P0.eventOn(DEVICE_PIN_EVENT_ON_PULSE);
 *
 * void onPulse(Event evt)
 * {
 *     int duration = evt.timestamp;
 * }
 *
 * bus.listen(DEVICE_ID_IO_P0, DEVICE_PIN_EVT_PULSE_HI, onPulse, MESSAGE_BUS_LISTENER_IMMEDIATE)
 * @endcode
 *
 * @return DEVICE_OK on success, or DEVICE_INVALID_PARAMETER if the given eventype does not match
 *
 * @note In the DEVICE_PIN_EVENT_ON_PULSE mode, the smallest pulse that was reliably detected was
 * 85us, around 5khz. If more precision is required, please use the InterruptIn class supplied by
 * ARM mbed.
 */
int STM32L4xxPin::eventOn(int eventType)
{
    switch (eventType)
    {
    case DEVICE_PIN_EVENT_ON_EDGE:
    case DEVICE_PIN_EVENT_ON_PULSE:
        enableRiseFallEvents(eventType);
        break;

    case DEVICE_PIN_EVENT_ON_TOUCH:
        isTouched();
        break;

    case DEVICE_PIN_EVENT_NONE:
        disableEvents();
        break;

    default:
        return DEVICE_INVALID_PARAMETER;
    }

    return DEVICE_OK;
}
} // namespace codal