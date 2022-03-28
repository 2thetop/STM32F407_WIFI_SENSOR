
/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "gpio.h"

#include "WiFi.h"
//#include "DS3231.h"
//#include "Light.h"

/* USER CODE BEGIN 0 */
#include "global_define.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>	// va_list
#include <string.h>
#include <time.h>
//#include "main_define.h"
#include "main.h"


#define __USE_MY_AP__
//#define __USE_IRENOX_AP__

#define MAX_COMMAND_LENGTH					64
#define MAX_RESPONSE_LEGTH					128

typedef struct PARSING_DATA_ITEM {
	uint32_t type;
	uint32_t id;
	int8_t* pstring;
	uint32_t length;
} PARSING_DATA, *PPARSING_DATA;


typedef struct WIFI_COMMUNICATION_ITEM {
	ESTATE	cmdType;
	ESTATE  cmdID;
	const int8_t *pstr;
	uint32_t responseLength;
} WIFI_COMM_ITEM, *PWIFI_COMM_ITEM;

typedef struct COMMAND_RESPONSE_ITEM {
	ESTATE  cmdID;
	const int8_t *pstr;
	uint32_t responseLength;
} CMD_RESP_ITEM, *PCMD_RESP_ITEM;

typedef struct AP_LIST_DATA {
	const char *ssid_ptr;
	const char *password_ptr;
	int32_t		ssid_length;
} ALD, *PALD;


#define MAX_AP_COUNT	3

// NTP Server Address List
/*
	"1.nl.pool.ntp.org"
	"time.nist.gov"
	"time.windows.com"
	"time.google.com"
	"1.kr.pool.ntp.org"
	"clock.iptime.co.kr"
*/
 
//nst int8_t szNTPServerAddress[] = "1.nl.pool.ntp.org";

// Test Server Address
const int8_t szTestServerAddress[] = "192.168.1.10";		//eroo@52.79.53.140 / oore!@#$
//const int8_t szTestServerAddress[] = "112.216.109.238"		// irenox server
const int32_t nTestServerPort = 7890;


// Device ID
//const int8_t szDeviceID[] = "a123456789";
const char szDeviceID[] = "a000000001";

// AP List
#ifdef __USE_MY_AP__		
const int8_t szSSID[] = "WIFI_AX";
const int8_t szPassword[] = "@i1topassi1top";

#elif defined __USE_IRENOX_AP__
const int8_t szSSID[] = "iptime";
const int8_t szPassword[] = "12345678890";
#endif


#define CHANNEL_NTP_SERVER		2
#define CHANNEL_TEST_SERVER		0

#define MAX_RESPONSE_TABLE_COUNT 		23
	
const WIFI_COMM_ITEM rspTable[MAX_RESPONSE_TABLE_COUNT] = {
	{ CMD_COMMON, RSP_OK, "OK\r\n", 4 },
	{ CMD_COMMON, RSP_CONNECT_OK, "CONNECT\r\n", 9 },
	{ CMD_COMMON, RSP_ALREADY_CONNECT, "ALREADEY CONNECTED\r\n", 20 },
	{ CMD_COMMON, RSP_SEND_OK, "SEND OK\r\n", 9 },
	{ CMD_COMMON, RSP_CLOSED_SERVER, "0,CLOSED\r\n", 10},
//	{ CMD_COMMON, RSP_CLOSED_NTP_SERVER, "2,CLOSED\r\n", 10},
	{ CMD_COMMON, RSP_INVALID_LINK,	"link is not valid\r\n", 19},

	{ CMD_COMMON, RSP_AP_FOUND_OK, "+CWLAP:", 7 },
#if 0
	{ CMD_COMMON, RSP_WAIT_NTP_PACKET_OK, "+IPD,2,48:", 9}, 	// Function 1 Command
		
	{ CMD_SEND_IDENTIFY_SERVER, RSP_FUNCTION_0, "+IPD,0,19:", 9},	// Function 0 Response
	{ CMD_COMMON, REQ_FUNCTION_1, "+IPD,0,18:", 9},	// Function 1 Command
	{ CMD_COMMON, REQ_FUNCTION_2, "+IPD,0,22:", 9},	// Function 2 Command
	{ CMD_COMMON, REQ_FUNCTION_3, "+IPD,0,23:", 9},	// Function 3 Command
	{ CMD_COMMON, REQ_FUNCTION_4, "+IPD,0,19:", 9},	// Function 4 Command
	{ CMD_COMMON, REQ_FUNCTION_5, "+IPD,0,29:", 9},	// Function 5 Command
#endif
	{ CMD_SET_MODE, RSP_SET_MODE_OK, "OK\r\n", 4 },
	{ CMD_ENABLE_MULTICONNECT, RSP_MULTICONNECT_OK, "OK\r\n", 4 },
	{ CMD_SETUP_SERVER, RSP_SERVER_OK, "OK\r\n", 4 },
	{ CMD_CONNECT_AP, RSP_GOT_IP, "WIFI GOT IP\r\n",  13},
//	{ CMD_CONNECT_SERVER, RSP_CONNECT_OK, "CONNECT\r\n", 9 },
	{ CMD_REQUEST_SEND_DATA, RSP_READY_TO_SEND, "OK\r\n", 4 },
	{ CMD_RESET, RSP_RESET_OK, "ready\r\n", 7 },
	{ CMD_RESET, RSP_GOT_IP, "WIFI GOT IP\r\n", 13 },
	{ CMD_RESET, RSP_CLOSED, "CLOSED\r\n", 8 },
};	

/*
#define MAX_ARDUINO_RESPONSE_TABLE_COUNT 		23
	
const WIFI_COMM_ITEM rspArduinoTable[MAX_ARDUINO_RESPONSE_TABLE_COUNT] = {
	{ CMD_COMMON, RSP_OK, "OK\r\n", 4 },
	{ CMD_COMMON, RSP_CONNECT_OK, "CONNECT\r\n", 9 },
	{ CMD_COMMON, RSP_ALREADY_CONNECT, "ALREADEY CONNECTED\r\n", 20 },
	{ CMD_COMMON, RSP_SEND_OK, "SEND OK\r\n", 9 },
	{ CMD_COMMON, RSP_CLOSED_SERVER, "0,CLOSED\r\n", 10},
//	{ CMD_COMMON, RSP_CLOSED_NTP_SERVER, "2,CLOSED\r\n", 10},
	{ CMD_COMMON, RSP_INVALID_LINK,	"link is not valid\r\n", 19},

	{ CMD_COMMON, RSP_AP_FOUND_OK, "+CWLAP:", 7 },

	{ CMD_SET_MODE, RSP_SET_MODE_OK, "OK\r\n", 4 },
	{ CMD_ENABLE_MULTICONNECT, RSP_MULTICONNECT_OK, "OK\r\n", 4 },
	{ CMD_SETUP_SERVER, RSP_SERVER_OK, "OK\r\n", 4 },
	{ CMD_CONNECT_AP, RSP_GOT_IP, "WIFI GOT IP\r\n",  13},
//	{ CMD_CONNECT_SERVER, RSP_CONNECT_OK, "CONNECT\r\n", 9 },
	{ CMD_REQUEST_SEND_DATA, RSP_READY_TO_SEND, "OK\r\n", 4 },
	{ CMD_RESET, RSP_RESET_OK, "ready\r\n", 7 },
	{ CMD_RESET, RSP_GOT_IP, "WIFI GOT IP\r\n", 13 },
	{ CMD_RESET, RSP_CLOSED, "CLOSED\r\n", 8 },
};	

"Starting WiFi..... "
"Waiting for new SSID & password within 5 seconds....."
"Connecting to "
"Wait for connecting WiFi AP... "
"WiFi AP is connected"

"Fail to connect to server"
"Close server connection"

"Succeed to connect to server"
"WiFi AP is disconnected..."
*/

//extern  time_t	timeRTC;


static ESTATE parsingResponse(UART_TYPE _uartType, int8_t *line, uint32_t count);

//static void CMD_InitBuffer(UART_TYPE _uartType);
//static void CMD_PushChar(UART_TYPE _uartType, uint8_t ch);
//static uint32_t CMD_GetBufferIndex(UART_TYPE _uartType);



//int32_t board_id_ = 1;


static CMDLINE_PACK cmdPack[MAX_UART_PORT];

volatile ESTATE gvReceiveMode = STATE_RECEIVE_MODE_INIT;
static int nTotalReceiveDataCount = 0;
static int nCurrentReceiveDataCount = 0;
static int nReceiveChannel = 0;
static uint8_t aReceiveDataCount[3] = { 0 };

//static TCPD	gTCPD;

static ESTATE_ARDUINO state_arduino_ = STATE_NO_WIFI;
static uint8_t cdi_updated_ = 0;
//static CDI cdi;
//static CDI cdi = { "WIFI_AX", "@i1topassi1top", "192.168.1.10", 7890, 6 };
//static CDI cdi = { "WIFI_2.4G", "@i1topassi1top", "192.168.31.10", 7890, 6 };
static CDI cdi = { "ir-SCADA", "ir123456", "192.168.0.30", 7890, 1 };
//"ssid:WIFI_AX,password:@i1topassi1top,host:192.168.1.10,port:7890,id:6"
//"ssid:ir-SCADA,password:ir123456,host:192.168.0.30,port:7890,id:4"

