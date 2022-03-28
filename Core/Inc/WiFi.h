/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WIFI_H
#define __WIFI_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usart.h"
#include <time.h>

/* USER CODE BEGIN Includes */
#include "CircularQueue.h"
//#include "Packet.h"
/* USER CODE END Includes */

//extern UART_HandleTypeDef huart2;
//extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
	 
extern UART_Q gUarts[MAX_UART_PORT];
extern UART_HandleTypeDef *pUartHandleArray[MAX_UART_PORT];


/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */



typedef enum {

	State_Unknown=-1,
	State_Error=0,
	State_Reset=10,
	State_Init=20,
	State_APConnect=30,
	//State_IPGet=40,
	State_ServerMode=50,
	State_QuerySendData=60,
	//State_SendData=70,
	MAX_STATE_COUNT=6,
	
	State_Sub_Unknown=0,
	State_Sub_ServerConnect=80,
	State_Sub_QuerySendData=90,
	MAX_SUB_STATE_COUNT=2,


	/////////////////////////////////////////////////////////////////
	// Common Defines

	STATE_NOT_INIT=0,
	STATE_INIT=100,

	STATE_INIT_UART,
	CMD_INIT_UART,
	RSP_INIT_UART_OK,
	
	CMD_SET_MODE,
	RSP_SET_MODE_OK,
	
	STATE_SETUP_UART,
	CMD_SETUP_UART,

	STATE_CHECK_AP,
	CMD_CHECK_AP,
	RSP_AP_FOUND_OK,
	RSP_CHECK_AP_OK, 
	
	STATE_CONNECT_AP,
	CMD_CONNECT_AP,
	RSP_CONNECT_OK,

	STATE_AP_CONNECTED,

	STATE_CHECK_IP,
	CMD_CHECK_IP,
	RSP_CHECK_IP_OK,
	
	CMD_ENABLE_MULTICONNECT,
	RSP_MULTICONNECT_OK,

//	STATE_ENABLED_MULTICONNECTION,
	STATE_IDLE_AP_CONNECTED,

//	STATE_GET_NTP_TIME,
//	STATE_SEND_NTP_TIME,
//	STATE_SETUP_SERVER,

	CMD_NONE=0,
	CMD_COMMON=200,
	CMD_RESET=201,
//	CMD_GET_NTP_TIME=207,
//	CMD_SEND_NTP_TIME=208,
	CMD_SETUP_SERVER=209,

	// Common Response	
	RSP_NOT_FOUND=220,
	RSP_OK,
	RSP_RESET_OK,
	RSP_SETUP_UART,
	RSP_GOT_IP,
	RSP_ALREADY_CONNECT,
	RSP_CLOSED,
	RSP_READY_TO_SEND,
	RSP_SEND_OK,

//	RSP_GET_NTP_TIME_OK,
//	RSP_SEND_NTP_TIME_OK,

	RSP_CLOSED_SERVER,
//	RSP_CLOSED_NTP_SERVER,
	RSP_INVALID_LINK,

	RSP_SERVER_OK,


	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// LINK ID=0 Defines

	STATE_CONNECT_SERVER=300,
	CMD_CONNECT_SERVER,
	RSP_CONNECT_SERVER_OK,

	STATE_REQUEST_IDENTIFY_SERVER,
	CMD_REQUEST_IDENTIFY_SERVER,
	RSP_REQUEST_IDENTIFY_SERVER_OK,

	STATE_SEND_IDENTIFY_SERVER,
	CMD_SEND_IDENTIFY_SERVER,
	RSP_SEND_IDENTIFY_SERVER_OK,

	STATE_CHECK_IDENTIFY_SERVER,
#if 0
	// Function 1
	STATE_REQUEST_SEND_NTP_TIME_TO_SERVER,
	CMD_REQUEST_SEND_NTP_TIME_TO_SERVER,
	RSP_REQUEST_SEND_NTP_TIME_TO_SERVER_OK,

	STATE_SEND_NTP_TIME_TO_SERVER,
	CMD_SEND_NTP_TIME_TO_SERVER,
	RSP_SEND_NTP_TIME_TO_SERVER_OK,

	// Function 2	
	STATE_REQUEST_SEND_NEW_TIME_TO_SERVER,


	//Function 3
	
	STATE_REQUEST_SEND_ONOFF_RESULT_TO_SERVER,
	CMD_REQUEST_SEND_ONOFF_RESULT_TO_SERVER,
	RSP_REQUEST_SEND_ONOFF_RESULT_TO_SERVER_OK,

	STATE_SEND_ONOFF_RESULT_TO_SERVER,
	CMD_SEND_ONOFF_RESULT_TO_SERVER,
	RSP_SEND_ONOFF_RESULT_TO_SERVER_OK,
#endif


	STATE_WAITING_REQUEST,

	STATE_REQUEST_SEND_DATA,
	CMD_REQUEST_SEND_DATA,

	STATE_SEND_DATA,
	CMD_SEND_DATA,

	STATE_IDLE_SERVER_CONNECTED,
	
	STATE_RETRY_CONNECT_SERVER,
	CMD_DISCONNECT_SERVER,
	RSP_DISCONNECT_SERVER_OK,
	
	//CMD_CLOSE_SERVER=264,
	//CMD_GET_STATE=228,
	MAX_COMMAND_COUNT=14,

	/////////////////////////////////////////////////////////////////
#if 0
	/////////////////////////////////////////////////////////////////
	// LINK ID=2 Defines

	STATE_CONNECT_NTP_SERVER=400,
	CMD_CONNECT_NTP_SERVER,
	RSP_CONNECT_NTP_SERVER_OK,

	STATE_REQUEST_SEND_NTP_PACKET=410,
	CMD_REQUEST_SEND_NTP_PACKET,
	RSP_REQUEST_SEND_NTP_PACKET_OK,

	STATE_SEND_NTP_PACKET=420,
	CMD_SEND_NTP_PACKET,
	RSP_SEND_NTP_PACKET_OK,

	STATE_WAIT_NTP_PACKET=430,
	RSP_WAIT_NTP_PACKET_OK,

	STATE_SET_NTP_TIME,

	STATE_DISCONNECT_NTP_SERVER=440,
	CMD_DISCONNECT_NTP_SERVER,
	RSP_DISCONNECT_NTP_SERVER_OK,
	/////////////////////////////////////////////////////////////////	

	RSP_NTP_TIME_PACKET,

	RSP_FUNCTION_0,
	
	REQ_FUNCTION_1,
	REQ_FUNCTION_2,
	REQ_FUNCTION_3,
	REQ_FUNCTION_4,
	REQ_FUNCTION_5,
	//RSP_CLOSE_OK=313,
	//RSP_STATE_OK=315,
	MAX_RESPONSE_COUNT=11,
#endif

	STATE_RECEIVE_MODE_INIT=0,
	STATE_RECEIVE_MODE_PLUS=500,
	STATE_RECEIVE_MODE_I,
	STATE_RECEIVE_MODE_P,
	STATE_RECEIVE_MODE_D,
	STATE_RECEIVE_MODE_COMMA1,
	STATE_RECEIVE_MODE_ID,
	STATE_RECEIVE_MODE_COMMA2,
	STATE_RECEIVE_MODE_LENGTH1,
	STATE_RECEIVE_MODE_LENGTH2,
	STATE_RECEIVE_MODE_DATA,
} ESTATE, *PESTATE;



