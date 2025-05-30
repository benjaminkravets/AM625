/*
 *  Copyright (C) 2018-2025 Texas Instruments Incorporated
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

#define APP_MCSPI_MSGSIZE (10)

//enable 3.3 rail (VCC3V3_EXP)
void vcc_en()
{
    TCA6424_Config exp_cfg;
    TCA6424_Params exp_prm;
    //TCA6424_Attrs exp_attr;

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

void UART1_FET_SEL_set()
{
    TCA6424_Config exp_cfg;
    TCA6424_Params exp_prm;
    //TCA6424_Attrs exp_attr;

    TCA6424_Params_init(&exp_prm);

    if (TCA6424_open(&exp_cfg, &exp_prm) == SystemP_FAILURE)
    {
        DebugP_log("ioexp open failed \r\n");
    }
    else
    {
        DebugP_log("ioexp open succeeded \r\n");
    }

    TCA6424_config(&exp_cfg, 21, TCA6424_MODE_OUTPUT);

    TCA6424_setOutput(&exp_cfg, 21, TCA6424_OUT_STATE_LOW);

    TCA6424_close(&exp_cfg);
}

void UART1_FET_BUF_EN_set()
{
    TCA6424_Config exp_cfg;
    TCA6424_Params exp_prm;
    //TCA6424_Attrs exp_attr;

    TCA6424_Params_init(&exp_prm);

    if (TCA6424_open(&exp_cfg, &exp_prm) == SystemP_FAILURE)
    {
        DebugP_log("ioexp open failed \r\n");
    }
    else
    {
        DebugP_log("ioexp open succeeded \r\n");
    }

    TCA6424_config(&exp_cfg, 10, TCA6424_MODE_OUTPUT);

    TCA6424_setOutput(&exp_cfg, 10, TCA6424_OUT_STATE_HIGH);

    TCA6424_close(&exp_cfg);
}

void spi_try() {
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint8_t             transmitBuffer[APP_MCSPI_MSGSIZE] = "0123456789";
    uint8_t             receiveBuffer[APP_MCSPI_MSGSIZE] = {0};

    /* Fill in transmitBuffer */
    spiTransaction.channel  = 0U;
    spiTransaction.dataSize  = 8U;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = APP_MCSPI_MSGSIZE;
    spiTransaction.txBuf    = (void *)transmitBuffer;
    spiTransaction.rxBuf    = (void *)receiveBuffer;
    spiTransaction.args     = NULL;

    /* Initiate transfer */
    transferOK = MCSPI_transfer(gMcspiHandle[0], &spiTransaction);
    if((SystemP_SUCCESS != transferOK) ||
       (MCSPI_TRANSFER_COMPLETED != spiTransaction.status))
    {
        /* MCSPI transfer failed!! */
        DebugP_log("%i %i \r\n", transferOK, spiTransaction.status);
        DebugP_assert(FALSE);
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
    UART1_FET_SEL_set();
    UART1_FET_BUF_EN_set();
    while (1)
    {
        empty_main(NULL);
        spi_try();
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