WSD	wsd;
SSD aSSD[4];

//NUD	nud;


void InitWiFi()
{
	InitWSD(&wsd);

	InitSSD(&aSSD[0]);
	InitSSD(&aSSD[1]);
	InitSSD(&aSSD[2]);
	InitSSD(&aSSD[3]);
}


void InitWSD(PWSD pWSD)
{
	pWSD->state_ = STATE_NOT_INIT;
	
	pWSD->last_sent_command_ = CMD_NONE;
	
	pWSD->watchdog_send_interval_ = DATA_SEND_TIMEOUT_INTERVAL;
	pWSD->last_watchdog_send_tick_ = 0;
	pWSD->is_set_watchdog_send_ = 0;
	pWSD->is_enabled_watchdog_send_ = 0;
	
	pWSD->is_waiting_wifi_response_ = 0;
	pWSD->wifi_command_interval_ = 10000;
	pWSD->last_wifi_command_tick_ = 0;
	pWSD->wifi_command_retry_count_ = 0;
	pWSD->wifi_command_retry_count_limit_ = 5;
	
	pWSD->is_delaying_wifi_command_ = 0;
	pWSD->wifi_command_delay_ = 5000;
	pWSD->wifi_command_delay_tick_ = 0;
	
	pWSD->wifi_command_recoonect_count_ = 0;
	pWSD->wifi_command_recoonect_count_limit_ = 5;

	//pWSD->ntp_server_connected_ = 0;
	//pWSD->ntp_read_ = 0;
	
	pWSD->server_connected_ = 0;
	pWSD->server_identified_ = 0;

	//pWSD->ntp_retry_count_ = 0;
	//pWSD->max_ntp_retry_count_ = 5;

	//pWSD->last_ntp_time_tick_ = 0;
	//pWSD->max_ntp_time_tick_ = 10 * 1000;

	pWSD->last_ping_tick_ = 0;
	pWSD->max_ping_tick_ = 60 * 1000;
}

void InitSSD(PSSD pSSD)
{
	pSSD->wsd.state_ = STATE_NOT_INIT;
	
	pSSD->wsd.last_sent_command_ = CMD_NONE;
	
	pSSD->wsd.watchdog_send_interval_ = DATA_SEND_TIMEOUT_INTERVAL;
	pSSD->wsd.last_watchdog_send_tick_ = 0;
	pSSD->wsd.is_set_watchdog_send_ = 0;
	pSSD->wsd.is_enabled_watchdog_send_ = 0;	
	
	pSSD->wsd.is_waiting_wifi_response_ = 0;
	pSSD->wsd.wifi_command_interval_ = 10000;
	pSSD->wsd.last_wifi_command_tick_ = 0;
	pSSD->wsd.wifi_command_retry_count_ = 0;
	pSSD->wsd.wifi_command_retry_count_limit_ = 5;
	
	pSSD->wsd.is_delaying_wifi_command_ = 0;
	pSSD->wsd.wifi_command_delay_ = 5000;
	pSSD->wsd.wifi_command_delay_tick_ = 0;
	
	pSSD->wsd.wifi_command_recoonect_count_ = 0;
	pSSD->wsd.wifi_command_recoonect_count_limit_ = 5;

	pSSD->gvReceiveMode = STATE_RECEIVE_MODE_INIT;
	pSSD->nTotalReceiveDataCount = 0;
	pSSD->nCurrentReceiveDataCount = 0;
	pSSD->nReceiveChannel = 0;
	pSSD->aReceiveDataCount[0] = 0;
	pSSD->aReceiveDataCount[1] = 0;
    pSSD->aReceiveDataCount[2] = 0;
	//pSSD->gTCPD;
}

ESTATE GetState(void) 
{
	return wsd.state_;
}

void SetState(ESTATE _state)
{
	wsd.state_ = _state;
}

ESTATE GetLastCommand() 
{
	return wsd.last_sent_command_;
}

void SetLastCommand(ESTATE _last_command)
{
	wsd.last_sent_command_ = _last_command;
}

uint32_t IsDelayingToSendCommand(void)
{
	return wsd.is_delaying_wifi_command_;
}

void SetDelayingToSendCommand(uint32_t _tick, uint32_t _delay)
{
	wsd.is_delaying_wifi_command_ = 1;
	wsd.wifi_command_delay_tick_ = _tick;
	wsd.wifi_command_delay_ = _delay;
}

uint32_t CheckReadyToSendCommand(uint32_t _tick)
{	
	uint32_t _is_ready_to_send_command = 0;
	
	if(wsd.wifi_command_delay_ <= (_tick - wsd.wifi_command_delay_tick_)) {
		wsd.is_delaying_wifi_command_ = 0;
		wsd.wifi_command_delay_ = 1000;
		wsd.wifi_command_delay_tick_ = _tick;
		_is_ready_to_send_command = 1;
	}

	return _is_ready_to_send_command;
}

uint32_t IsWaitingForResponse(void)
{
	return wsd.is_waiting_wifi_response_;
}

void ClearWaitingForResponse(void)
{
	wsd.is_waiting_wifi_response_ = 0;
}

void SetWaitingForResponse(uint32_t _tick, uint32_t _interval)
{
	wsd.is_waiting_wifi_response_ = 1;

	wsd.last_wifi_command_tick_ = _tick;
	wsd.wifi_command_interval_ = _interval;
	wsd.wifi_command_retry_count_ = 0;
	wsd.wifi_command_retry_count_limit_ = 3;
}

uint32_t IsExpiredWaitingForResponse(uint32_t _tick)
{	
	uint32_t _is_expired = 0;
	
	if(wsd.wifi_command_interval_ <= (_tick - wsd.last_wifi_command_tick_)) {
		wsd.last_wifi_command_tick_ = _tick;
		wsd.wifi_command_retry_count_++;
		if(wsd.wifi_command_retry_count_limit_ <= wsd.wifi_command_retry_count_) {
			_is_expired = 1;
		}
	}

	return _is_expired;
}

void ClearReconnectCount() 
{  
	wsd.wifi_command_recoonect_count_ = 0;
	wsd.wifi_command_recoonect_count_limit_ = 5;
}

void IncreaseReconnectCount() 
{
	wsd.wifi_command_recoonect_count_++;
}

uint32_t IsExpiredWaitingForReconnect()
{
	uint32_t _is_expired = 0;
	
	if(wsd.wifi_command_recoonect_count_limit_ <= wsd.wifi_command_recoonect_count_) {
		_is_expired= 1;
	}

	return _is_expired;
}

void EnableWatchDogForSendingData(uint32_t _enable, uint32_t _tick)
{
	wsd.is_enabled_watchdog_send_ = _enable;
	wsd.watchdog_send_interval_ = DATA_SEND_TIMEOUT_INTERVAL;
	wsd.last_watchdog_send_tick_ = _tick;
	wsd.is_set_watchdog_send_ = 0;
}

void ResetWatchDogForSendingData(uint32_t _tick)
{
	wsd.watchdog_send_interval_ = DATA_SEND_TIMEOUT_INTERVAL;
	wsd.last_watchdog_send_tick_ = _tick;
	wsd.is_set_watchdog_send_ = 0;
}

uint32_t IsExpiredWatchDogForSendingData(uint32_t _tick)
{
	uint32_t _is_expired_watchdog_send = 0;
	
	if(1 == wsd.is_enabled_watchdog_send_) {
		if(wsd.watchdog_send_interval_ <= (_tick - wsd.last_watchdog_send_tick_)) { 		
			wsd.last_watchdog_send_tick_ = _tick; 
		
			// 마지막 데이터 패킷을 보냄
			wsd.is_set_watchdog_send_ = 1;
			_is_expired_watchdog_send = 1;
		}
	}
	return _is_expired_watchdog_send;
}

uint32_t IsResendSensorData(void)
{
	return wsd.is_set_watchdog_send_;
}

#if 0
uint8_t IsConnectedNTPServer() 
{
	return wsd.ntp_server_connected_;
}

void SetConnectedNTPServer(uint8_t _connected)
{
	wsd.ntp_server_connected_ = _connected;
}

uint8_t IsReadNTP() 
{
	return wsd.ntp_read_;
}

void SetReadNTP(uint8_t _ntp_read)
{
	wsd.ntp_read_ = _ntp_read;
}

void SetNTPTImeTick(uint32_t _tick)	
{
	wsd.last_ntp_time_tick_ = _tick;
}

uint8_t IsExpiredNTPTImeTick(uint32_t _tick)
{
	return ((wsd.last_ntp_time_tick_ + wsd.max_ntp_time_tick_) <= _tick);
}

