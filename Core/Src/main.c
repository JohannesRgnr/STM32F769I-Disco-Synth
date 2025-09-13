/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include <stdio.h>
#include <string.h>

#include "i2c.h"
#include "sai.h"
#include "gpio.h"
#include "usart.h"
#include "audio.h"
#include "console.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern UART_HandleTypeDef huart1;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LCD_FRAME_BUFFER          SDRAM_DEVICE_ADDR


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);
/* USER CODE BEGIN PFP */
static void Display_Default(void);
static void Display_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Define serial input and output functions using UART
// int __io_putchar(int ch)
// {
//   HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100); // infinite delay value
//   return 1;
// }
//
// // Read a character from the UART with small timeout
// // If HAL_UART_Receive() returns error, return EOF (-1), else return the character read
// int __io_getchar(void)
// {
//   uint8_t ch = 0;
//
//   //__HAL_UART_CLEAR_OREFLAG(&huart5);
//
//   HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY);
//
//   return ch;
// }

char *intro_string = "Entering main application... \r\n";
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  USART1_Init();
  MX_SAI1_Init();
  /* Initialize the LCD */
  BSP_LCD_Init();
  /* Initialize the LCD Layers */
  BSP_LCD_LayerDefaultInit(LTDC_DEFAULT_ACTIVE_LAYER, LCD_FRAME_BUFFER);
  /* USER CODE BEGIN 2 */
  HAL_UART_Transmit(&huart1, (uint8_t*)intro_string, strlen(intro_string), HAL_MAX_DELAY);
  AUDIO_Init();
  ConsoleInit();

  Display_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  while (1)
  {
    ConsoleProcess();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}


/* USER CODE BEGIN 4 */
static void Display_Default(void)
{
	/* Default LCD settings */
	  BSP_LCD_SetFont(&Font12);
	  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}


static void Display_Init(void)
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
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
