/*
 * hardware_cmd.c
 *
 *  Created on: Apr 27, 2023
 *      Author: Phuphu
 */

#include "cyhal.h"
#include "cybsp.h"
#include "cy8ckit_028_sense.h"
#include "GUI.h"

//OLED command
void oled_print_top(const char * s){
	GUI_GotoXY(0,0);
	GUI_DispString(s);
}

void oled_print_bot(const char * s){
	GUI_GotoXY(0,50);
	GUI_DispString(s);
}

void oled_print_line_n(const char * s,int linenum){ //linenum is 1-6
	int line = (linenum-1)*10;
	GUI_GotoXY(0,line);
	GUI_DispString(s);
}

//LED control
void led_green_on(void){
	cyhal_gpio_write(CYBSP_LED_RGB_GREEN, CYBSP_LED_STATE_ON);
}

void led_green_off(void){
	cyhal_gpio_write(CYBSP_LED_RGB_GREEN, CYBSP_LED_STATE_OFF);
}

void led_red_on(void){
	cyhal_gpio_write(CYBSP_LED_RGB_RED, CYBSP_LED_STATE_ON);
}

void led_red_off(void){
	cyhal_gpio_write(CYBSP_LED_RGB_RED, CYBSP_LED_STATE_OFF);
}

void led_blue_on(void){
	cyhal_gpio_write(CYBSP_LED_RGB_BLUE, CYBSP_LED_STATE_ON);
}

void led_blue_off(void){
	cyhal_gpio_write(CYBSP_LED_RGB_BLUE, CYBSP_LED_STATE_OFF);
}

//ADC potentiometer reading
int32_t poten_read(){
	int32_t ADCresult = 0; // ADC conversion result
    int32_t microVolts = 0; // Var to store voltage conversion of ADC result
    Cy_SAR_StartConvert(ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
    if(Cy_SAR_IsEndConversion(ADC_HW, CY_SAR_WAIT_FOR_RESULT)== CY_SAR_SUCCESS){
          ADCresult = Cy_SAR_GetResult32(ADC_HW, 0);
          microVolts = Cy_SAR_CountsTo_uVolts(ADC_HW, 0, ADCresult);
    }
    return microVolts;
}