uint8_t CheckReceivedNTPTIme(uint32_t _tick)
{
	uint8_t is_received_ntp_time = 0;
	
	if (1 == IsConnectedNTPServer()) {
		if(1 == IsExpiredNTPTImeTick(_tick)) {
			if (0 == IsExceededNTPReryCount()) {
				SetState(STATE_REQUEST_SEND_NTP_PACKET);
				IncreaseNTPRetryCount();
			}
			else {
				SetState(STATE_DISCONNECT_NTP_SERVER);
				SetReadNTP(0);
			}
		}
		else {
			is_received_ntp_time = 1;
		}
	}
	return is_received_ntp_time;
}

void ResetNTPRetryCount()
{
	wsd.ntp_retry_count_ = 0;
}

void IncreaseNTPRetryCount()
{
	wsd.ntp_retry_count_++;
}

uint8_t IsExceededNTPReryCount()
{
	return (wsd.max_ntp_retry_count_ <= wsd.ntp_retry_count_);
}
#endif

uint8_t IsConnectedServer() 
{
	return wsd.server_connected_;
}

void SetConnectedServer(uint8_t _server_connected)
{
	wsd.server_connected_ = _server_connected;
}

uint8_t IsIdentifiedServer()
{
	return wsd.server_identified_;
}

void SetIdentifiedServer(uint8_t _server_identified)
{
	wsd.server_identified_ = _server_identified;
}

void SetPingTick(uint32_t _tick)
{
	wsd.last_ping_tick_ = _tick;
}

uint8_t IsExpiredPingTick(uint32_t _tick)
{
	return ((wsd.last_ping_tick_ + wsd.max_ping_tick_) <= _tick);
}

uint8_t CheckConnectingServer(uint32_t _tick)
{
	uint8_t is_connecting_server = 0;
	
	if (1 == IsConnectedServer()) {
		if(1 == IsExpiredPingTick(_tick)) {
			SetState(STATE_RETRY_CONNECT_SERVER);
		}
		else {
			is_connecting_server = 1;
		}
	}
	return is_connecting_server;
}


void SendWiFiCommand(ESTATE _state)
{
	switch(_state) {
	case CMD_RESET:				
		ResetESP8266();		SetLastCommand(_state); break;
	case CMD_INIT_UART:			
		InitESP8266Uart();	SetLastCommand(_state); break;
	case CMD_SET_MODE:			
		SetStationMode();	SetLastCommand(_state); break;
	case CMD_CHECK_AP:			
		CheckAP();			SetLastCommand(_state); break;
	case CMD_CONNECT_AP:		
		ConnectAP(szSSID, szPassword);	SetLastCommand(_state); break;
	case CMD_CHECK_IP:
		CheckIPAddress();	SetLastCommand(_state); break;
	case CMD_ENABLE_MULTICONNECT: 
		SetMulticonnectionMode();	SetLastCommand(_state); break;
#if 0		
	case CMD_CONNECT_NTP_SERVER: 		
		ConnectNTPServer((int8_t *)szNTPServerAddress);	SetLastCommand(_state); break;
	case CMD_REQUEST_SEND_NTP_PACKET:  	
		RequestSendNTPPacket();	SetLastCommand(_state); break;
	case CMD_SEND_NTP_PACKET:			
		SendNTPPacket();		SetLastCommand(_state);	break;
	case CMD_DISCONNECT_NTP_SERVER: 	
		DisconnectNTPServer();	SetLastCommand(_state); break;
//	case CMD_GET_NTP_TIME: 		
//		UartPrintf(UART_ESP12, (const int8_t*)cmdTable[4].pstr);	SetLastCommand(_state); break;
#endif
	case CMD_SETUP_SERVER:		
		//UartPrintf(UART_ESP12, (const int8_t*)cmdTable[5].pstr);	SetLastCommand(_state); break;
		ConfigureServer();		SetLastCommand(_state); break;
	case CMD_CONNECT_SERVER:	
		ConnectServer((int8_t *)szTestServerAddress, nTestServerPort);	SetLastCommand(_state); break;
	case CMD_REQUEST_SEND_DATA:	
		//UartPrintf(UART_ESP12, (const int8_t*)cmdTable[7].pstr);	SetLastCommand(_state); break;
#if 0		
	case CMD_REQUEST_IDENTIFY_SERVER:	
		/*UartPuts(UART_ESP12, "AT+CIPSEND=0,18\r\n", 17);*/
		RequestSendIdentifyCommand();	SetLastCommand(_state); break;
	case CMD_SEND_IDENTIFY_SERVER:	
		SendFuntion0Command();		SetLastCommand(_state);		break;	
	case CMD_REQUEST_SEND_NTP_TIME_TO_SERVER:	
		RequestSendNTPTimeToServer();	SetLastCommand(_state);	break;	
	case CMD_SEND_NTP_TIME_TO_SERVER:		
		SendNTPTImeToServer();		SetLastCommand(_state);		break;
	case CMD_REQUEST_SEND_ONOFF_RESULT_TO_SERVER:
		RequestSendOnOffResultToServer();	SetLastCommand(_state);		break;
	case CMD_SEND_ONOFF_RESULT_TO_SERVER:
		SendOnOffResultToServer();	SetLastCommand(_state);		break;
#endif		
	case CMD_DISCONNECT_SERVER:
		DisconnectServer();	SetLastCommand(_state);		break;
	}
}

