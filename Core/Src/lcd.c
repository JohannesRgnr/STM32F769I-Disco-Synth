/**
 * @file lcd.c
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 13.09.25
 * @note
 */

#include "../Inc/lcd.h"

#include <stdio.h>

#include "oscillators.h"
#include "spectra.h"

void Display_Default(void)
{
	/* Default LCD settings */
	  BSP_LCD_SetFont(&Font12);
	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}


void Display_Init(void)
{
  // uint8_t FreqStr[256] = {0};
  /* Set LCD Foreground Layer  */
	BSP_LCD_SelectLayer(LTDC_DEFAULT_ACTIVE_LAYER);

	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	/* Clear the LCD */
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_Clear(LCD_COLOR_BLACK);


	/* Set the LCD Text Color */
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);

	/* Display LCD messages */
	char str[128];
	sprintf(str, "SAI DEMO - %d voices additive synthesis", harmonics);
	BSP_LCD_SetFont(&FontInconsolataNerdFont20);
	BSP_LCD_DisplayStringAt(16, BSP_LCD_GetYSize()/2, (uint8_t *)str, CENTER_MODE);
}

