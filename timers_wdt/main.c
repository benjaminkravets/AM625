/*
 *  Copyright (C) 2018-2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

#include "drivers/watchdog.h"
void empty_main(void *args);

uint32_t led_state = 0;

void turn_on_h17() {
    uint32_t baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CONFIG_GPIO0_H17_BASE_ADDR);
    GPIO_pinWriteHigh(baseAddr, CONFIG_GPIO0_H17_PIN);

}
void h17_callback(void *args) {

    uint32_t baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CONFIG_GPIO0_H17_BASE_ADDR);

    if (led_state == 0) {
        GPIO_pinWriteHigh(baseAddr, CONFIG_GPIO0_H17_PIN);
        led_state = 1;
    } else if (led_state == 1) {
        GPIO_pinWriteLow(baseAddr, CONFIG_GPIO0_H17_PIN);
        led_state = 0;
    }


}

void watchdogCallback(void * arg)
{
    turn_on_h17();

    while(1) {}
}


int main()
{
    int32_t status = SystemP_SUCCESS;

    System_init();
    Board_init();

    HwiP_Params hwiPrms;
    status = SystemP_SUCCESS;
    static HwiP_Object hRtiHwiObject;

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum = CONFIG_WDT0_INTR;
    hwiPrms.callback = &watchdogCallback;
    status = HwiP_construct(&hRtiHwiObject, &hwiPrms);

    /* Open drivers */
    Drivers_open();
    /* Open flash and board drivers */
    status = Board_driversOpen();
    DebugP_assert(status==SystemP_SUCCESS);

    empty_main(NULL);
    Watchdog_clear(gWatchdogHandle[0]);



    while (1)
    {
        DebugP_log("Watchdog cleared \r\n");
        Watchdog_clear(gWatchdogHandle[0]);

        for (volatile uint32_t i = 0; i < (1 << 27); i++)
        {
        }
    }


    /* Close board and flash drivers */
    Board_driversClose();
    /* Close drivers */
    Drivers_close();

    Board_deinit();
    System_deinit();

    return 0;
}
