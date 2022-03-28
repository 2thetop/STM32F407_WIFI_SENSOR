/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "CircularQueue.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

/* USER CODE BEGIN Private defines */
#define UART_RECEIVE_TIMEOUT	300

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#if 0

typedef enum {
	UART_NONE=-1,
	UART_P1,
	UART_P2,
	UART_P3,
	UART_P4,
	UART_P5,
	UART_P6,
 	UART_LAST,
	MAX_UART_PORT = UART_LAST,
	UART_VCP=UART_LAST,
	UART_CDC=UART_LAST,
	UART_ESP12=UART_P1,
	UART_TEMP_HUM=UART_P2,
	UART_DUST=UART_P3,
	UART_VIBRATION=UART_P4,
	UART_UV=UART_P5,
	UART_TENSIOIN=UART_P6,
	UART_DEBUG=UART_VCP,
} UART_TYPE;

#else

typedef enum {
	UART_NONE=-1,
	UART_P1=0,
	UART_P2,
	UART_P3,
	UART_P4,
	UART_P5,
	UART_P6,
	UART_VCP,
	UART_CDC=UART_VCP,
 	UART_LAST,
	MAX_UART_PORT = UART_LAST,
	UART_ESP12=UART_P1,
	UART_TEMP_HUM=UART_P2,
	UART_TENSION=UART_P3,
	UART_UV=UART_P4,
	UART_DUST=UART_P5,
	UART_VIBRATION=UART_P6,
//#ifdef  __USE_UART6_FOR_DEBUG__
//	UART_DEBUG=UART_VIBRATION,
//#else
	UART_DEBUG=UART_VCP,
//#endif	
} UART_TYPE;

#endif

typedef enum {
	UART_BS=0x08,
	UART_LF=0x0A,
	UART_CR=0x0D,
	UART_ESCAPE=0x1B,
	UART_DEL=0x7F,
	UART_PLUS=0x2B,
} UART_CHAR;

typedef struct {
	CQ_BUFFER	rxQ;
	CQ_BUFFER	txQ;
	uint32_t 	isTransmitting;
	uint32_t	useReceiveTimeout;
	uint32_t 	isReceived;
	uint32_t	lastReceiveTime;
	uint32_t 	receiveTimout;
	uint32_t 	bufferIndex;
	uint8_t 	buffer[MAX_CQ_BUFFER_COUNT];
	uint8_t		rxChar;
	uint8_t		dummy[3];
	
} UART_Q, *PUART_Q;;

extern UART_Q gUarts[MAX_UART_PORT];

/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_UART5_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_USART6_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void UART_Init();

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void UART_TX_DefaultProc(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void UART_RX_DefaultProc(void);


void UartChar(UART_TYPE ut, const int8_t _ch);
uint32_t UartPuts(UART_TYPE ut, const int8_t *str, int32_t len);
void UartPrintf(UART_TYPE ut, const int8_t *fmt, ...);
void HAL_UART_LoopbackTest(void);
void HAL_UART_BypassTest(void);
void UART_CheckReceiveTimeout(void);
uint32_t SendSensorPacketByWiFi(uint8_t *str, uint32_t len);

uint32_t ParsingTempHum(const uint8_t *str, uint32_t len);
uint32_t ParsingTension(const uint8_t *str, uint32_t len);
uint32_t ParsingUV(const uint8_t *str, uint32_t len);
uint32_t ParsingDust(const uint8_t *str, uint32_t len);
uint32_t ParsingVibration(const uint8_t *str, uint32_t len);


void ProcCommand(UART_TYPE ut, const int8_t _ch);

//void MakeHelpString(char* buffer, int size);
void SendHelpString();
//void MakeConfigString(PCDI pcdi, char* buffer, int size);
void SendString(char* buffer);


void ExtractString(char const* src, char *dest, int dest_size);
void ExtractNumber(char const* src, uint16_t* dest);
void GetSSID(char const* buffer, char *ssid);
void GetPassword(char const* buffer, char *password);
void GetHost(char const* buffer, char *host);
void GetPort(char const* buffer, uint16_t port);
	

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
