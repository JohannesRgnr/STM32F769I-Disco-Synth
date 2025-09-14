/**
 * @file lcd.h
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 13.09.25
 * @note
 */

#ifndef MINIMAL_SAI_LCD_H
#define MINIMAL_SAI_LCD_H

#include "stm32f769i_discovery_lcd.h"

#define LCD_FRAME_BUFFER          SDRAM_DEVICE_ADDR

void Display_Default(void);
void Display_Init(void);
void Display_partials(void);



#endif //MINIMAL_SAI_LCD_H