/**
 * @file lcd.c
 * @author Johannes R.
 * @brief 
 * @version 
 * @date 13.09.25
 * @note
 */

#include "../Inc/lcd.h"

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
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

  /* Display LCD messages */
  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAt(2, 4, (uint8_t *)"Vol+", LEFT_MODE);
  BSP_LCD_DisplayStringAt(2, BSP_LCD_GetYSize() - 16, (uint8_t *)"Vol-", LEFT_MODE);
  BSP_LCD_DisplayStringAt(91, 8, (uint8_t *)"RESONATOR", LEFT_MODE);
  BSP_LCD_DisplayStringAt(305, 8, (uint8_t *)"MOOG LP Filter", LEFT_MODE);
  BSP_LCD_DisplayStringAt(320, BSP_LCD_GetYSize() - 16, (uint8_t *)"Current preset: Bell ", LEFT_MODE);


  BSP_LCD_DisplayStringAt(50, BSP_LCD_GetYSize() - 16, (uint8_t *)"PRC", LEFT_MODE);
  BSP_LCD_DisplayStringAt(130, BSP_LCD_GetYSize() - 16, (uint8_t *)"QT", LEFT_MODE);
  BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() - 115, 225, (uint8_t *)"seq 1", LEFT_MODE);
  BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
  BSP_LCD_DisplayStringAt(90, BSP_LCD_GetYSize() - 16, (uint8_t *)"SUS", LEFT_MODE);
  BSP_LCD_DisplayStringAt(170, BSP_LCD_GetYSize() - 16, (uint8_t *)"FREE", LEFT_MODE);
  BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() - 75, 225, (uint8_t *)"seq 2", LEFT_MODE);
  BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() - 155, 225, (uint8_t *)"demo", LEFT_MODE);



  /* Display LCD X-Y Pads */
  BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);
  BSP_LCD_FillRect(26, 26, BSP_LCD_GetXSize()/2 - 48, BSP_LCD_GetYSize() - 48);
  BSP_LCD_FillRect(BSP_LCD_GetXSize()/2 +1, 26, BSP_LCD_GetXSize()/2 - 24, BSP_LCD_GetYSize()/2 - 24);
  BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
  BSP_LCD_FillRect(25, 25, BSP_LCD_GetXSize()/2 - 49, BSP_LCD_GetYSize() - 49);
  BSP_LCD_FillRect(BSP_LCD_GetXSize()/2, 25, BSP_LCD_GetXSize()/2 - 25, BSP_LCD_GetYSize()/2 - 25);


  /*display Sequencer play button */
  BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
  Point Points[]= {{BSP_LCD_GetXSize() - 33, 220}, {BSP_LCD_GetXSize() - 33, 240}, {BSP_LCD_GetXSize() - 16, 230}};
  BSP_LCD_FillPolygon(Points, 3);

  Display_Default();

}
