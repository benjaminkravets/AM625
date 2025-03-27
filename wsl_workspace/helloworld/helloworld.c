#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/gpio.h>
#include <linux/spi/spi.h>
#include <sys/ioctl.h>
#include <string.h>


int main() {
    int fd;
    struct gpiohandle_request req;
    struct gpiohandle_data data;

    printf("hi \r\n");

    // Open the GPIO chip device
    fd = open("/dev/gpiochip2", O_RDONLY);
    if (fd < 0) {
        perror("Error opening gpiochip2");
        return -1;
    }

    // Prepare the handle request
    req.lineoffsets[0] = 5; // GPIO line offset
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.default_values[0] = 0; // Initial value
    strcpy(req.consumer_label, "my_gpio");

    req.lines = 1;

    // Request the GPIO line handle
    if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req) < 0) {
        perror("Failed to request GPIO line handle");
        close(fd);
        return -1;
    }

    // Set the GPIO line value
    data.values[0] = 1; // Set value to 1 (high)
    if (ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) < 0) {
        perror("Failed to set GPIO line value");
        close(req.fd);
        close(fd);
        return -1;
    }

    printf("GPIO line value set successfully\n");

    // Clean up
    close(req.fd);
    close(fd);

    return 0;
}