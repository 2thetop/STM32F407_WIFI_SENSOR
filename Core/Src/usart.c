/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <stdarg.h>	// va_list
//#include "console.h"

UART_Q gUarts[MAX_UART_PORT];
UART_HandleTypeDef *pUartHandleArray[MAX_UART_PORT];

/* USER CODE END 0 */

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

/* UART4 init function */
void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}
/* UART5 init function */
void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 9600;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}
/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspInit 0 */

  /* USER CODE END UART4_MspInit 0 */
    /* UART4 clock enable */
    __HAL_RCC_UART4_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**UART4 GPIO Configuration
    PA0-WKUP     ------> UART4_TX
    PA1     ------> UART4_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN UART4_MspInit 1 */

  /* USER CODE END UART4_MspInit 1 */
  }
  else if(uartHandle->Instance==UART5)
  {
  /* USER CODE BEGIN UART5_MspInit 0 */

  /* USER CODE END UART5_MspInit 0 */
    /* UART5 clock enable */
    __HAL_RCC_UART5_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**UART5 GPIO Configuration
    PC12     ------> UART5_TX
    PD2     ------> UART5_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN UART5_MspInit 1 */

  /* USER CODE END UART5_MspInit 1 */
  }
  else if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */
    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspDeInit 0 */

  /* USER CODE END UART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART4_CLK_DISABLE();

    /**UART4 GPIO Configuration
    PA0-WKUP     ------> UART4_TX
    PA1     ------> UART4_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1);

  /* USER CODE BEGIN UART4_MspDeInit 1 */

  /* USER CODE END UART4_MspDeInit 1 */
  }
  else if(uartHandle->Instance==UART5)
  {
  /* USER CODE BEGIN UART5_MspDeInit 0 */

  /* USER CODE END UART5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART5_CLK_DISABLE();

    /**UART5 GPIO Configuration
    PC12     ------> UART5_TX
    PD2     ------> UART5_RX
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

  /* USER CODE BEGIN UART5_MspDeInit 1 */

  /* USER CODE END UART5_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();

    /**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void UART_Init()
{
	MX_UART4_Init();
	MX_UART5_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	MX_USART6_UART_Init();

	//gUarts[UART_P1] =

	pUartHandleArray[UART_ESP12] = &huart1;
	pUartHandleArray[UART_TEMP_HUM] = &huart2;
	pUartHandleArray[UART_DUST] = &huart3;
	pUartHandleArray[UART_VIBRATION] = &huart4;
	pUartHandleArray[UART_UV] = &huart5;
	pUartHandleArray[UART_TENSIOIN] = &huart6;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	PUART_Q pUartQ;

		  if(USART1 == huart->Instance)  pUartQ = &gUarts[UART_ESP12];
	 else if(USART2 == huart->Instance)  pUartQ = &gUarts[UART_TEMP_HUM];
	 else if(USART3 == huart->Instance)  pUartQ = &gUarts[UART_DUST];
	 else if(UART4 == huart->Instance)	 pUartQ = &gUarts[UART_VIBRATION];
	 else if(UART5 == huart->Instance)	 pUartQ = &gUarts[UART_UV];
	 else if(USART6 == huart->Instance)  pUartQ = &gUarts[UART_TENSIOIN];
	 else return;

	uint32_t _savedCount = CQ_GetDataCount(&pUartQ->txQ);
	if(0 < _savedCount) {
		uint32_t _transmitCount = CQ_PopString(&pUartQ->txQ, pUartQ->txBuffer, _savedCount);
		HAL_UART_Transmit_IT(huart, pUartQ->txBuffer, _transmitCount);
		pUartQ->isTransmitting = 1;
	}
	else {
		pUartQ->isTransmitting = 0;
	}
}

void UART_TX_DefaultProc(void)
{
	PUART_Q pUartQ;
	uint32_t _savedCount;
	uint32_t _transmitCount;

#if 0
	pUartQ = &gUarts[UART_ESP12];
	if(0 == CQ_IsEmpty(&pUartQ->txQ)) {
		if(0 == pUartQ->isTransmitting) {
			_savedCount = CQ_GetDataCount(&pUartQ->txQ);
			_transmitCount = CQ_PopString(&pUartQ->txQ, pUartQ->txBuffer, _savedCount);
			HAL_UART_Transmit_IT(&huart2, pUartQ->txBuffer, _transmitCount);
			pUartQ->isTransmitting = 1;
		}
	}

	pUartQ = &gUarts[UART_DEBUG];
	if(0 == CQ_IsEmpty(&pUartQ->txQ)) {
		if(0 == pUartQ->isTransmitting) {
			_savedCount = CQ_GetDataCount(&pUartQ->txQ);
			_transmitCount = CQ_PopString(&pUartQ->txQ, pUartQ->txBuffer, _savedCount);
			HAL_UART_Transmit_IT(&huart3, pUartQ->txBuffer, _transmitCount);
			pUartQ->isTransmitting = 1;
		}
	}
#else
	UART_HandleTypeDef *phuart;

	for(int i = 0; i < MAX_UART_PORT; i++) {
		phuart = pUartHandleArray[i];
		pUartQ = &gUarts[i];
		
		if(0 == CQ_IsEmpty(&pUartQ->txQ)) {
			if(0 == pUartQ->isTransmitting) {
				_savedCount = CQ_GetDataCount(&pUartQ->txQ);
				_transmitCount = CQ_PopString(&pUartQ->txQ, pUartQ->txBuffer, _savedCount);
				HAL_UART_Transmit_IT(phuart, pUartQ->txBuffer, _transmitCount);
				pUartQ->isTransmitting = 1;
			}
		}
	}
#endif
	
}


void UART_RX_DefaultProc(void)
{
	PUART_Q pUartQ;
	uint32_t _receiveCount;
	uint8_t _ch;

	pUartQ = &gUarts[UART_ESP12];
	PCQ_BUFFER pRxQ = &pUartQ->rxQ;

	if(0 == CQ_IsEmpty(pRxQ)) {
		_receiveCount = CQ_GetDataCount(pRxQ);
		for(uint32_t j=0; j<_receiveCount; j++) {
			CQ_PopChar(pRxQ, &_ch);
			UartChar(UART_DEBUG, _ch);
			//WiFi_ParsingProc(UART_ESP12, _ch);
			putchar(_ch);
		}
	}

	pUartQ = &gUarts[UART_DEBUG];
	pRxQ = &pUartQ->rxQ;

	if(0 == CQ_IsEmpty(pRxQ)) {
		_receiveCount = CQ_GetDataCount(pRxQ);
		for(uint32_t j=0; j<_receiveCount; j++) {
			CQ_PopChar(pRxQ, &_ch);
			UartChar(UART_ESP12, _ch);
		}
	}
}


/**
  * @brief Rx Transfer completed callback.
  * @param huart: UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	PUART_Q pUartQ;

         if(USART1 == huart->Instance)	pUartQ = &gUarts[UART_ESP12];
	else if(USART2 == huart->Instance)	pUartQ = &gUarts[UART_TEMP_HUM];
    else if(USART3 == huart->Instance)	pUartQ = &gUarts[UART_DUST];
	else if(UART4 == huart->Instance)	pUartQ = &gUarts[UART_VIBRATION];
	else if(UART5 == huart->Instance)	pUartQ = &gUarts[UART_UV];
	else if(USART6 == huart->Instance)	pUartQ = &gUarts[UART_TENSIOIN];
	else return;

	CQ_PushChar(&pUartQ->rxQ, pUartQ->rxChar);
	HAL_UART_Receive_IT(huart, &pUartQ->rxChar, 1);
}

void UartChar(UART_TYPE ut, const int8_t _ch)
{
	PCQ_BUFFER pQ = &gUarts[ut].txQ;

	if(0 == CQ_IsFull(pQ))	{
		CQ_PushChar(pQ, _ch);
	}
}


uint32_t UartPuts(UART_TYPE ut, const int8_t *str, int32_t len)
{
	uint32_t _copyCount = 0;
	uint32_t _freeCount = 0;

	if (len) {
		PCQ_BUFFER pQ = &gUarts[ut].txQ;

		_freeCount = CQ_GetFreeCount(pQ);
		_copyCount = (len < _freeCount) ? len:_freeCount;

		CQ_PushString(pQ,(uint8_t*)str,_copyCount);

		if(UART_DEBUG == ut) {
			printf((const char*)str);
		}
	}

	return _copyCount;
}

void UartPrintf(UART_TYPE ut, const int8_t *fmt, ...)
{
	va_list args;
	int len;
	int8_t _szFmt[128] = {0};

	va_start(args, fmt);
	len = vsprintf((char*)_szFmt, (const char*)fmt, args);
	_szFmt[len] = NULL;
	va_end(args);

	UartPuts(ut, _szFmt, len);
}

uint8_t uartBuffer_[MAX_CQ_BUFFER_COUNT];

void HAL_UART_LoopbackTest(void)
{
	PUART_Q pUartQ;

	pUartQ = &gUarts[UART_ESP12];
	if(0 == pUartQ->isTransmitting) {
		uint32_t _receiveCount = CQ_GetDataCount(&pUartQ->rxQ);
		if(0 < _receiveCount) {
			uint32_t _copiedCount = CQ_PopString(&pUartQ->rxQ, uartBuffer_, _receiveCount);
			CQ_PushString(&pUartQ->txQ, uartBuffer_, _copiedCount);
		}
	}

	pUartQ = &gUarts[UART_DEBUG];
	if(0 == pUartQ->isTransmitting) {
		uint32_t _receiveCount = CQ_GetDataCount(&pUartQ->rxQ);
		if(0 < _receiveCount) {
			uint32_t _copiedCount = CQ_PopString(&pUartQ->rxQ, uartBuffer_, _receiveCount);
			CQ_PushString(&pUartQ->txQ, uartBuffer_, _copiedCount);
		}
	}
}


void HAL_UART_BypassTest(void)
{
	PUART_Q pUartQ1;
	PUART_Q pUartQ2;

	pUartQ1 = &gUarts[UART_ESP12];
	pUartQ2 = &gUarts[UART_DEBUG];

	if(0 == pUartQ2->isTransmitting) {
		uint32_t _receiveCount = CQ_GetDataCount(&pUartQ1->rxQ);
		if(0 < _receiveCount) {
			uint32_t _copiedCount = CQ_PopString(&pUartQ1->rxQ, uartBuffer_, _receiveCount);
			CQ_PushString(&pUartQ2->txQ, uartBuffer_, _copiedCount);
		}
	}

	if(0 == pUartQ1->isTransmitting) {
		uint32_t _receiveCount = CQ_GetDataCount(&pUartQ2->rxQ);
		if(0 < _receiveCount) {
			uint32_t _copiedCount = CQ_PopString(&pUartQ2->rxQ, uartBuffer_, _receiveCount);
			CQ_PushString(&pUartQ1->txQ, uartBuffer_, _copiedCount);
		}
	}
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
