/*******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the Empty Application Example
*              for ModusToolbox.
*
* Related Document: See README.md
*
*
********************************************************************************
* Copyright 2021-2023, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "cyhal.h"
#include "cybsp.h"


#include "cy8ckit_028_sense.h"
#include "GUI.h"
#include "hardware_cmd.h"

xensiv_dps3xx_t pressure_sensor;
cyhal_i2c_t i2c;
cyhal_i2c_cfg_t i2c_cfg = {
    .is_slave = false,
    .address = 0,
    .frequencyhal_hz = 400000
};


#define MTB_DPS3XX_I2C_ADDR_DEFAULT 0x77

/*******************************************************************************
* Macros
*******************************************************************************/


/*******************************************************************************
* Global Variables
*******************************************************************************/


/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void floatToStr(uint8_t *out, float x,int decimalPoint);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CPU. It...
*    1.
*    2.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    char str[80];
    // UART context variable
   	cy_stc_scb_uart_context_t UART_context;


    #if defined (CY_DEVICE_SECURE)
       cyhal_wdt_t wdt_obj;

       /* Clear watchdog timer so that it doesn't trigger a reset */
       result = cyhal_wdt_init(&wdt_obj, cyhal_wdt_get_max_timeout_ms());
       CY_ASSERT(CY_RSLT_SUCCESS == result);
       cyhal_wdt_free(&wdt_obj);
    #endif
    /* Initialize the device and board peripherals */
    result = cybsp_init();
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    /* Enable global interrupts */
    __enable_irq();


    /* Initialize i2c */
    result = cyhal_i2c_init(&i2c, CY8CKIT_028_SENSE_PIN_I2C_SDA, CY8CKIT_028_SENSE_PIN_I2C_SCL, NULL);
    CY_ASSERT(result == CY_RSLT_SUCCESS);
    result = cyhal_i2c_configure(&i2c, &i2c_cfg);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    /* Initialize pressure sensor */
    result = xensiv_dps3xx_mtb_init_i2c(&pressure_sensor, &i2c, MTB_DPS3XX_I2C_ADDR_DEFAULT);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    /* Initialize the OLED display */
    result = mtb_ssd1306_init_i2c(&i2c);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    GUI_Init();

    /* Configure and enable the UART peripheral */
    Cy_SCB_UART_Init(UART_HW, &UART_config, &UART_context);
    Cy_SCB_UART_Enable(UART_HW);


    // Initialize the AREF - block needed by ADC_HW ADC
    Cy_SysAnalog_Init(&AREF_config);
    // Initialize AREF
    Cy_SysAnalog_Enable();

    // Initialize the ADC
    Cy_SAR_Init(ADC_HW, &ADC_config);
    // Enable the ADC
    Cy_SAR_Enable(ADC_HW);

    int32_t ADCresult = 0; // ADC conversion result
    int32_t microVolts = 0; // Var to store voltage conversion of ADC result

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
}


/* [] END OF FILE */
