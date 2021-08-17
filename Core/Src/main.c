/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define BLINK_WHITE_LED_INTERVAL		500

typedef struct st_AP_INFO {
	uint8_t szSSID[64];
	uint8_t szPassword[64];
	uint32_t portNum;
} APINFO, *PAPINFO;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

APINFO apInfo = { "WIFI_2.4G", "1234567890", 7890 };

uint32_t board_id_ = 0;
uint32_t blink_white_led_tick_ = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void BlinkWhiteLED(uint32_t _current_tick);
void CheckSwitchLED();
uint32_t GetBoardID();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t current_tick_ = 0;
	uint32_t display_time_tick_ = 0;
	uint32_t check_reservation_tick_ = 0;
	uint32_t test_cdc_tick_ = 0;

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
  MX_TIM4_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(LED1_WHITE_GPIO_Port, LED1_WHITE_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED2_RED_GPIO_Port, LED2_RED_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED3_BLUE_GPIO_Port, LED3_BLUE_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED4_YELLOW_GPIO_Port, LED4_YELLOW_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED5_GREEN_GPIO_Port, LED5_GREEN_Pin, GPIO_PIN_SET);

  HAL_TIM_Base_Start_IT(&htim4);

#if 1

	board_id_ = GetBoardID();

  //////////////////////////////////////////////////////////////////////////////////////
  // UART ????????? ?????????.
  HAL_UART_Receive_IT(&huart1, &gUarts[UART_ESP12].rxChar, 1);
  //HAL_UART_Receive_IT(&huart2, &gUarts[UART_TEMP_HUM].rxChar, 1);
  //HAL_UART_Receive_IT(&huart3, &gUarts[UART_DUST].rxChar, 1);
  //HAL_UART_Receive_IT(&huart4, &gUarts[UART_VIBRATION].rxChar, 1);
  //HAL_UART_Receive_IT(&huart5, &gUarts[UART_UV].rxChar, 1);
  //HAL_UART_Receive_IT(&huart6, &gUarts[UART_TENSIOIN].rxChar, 1);

  //////////////////////////////////////////////////////////////////////////////////////
  // WiFi Module??? 초기??? ???.
  HAL_GPIO_WritePin(ESP_nRESET_GPIO_Port, ESP_nRESET_Pin, GPIO_PIN_SET);
  //////////////////////////////////////////////////////////////////////////////////////


#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */



  while (1)
  {
	  current_tick_ = HAL_GetTick();

	  BlinkWhiteLED(current_tick_);

#if 0
      UART_RX_DefaultProc();
      UART_TX_DefaultProc();
#endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

#if 0
      if ((current_tick_ - test_cdc_tick_) > 1000) {
    	  test_cdc_tick_ = current_tick_;
    	  uint8_t buffer[100] = "CDC test string...\r\n";
    	  uint16_t string_length = 21;
    	  CDC_Transmit_FS(buffer, string_length);
      }
#endif

#if 0
      CheckSwitchLED();
#endif
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
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void BlinkWhiteLED(uint32_t _current_tick)
{
	if (BLINK_WHITE_LED_INTERVAL < (_current_tick - blink_white_led_tick_)) {
		blink_white_led_tick_ = _current_tick;
		HAL_GPIO_TogglePin(LED1_WHITE_GPIO_Port, LED1_WHITE_Pin);
	}
}

void CheckSwitchLED()
{
	GPIO_PinState tact_sw1_state = HAL_GPIO_ReadPin(TACT_SW1_GPIO_Port, TACT_SW1_Pin);
	GPIO_PinState tact_sw2_state = HAL_GPIO_ReadPin(TACT_SW2_GPIO_Port, TACT_SW2_Pin);
	GPIO_PinState dip_sw1_state = HAL_GPIO_ReadPin(DIP_SW1_GPIO_Port, DIP_SW1_Pin);
	GPIO_PinState dip_sw2_state = HAL_GPIO_ReadPin(DIP_SW2_GPIO_Port, DIP_SW2_Pin);
	GPIO_PinState dip_sw3_state = HAL_GPIO_ReadPin(DIP_SW3_GPIO_Port, DIP_SW3_Pin);
	GPIO_PinState dip_sw4_state = HAL_GPIO_ReadPin(DIP_SW4_GPIO_Port, DIP_SW4_Pin);

	if ((GPIO_PIN_RESET == tact_sw1_state) || (GPIO_PIN_RESET == tact_sw2_state))  {
		  HAL_GPIO_WritePin(LED1_WHITE_GPIO_Port, LED1_WHITE_Pin, GPIO_PIN_RESET);
	}
	else {
		  HAL_GPIO_WritePin(LED1_WHITE_GPIO_Port, LED1_WHITE_Pin, GPIO_PIN_SET);
	}

	if (GPIO_PIN_RESET == dip_sw1_state) {
		HAL_GPIO_WritePin(LED2_RED_GPIO_Port, LED2_RED_Pin, GPIO_PIN_RESET);
	}
	else {
		  HAL_GPIO_WritePin(LED2_RED_GPIO_Port, LED2_RED_Pin, GPIO_PIN_SET);
	}

	if (GPIO_PIN_RESET == dip_sw2_state) {
		  HAL_GPIO_WritePin(LED3_BLUE_GPIO_Port, LED3_BLUE_Pin, GPIO_PIN_RESET);
	}
	else {
		  HAL_GPIO_WritePin(LED3_BLUE_GPIO_Port, LED3_BLUE_Pin, GPIO_PIN_SET);
	}

	if (GPIO_PIN_RESET == dip_sw3_state) {
		  HAL_GPIO_WritePin(LED4_YELLOW_GPIO_Port, LED4_YELLOW_Pin, GPIO_PIN_RESET);
	}
	else {
		  HAL_GPIO_WritePin(LED4_YELLOW_GPIO_Port, LED4_YELLOW_Pin, GPIO_PIN_SET);
	}

	if (GPIO_PIN_RESET == dip_sw4_state) {
		  HAL_GPIO_WritePin(LED5_GREEN_GPIO_Port, LED5_GREEN_Pin, GPIO_PIN_RESET);
	}
	else {
		  HAL_GPIO_WritePin(LED5_GREEN_GPIO_Port, LED5_GREEN_Pin, GPIO_PIN_SET);
	}
}

uint32_t GetBoardID()
{
	uint32_t _board_id = 0;

	if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(DIP_SW1_GPIO_Port, DIP_SW1_Pin)) {
		_board_id |= 0x01;
	}

	if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(DIP_SW2_GPIO_Port, DIP_SW2_Pin)) {
		_board_id |= 0x02;
	}

	if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(DIP_SW3_GPIO_Port, DIP_SW3_Pin)) {
		_board_id |= 0x04;
	}

	if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(DIP_SW4_GPIO_Port, DIP_SW4_Pin)) {
		_board_id |= 0x08;
	}

	return _board_id;
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
