#include "littlefs_app_driver.h"
#include "lfs.h"
#include "MT25Q.h"

// variables used by the filesystem
lfs_t lfs;
lfs_file_t file;

// int read (const struct lfs_config *c, lfs_block_t block,
//             lfs_off_t off, void *buffer, lfs_size_t size)
// {
//     printf("read: block %d, offset %d, size %d\n", block, off, size);
//     return 1;
// }

// int prog(const struct lfs_config *c, lfs_block_t block,
//             lfs_off_t off, const void *buffer, lfs_size_t size)
// {
//     printf("prog: block %d, offset %d, size %d\n", block, off, size);
//     return 1;
// }

// int erase(const struct lfs_config *c, lfs_block_t block)
// {
//     printf("erase: block %d\n", block);
//     return 1;
// }
// int sync(const struct lfs_config *c)
// {
//     printf("sync\n");
//     return 1;
// }

// configuration of the filesystem is provided by this struct
const struct lfs_config cfg = {
    // block device operations
    .read = MT25Q_read_memory,
    .prog = MT25Q_prog_memory,
    .erase = MT25Q_subsector_erase,
    .sync = MT25Q_sync,

    // block device configuration
    // .read_size = 16,
    // .prog_size = 16,
    // .block_size = 4096,
    // .block_count = 128,
    // .cache_size = 16,
    // .lookahead_size = 16,
    // .block_cycles = 500,

    .read_size = 16,
    .prog_size = 16,
    .block_size = 4096,
    .block_count = 4096,
    .cache_size = 16,
    .lookahead_size = 64,
    .block_cycles = 500,


};

// entry point
int littlefs_main(void)
{
    // mount the filesystem
    int err = lfs_mount(&lfs, &cfg);

    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err)
    {
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }

    // read current count
    uint32_t boot_count = 0;
    lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

    // update boot count
    boot_count += 1;
    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // release any resources we were using
    lfs_unmount(&lfs);

    // print the boot count
    printf("boot_count: %d\n", boot_count);

    return 0;
}