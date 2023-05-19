# RGB LED control

# This is hardware command for easy use

This is a minimal starter application for Infineon MCU devices.
which include

- CY8CKIT-062s2-43012
- CY8CKIT-028-SENSE.
## Requirements
- [ModusToolbox™ software](https://www.infineon.com/modustoolbox) v3.0 or later (tested with v3.0)
- CY8CKIT-062s2-43012
- CY8CKIT-028-SENSE.
- Programming language: C
- Associated parts: All [PSoC™ 6 MCU](https://www.infineon.com/cms/en/product/microcontroller/32-bit-psoc-arm-cortex-microcontroller/psoc-6-32-bit-arm-cortex-m4-mcu) parts, [XMC7000 MCU](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/), and [AIROC™ CYW20829 Bluetooth® LE SoC](https://www.infineon.com/cms/en/product/promopages/airoc20829)
## Supported toolchains (make variable 'TOOLCHAIN')
- GNU Arm® embedded compiler v10.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm® compiler v6.16 (`ARM`)
- IAR C/C++ compiler v9.30.1 (`IAR`)
## RGB LED functions

These functions will turn on RGB led on CY8CKIT-062S2043012 following this

**led_green_on(void)**

Turn on the green LED 

**led_green_off(void)**

Turn off the green LED 

**led_red_on(void)**

Turn on the red LED 

**led_red_off(void)**

Turn off the red LED 

**led_blue_on(void)**

Turn on the blue LED 

**led_blue_off(void)**

Turn off the blue LED 

## How to use

Import this application to your modus project and go to file main.c
BSP and device are already configured all you need is to program your function in main() under for;; loop.

For example, the following code is to circle the RGB LED.


    for (;;)
        {
          //Loop between red green blue LED
            led_blue_on();
            cyhal_system_delay_ms(1000);
            led_blue_off();
            led_green_on();
            cyhal_system_delay_ms(1000);
            led_green_off();
            led_red_on();
            cyhal_system_delay_ms(1000);
            led_red_off();
        }

when you finish writing your code go to

- Build Application
- wait for your program to finish building
- go to Launch > [Your app name] debug (KitProg3_Miniprog4)

you should see the LED circling in Blue>Green>Red and keep repeating.

