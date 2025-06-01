#include "MT25Q.h"

#include <ti_drivers_config.h>
#include "ti_drivers_open_close.h"




void MT25Q_read_id() {
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint8_t             transmitBuffer[10] = {0x9e};
    uint8_t             receiveBuffer[10] = {0};

    /* Fill in transmitBuffer */
    spiTransaction.channel  = 0U;
    spiTransaction.dataSize  = 8U;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = 10;
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

int MT25Q_read_memory(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void * buffer, lfs_size_t size) {
    printf("MT25Q_read_memory block %d off %d size %d\n", block, off, size);
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint8_t             transmitBuffer[4] = {0};
    uint8_t             receiveBufferDummy[4] = {0};
 
    /* Fill in transmitBuffer with commands */
    spiTransaction.channel  = 0U;
    spiTransaction.dataSize  = 8U;
    spiTransaction.csDisable = FALSE;
    spiTransaction.count    = 4;
    spiTransaction.txBuf    = (void *)transmitBuffer;
    spiTransaction.rxBuf    = (void *)receiveBufferDummy;
    spiTransaction.args     = NULL;

    transmitBuffer[0] = 0x3;
    uint32_t address = block * 4096 + off; //replace 4096 with passed block size
    transmitBuffer[1] = (uint8_t)(address >> 16);
    transmitBuffer[2] = (uint8_t)(address >> 8);
    transmitBuffer[3] = (uint8_t)(address);
 
    /* Initiate transfer */
    transferOK = MCSPI_transfer(gMcspiHandle[0], &spiTransaction);
    if((SystemP_SUCCESS != transferOK) ||
       (MCSPI_TRANSFER_COMPLETED != spiTransaction.status))
    {
        /* MCSPI transfer failed!! */
        DebugP_assert(FALSE);
    }

    uint8_t *           transmitBufferDummy = malloc(size);
 
    /* Read Data drom slave if any */
 
    /* Fill in transmitBuffer with data */
    spiTransaction.channel  = 0U;
    spiTransaction.dataSize  = 8U;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = size;
    spiTransaction.txBuf    = (void *)transmitBufferDummy;
    spiTransaction.rxBuf    = (void *)buffer;
    spiTransaction.args     = NULL;
 
    /* Initiate transfer */
    transferOK = MCSPI_transfer(gMcspiHandle[0], &spiTransaction);
    if((SystemP_SUCCESS != transferOK) ||
       (MCSPI_TRANSFER_COMPLETED != spiTransaction.status))
    {
        /* MCSPI transfer failed!! */
        DebugP_assert(FALSE);
    }

    free(transmitBufferDummy);

    return 0;
}

void MT25Q_enable_write() {
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint8_t             transmitBuffer[1] = {0x6};
    uint8_t             receiveBuffer[1] = {0};

    /* Fill in transmitBuffer */
    spiTransaction.channel  = 0U;
    spiTransaction.dataSize  = 8U;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = 1;
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

// check status register, including whether write is enabled
void MT25Q_read_status() {
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint8_t             transmitBuffer[2] = {0x5};
    uint8_t             receiveBuffer[2] = {0};

    /* Fill in transmitBuffer */
    spiTransaction.channel  = 0U;
    spiTransaction.dataSize  = 8U;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = 2;
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

int MT25Q_prog_memory(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void * buffer, lfs_size_t size) {
    printf("MT25Q_prog_memory block %d off %d size %d\n", block, off, size);
    MT25Q_read_status();
    MT25Q_enable_write();
    MT25Q_read_status();
    //first transaction is size 4- command plus address
    //chained transaction, command then data

    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint8_t             transmitBuffer[4] = {0};
    uint8_t *           receiveBufferDummy = malloc(size);
 
    /* Fill in transmitBuffer with commands */
    spiTransaction.channel  = 0U;
    spiTransaction.dataSize  = 8U;
    spiTransaction.csDisable = FALSE;
    spiTransaction.count    = 4;
    spiTransaction.txBuf    = (void *)transmitBuffer;
    spiTransaction.rxBuf    = (void *)receiveBufferDummy;
    spiTransaction.args     = NULL;

    transmitBuffer[0] = 0x2;
    uint32_t address = block * 4096 + off; //replace 4096 with passed block size
    transmitBuffer[1] = (uint8_t)(address >> 16);
    transmitBuffer[2] = (uint8_t)(address >> 8);
    transmitBuffer[3] = (uint8_t)(address);
 
    /* Initiate transfer */
    transferOK = MCSPI_transfer(gMcspiHandle[0], &spiTransaction);
    if((SystemP_SUCCESS != transferOK) ||
       (MCSPI_TRANSFER_COMPLETED != spiTransaction.status))
    {
        /* MCSPI transfer failed!! */
        DebugP_assert(FALSE);
    }

    //uint8_t *           receiveBufferDummy = malloc(size);
 
    // /* Read Data drom slave if any */
 
    /* Fill in transmitBuffer with data */
    spiTransaction.channel  = 0U;
    spiTransaction.dataSize  = 8U;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = size;
    spiTransaction.txBuf    = (void *)buffer;
    spiTransaction.rxBuf    = (void *)receiveBufferDummy;
    spiTransaction.args     = NULL;
 
    /* Initiate transfer */
    transferOK = MCSPI_transfer(gMcspiHandle[0], &spiTransaction);
    if((SystemP_SUCCESS != transferOK) ||
       (MCSPI_TRANSFER_COMPLETED != spiTransaction.status))
    {
        /* MCSPI transfer failed!! */
        DebugP_assert(FALSE);
    }

  free(receiveBufferDummy);

  return 0;
}

int MT25Q_subsector_erase(const struct lfs_config *c, lfs_block_t block){
    printf("MT25Q_subsector_erase block %d\n", block);
    
    MT25Q_enable_write();
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint8_t             transmitBuffer[4] = {0};
    uint8_t             receiveBufferDummy[4] = {0};
 
    /* Fill in transmitBuffer with commands */
    spiTransaction.channel  = 0U;
    spiTransaction.dataSize  = 8U;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = 4;
    spiTransaction.txBuf    = (void *)transmitBuffer;
    spiTransaction.rxBuf    = (void *)receiveBufferDummy;
    spiTransaction.args     = NULL;

    transmitBuffer[0] = 0x20;
    uint32_t address = block * 4096; //replace 4096 with passed block size
    transmitBuffer[1] = (uint8_t)(address >> 16);
    transmitBuffer[2] = (uint8_t)(address >> 8);
    transmitBuffer[3] = (uint8_t)(address);
 
    /* Initiate transfer */
    transferOK = MCSPI_transfer(gMcspiHandle[0], &spiTransaction);
    if((SystemP_SUCCESS != transferOK) ||
       (MCSPI_TRANSFER_COMPLETED != spiTransaction.status))
    {
        /* MCSPI transfer failed!! */
        DebugP_assert(FALSE);
    }

    return 0;
}

int MT25Q_sync(const struct lfs_config *c)
{
    printf("MT25Q_sync\n");
    return 0;
}