typedef enum {
	STATE_NO_WIFI = 0,
	STATE_WIAT_CONFIG_DATA,
	STATE_READ_EEPROM,
	STATE_START_CONNECTING,
	STATE_CONNECTING_WIFI_AP,
	STATE_CONNECTED_AP,
	STATE_CONNECTED_SERVER,
} ESTATE_ARDUINO;


#define MAX_ARGS_COUNT		72

typedef struct {
	UART_TYPE 	uartType;
	int8_t 	 *args[MAX_ARGS_COUNT];
	uint32_t  argc;
	void *param;
} ARGUMENTS_CB, *PARGUMENTS_CB;

typedef uint32_t (*FXCmdLine)(PARGUMENTS_CB pArgs);

typedef struct {
	const int8_t 	*cmd;
	FXCmdLine	fx;
	const int8_t	*help;
} CMDLINE_CB, *PCMDLINE_CB;


#define MAX_CMDLINE_BUFFER_COUNT		256

typedef struct {
	int8_t aBuffer[MAX_CMDLINE_BUFFER_COUNT];
	uint32_t nIndex;
} CMDLINE_PACK, *PCMDLINE_PACK;



#define DATA_SEND_TIMEOUT_INTERVAL			10000
#define RESET_COMMAND_WAIT_TIMEOUT			8000
#define SETMODE_COMMAND_WAIT_TIMEOUT		3000