void ResetESP8266ByGPIO()
{
	HAL_GPIO_WritePin(ESP_nRESET_GPIO_Port, ESP_nRESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(ESP_nRESET_GPIO_Port, ESP_nRESET_Pin, GPIO_PIN_SET);
}


void ResetESP8266()
{
	UartPuts(UART_ESP12, "AT+RST\r\n", 8);
	//UartPuts(UART_ESP12, "AT+GMR\r\n", 8);
	//UartPuts(UART_ESP12, "AT\r\n", 4);
}

void InitESP8266Uart()
{
	UartPuts(UART_ESP12, "AT+UART_DEF=115200,8,1,0,3\r\n", 28);
}

void SetStationMode()
{
	UartPuts(UART_ESP12,  "AT+CWMODE=1\r\n", 13);
}

void CheckAP()
{
	/* found_ap_index = -1; */
	UartPuts(UART_ESP12, "AT+CWLAP\r\n", 10);
}

void SetMulticonnectionMode()
{
	UartPuts(UART_ESP12, "AT+CIPMUX=1\r\n", 13);
}

int32_t CompareSSID(int8_t *ssid_ptr)
{
	int32_t found_index = -1;

#if 0
	for (int32_t i = 0; i < MAX_AP_COUNT; i++) {
		if (0 == strncmp((const char*)(ssid_ptr + 11), (const char*)aListAP[i].ssid_ptr, aListAP[i].ssid_length)) {
			found_index = i;
			UartPrintf(UART_DEBUG, ">>> Found AP SSID=%s\r\n", (const char*)aListAP[i].ssid_ptr);
			break;
		}
	}
#endif
	return found_index;
}

void ConnectAP(int8_t const *pszSSID, int8_t const *pszPassword)
{
	int8_t aBuffer[64];

	sprintf((char*)aBuffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", pszSSID, pszPassword);

	int32_t str_count = strlen((char const*)aBuffer);
	UartPuts(UART_ESP12, (const int8_t*)aBuffer, str_count);
}

void CheckIPAddress()
{
	UartPuts(UART_ESP12, "AT+CIPSTA?\r\n", 12);
}

#if 0
void ConnectNTPServer(int8_t *pNTP)
{
	int8_t aBuffer[64];
	//1.nl.pool.ntp.org
	sprintf((char*)aBuffer, "AT+CIPSTART=2,\"UDP\",\"%s\",123\r\n", pNTP);
	
	int32_t str_count = strlen((char const*)aBuffer);
	UartPuts(UART_ESP12, (const int8_t*)aBuffer, str_count);
}

void RequestSendNTPPacket()
{
	RequestToSendData(CHANNEL_NTP_SERVER, 48);
}

void SendNTPPacket()
{
	const NPD	npd = { 0xE3, 0, 6, 0xEC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	PNUD pNUD = (PNUD)&npd;

	pNUD->aBuffer[12] = 49;
	pNUD->aBuffer[13] = 0x4E;
	pNUD->aBuffer[14] = 49;
	pNUD->aBuffer[15] = 52;

	UartPuts(UART_ESP12, (const int8_t *)&npd, 48);
}

void DisconnectNTPServer()
{
	UartPuts(UART_ESP12, (const int8_t *)"AT+CIPCLOSE=2\r\n", 15 );
}
#endif

void ConfigureServer()
{
	UartPuts(UART_ESP12, (const int8_t *)"AT+CIPSERVER=1\r\n", 15);
}

void ConnectServer(int8_t *pServer, int32_t port_number)
{
	int8_t aBuffer[64];

	sprintf((char*)aBuffer, "AT+CIPSTART=0,\"TCP\",\"%s\",%d\r\n", pServer, port_number);
	
	int32_t str_count = strlen((char const*)aBuffer);
	UartPuts(UART_ESP12, (const int8_t*)aBuffer, str_count);
}

void DisconnectServer()
{
	UartPuts(UART_ESP12, (const int8_t *)"AT+CIPCLOSE=0\r\n", 15 );
}

#if 0

void RequestSendPacketToNTPServer(int8_t count)
{
	RequestToSendData(CHANNEL_NTP_SERVER, count);
}

void RequestSendIdentifyCommand()
{
	RequestToSendData(CHANNEL_TEST_SERVER, 18);
}

void MakeFunctionCommand(PTCPD pTCPD, int nFuncNum, uint8_t nDataSize)
{
	memset(pTCPD, 0, sizeof(TCPD));
	
	pTCPD->d.dwMagic = MAGIC_CODE;
	pTCPD->d.wVersion = VERSION;
	
	strncpy((char*)pTCPD->d.aID, (const char*)szDeviceID, TCP_PACKET_HEADER_ID_SIZE);

	pTCPD->d.cFunction = (uint8_t)nFuncNum;
	pTCPD->d.cSize = nDataSize;
}
#endif

void RequestToSendData(int32_t ch_id, int32_t count)
{
	int8_t aBuffer[20];
	
	sprintf((char*)aBuffer, "AT+CIPSEND=%d,%d\r\n", ch_id, count);
	
	int32_t str_count = strlen((char const*)aBuffer);
	UartPuts(UART_ESP12, (const int8_t*)aBuffer, str_count);
}

#if 0
void SendFuntion0Command(void)
{
	TCPD	cmdFunc;
	
	MakeFunctionCommand(&cmdFunc, 0);
	UartPuts(UART_ESP12, (const int8_t*)&cmdFunc, TCP_PACKET_HEADER_SIZE);	
}	

void RequestSendNTPTimeToServer()
{
	RequestToSendData(CHANNEL_TEST_SERVER, 25);
}

void SendNTPTImeToServer()
{
	struct tm TM;
	ReadRTC_TM(&TM);
	SendFuntion1Response(0, &TM);
}

// Synch NTP Time
void SendFuntion1Response(uint8_t resp, struct tm *pTM)
{
	TCPD	cmdFunc;
	
	MakeFunctionCommand(&cmdFunc, 1, 7);
	cmdFunc.d.aBuffer[0] = resp;
	cmdFunc.d.aBuffer[1] = HEX2BCD(pTM->tm_year - 100);	// year	 
	cmdFunc.d.aBuffer[2] = HEX2BCD(pTM->tm_mon + 1);		// month
	cmdFunc.d.aBuffer[3] = HEX2BCD(pTM->tm_mday);	// day
	cmdFunc.d.aBuffer[4] = HEX2BCD(pTM->tm_hour);	// hour
	cmdFunc.d.aBuffer[5] = HEX2BCD(pTM->tm_min);		// minute
	cmdFunc.d.aBuffer[6] = HEX2BCD(pTM->tm_sec);		// second;

	UartPuts(UART_ESP12, (const int8_t*)&cmdFunc, TCP_PACKET_HEADER_SIZE + 7);	
}

// Set Time Offset
void SendFuntion2Response(uint8_t resp, struct tm *pTM)
{
	TCPD	cmdFunc;
	
	MakeFunctionCommand(&cmdFunc, 1, 7);
	cmdFunc.d.aBuffer[0] = resp;
	cmdFunc.d.aBuffer[1] = HEX2BCD(pTM->tm_year - 100);	// year	 
	cmdFunc.d.aBuffer[2] = HEX2BCD(pTM->tm_mon + 1);		// month
	cmdFunc.d.aBuffer[3] = HEX2BCD(pTM->tm_mday);	// day
	cmdFunc.d.aBuffer[4] = HEX2BCD(pTM->tm_hour);	// hour
	cmdFunc.d.aBuffer[5] = HEX2BCD(pTM->tm_min);		// minute
	cmdFunc.d.aBuffer[6] = HEX2BCD(pTM->tm_sec);		// second;

		
	UartPuts(UART_ESP12, (const int8_t*)&cmdFunc, TCP_PACKET_HEADER_SIZE + 7);	
}


void RequestSendOnOffResultToServer()
{
	RequestToSendData(CHANNEL_TEST_SERVER, 19);
}

void SendOnOffResultToServer()
{
	SendFuntion3Response(0);
}

//Light On
void SendFuntion3Response(uint8_t resp)
{
	TCPD	cmdFunc;
	
	MakeFunctionCommand(&cmdFunc, 1, 1);
	cmdFunc.d.aBuffer[0] = resp;

	UartPuts(UART_ESP12, (const int8_t*)&cmdFunc, TCP_PACKET_HEADER_SIZE + 1);	
}

//Light Off
void SendFuntion4Response(uint8_t resp)
{
	TCPD	cmdFunc;
	
	MakeFunctionCommand(&cmdFunc, 1, 1);
	cmdFunc.d.aBuffer[0] = resp;

	UartPuts(UART_ESP12, (const int8_t*)&cmdFunc, TCP_PACKET_HEADER_SIZE + 1);	
}

// Reserve Light On Off Time
void SendFuntion5Response(uint8_t resp)
{
	TCPD	cmdFunc;
	
	MakeFunctionCommand(&cmdFunc, 1, 1);
	cmdFunc.d.aBuffer[0] = resp;

	UartPuts(UART_ESP12, (const int8_t*)&cmdFunc, TCP_PACKET_HEADER_SIZE + 1);	
}
#endif


ESTATE parsingResponse(UART_TYPE _uartType, int8_t *line, uint32_t count)
{
	ESTATE _response_id = RSP_NOT_FOUND;

	ESTATE _last_command = GetLastCommand(); 
	
	for(uint32_t i=0; i<MAX_RESPONSE_TABLE_COUNT; i++) {
		if((_last_command == rspTable[i].cmdType) || 
			(CMD_RESET == rspTable[i].cmdType) || 
			(CMD_COMMON == rspTable[i].cmdType)) {
			if (0 == strncmp((const char*)line, (const char*)rspTable[i].pstr, rspTable[i].responseLength)) {
				_response_id = rspTable[i].cmdID;
                break;
			}
		}
	}

	return _response_id;
}

uint32_t WiFi_ParsingProc(UART_TYPE _uartType, uint8_t ch)
{
	switch (ch) {
#if 0		
	case UART_CR:
		CMD_PushChar(_uartType, ch);
		if (STATE_RECEIVE_MODE_DATA == gvReceiveMode) { 
			if(1 == CheckReceiveData(_uartType, ch)) {
				ParseReceiveData(_uartType, ch);
				CMD_InitBuffer(_uartType);
			}
		}
		break;
#endif		
	case UART_LF:
		if (STATE_RECEIVE_MODE_DATA == gvReceiveMode) { 
			CMD_PushChar(_uartType, ch);

			if(1 == CheckReceiveData(_uartType, ch)) {
				ParseReceiveData(_uartType, ch);
				CMD_InitBuffer(_uartType);
			}
		}
		else {
			CMD_PushChar(_uartType, ch);
			CMD_PushChar(_uartType, 0);

			ParseReceiveData(_uartType, ch);
			CMD_InitBuffer(_uartType);
		}
		break;
		
	case UART_PLUS:
		CMD_PushChar(_uartType, ch);

		if (STATE_RECEIVE_MODE_INIT == gvReceiveMode) {
			gvReceiveMode = STATE_RECEIVE_MODE_PLUS;
			nTotalReceiveDataCount = 0;
			nCurrentReceiveDataCount = 0;
			nReceiveChannel = 0;
			aReceiveDataCount[0] = 0;
			aReceiveDataCount[1] = 0;
			aReceiveDataCount[2] = 0;
		}
		break;

	default:
		CMD_PushChar(_uartType, ch);

		if(STATE_RECEIVE_MODE_PLUS <= gvReceiveMode) {
			if(1 == CheckReceiveData(_uartType, ch)) {
				ParseReceiveData(_uartType, ch);
				CMD_InitBuffer(_uartType);
			}
		}
		break;
	}

	return CMD_GetBufferIndex(_uartType);
}


uint32_t Arduino_ParsingProc(UART_TYPE _uartType, uint8_t ch)
{
	PUART_Q pUartQ = &gUarts[UART_ESP12];
	//PCQ_BUFFER pRxQ = &pUartQ->rxQ;
	//pUartQ->buffer
/*
	"Starting WiFi..... " --> NO_WIFI
	"Waiting for new SSID & password within 5 seconds....." --> CONFIG
	"Connecting to "
	"Wait for connecting WiFi AP... " --> CONNECTING_AP
	"WiFi AP is connected" --> CONNECTED_AP
	
	"Fail to connect to server" 
	"Close server connection"
	
	"Succeed to connect to server" --> CONNECTED_SERVER
	"WiFi AP is disconnected..."  
*/
	switch (ch) {
	case UART_LF:
		CMD_PushChar(_uartType, ch);
		CMD_PushChar(_uartType, 0);

		//ParseReceiveData(_uartType, ch);
				
		if (0 == strncmp("Starting WiFi..... ", (char const*)pUartQ->buffer, 19)) {
			state_arduino_ = STATE_NO_WIFI;
		}
		else if (0 == strncmp("Waiting for new SSID & password within 5 seconds.....", (char const*)pUartQ->buffer, 53)) {
			state_arduino_ = STATE_WIAT_CONFIG_DATA;
			if (1 == IsUpdatedCDI()) {
				SetUpdateCDI(0);
				
				char buffer[80];
				memset(buffer, 0, sizeof(buffer));
				sprintf(buffer, "ssid:%s,password:%s,host:%s,port:%d,id:%d",
						cdi.ssid, cdi.password, cdi.host, cdi.port, cdi.id);
				int _length = strlen(buffer);
				UartPuts(UART_ESP12, (const int8_t*)buffer, _length);
			}
		}
		else if (0 == strncmp("Reading config data from EEPROM.....", (char const*)pUartQ->buffer, 36)) {
			state_arduino_ = STATE_READ_EEPROM;
		} 
		else if (0 == strncmp("Connecting to ", (char const*)pUartQ->buffer, 14)) {
			state_arduino_ = STATE_START_CONNECTING;
		}
		else if (0 == strncmp("Wait for connecting WiFi AP... ", (char const*)pUartQ->buffer, 31)) {
			state_arduino_ = STATE_CONNECTING_WIFI_AP;
		}
		else if (0 == strncmp("WiFi AP is connected", (char const*)pUartQ->buffer, 20)) {
			state_arduino_ = STATE_CONNECTED_AP;
		}
		else if (0 == strncmp("Fail to connect to server", (char const*)pUartQ->buffer, 25)) {
			state_arduino_ = STATE_CONNECTED_AP;
		}
		else if (0 == strncmp("Close server connection", (char const*)pUartQ->buffer, 23)) {
			state_arduino_ = STATE_CONNECTED_AP;
		}
		else if (0 == strncmp("Succeed to connect to server", (char const*)pUartQ->buffer, 28)) {
			state_arduino_ = STATE_CONNECTED_SERVER;
		}
		else if (0 == strncmp("WiFi AP is disconnected...", (char const*)pUartQ->buffer, 26)) {
			state_arduino_ = STATE_NO_WIFI;
		}
		
		CMD_InitBuffer(_uartType);
		break;
		
	default:
		CMD_PushChar(_uartType, ch);
		break;
	}

	return CMD_GetBufferIndex(_uartType);
}


uint8_t IsConnectedArduinoServer()
{
	return (STATE_CONNECTED_SERVER == state_arduino_);
}

uint8_t IsUpdatedCDI()
{
	return cdi_updated_;
}

void SetUpdateCDI(uint8_t _update)
{
	cdi_updated_ = _update;
}

PCDI GetCDI()
{
	return (&cdi);
}

void SetCdiSSID(char *pbuff, uint32_t length)
{
	if (0 < length) {
		strncpy(cdi.ssid, pbuff, length);
	}
}

void SetCdiPassword(char *pbuff, uint32_t length)
{
	if (0 < length) {
		strncpy(cdi.password, pbuff, length);
	}
}

void SetCdiHost(char *pbuff, uint32_t length)
{
	if (0 < length) {
		strncpy(cdi.host, pbuff, length);
	}
}

void SetCdiPort(int num)
{
	cdi.port = (uint16_t)num;
}

void SetCdiID(int num)
{
	cdi.id = (uint16_t)num;
}
	
void InitReceiveDataState()
{
	gvReceiveMode = STATE_RECEIVE_MODE_INIT;
	nTotalReceiveDataCount = 0;
	nCurrentReceiveDataCount = 0;
	nReceiveChannel = 0;
	aReceiveDataCount[0] = 0;
	aReceiveDataCount[1] = 0;
	aReceiveDataCount[2] = 0;
}

uint8_t CheckReceiveData(UART_TYPE _uartType, uint8_t ch)
{
	uint8_t bIsReceiveDataDone = 0;
#if 0	
	uint8_t bIsFailedReceiveDataMode = 0;
	int32_t nFailNum = 0;

	switch (gvReceiveMode) {
	case STATE_RECEIVE_MODE_PLUS:
		if ('I' == ch) {
			gvReceiveMode = STATE_RECEIVE_MODE_I;
		}
		else {
			bIsFailedReceiveDataMode = 1;
			nFailNum = 1;
		}
		break;
	case STATE_RECEIVE_MODE_I:
		if ('P' == ch) {
			gvReceiveMode = STATE_RECEIVE_MODE_P;
		}
		else {
			bIsFailedReceiveDataMode = 1;
			nFailNum = 2;
		}
		break;
	case STATE_RECEIVE_MODE_P:
		if ('D' == ch) {
			gvReceiveMode = STATE_RECEIVE_MODE_D;
		}
		else {
			bIsFailedReceiveDataMode = 1;
			nFailNum = 3;
		}
		break;
	case STATE_RECEIVE_MODE_D:
		if (',' == ch) {
			gvReceiveMode = STATE_RECEIVE_MODE_COMMA1;
		}
		else {
			bIsFailedReceiveDataMode = 1;
			nFailNum = 4;
		}
		break;
	case STATE_RECEIVE_MODE_COMMA1:
		if (('0' <= ch) && (ch <= '4')) {
			gvReceiveMode = STATE_RECEIVE_MODE_ID;
			nReceiveChannel = ch - '0';
		}
		else {
			bIsFailedReceiveDataMode = 1;
			nFailNum = 5;
		}
		break;
	case STATE_RECEIVE_MODE_ID:
		if (',' == ch) {
			gvReceiveMode = STATE_RECEIVE_MODE_COMMA2;
		}
		else {
			bIsFailedReceiveDataMode = 1;
			nFailNum = 6;
		}
		break;
	case STATE_RECEIVE_MODE_COMMA2:
		if (('0' <= ch) && (ch <= '9')) {
			gvReceiveMode = STATE_RECEIVE_MODE_LENGTH1;
			aReceiveDataCount[0] = ch;
		}
		else {
			bIsFailedReceiveDataMode = 1;
			nFailNum = 7;
		}
		break;
	case STATE_RECEIVE_MODE_LENGTH1:
		if (('0' <= ch) && (ch <= '9')) {
			gvReceiveMode = STATE_RECEIVE_MODE_LENGTH2;
			aReceiveDataCount[1] = ch;
		}
		else {
			bIsFailedReceiveDataMode = 1;
			nFailNum = 8;
		}
		break;
	case STATE_RECEIVE_MODE_LENGTH2:
		if (':' == ch) {
			gvReceiveMode = STATE_RECEIVE_MODE_DATA;
			nTotalReceiveDataCount = atoi((char const *)aReceiveDataCount);
		}
		else {
			bIsFailedReceiveDataMode = 1;
			nFailNum = 9;
		}
		break;
	case STATE_RECEIVE_MODE_DATA:
		if (NTP_PACKET_DATA_COUNT == nTotalReceiveDataCount) {
			nud.aBuffer[nCurrentReceiveDataCount] = ch;	
		}
		else {
			gTCPD.aBuffer[nCurrentReceiveDataCount] = ch;		
		}
		nCurrentReceiveDataCount++;
		
		if(nTotalReceiveDataCount <= nCurrentReceiveDataCount) {
			CMD_PushChar(_uartType, UART_CR);
			CMD_PushChar(_uartType, UART_LF);
			CMD_PushChar(_uartType, 0);
			
			bIsReceiveDataDone = 1;

			gvReceiveMode = STATE_RECEIVE_MODE_INIT;
			//nTotalReceiveDataCount = 0;
			//nCurrentReceiveDataCount = 0;
			//nReceiveChannel = 0;
			aReceiveDataCount[0] = 0;
			aReceiveDataCount[1] = 0;
			aReceiveDataCount[2] = 0;
		}
		break;
	}

	if (1 == bIsFailedReceiveDataMode) {
		if (1 < nFailNum) {
			int8_t aBuffer[50];
			sprintf((char*)aBuffer, "[Error] CheckReceiveData(), nFailNum=%d\r\n", nFailNum);
			UartPrintf(UART_DEBUG, aBuffer);
		}
		
		InitReceiveDataState();
	}
#endif

	return bIsReceiveDataDone;
}


void DumpCmdPack(UART_TYPE _uartType, int8_t *line, uint32_t count)
{
    int8_t aBuffer[512];

    int8_t *pin = line;
    const int8_t *hex = "0123456789ABCDEF";
    int8_t *pout = aBuffer;
    int32_t i = 0;
    for(; i < count - 1; ++i){
        *pout++ = hex[(*pin>>4) & 0xF];
        *pout++ = hex[(*pin++) & 0xF];
        *pout++ = ':';
    }
    *pout++ = hex[(*pin>>4)&0xF];
    *pout++ = hex[(*pin)&0xF];
	*pout++ = 0x0D;
	*pout++ = 0x0A;
    *pout = 0;

	UartPrintf(_uartType, aBuffer);
}

void ParseReceiveData(UART_TYPE _uartType, uint8_t ch)
{
	ESTATE _responseID = RSP_NOT_FOUND;
	uint32_t _tick = HAL_GetTick();

	_responseID = parsingResponse(_uartType, (int8_t*)cmdPack[_uartType].aBuffer, cmdPack[_uartType].nIndex);

#if 0
	if (RSP_NOT_FOUND != _responseID) {
		DumpCmdPack(UART_DEBUG, (int8_t*)cmdPack[_uartType].aBuffer, cmdPack[_uartType].nIndex);
	}
#endif	

	if (RSP_OK == _responseID ) {
		ESTATE _lastCommand = GetLastCommand();
		switch (_lastCommand) {
		case CMD_INIT_UART:				_responseID = RSP_INIT_UART_OK;	break;
		case CMD_SET_MODE:				_responseID = RSP_SET_MODE_OK;	break;
		case CMD_CHECK_IP:				_responseID = RSP_CHECK_IP_OK;	break;
		case CMD_ENABLE_MULTICONNECT:	_responseID = RSP_MULTICONNECT_OK;	break;
		case CMD_SETUP_SERVER:			_responseID = RSP_SERVER_OK;	break;
#if 0		
		case CMD_CONNECT_NTP_SERVER:	_responseID = RSP_CONNECT_NTP_SERVER_OK;	break;
		case CMD_REQUEST_SEND_NTP_PACKET:	_responseID = RSP_REQUEST_SEND_NTP_PACKET_OK;	break;
		case CMD_DISCONNECT_NTP_SERVER: _responseID = RSP_DISCONNECT_NTP_SERVER_OK;	break;
#endif		
		case CMD_REQUEST_SEND_DATA: 	_responseID = RSP_SEND_OK;	break;
		case CMD_CONNECT_SERVER:		_responseID = RSP_CONNECT_SERVER_OK;	break;
		case CMD_REQUEST_IDENTIFY_SERVER:	_responseID = RSP_REQUEST_IDENTIFY_SERVER_OK;	break;
#if 0		
		case CMD_REQUEST_SEND_NTP_TIME_TO_SERVER:		
			_responseID = RSP_REQUEST_SEND_NTP_TIME_TO_SERVER_OK;	break;
		case CMD_REQUEST_SEND_ONOFF_RESULT_TO_SERVER:		
			_responseID = RSP_REQUEST_SEND_ONOFF_RESULT_TO_SERVER_OK;	break;		
#endif			
		}
	}
	else if (RSP_CONNECT_OK == _responseID) {
		ESTATE _lastCommand = GetLastCommand();
		switch (_lastCommand) {
		case CMD_CONNECT_SERVER:		_responseID = RSP_CONNECT_SERVER_OK;	break;
		}
	}
	else if (RSP_SEND_OK == _responseID) {
		ESTATE _lastCommand = GetLastCommand();
		switch (_lastCommand) {
		case CMD_CHECK_AP:				_responseID = RSP_CHECK_AP_OK;	break;
		//case CMD_SEND_NTP_PACKET:		_responseID = RSP_SEND_NTP_PACKET_OK;	break;
		case CMD_REQUEST_IDENTIFY_SERVER:	_responseID = RSP_REQUEST_IDENTIFY_SERVER_OK;	break;
		case CMD_SEND_IDENTIFY_SERVER:		_responseID = RSP_SEND_IDENTIFY_SERVER_OK;	break;
#if 0		
		case CMD_SEND_NTP_TIME_TO_SERVER:	_responseID = RSP_SEND_NTP_TIME_TO_SERVER_OK;	break;
		case CMD_SEND_ONOFF_RESULT_TO_SERVER:	_responseID = RSP_SEND_ONOFF_RESULT_TO_SERVER_OK; 	break;
#endif		
		}
	}

	switch(_responseID) {
	case RSP_RESET_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_RESET_OK\r\n");
		SetState(STATE_INIT_UART);
		ClearWaitingForResponse();
		ClearReconnectCount();
		SetDelayingToSendCommand(_tick, 10000);
		EnableWatchDogForSendingData(0, _tick);
		//tConnectedNTPServer(0);
		SetConnectedServer(0);
		SetIdentifiedServer(0);
		SetPingTick(_tick);
		//setNTPRetryCount();
		//SetupBlinkLED(0,2000,1);
		break;
	case RSP_INIT_UART_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_INIT_UART_OK\r\n");
		SetState(STATE_INIT);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 1000);
		//SetupBlinkLED(0,2000,2);
		break;
		
	case RSP_SET_MODE_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_SETMODE_OK\r\n");	
		SetState(STATE_CONNECT_AP);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 1000);
		break;
	case RSP_AP_FOUND_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_AP_FOUND_OK\r\n");
#if 0		
		SetState(STATE_CHECK_AP);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 1000);
		//SetupBlinkLED(0,2000,2);
#else
		//{
		//	int found = CompareSSID((int8_t*)cmdPack[_uartType].aBuffer);
		//	if(0 <= found) {
		//		found_ap_index = found;
		//	}
		//}
#endif
		break;			
	case RSP_CHECK_AP_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_CHECK_AP_OK\r\n");
		SetState(STATE_CONNECT_AP);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 1000);
		break;
	case RSP_GOT_IP:
		UartPrintf(UART_DEBUG, ">>> Received RSP_GOT_IP\r\n");
		SetState(STATE_CHECK_IP);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 1000);
		break;
	case RSP_CHECK_IP_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_CHECK_IP_OK\r\n");
		SetState(STATE_AP_CONNECTED);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 1000);
		break;
