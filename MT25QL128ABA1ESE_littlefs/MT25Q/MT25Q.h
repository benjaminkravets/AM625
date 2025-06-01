#include <stdint.h>
#include "lfs.h"
void MT25Q_read_id(void);
int MT25Q_read_memory(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
void MT25Q_enable_write(void);
void MT25Q_read_status(void);
int MT25Q_prog_memory(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void * buffer, lfs_size_t size);
int MT25Q_subsector_erase(const struct lfs_config *c, lfs_block_t block);
int MT25Q_sync(const struct lfs_config *c);