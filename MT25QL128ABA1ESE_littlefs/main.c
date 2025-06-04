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

#include "ti_board_config.h"
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include <stdlib.h>

#include "ioexp_tca6424.h"
#include "littlefs_app_driver.h"
#include "string.h"

#include "MT25Q.h"




void empty_main(void *args);

// enable 3.3 rail (VCC3V3_EXP)
void vcc_en() {
  TCA6424_Config exp_cfg;
  TCA6424_Params exp_prm;
  // TCA6424_Attrs exp_attr;

  TCA6424_Params_init(&exp_prm);

  if (TCA6424_open(&exp_cfg, &exp_prm) == SystemP_FAILURE) {
    DebugP_log("ioexp open failed \r\n");
  } else {
    DebugP_log("ioexp open succeeded \r\n");
  }

  TCA6424_config(&exp_cfg, 5, TCA6424_MODE_OUTPUT);

  TCA6424_setOutput(&exp_cfg, 5, TCA6424_OUT_STATE_HIGH);

  TCA6424_close(&exp_cfg);
}


int main() {
  int32_t status = SystemP_SUCCESS;

  System_init();
  Board_init();

  /* Open drivers */
  Drivers_open();
  /* Open flash and board drivers */
  status = Board_driversOpen();
  DebugP_assert(status == SystemP_SUCCESS);

  vcc_en();
  empty_main(NULL);
  littlefs_main();

  //uint8_t * MT25Q_read_buffer = malloc(256);

  #define READSIZE (256)
  uint8_t read_write_buffer[READSIZE];
  uint32_t x = 0;
  for (uint32_t i = READSIZE - 1 ; i > 0 ; i--) {
    read_write_buffer[x] = 0;
    x++;
  }

  // char * ptrtest = malloc(256);

  // //const struct lfs_config * a = 0;

  // ptrtest[0] = 'a';

  while (1)
  {
    empty_main(NULL);
    //MT25Q_read_id();
    //MT25Q_read_memory(a, 0, 0, read_write_buffer, 256);
    //MT25Q_read_memory(a, 1, 0, read_write_buffer, 256);
    //MT25Q_read_memory(a, 2, 0, read_write_buffer, 256);

    //MT25Q_prog_memory(a, 0, 0, read_write_buffer, 256);
    // MT25Q_subsector_erase(0);
    //MT25Q_subsector_erase(1);
    // MT25Q_subsector_erase(2);
    //printf("Yes this works \r\n");

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