#if 0			
	case RSP_CONNECT_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_CONNECT_OK\r\n");
		SetState(STATE_SERVER_CONNECTED);
		ClearWaitingForResponse();
		ClearReconnectCount();
		SetDelayingToSendCommand(_tick, 1000);
		EnableWatchDogForSendingData(1, _tick);
		//SetupBlinkLED(1,2000,1);
		break;
#endif
	case RSP_MULTICONNECT_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_MULTICONNECT_OK\r\n");
		SetState(STATE_IDLE_AP_CONNECTED);
		ClearWaitingForResponse();
		break;
#if 0
	case RSP_CONNECT_NTP_SERVER_OK:
		UartPrintf(UART_DEBUG, ">>> Received Set RSP_CONNECT_NTP_SERVER_OK\r\n");
		SetState(STATE_REQUEST_SEND_NTP_PACKET);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 2000);
		SetNTPTImeTick(_tick);
		SetConnectedNTPServer(1);
		break;

	case RSP_REQUEST_SEND_NTP_PACKET_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_REQUEST_NTP_PACKET_OK\r\n");
		SetState(STATE_SEND_NTP_PACKET);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 2000);
		break;

	case RSP_SEND_NTP_PACKET_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_SEND_NTP_PACKET_OK\r\n");
		SetState(STATE_WAIT_NTP_PACKET);
		ClearWaitingForResponse();
		//SetDelayingToSendCommand(_tick, 2000);
		break;

	case RSP_WAIT_NTP_PACKET_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_WAIT_NTP_PACKET_OK\r\n");
		SetState(STATE_SET_NTP_TIME);
		ClearWaitingForResponse();
		SetNTPTImeTick(_tick);
		break;

	case RSP_DISCONNECT_NTP_SERVER_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_DISCONNECT_NTP_SERVER_OK\r\n");
		SetState(STATE_IDLE_AP_CONNECTED);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 1000);
		SetConnectedNTPServer(0);
		SetNTPTImeTick(_tick);
		break;
