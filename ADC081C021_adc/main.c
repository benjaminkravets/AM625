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

#include "ioexp_tca6424.h"

void empty_main(void *args);

void vcc_en()
{
    TCA6424_Config exp_cfg;
    TCA6424_Params exp_prm;
    TCA6424_Attrs exp_attr;

    TCA6424_Params_init(&exp_prm);

    if (TCA6424_open(&exp_cfg, &exp_prm) == SystemP_FAILURE)
    {
        DebugP_log("ioexp open failed \r\n");
    }
    else
    {
        DebugP_log("ioexp open succeeded \r\n");
    }

    TCA6424_config(&exp_cfg, 5, TCA6424_MODE_OUTPUT);

    TCA6424_setOutput(&exp_cfg, 5, TCA6424_OUT_STATE_HIGH);

    TCA6424_close(&exp_cfg);
}

void i2c_tx() {

    I2C_Transaction blah;
    I2C_Transaction_init(&blah);

    uint8_t rx[2];

    blah.readBuf = rx;
    blah.readCount = 2;
    blah.targetAddress = (0x5A);

    if (I2C_transfer(gI2cHandle[1], &blah) != I2C_STS_SUCCESS)
    {
        DebugP_log("i2c0 send failed \r\n");
    }
    else
    {
        uint32_t reading = ((rx[0] << 4) | (rx[1] >> 4));

        DebugP_log("i2c0 send succeeded \r\n");
        DebugP_log("%i %i %i \r\n", rx[0], rx[1], reading);

    }
}

int main()
{
    int32_t status = SystemP_SUCCESS;

    System_init();
    Board_init();

    /* Open drivers */
    Drivers_open();
    /* Open flash and board drivers */
    status = Board_driversOpen();
    DebugP_assert(status==SystemP_SUCCESS);

    empty_main(NULL);
    vcc_en();
    while (1)
    {
        i2c_tx();
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
