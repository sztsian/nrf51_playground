#include <stdbool.h>
#include <stdint.h>

#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "boards.h"

int main(const int argc, const char* argv[]) {
    bsp_board_leds_init();

    /* Initialize the log module */
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));

    /* Print welcome string and flush log buffer */
    NRF_LOG_INFO("Application started.\r\n");
    NRF_LOG_FLUSH();
    for(;;) {
        // Dead Loop
        for(int i = 0; i < LEDS_NUMBER; i++) {
            bsp_board_led_invert(i);
            nrf_delay_ms(500);
        }
    }

    return 0;
}