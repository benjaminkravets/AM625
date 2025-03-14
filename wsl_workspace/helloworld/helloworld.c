#include <stdio.h>
#include <linux/gpio.h>
#include <linux/gpiod.h>

int main() {

    
    struct gpio_chip *chip;
    struct gpio_line *line;
    int req, value;

    chip = gpiod_chip_open("/dev/gpiochip2");
    if (!chip) {
        printf("Failed to open gpiochip2\n");
        return 1;
    }

    line = gpiod_chip_get_line(chip, 5);
    

    if (!line) {
        printf("Failed to get line 5\n");
        return 1;
    }



    
}