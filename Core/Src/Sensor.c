
/* Includes ------------------------------------------------------------------*/

#include "Sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>	// va_list
#include <string.h>


SDP	sdp;


void InitSensor(uint16_t _boardID)
{
	sdp.updateFlag = 0;
	sdp.boardID = _boardID;
	sdp.sequenceID = 1;
	sdp.temperature = 0.0f;
	sdp.humidity = 0.0f;
	sdp.tension = 0;
	sdp.UV = 0.0f;
	sdp.dustPM1_0 = 0;
	sdp.dustPM2_5 = 0;
	sdp.dustPM10_0 = 0;
	sdp.curVibration = 0;
	sdp.minVibration = 0;
	sdp.maxVibration = 0;
}

uint32_t IsUpdatedSensorFlag()
{
	return (0 != sdp.updateFlag);
}

void ClearSensorFlag()
{
	sdp.updateFlag = 0;
}

uint32_t MakeSensorPacket(char *packet, uint32_t size)
{
	if ((NULL == packet) || (0 == size)) {
		return 0;
	}

	sprintf(packet, "[%03d,%08d,%4.1f,%4.1f,%d,%4.1f,%05d,%05d,%05d,%d,%d,%d]",
			sdp.boardID,
			sdp.sequenceID,
			sdp.temperature,
			sdp.humidity,
			sdp.tension,
			sdp.UV,
			sdp.dustPM1_0,
			sdp.dustPM2_5,
			sdp.dustPM10_0,
			sdp.curVibration,
			sdp.minVibration,
			sdp.maxVibration);
	
	sdp.sequenceID++;
	
	return 1;
}

/*
	DHT22, Connect error, 0.0, 0.0
	��DHT22, Connect error, 0.0, 0.0
	DHT22, OK, 62.9, 26.4
	HT22, OK, 63.0, 26.4
	DHT22, OK, 62.9, 26.4
	DHT22, OK, 62.7, 26.4
*/
uint32_t ParsingTempHum(const uint8_t *str, uint32_t len)
{
	char *p1 = NULL; 
	char *p2 = NULL; 

	if(NULL == str) return 0;

	p1 = strstr((const char*)str,  "OK, ");
	if(NULL == p1) return 0;

	p1 += 4;

	p2 = strchr((const char*)(p1+1), ',');
	if(NULL == p2) return 0;
	
	p2 += 2;
	
	//float fHum = atof((const char*)p1);
	//float fTemp = atof((const char*)p2); 
	sdp.humidity = atof((const char*)p1);
	sdp.temperature  = atof((const char*)p2); 
	sdp.updateFlag |= (UPDATED_TEMPERATURE | UPDATED_HUMIDITY);

	return 1;
}


/*
492
544
549
545
267
240
251
257
480
480
481
*/

uint32_t ParsingTension(const uint8_t *str, uint32_t len)
{
	//uint8_t* p1 = NULL; 
	//uint32_t nValue = 0;

	if(NULL == str) return 0;

	//nValue = atoi((const char*)str);
	sdp.tension = atoi((const char*)str);
	sdp.updateFlag |= UPDATED_TENSION;
	
	return 1;
}


/*
ML8511 example
output: 999, ML8511 output: 102, ML8511 voltage: 0.34, UV Intensity (mW/cm^2): -5.41
output: 998, ML8511 output: 149, ML8511 voltage: 0.49, UV Intensity (mW/cm^2): -4.12
output: 1010, ML8511 output: 224, ML8511 voltage: 0.73, UV Intensity (mW/cm^2): -2.14
output: 997, ML8511 output: 268, ML8511 voltage: 0.89, UV Intensity (mW/cm^2): -0.85
output: 1007, ML8511 output: 313, ML8511 voltage: 1.03, UV Intensity (mW/cm^2): 0.30
output: 993, ML8511 output: 364, ML8511 voltage: 1.21, UV Intensity (mW/cm^2): 1.82
output: 998, ML8511 output: 517, ML8511 voltage: 1.71, UV Intensity (mW/cm^2): 5.96
*/
uint32_t ParsingUV(const uint8_t *str, uint32_t len)
{
	char *p1 = NULL; 

	if(NULL == str) return 0;

	p1 = strstr((const char*)str,  "(mW/cm^2): ");
	if(NULL == p1) return 0;

	p1 += 11;
	
	//float fUV = atof((const char*)p1);
	sdp.UV = atof((const char*)p1);
	sdp.updateFlag |= UPDATED_UV;
	
	return 1;
}


