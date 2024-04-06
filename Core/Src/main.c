/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
#include "lcd.h"
#include "stdio.h"
#include "string.h"
#include "key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char M='L';
uint8_t N=0,R=1,K=1;
uint8_t temp_R,temp_K;
uint16_t P=50;
float MH=10,ML=10,V=100;

uint8_t key1;
uint8_t display=0;
uint16_t time5s_lock_flag;
char PARA = 'R';
uint8_t P_lock;

uint8_t led_show=0x01;

uint32_t capture_value;
uint32_t freqency;
uint32_t temp_freqency;

float temp_v=0;
uint32_t last_v;

uint16_t keep_time;
uint8_t keep_time_flag;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

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
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM17_Init();
  MX_ADC2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	LCD_Init();

	LCD_Clear(Black);
	
	HAL_TIM_Base_Start_IT(&htim17);
	HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	TIM2->CCR2 = 1250;
	
	HAL_ADC_Start(&hadc1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(time5s_lock_flag==0&&P_lock==0)
		{
			HAL_ADC_Start(&hadc2);
			P = (HAL_ADC_GetValue(&hadc2)/4096.f)*100;
			if(P>85)
			{
				P=85;
			}else if(P<10)
			{
				P=10;
			}
			TIM2->CCR2=(TIM2->ARR)*(P/100.f);
		}
		switch(display)
		{
			case 0:
			{
				{
					
					if(time5s_lock_flag==0)
					{
						LED_display(led_show=led_show&(~(0x01<<1)),1);
					}
					LCD_SetBackColor(Black);
					LCD_SetTextColor(White);
					char temp_show[30];
					sprintf(temp_show,"        DATA ");
					LCD_DisplayStringLine(Line1,(unsigned char *)temp_show);
					sprintf(temp_show,"     freq:%d ",freqency);
					LCD_DisplayStringLine(Line2,(unsigned char *)temp_show);
					sprintf(temp_show,"     M = %c ",M);
					LCD_DisplayStringLine(Line3,(unsigned char *)temp_show);
					sprintf(temp_show,"     P = %d%% ",P);
					LCD_DisplayStringLine(Line4,(unsigned char *)temp_show);
					sprintf(temp_show,"     V = %.1f",V);
					LCD_DisplayStringLine(Line5,(unsigned char *)temp_show);
					
					sprintf(temp_show,"     T = %ds ",time5s_lock_flag/100);
					LCD_DisplayStringLine(Line6,(unsigned char *)temp_show);
					
					sprintf(temp_show,"     P_lock = %d ",P_lock);
					LCD_DisplayStringLine(Line7,(unsigned char *)temp_show);
					
					sprintf(temp_show,"     CCR2 = %d ",TIM2->CCR2);
					LCD_DisplayStringLine(Line8,(unsigned char *)temp_show);
					sprintf(temp_show,"     ARR = %d ",TIM2->ARR);
					LCD_DisplayStringLine(Line9,(unsigned char *)temp_show);
					
					if(key1==11)
					{
						LED_display(led_show=(led_show&(~0x01)),1);
						LED_display(led_show=led_show&(~(0x01<<1)),1);
						key1 = 0;
						display++;
						temp_R = R;temp_K = K;
						if(display>2)
						{
							display=0;
						}
						LCD_Clear(Black);
					}else if(key1==21)
					{
						key1 = 0;
						
						if(M=='H'&&time5s_lock_flag==0)
						{
							N++;
							time5s_lock_flag=500;
							M = 'L';
						}else if(M=='L'&&time5s_lock_flag==0)
						{
							N++;
							time5s_lock_flag=500;
							M = 'H';
						}
					}
					else if(key1==41)
					{
						key1 = 0;
						if(P_lock==1)
						{
							LED_display(led_show=(led_show&~(0x01<<2)),1);
							P_lock = 0;
						}
					}
					else if(key1==42)
					{
						key1 = 0;
						if(P_lock==0)
						{
							LED_display(led_show=(led_show|0x04),1);
							P_lock =1;
						}
					}
						
				}
			}break;
			case 1:
			{
				{
					
					LCD_SetBackColor(Black);
					LCD_SetTextColor(White);
					char temp_show[30];
					sprintf(temp_show,"        PARA ");
					LCD_DisplayStringLine(Line1,(unsigned char *)temp_show);
					sprintf(temp_show,"     R = %d ",temp_R);
					LCD_DisplayStringLine(Line3,(unsigned char *)temp_show);
					sprintf(temp_show,"     K = %d ",temp_K);
					LCD_DisplayStringLine(Line4,(unsigned char *)temp_show);
					sprintf(temp_show,"     cur PARA = %c ",PARA);
					LCD_DisplayStringLine(Line5,(unsigned char *)temp_show);
					if(key1==11)
					{
						key1 = 0;
						LED_display(led_show=(led_show&(~0x01)),1);
						display++;
						R = temp_R; K = temp_K;
						if(display>2)
						{
							display=0;
						}
						LCD_Clear(Black);
					}else if(key1==21)
					{
						key1 = 0;
						if(PARA=='R')
						{
							PARA='K';
						}else if(PARA=='K')
						{
							PARA='R';
						}
					}
					else if(key1==31)
					{
						key1 = 0;
						if(PARA=='R')
						{
							temp_R++;
							if(temp_R>10)
								temp_R = 1;
						}else if(PARA=='K')
						{
							temp_K++;
							if(temp_K>10)
								temp_K = 1;
						}
					}
					else if(key1==41)
					{
						key1 = 0;
						if(PARA=='R')
						{
							temp_R--;
							if(temp_R<1)
								temp_R = 10;
						}else if(PARA=='K')
						{
							temp_K--;
							if(temp_K<1)
								temp_K = 10;
						}
					}						
				}
			}break;
			case 2:
			{
						LCD_SetBackColor(Black);
						LCD_SetTextColor(White);
						char temp_show[30];
						sprintf(temp_show,"        RECD ");
						LCD_DisplayStringLine(Line1,(unsigned char *)temp_show);
						sprintf(temp_show,"     N = %d ",N);
						LCD_DisplayStringLine(Line3,(unsigned char *)temp_show);
						sprintf(temp_show,"     MH = %.1f ",MH);
						LCD_DisplayStringLine(Line4,(unsigned char *)temp_show);
						sprintf(temp_show,"     ML = %.1f ",ML);
						LCD_DisplayStringLine(Line5,(unsigned char *)temp_show);
						sprintf(temp_show,"     Key = %d ",key1);
						LCD_DisplayStringLine(Line6,(unsigned char *)temp_show);
					
						if(key1==11)
						{
							key1 = 0;
							LED_display(led_show=(led_show|0x01),1);
							display++;
							if(display>2)
							{
								display=0;
							}
							LCD_Clear(Black);
						}
			}break;
			
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3)
	{
		capture_value = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_2);
		freqency = 80000000/(80*capture_value);
		TIM3 ->CNT =0;
		V = ((freqency*6.28f*R)/(100*K));
		if(M=='L')
		{
			if(V>ML)
			{
				keep_time_flag=1;
			}else
			{
				keep_time=0;
				keep_time_flag=0;
			}
			
			if(keep_time>200)
			{
				keep_time=0;
				ML=V;
			}
		}
		else if(M=='H')
		{
			if(V>MH)
			{
				keep_time_flag=1;
			}else
			{
				keep_time=0;
				keep_time_flag=0;
			}
			
			if(keep_time>200)
			{
				keep_time=0;
				MH=V;
			}
		}
		
	}
	
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

#ifdef  USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