#endif
#if 0
	case RSP_GET_NTP_TIME_OK:
		UartPrintf(UART_DEBUG, ">>> Received Get NTP Time OK\r\n");
		SetState(STATE_GET_NTP_TIME);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 2000);
		break;
#endif

	case RSP_CLOSED:
		UartPrintf(UART_DEBUG, ">>> Received RSP_CLOSED\r\n");
		SetState(STATE_AP_CONNECTED);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 2000);
		IncreaseReconnectCount();
		if(IsExpiredWaitingForReconnect()) {
			SetState(STATE_NOT_INIT);
		}
		break;
	case RSP_READY_TO_SEND:
		UartPrintf(UART_DEBUG, ">>> Received RSP_READY_TO_SEND\r\n");
		SetState(STATE_REQUEST_SEND_DATA);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 200);
		break;

	case RSP_CONNECT_SERVER_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_CONNECT_SERVER_OK\r\n");
		SetState(STATE_REQUEST_IDENTIFY_SERVER);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 2000);
		SetConnectedServer(1);
		SetPingTick(_tick);
		break;
	case RSP_CLOSED_SERVER:
		UartPrintf(UART_DEBUG, ">>> Received RSP_CLOSED_SERVER\r\n");
		SetState(STATE_IDLE_AP_CONNECTED);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 2000);
		SetConnectedServer(0);
		SetIdentifiedServer(0);
		SetPingTick(_tick);
		break;
	case RSP_REQUEST_IDENTIFY_SERVER_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_IDENTIFY_SERVER_OK\r\n");
		SetState(STATE_SEND_IDENTIFY_SERVER);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 2000);
		break;

	case RSP_SEND_IDENTIFY_SERVER_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_SEND_IDENTIFY_SERVER_OK\r\n");
		SetState(STATE_CHECK_IDENTIFY_SERVER);
		ClearWaitingForResponse();
		break;
