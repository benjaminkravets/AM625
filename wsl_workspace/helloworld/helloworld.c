
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <string.h>

#include <omap

int main() {
    int fd_spi;
    const char *spi_device = "/dev/spidev1.0";
    unsigned char tx_buffer[] = {0xAA, 0xBB, 0xCC}; // Data to transmit
    unsigned char rx_buffer[sizeof(tx_buffer)] = {0}; // Buffer for received data
    struct spi_ioc_transfer spi_transfer = {0}; // SPI transfer structure
    int ret;

    // Open the SPI device
    fd_spi = open(spi_device, O_RDWR);
    if (fd_spi < 0) {
        perror("Error opening SPI device");
        return -1;
    }

    printf("SPI device opened successfully\n");
    

    // Configure the SPI transfer
    spi_transfer.tx_buf = (unsigned long)tx_buffer; // Transmit buffer
    spi_transfer.rx_buf = (unsigned long)rx_buffer; // Receive buffer
    spi_transfer.len = sizeof(tx_buffer);           // Length of data
    spi_transfer.speed_hz = 500000;                 // SPI speed (500 kHz)
    spi_transfer.bits_per_word = 8;                 // Bits per word
    spi_transfer.delay_usecs = 0;                   // No delay

    // Perform the SPI transfer
    ret = ioctl(fd_spi, SPI_IOC_MESSAGE(1), &spi_transfer);
    if (ret < 0) {
        perror("Error during SPI transfer");
        close(fd_spi);
        return -1;
    }

    printf("SPI transfer completed successfully\n");
    printf("Received data: ");
    for (size_t i = 0; i < sizeof(rx_buffer); i++) {
        printf("0x%02X ", rx_buffer[i]);
    }
    printf("\n");

    // Close the SPI device
    close(fd_spi);

    return 0;
}




// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <linux/gpio.h>
// #include <linux/spi/spi.h>
// #include <sys/ioctl.h>
// #include <string.h>

// int main() {
//     int fd;
//     struct gpiohandle_request req;
//     struct gpiohandle_data data;

//     printf("hi \r\n");

//     // Open the GPIO chip device
//     fd = open("/dev/gpiochip2", O_RDONLY);
//     if (fd < 0) {
//         perror("Error opening gpiochip2");
//         return -1;
//     }

//     // Prepare the handle request
//     req.lineoffsets[0] = 5; // GPIO line offset
//     req.flags = GPIOHANDLE_REQUEST_OUTPUT;
//     req.default_values[0] = 0; // Initial value
//     strcpy(req.consumer_label, "my_gpio");

//     req.lines = 1;

//     // Request the GPIO line handle
//     if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req) < 0) {
//         perror("Failed to request GPIO line handle");
//         close(fd);
//         return -1;
//     }

//     // Set the GPIO line value
//     data.values[0] = 0; // Set value to 1 (high)
//     if (ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) < 0) {
//         perror("Failed to set GPIO line value");
//         close(req.fd);
//         close(fd);
//         return -1;
//     }

//     printf("GPIO line value set successfully\n");

//     // Clean up
//     close(req.fd);
//     close(fd);

//     return 0;
// }