typedef struct WIFI_STATE_DATA {

	ESTATE 	state_;

	ESTATE 	last_sent_command_;

	uint32_t watchdog_send_interval_;
	uint32_t last_watchdog_send_tick_;
	uint32_t is_set_watchdog_send_;
	uint32_t is_enabled_watchdog_send_;


	uint32_t is_waiting_wifi_response_;
	uint32_t wifi_command_interval_;
	uint32_t last_wifi_command_tick_;
	uint32_t wifi_command_retry_count_;
	uint32_t wifi_command_retry_count_limit_;

	uint32_t is_delaying_wifi_command_;
	uint32_t wifi_command_delay_;
	uint32_t wifi_command_delay_tick_;

	uint32_t wifi_command_recoonect_count_;
	uint32_t wifi_command_recoonect_count_limit_;

	//uint8_t 	ntp_server_connected_;
	//uint8_t 	ntp_read_;
	uint8_t 	server_connected_;
	uint8_t 	server_identified_;
	
	//uint32_t ntp_retry_count_;
	//uint32_t max_ntp_retry_count_;
	
	//uint32_t last_ntp_time_tick_;
	//uint32_t max_ntp_time_tick_;
	
	uint32_t last_ping_tick_;
	uint32_t max_ping_tick_;
} WSD, *PWSD;


typedef struct SERVER_STATE_DATA {
	WSD		wsd;
	
	ESTATE 	gvReceiveMode;
	int 	nTotalReceiveDataCount;
	int 	nCurrentReceiveDataCount;
	int 	nReceiveChannel;
	uint8_t aReceiveDataCount[3];

	//TCPD	gTCPD;
} SSD, *PSSD;


typedef struct st_AP_INFO {
	uint8_t szSSID[64];
	uint8_t szPassword[64];
	uint32_t portNum;
} APINFO, *PAPINFO;



#define MAX_SSID_LENGTH        32
#define MAX_PASSWORD_LENGTH    32
#define MAX_HOST_IP_LENGTH     15
#define MAX_PORT_LENGTH        2

typedef struct CONFIG_DATA_INFO {
  //uint16_t size;
  char ssid[MAX_SSID_LENGTH+1];
  char password[MAX_PASSWORD_LENGTH+1];
  char host[MAX_HOST_IP_LENGTH+1];
  uint16_t port;
  uint16_t id; 
} CDI, *PCDI;



uint32_t Arduino_ParsingProc(UART_TYPE _uartType, uint8_t ch);
uint8_t IsConnectedArduinoServer();
uint8_t IsUpdatedCDI();
void SetUpdateCDI(uint8_t _update);
PCDI GetCDI();
void SetCdiSSID(char *puff, uint32_t length);
void SetCdiPassword(char *puff, uint32_t length);
void SetCdiHost(char *puff, uint32_t length);
void SetCdiPort(int num);
void SetCdiID(int num);


uint32_t WiFi_ParsingProc(UART_TYPE _uartType, uint8_t ch);
uint32_t Arduino_ParsingProc(UART_TYPE _uartType, uint8_t ch);
void InitReceiveDataState();
uint8_t CheckReceiveData(UART_TYPE _uartType, uint8_t ch);
void DumpCmdPack(UART_TYPE _uartType, int8_t *line, uint32_t count);
void ParseReceiveData(UART_TYPE _uartType, uint8_t ch);

uint32_t WiFi_DefaultProc(uint32_t _tick);


void InitWiFi();

void InitWSD(PWSD pWSD);
void InitSSD(PSSD pSSD);

ESTATE GetMode(void); 
void SetMode(ESTATE _state);
ESTATE GetSbMode(void); 
void SetSubMode(ESTATE _state);


ESTATE GetLastCommand(); 
void SetLastCommand(ESTATE _last_command);
uint32_t IsDelayingToSendCommand(void);
void SetDelayingToSendCommand(uint32_t _tick, uint32_t _delay);
uint32_t CheckReadyToSendCommand(uint32_t _tick);
uint32_t IsWaitingForResponse(void);
void ClearWaitingForResponse(void);
void SetWaitingForResponse(uint32_t _tick, uint32_t _interval);
uint32_t IsExpiredWaitingForResponse(uint32_t _tick);
void ClearReconnectCount();
void IncreaseReconnectCount();
uint32_t IsExpiredWaitingForReconnect();
void EnableWatchDogForSendingData(uint32_t _enable, uint32_t _tick);
void ResetWatchDogForSendingData(uint32_t _tick);
uint32_t IsExpiredWatchDogForSendingData(uint32_t _tick);
uint32_t IsResendSensorData(void);
#if 0
uint8_t IsReadNTP();
void SetReadNTP(uint8_t _ntp_read);

