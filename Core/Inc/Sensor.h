/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SENSOR_H_
#define __SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "CircularQueue.h"
/* USER CODE END Includes */


#define MAX_DUST_DATA_COUNT  32


#if 0

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

#endif

typedef struct _SENSOR_TEMPERATURE_HUMIDITY_INFO {
	float fHumidity;
	float fTemperature;
} STHI, *PSTHI;



typedef struct _DUST_SENSOR_DATA {
	uint8_t frameHeader[2];
	uint16_t frameLen;		//MAX_DUST_DATA_COUNT;
	uint16_t concPM1_0_CF1;
	uint16_t concPM2_5_CF1;
	uint16_t concPM10_0_CF1;
	uint16_t concPM1_0_amb;
	uint16_t concPM2_5_amb;
	uint16_t concPM10_0_amb;
	uint16_t rawGt0_3um;
	uint16_t rawGt0_5um;
	uint16_t rawGt1_0um;
	uint16_t rawGt2_5um;
	uint16_t rawGt5_0um;
	uint16_t rawGt10_0um;
	uint8_t version;
	uint8_t errorCode;
	uint16_t checksum;
} DSD, *PDSD;


uint32_t ParsingTempHum(const uint8_t *str, uint32_t len);
uint32_t ParsingTension(const uint8_t *str, uint32_t len);
uint32_t ParsingUV(const uint8_t *str, uint32_t len);
uint32_t ParsingDust(const uint8_t *str, uint32_t len);
uint32_t ParsingVibration(const uint8_t *str, uint32_t len);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_H_ */



