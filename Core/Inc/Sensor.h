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
	uint8_t hi_checksum;
	uint8_t lo_checksum;
} DSD, *PDSD;



#define UPDATED_TEMPERATURE		0x0001
#define UPDATED_HUMIDITY		0x0002
#define UPDATED_TENSION			0x0004
#define UPDATED_UV				0x0008
#define UPDATED_DUST			0x0010
#define UPDATED_VIBRATION		0x0020

typedef struct _SENSOR_DATA_PACKET {
	uint16_t updateFlag;
	uint16_t boardID;
	uint32_t sequenceID;
	float temperature;
	float humidity;
	uint16_t tension;
	float UV;
	uint16_t dustPM1_0;
	uint16_t dustPM2_5;
	uint16_t dustPM10_0;
	uint16_t curVibration;
	uint16_t minVibration;
	uint16_t maxVibration;
} SDP, *PSDP;



void InitSensor(uint16_t _boardID);
uint32_t IsUpdatedSensorFlag();
void ClearSensorFlag();
uint32_t MakeSensorPacket(char *packet, uint32_t size);
uint32_t ParsingTempHum(const uint8_t *str, uint32_t len);
uint32_t ParsingTension(const uint8_t *str, uint32_t len);
uint32_t ParsingUV(const uint8_t *str, uint32_t len);
uint32_t ParsingDust(const uint8_t *str, uint32_t len);
uint32_t ParsingVibration(const uint8_t *str, uint32_t len);


extern SDP sdp;

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_H_ */



