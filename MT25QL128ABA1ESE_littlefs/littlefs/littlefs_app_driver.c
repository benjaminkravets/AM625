#include "littlefs_app_driver.h"



#include "lfs.h"
#include "MT25Q.h"

// variables used by the filesystem
lfs_t lfs;
lfs_file_t file;



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

void ls_dir(){
    struct lfs_info info;
    lfs_dir_t dir;

    printf("ls: \r\n");

    lfs_dir_open(&lfs, &dir, "/test");
    while (lfs_dir_read(&lfs, &dir, &info) > 0) {
        printf("%s \r\n", info.name);
    }
    lfs_dir_close(&lfs, &dir);
}

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

    //begin added

    volatile int a = lfs_mkdir(&lfs, "/test");

    a = lfs_file_open(&lfs, &file, "/test/test_file", LFS_O_RDWR | LFS_O_CREAT);
    (void) a;
    ls_dir();

    //end added

    // release any resources we were using
    lfs_unmount(&lfs);

    // print the boot count
    printf("boot_count: %d\n", boot_count);

    return 0;
}