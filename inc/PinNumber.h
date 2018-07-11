#ifndef PINNUMBER_H
#define PINNUMBER_H

#include "cmsis.h"
#include "PinNamesTypes.h"
#include "Pin.h"

namespace codal {
enum class PinNumber:uint8_t {
        PA_0  = 0x00,
        PA_1  = 0x01,
        PA_2  = 0x02,
        PA_3  = 0x03,
        PA_4  = 0x04,
        PA_5  = 0x05,
        PA_6  = 0x06,
        PA_7  = 0x07,
        PA_8  = 0x08,
        PA_9  = 0x09,
        PA_10 = 0x0A,
        PA_11 = 0x0B,
        PA_12 = 0x0C,
        PA_13 = 0x0D,
        PA_14 = 0x0E,
        PA_15 = 0x0F,

        PB_0  = 0x10,
        PB_1  = 0x11,
        PB_2  = 0x12,
        PB_3  = 0x13,
        PB_4  = 0x14,
        PB_5  = 0x15,
        PB_6  = 0x16,
        PB_7  = 0x17,
        PB_8  = 0x18,
        PB_9  = 0x19,
        PB_10 = 0x1A,
        PB_11 = 0x1B,
        PB_12 = 0x1C,
        PB_13 = 0x1D,
        PB_14 = 0x1E,
        PB_15 = 0x1F,

        PC_0  = 0x20,
        PC_1  = 0x21,
        PC_2  = 0x22,
        PC_3  = 0x23,
        PC_4  = 0x24,
        PC_5  = 0x25,
        PC_6  = 0x26,
        PC_7  = 0x27,
        PC_8  = 0x28,
        PC_9  = 0x29,
        PC_10 = 0x2A,
        PC_11 = 0x2B,
        PC_12 = 0x2C,
        PC_13 = 0x2D,
        PC_14 = 0x2E,
        PC_15 = 0x2F,

        PD_0  = 0x30,
        PD_1  = 0x31,
        PD_2  = 0x32,
        PD_3  = 0x33,
        PD_4  = 0x34,
        PD_5  = 0x35,
        PD_6  = 0x36,
        PD_7  = 0x37,
        PD_8  = 0x38,
        PD_9  = 0x39,
        PD_10 = 0x3A,
        PD_11 = 0x3B,
        PD_12 = 0x3C,
        PD_13 = 0x3D,
        PD_14 = 0x3E,
        PD_15 = 0x3F,

        PE_0  = 0x40,
        PE_1  = 0x41,
        PE_2  = 0x42,
        PE_3  = 0x43,
        PE_4  = 0x44,
        PE_5  = 0x45,
        PE_6  = 0x46,
        PE_7  = 0x47,
        PE_8  = 0x48,
        PE_9  = 0x49,
        PE_10 = 0x4A,
        PE_11 = 0x4B,
        PE_12 = 0x4C,
        PE_13 = 0x4D,
        PE_14 = 0x4E,
        PE_15 = 0x4F,

        PH_0  = 0x70,
        PH_1  = 0x71,

        // ADC internal channels
        ADC_TEMP = 0xF0,
        ADC_VREF = 0xF1,
        ADC_VBAT = 0xF2,

        // Arduino connector namings
        A0          = PC_5,
        A1          = PC_4,
        A2          = PC_3,
        A3          = PC_2,
        A4          = PC_1,
        A5          = PC_0,
        D0          = PA_1,
        D1          = PA_0,
        D2          = PD_14,
        D3          = PB_0,
        D4          = PA_3,
        D5          = PB_4,
        D6          = PB_1,
        D7          = PA_4,
        D8          = PB_2,
        D9          = PA_15,
        D10         = PA_2,
        D11         = PA_7,
        D12         = PA_6,
        D13         = PA_5,
        D14         = PB_9,
        D15         = PB_8,
        // STDIO for console print
        STDIO_UART_TX = PB_6,
        STDIO_UART_RX = PB_7,
        // Generic signals namings
        LED1        = D13, // Green LED (LD1)
        LED2        = PB_14, // Green LED (LD2)
        LED3        = PC_9, // Yellow LED (LD3 WIFI) / Blue LED (LD4 BLE)
        LED4        = LED3,
        USER_BUTTON = PC_13,
        BUTTON1     = USER_BUTTON,
        BUTTON2     = USER_BUTTON,
        BUTTON3     = USER_BUTTON,
        BUTTON4     = USER_BUTTON,
        BUTTON5     = USER_BUTTON,
        SERIAL_TX   = STDIO_UART_TX,
        SERIAL_RX   = STDIO_UART_RX,
        USBTX       = STDIO_UART_TX,
        USBRX       = STDIO_UART_RX,
        I2C_SCL     = D15,
        I2C_SDA     = D14,
        SPI_MOSI    = D11,
        SPI_MISO    = D12,
        SPI_SCK     = D13,
        SPI_CS      = D10,
        PWM_OUT     = D9,

        /**** USB pins ****/
        USB_OTG_FS_DM = PA_11,
        USB_OTG_FS_DP = PA_12,
        USB_OTG_FS_ID = PA_10,
        USB_OTG_FS_NOE = PC_9,
        USB_OTG_FS_NOE_ALT0 = PA_13,
        USB_OTG_FS_SOF = PA_8,
        USB_OTG_FS_VBUS = PA_9,

        /**** OSCILLATOR pins ****/
        RCC_OSC32_IN = PC_14,
        RCC_OSC32_OUT = PC_15,
        RCC_OSC_IN = PH_0,
        RCC_OSC_OUT = PH_1,

        /**** DEBUG pins ****/
        SYS_JTCK_SWCLK = PA_14,
        SYS_JTDI = PA_15,
        SYS_JTDO_SWO = PB_3,
        SYS_JTMS_SWDIO = PA_13,
        SYS_JTRST = PB_4,
        SYS_PVD_IN = PB_7,
        SYS_TRACECLK = PE_2,
        SYS_TRACED0 = PE_3,
        SYS_TRACED1 = PE_4,
        SYS_TRACED2 = PE_5,
        SYS_TRACED3 = PE_6,
        SYS_WKUP1 = PA_0,
        SYS_WKUP2 = PC_13,
        SYS_WKUP3 = PE_6,
        SYS_WKUP4 = PA_2,
        SYS_WKUP5 = PC_5,

        // Not connected
        NC = (uint8_t)(0xFF)
    };
}
typedef codal::PinNumber PinNumber;
constexpr auto NC = -1;

#endif