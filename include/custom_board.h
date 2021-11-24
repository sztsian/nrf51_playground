/**
 * @file custom_board.h
 * @author imi415 <imi415.public@gmail.com>
 * @brief Custom board file for Waveshare BLE-400 board.
 * @version 0.1
 * @date 2021-11-24
 * 
 * @copyright Copyright (c) 2021 imi415
 * 
 */

#ifndef CUSTOM_BOARD_H
#define CUSTOM_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

// LEDs definitions for Waveshare BLE-400
#define LED_START      18
#define LED_0          18
#define LED_1          19
#define LED_2          20
#define LED_3          21
#define LED_4          22
#define LED_STOP       22

#define LEDS_ACTIVE_STATE 1

#define LEDS_INV_MASK  LEDS_MASK

#define LED_0_MASK     (1<<LED_0)
#define LED_1_MASK     (1<<LED_1)
#define LED_2_MASK     (1<<LED_2)
#define LED_3_MASK     (1<<LED_3)
#define LED_4_MASK     (1<<LED_4)

#define BSP_LED_0 LED_0
#define BSP_LED_1 LED_1
#define BSP_LED_2 LED_2
#define BSP_LED_3 LED_3
#define BSP_LED_4 LED_4

// Buttons definitions for Waveshare BLE-400
#define BUTTON_START   16
#define BUTTON_0       16
#define BUTTON_1       17
#define BUTTON_END     17
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BSP_BUTTON_0   BUTTON_0
#define BSP_BUTTON_1   BUTTON_1

#define BUTTONS_LIST { BUTTON_0, BUTTON_1, }
#define LEDS_LIST { LED_0, LED_1, LED_2, LED_3, LED_4, }

#define BUTTONS_NUMBER 2
#define LEDS_NUMBER    5

// UART connection with CP2102
#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  9
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define HWFC           false

// Low frequency clock source to be used by the SoftDevice
#ifdef S210
#define NRF_CLOCK_LFCLKSRC      NRF_CLOCK_LFCLKSRC_XTAL_20_PPM
#else
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}
#endif

#ifdef __cplusplus
}
#endif

#endif