#if 0
	case RSP_FUNCTION_0:	// Function 0 Response
		UartPrintf(UART_DEBUG, ">>> Received RSP_FUNCTION_0\r\n");
		SetState(STATE_CHECK_IDENTIFY_SERVER);
		ClearWaitingForResponse();
		break;
		
	case REQ_FUNCTION_1:	// Function 1 Command
		UartPrintf(UART_DEBUG, ">>> Received REQ_FUNCTION_1\r\n");
		SetState(STATE_REQUEST_SEND_NTP_TIME_TO_SERVER);
		ClearWaitingForResponse();
		break;
		
	case RSP_REQUEST_SEND_NTP_TIME_TO_SERVER_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_REQUEST_SEND_NTP_TIME_TO_SERVER_OK\r\n");
		SetState(STATE_SEND_NTP_TIME_TO_SERVER);
		ClearWaitingForResponse();
		break;

	case RSP_SEND_NTP_TIME_TO_SERVER_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_SEND_NTP_TIME_TO_SERVER_OK\r\n");
		SetState(STATE_IDLE_SERVER_CONNECTED);
		ClearWaitingForResponse();
		SetPingTick(_tick);
		break;
		
	case REQ_FUNCTION_2:	// Function 2 Command
		UartPrintf(UART_DEBUG, ">>> Received REQ_FUNCTION_2\r\n");
		SetState(STATE_REQUEST_SEND_NEW_TIME_TO_SERVER);
		ClearWaitingForResponse();
		break;
		
	case REQ_FUNCTION_3:	// Function 3 Command
		UartPrintf(UART_DEBUG, ">>> Received REQ_FUNCTION_3\r\n");
		SetState(STATE_REQUEST_SEND_ONOFF_RESULT_TO_SERVER);
		ClearWaitingForResponse();
		break;
		
	case RSP_REQUEST_SEND_ONOFF_RESULT_TO_SERVER_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_REQUEST_SEND_ONOFF_RESULT_TO_SERVER_OK\r\n");
		SetState(STATE_SEND_ONOFF_RESULT_TO_SERVER);
		ClearWaitingForResponse();
		break;

	case RSP_SEND_ONOFF_RESULT_TO_SERVER_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_SEND_ONOFF_RESULT_TO_SERVER_OK\r\n");
		SetState(STATE_IDLE_SERVER_CONNECTED);
		ClearWaitingForResponse();
		break;
		
	case REQ_FUNCTION_4:	// Function 4 Command
		UartPrintf(UART_DEBUG, ">>> Received REQ_FUNCTION_4\r\n");
		SetState(STATE_REQUEST_SEND_ONOFF_RESULT_TO_SERVER);
		ClearWaitingForResponse();
		break;
		
	case REQ_FUNCTION_5:	// Function 5 Command
		UartPrintf(UART_DEBUG, ">>> Received REQ_FUNCTION_5\r\n");
		SetState(STATE_REQUEST_SEND_ONOFF_RESULT_TO_SERVER);
		ClearWaitingForResponse();
		break;
#endif
	case RSP_INVALID_LINK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_INVALID_LINK\r\n");
		ClearWaitingForResponse();
		break;
#if 0			
	case RSP_SEND_OK:
		UartPrintf(UART_DEBUG, ">>> Received RSP_SEND_OK\r\n");
		SetState(STATE_SERVER_CONNECTED);
		ClearWaitingForResponse();
		SetDelayingToSendCommand(_tick, 200);
		ResetWatchDogForSendingData(_tick);
		//SetupBlinkLED(1,2000,1);
		break;
#endif			
	}

}