void SetNTPTImeTick(uint32_t _tick);
uint8_t IsExpiredNTPTImeTick(uint32_t _tick);
uint8_t CheckReceivedNTPTIme(uint32_t _tick);

void ResetNTPRetryCount();
void IncreaseNTPRetryCount();
uint8_t IsExceededNTPReryCount();
#endif

uint8_t IsConnectedServer();
void SetConnectedServer(uint8_t _server_connected);
uint8_t IsIdentifiedServer();
void SetIdentifiedServer(uint8_t _server_identified);

void SetPingTick(uint32_t _tick);
uint8_t IsExpiredPingTick(uint32_t _tick);
uint8_t CheckConnectingServer(uint32_t _tick);

void SendWiFiCommand(ESTATE _state);

void ResetESP8266ByGPIO();
void ResetESP8266();
void InitESP8266Uart();
void SetStationMode();
void CheckAP();
void SetMulticonnectionMode();

int32_t CompareSSID(int8_t*);
//void ConnectAP(int32_t ap_index);
void ConnectAP(int8_t const *pszSSID, int8_t const *pszPassword);
void CheckIPAddress();

#if 0
// NTP Server Function
void ConnectNTPServer(int8_t *pNTP);
void RequestSendNTPPacket();
void SendNTPPacket();
void DisconnectNTPServer();
#endif

// Server Function
void ConfigureServer();
void ConnectServer(int8_t *pServer, int32_t port_number);
void DisconnectServer();


void CMD_InitBuffer(UART_TYPE _uartType);
void CMD_PushChar(UART_TYPE _uartType, uint8_t ch);
uint32_t CMD_GetBufferIndex(UART_TYPE _uartType);


#if 0
void RequestSendPacketToNTPServer(int8_t count);

void RequestSendIdentifyCommand();
void MakeFunctionCommand(PTCPD pTCPD, int nFuncNum, uint8_t nDataSize = 0);
void RequestToSendData(int32_t ch_id, int32_t count);
void SendFuntion0Command(void);
void RequestSendNTPTimeToServer();
void SendNTPTImeToServer();

// Synch NTP Time
void SendFuntion1Response(uint8_t resp, struct tm *pTM);
// Set Time Offset
void SendFuntion2Response(uint8_t resp, struct tm *pTM);

//Light On
void RequestSendOnOffResultToServer();
void SendOnOffResultToServer();

void SendFuntion3Response(uint8_t resp);
//Light Off
void SendFuntion4Response(uint8_t resp);
// Reserve Light On Off Time
void SendFuntion5Response(uint8_t resp);
#endif

#define MAKE_INT32(a, b, c, d)		        ((((int)(d) << 24) & 0xFF000000) | \
											(((int)(c) << 16) & 0x00FF0000) |  \
											(((int)(b) << 8) & 0x0000FF00) |   \
											((int)(a) & 0x000000FF))
											
#define HEX2BCD(a) 		((((a) / 10) << 4) | ((a) % 10))
#define BCD2HEX(a)		((((a >> 4) & 0x0F) * 10) + ((a) & 0x0F))

#ifndef htonl
#define htonl(a)                    \
    ((((a) >> 24) & 0x000000ff) |   \
     (((a) >>  8) & 0x0000ff00) |   \
     (((a) <<  8) & 0x00ff0000) |   \
     (((a) << 24) & 0xff000000))
#endif

#ifndef ntohl
#define ntohl(a)    htonl((a))
#endif 

#if 0
#define NTP_OFFSET                          2208988800ULL
#define SEOUL_TIMEZONE_OFFSET				(9 * 60 * 60)


time_t GetNTPTime(NUD *pNUD);
time_t GetTimeFromNTPTime(NUD *pNUD);

void MakeTM(struct tm* pTM, NUD *pNUD);

void ConvertNTPTimeToString(uint8_t *pstrTime, NUD *pNUD);
void SaveRTCWithNTPTime(NUD *pNUD);

#endif


/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /* __WIFI_H */

/**
  * @}
  */

/**
  * @}
  */