/*

42 4D 00 1C 00 0A 00 0D 00 0E 00 0A 00 0D 00 0E 
09 3F 03 2F 00 96 00 0B 00 02 00 00 00 00 02 12 
03 2F 00 96 42 4D 00 1C 00 0A 00 0D 00 0E 00 0A 
00 00 0D 00 0E 09 3F 03 2F 00 96 00 0B 00 02 00 
00 00 00 02 12 0B 00 02 00 00 00 00 02 12 42 4D 
00 1C 00 0A 00 0D 00 0E 00 0A 00 0D 00 0E 09 3F 
03 2F 00 96 00 0B 00 02 00 00 00 00 02 12 42 4D 
00 1C 00 0A 00 0D 00 0E 00 0A 00 0D 00 0E 09 3F 
03 2F 00 96 00 0B 00 02 00 00 00 00 02 12 42 4D 
00 1C 00 0A 00 0D 00 0E 00 0A 00 0D 00 0E 09 3F 
03 2F 00 96 00 0B 00 02 00 00 00 00 02 12 42 4D 
00 1C 00 0A 00 0D 00 0E 00 0A 00 0D 00 0E 09 3F 
03 2F 00 96 00 0B 00 02 00 00 00 00 02 12 42 4D 
00 1C 00 0A 00 0D 00 0E 00 0A 00 0D 00 0E 09 3F 
03 2F 00 96 00 0B 00 02 00 00 00 00 02 12


Serial.print("Dust raw data debugging :  ");
Serial.print("1.0ug/m3:");
Serial.print(pms[10]);
Serial.print(pms[11]);
Serial.print("	");
Serial.print("2.5ug/m3:");
Serial.print(pms[12]);
Serial.print(pms[13]);
Serial.print("	");
Serial.print("2.5ug/m3:");
Serial.print(pms[14]);
Serial.println(pms[15]);

*/
uint32_t ParsingDust(const uint8_t *str, uint32_t len)
{
	uint8_t *p1 = (uint8_t*)str;
	PDSD pDsd = (PDSD)str;
	uint16_t _checksum = 0;
	
	if (NULL == p1) return 0;
	
	for(int i=0; i<(MAX_DUST_DATA_COUNT-2); i++){
		_checksum += *p1++;
    }

    //if(pDsd->checksum != _checksum) {
    if ((pDsd->hi_checksum != (_checksum >> 8)) &&
		(pDsd->lo_checksum != (_checksum & 0xFF))) {
		return 0;
    }
	
    if((0x42 != pDsd->frameHeader[0]) || (0x4d != pDsd->frameHeader[1])) {
		return 0;
    }

	//uint16_t concPM1_0_amb = pDsd->concPM1_0_amb;
	//uint16_t concPM2_5_amb = pDsd->concPM2_5_amb;
	//uint16_t concPM10_0_amb = pDsd->concPM10_0_amb;	
	sdp.dustPM1_0 = pDsd->concPM1_0_amb;
	sdp.dustPM2_5 = pDsd->concPM2_5_amb;
	sdp.dustPM10_0 = pDsd->concPM10_0_amb;	
	sdp.updateFlag |= UPDATED_DUST;
	
	return 1;
}

/*

@Vi215,34,0,0,4
@Vi215,35,0,0,4
@Vi215,36,1023,0,1023
@Vi215,37,873,0,1023
@Vi215,38,12,0,1023
@Vi215,39,121,0,1023
@Vi215,40,0,0,1023
@Vi215,41,0,0,1023
*/
uint32_t ParsingVibration(const uint8_t *str, uint32_t len)
{
	char* p1 = NULL; 
	uint32_t _index = 0;
	//uint32_t _min = 0, _current = 0, _max = 0;
	const char _seperator[] = ",\r\n";
	
	if(NULL == str) return 0;

    p1 = strtok((char*)str, _seperator);      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ

    while (NULL != p1) {
		if (2 == _index) {
			//_cur = atoi((const char*)p1);
			sdp.curVibration  = atoi((const char*)p1);
			sdp.updateFlag |= UPDATED_VIBRATION;
		}
		else if (3 == _index) {
			//_min = atoi((const char*)p1);
			sdp.minVibration  = atoi((const char*)p1);
			sdp.updateFlag |= UPDATED_VIBRATION;
		}
		else if (4 == _index) {
			//_max = atoi((const char*)p1);
			sdp.maxVibration  = atoi((const char*)p1);
			sdp.updateFlag |= UPDATED_VIBRATION;
			break;
		}
        //printf("%s\n", ptr);          // �ڸ� ���ڿ� ���
        p1 = strtok(NULL, _seperator);      // ���� ���ڿ��� �߶� �����͸� ��ȯ
        _index++;
    }

	return 1;
}