uint32_t WiFi_DefaultProc(uint32_t _tick)
{
	if(1 == IsDelayingToSendCommand()) {
		if(0 == CheckReadyToSendCommand(_tick)) {
			return 0;
		}
	}

	if(0 ==	IsWaitingForResponse()) {
		ESTATE _state = GetState();
		switch(_state) {
			case STATE_NOT_INIT:
			SendWiFiCommand(CMD_RESET);
			SetWaitingForResponse(_tick, RESET_COMMAND_WAIT_TIMEOUT);
			break;
		case STATE_INIT_UART:
			SendWiFiCommand(CMD_INIT_UART);
			SetWaitingForResponse(_tick, 2000);
			break;				
		case STATE_INIT:
			SendWiFiCommand(CMD_SET_MODE);
			SetWaitingForResponse(_tick, SETMODE_COMMAND_WAIT_TIMEOUT);
			break;
		case STATE_CHECK_AP:
			SendWiFiCommand(CMD_CHECK_AP);
			SetWaitingForResponse(_tick, 6000);
			break;
		case STATE_CONNECT_AP:
			SendWiFiCommand(CMD_CONNECT_AP);
			SetWaitingForResponse(_tick, 4000);
			break;
		case STATE_CHECK_IP:
			SendWiFiCommand(CMD_CHECK_IP);
			SetWaitingForResponse(_tick, 1000);
			break;				
		case STATE_AP_CONNECTED:
			SendWiFiCommand(CMD_ENABLE_MULTICONNECT);
			SetWaitingForResponse(_tick, 2000);
			break;
#if 1
		case STATE_IDLE_AP_CONNECTED:
			if (0 == IsConnectedServer()) {
				SetState(STATE_CONNECT_SERVER);
			}
			break;
#else
		case STATE_IDLE_AP_CONNECTED:
			if (0 == IsReadNTP()) {
				SetState(STATE_CONNECT_NTP_SERVER);
			}
			else if (0 == IsConnectedServer()) {
				SetState(STATE_CONNECT_SERVER);
			}
			break;

		case STATE_CONNECT_NTP_SERVER:
			SendWiFiCommand(CMD_CONNECT_NTP_SERVER);
			SetWaitingForResponse(_tick, 6000);
			break;
		case STATE_REQUEST_SEND_NTP_PACKET:
			if(1 == IsExceededNTPReryCount()) {
				SetState(STATE_NOT_INIT);
			}
			else {
				IncreaseNTPRetryCount();
			}		
			InitReceiveDataState();
			SendWiFiCommand(CMD_REQUEST_SEND_NTP_PACKET);
			SetWaitingForResponse(_tick, 2000);
			break;
		case STATE_SEND_NTP_PACKET:
			SendWiFiCommand(CMD_SEND_NTP_PACKET);
			SetWaitingForResponse(_tick, 2000);
			break;
		case STATE_WAIT_NTP_PACKET:
			break;
		case STATE_SET_NTP_TIME:
			{
				struct tm curTM;
				
				MakeTM(&curTM, &nud);

				if(curTM.tm_year < 123) {
					WriteRTCTime(curTM);
					SetReadNTP(1);

					SetState(STATE_DISCONNECT_NTP_SERVER);
				}
				else {
					SetState(STATE_REQUEST_SEND_NTP_PACKET);
				}
			}
			break;
		case STATE_DISCONNECT_NTP_SERVER:
			SendWiFiCommand(CMD_DISCONNECT_NTP_SERVER);
			SetWaitingForResponse(_tick, 2000);
			break;
#endif			
		case STATE_CONNECT_SERVER:
			SendWiFiCommand(CMD_CONNECT_SERVER);
			SetWaitingForResponse(_tick, 6000);
			break;
			
#if 0			
		case STATE_GET_NTP_TIME:
			SendWiFiCommand(CMD_SETUP_SERVER);
			SetWaitingForResponse(_tick, 2000);
			break;

		case STATE_SETUP_SERVER:
			//SendWiFiCommand(STATE_WAITING_REQUEST);
			//SetWaitingForResponse(_tick, 6000);
			break;
#endif

		case STATE_REQUEST_IDENTIFY_SERVER:
			SendWiFiCommand(CMD_REQUEST_IDENTIFY_SERVER);
			SetWaitingForResponse(_tick, 2000);
			break;

#if 0			
		case STATE_SEND_IDENTIFY_SERVER:
			SendWiFiCommand(CMD_SEND_IDENTIFY_SERVER);
			SetWaitingForResponse(_tick, 6000);
			break;

		case STATE_CHECK_IDENTIFY_SERVER:
			if (0 == gTCPD.d.aBuffer[0]) {
				SetState(STATE_IDLE_SERVER_CONNECTED);
			}
			else {
				SetState(STATE_SEND_IDENTIFY_SERVER);
			}
			break;

		///////////////////////////////////////////////////////////////
		// Funtion 1
		case STATE_REQUEST_SEND_NTP_TIME_TO_SERVER:
			SendWiFiCommand(CMD_REQUEST_SEND_NTP_TIME_TO_SERVER);
			SetWaitingForResponse(_tick, 2000);
			break;

		case STATE_SEND_NTP_TIME_TO_SERVER:
			SendWiFiCommand(CMD_SEND_NTP_TIME_TO_SERVER);
			SetWaitingForResponse(_tick, 2000);
			break;
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		// Funtion 2
		case STATE_REQUEST_SEND_NEW_TIME_TO_SERVER:
			{
				int32_t nOffset = MAKE_INT32(gTCPD.d.aBuffer[0],
											gTCPD.d.aBuffer[1],
											gTCPD.d.aBuffer[2],
											gTCPD.d.aBuffer[3]);

				timeRTC= ReadRTC_TimeT();
				timeRTC += nOffset;

				struct tm TM;
				TM = *localtime((const time_t*)&timeRTC);
				WriteRTCTime(TM);
			}
			SendWiFiCommand(CMD_REQUEST_SEND_NTP_TIME_TO_SERVER);
			SetWaitingForResponse(_tick, 2000);
			break;
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		// Funtion 3, 4, 5
		case STATE_REQUEST_SEND_ONOFF_RESULT_TO_SERVER:
			if (3 == gTCPD.d.cFunction) {
				int8_t light_id = gTCPD.d.aBuffer[0];
				int32_t nOffset = MAKE_INT32(gTCPD.d.aBuffer[1],
											gTCPD.d.aBuffer[2],
											gTCPD.d.aBuffer[3],
											gTCPD.d.aBuffer[4]);			
				LRD lrd;

				lrd.enable_ = 1;
				lrd.light_id_ = light_id;
				lrd.onoff_state_ = LIGHT_ON;
				lrd.flag_ = 0;
				lrd.time_on_ = timeRTC;
				lrd.time_off_ = (0 == nOffset) ? 0 : (timeRTC + nOffset);
				
				AddReservation(&lrd);

				Light_OnOff(light_id, 1);

				int8_t aBuffer[100];
				sprintf((char*)aBuffer, "Func3, Light=%d, timeRTC=%ld, Duration=%d, aBuffer[1]=%d, aBuffer[2]=%d, aBuffer[3]=%d, aBuffer[4]=%d\r\n",
						light_id, timeRTC, nOffset, gTCPD.d.aBuffer[1], gTCPD.d.aBuffer[2],
						gTCPD.d.aBuffer[3], gTCPD.d.aBuffer[4]);
				UartPrintf(UART_DEBUG, aBuffer);
			}
			else if (4 == gTCPD.d.cFunction) {
				int8_t light_id = gTCPD.d.aBuffer[0];
				Light_ForcedOff(light_id);

				int8_t aBuffer[100];
				sprintf((char*)aBuffer, "Func4, Light=%d\r\n", light_id);
				UartPrintf(UART_DEBUG, aBuffer);
			}
			else if (5 == gTCPD.d.cFunction) {

				int8_t light_id = gTCPD.d.aBuffer[0];
				int32_t nOffset = MAKE_INT32(gTCPD.d.aBuffer[7],
											gTCPD.d.aBuffer[8],
											gTCPD.d.aBuffer[9],
											gTCPD.d.aBuffer[10]);	

				struct tm TM;
				
				TM.tm_sec = BCD2HEX(gTCPD.d.aBuffer[6]);
				TM.tm_min = BCD2HEX(gTCPD.d.aBuffer[5]);
				TM.tm_hour = BCD2HEX(gTCPD.d.aBuffer[4]);
				TM.tm_mday = BCD2HEX(gTCPD.d.aBuffer[3]);
				TM.tm_mon = BCD2HEX(gTCPD.d.aBuffer[2]) - 1;
				TM.tm_year = BCD2HEX(gTCPD.d.aBuffer[1]) + 100;
				TM.tm_wday = 0;
				TM.tm_yday = 0;
				TM.tm_isdst = 0;

				time_t time = mktime(&TM);

				LRD lrd;
				
				lrd.enable_ = 1;
				lrd.light_id_ = light_id;
				lrd.onoff_state_ = LIGHT_OFF;
				lrd.flag_ = 0;
				lrd.time_on_ = time;
				lrd.time_off_ = time + nOffset;
				
				AddReservation(&lrd);

				int8_t aBuffer[100];
				sprintf((char*)aBuffer, "Func5, Light=%d, %d-%02d-%02d %02d:%02d:%02d, Offset=%d\r\n timeRTC=%ld, time_on=%ld, time_off=%ld\r\n",
						light_id, TM.tm_year, TM.tm_mon, TM.tm_mday, TM.tm_hour, TM.tm_min, TM.tm_sec, nOffset, 
						timeRTC, lrd.time_on_, lrd.time_off_);				
				UartPrintf(UART_DEBUG, aBuffer);
			}
			SendWiFiCommand(CMD_REQUEST_SEND_ONOFF_RESULT_TO_SERVER);
			SetWaitingForResponse(_tick, 2000);
			break;
		
		case STATE_SEND_ONOFF_RESULT_TO_SERVER:
			SendWiFiCommand(CMD_SEND_ONOFF_RESULT_TO_SERVER);
			SetWaitingForResponse(_tick, 2000);
			break;
			
		///////////////////////////////////////////////////////////////
#endif		
		case STATE_IDLE_SERVER_CONNECTED:
			break;


		case STATE_RETRY_CONNECT_SERVER:
			SendWiFiCommand(CMD_DISCONNECT_SERVER);
			SetWaitingForResponse(_tick, 2000);
			break;
			
		case STATE_WAITING_REQUEST:
			// 데이터를 보내야 하는 상황인지 판단하고 데이터를 보냄.
			break;
            
		case STATE_SEND_DATA:
			break;
		}
	}
	else {
		if(1 == IsExpiredWaitingForResponse(_tick)) {
			ESTATE _lastCommand = GetLastCommand();

			switch (_lastCommand) {
#if 0				
			case CMD_SEND_NTP_PACKET:	
				InitReceiveDataState();
				SetState(STATE_REQUEST_SEND_NTP_PACKET);
				break;
#endif
			default:
				//SendWiFiCommand(CMD_RESET);
				break;
			}

			wsd.is_waiting_wifi_response_ = 0;
			wsd.last_wifi_command_tick_ = _tick;
		}
	}

	if(1 == IsExpiredWatchDogForSendingData(_tick)) {			
		// 마지막 데이터 패킷을 보냄
		//is_set_watchdog_send_ = 1;
		// 위 설정이 IsExpiredWatchDogForSendingData() 함수 내부적으로 자동으로 처리됨.
	}

	return 0;
}

#if 0
time_t GetNTPTime(NUD *pNUD)
{
	time_t timeSince1900;
	
	timeSince1900 = (time_t)((pNUD->aBuffer[40] << 24) | (pNUD->aBuffer[41] << 16) | 
							(pNUD->aBuffer[42] << 8) | pNUD->aBuffer[43]);

	return timeSince1900;
}

time_t GetTimeFromNTPTime(NUD *pNUD)
{
	time_t timeSince1970;
	
	timeSince1970 = (time_t)((pNUD->aBuffer[40] << 24) | (pNUD->aBuffer[41] << 16) | 
							(pNUD->aBuffer[42] << 8) | pNUD->aBuffer[43]) - NTP_OFFSET;

	return timeSince1970;
}

void MakeTM(struct tm* pTM, NUD *pNUD)
{
	time_t timeSince1900 = ntohl(nud.n.txTm_s) - NTP_OFFSET;

	time_t secondsEpoch = (time_t)(timeSince1900 + SEOUL_TIMEZONE_OFFSET);

	*pTM = *localtime(&secondsEpoch);
}

void ConvertNTPTimeToString(uint8_t *pstrTime, NUD *pNUD)
{
	// 1543622400UL		1970-01-01 - 2018-12-01
	// 2208988800UL		1900-01-01 - 1970-01-01
	uint32_t unSecsSince1970 = ((pNUD->aBuffer[40] << 24) | (pNUD->aBuffer[41] << 16) | (pNUD->aBuffer[42] << 8) | pNUD->aBuffer[43]) - NTP_OFFSET;

    time_t secondsEpoch = (time_t)(unSecsSince1970 + SEOUL_TIMEZONE_OFFSET);
    struct tm t = *localtime(&secondsEpoch);
    t.tm_year += 1900;
    t.tm_mon  += 1;

	sprintf((char*)pstrTime, "%d-%02d-%02d %02d:%02d:%02d", 
            t.tm_year, t.tm_mon, t.tm_mday, 
            t.tm_hour, t.tm_min, t.tm_sec);	
}

void SaveRTCWithNTPTime(NUD *pNUD)
{
	struct tm curTM;
	
	MakeTM(&curTM, &nud);
	WriteRTCTime(curTM);
}
#endif

void CMD_InitBuffer(UART_TYPE _uartType)
{
	cmdPack[_uartType].nIndex = 0;
	memset(cmdPack[_uartType].aBuffer, 0, MAX_CMDLINE_BUFFER_COUNT);
}
	
void CMD_PushChar(UART_TYPE _uartType, uint8_t ch)
{
	PCMDLINE_PACK pCmdPack	= &cmdPack[_uartType];

	if(pCmdPack->nIndex < MAX_CMDLINE_BUFFER_COUNT-1) {
		pCmdPack->aBuffer[pCmdPack->nIndex++] = ch;
	}
}

uint32_t CMD_GetBufferIndex(UART_TYPE _uartType) 
{
	return cmdPack[_uartType].nIndex;
}

