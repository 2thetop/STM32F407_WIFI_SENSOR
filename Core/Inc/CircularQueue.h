#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#define MAX_CQ_BUFFER_COUNT		256		/// 0x0200
//volatile uint32_t nHead;
//volatile uint32_t nTail;
//volatile uint8_t	aCQBuffer[MAX_CQ_BUFFER_COUNT];

typedef struct {
	uint32_t nHead;
	uint32_t nTail;
	uint8_t	aQuque[MAX_CQ_BUFFER_COUNT];
} CQ_BUFFER, *PCQ_BUFFER;


void CQ_InitBuffer(PCQ_BUFFER pCQ);
void CQ_RemoveAll(PCQ_BUFFER pCQ);
uint32_t CQ_GetDataCount(PCQ_BUFFER pCQ);
uint32_t CQ_GetFreeCount(PCQ_BUFFER pCQ);
uint32_t CQ_GetHead(PCQ_BUFFER pCQ);
uint32_t CQ_GetTail(PCQ_BUFFER pCQ);
uint32_t CQ_IncreaseHead(PCQ_BUFFER pCQ);
uint32_t CQ_IncreaseTail(PCQ_BUFFER pCQ);
uint32_t CQ_IsEmpty(PCQ_BUFFER pCQ);
uint32_t CQ_IsFull(PCQ_BUFFER pCQ);
volatile uint8_t* CQ_GetFreeBuffer(PCQ_BUFFER pCQ);
volatile uint8_t* CQ_GetDataBuffer(PCQ_BUFFER pCQ);
uint32_t CQ_PushChar(PCQ_BUFFER pCQ, uint8_t data);
uint32_t CQ_PushString(PCQ_BUFFER pCQ, uint8_t* pData, uint32_t count);
uint32_t CQ_PopChar(PCQ_BUFFER pCQ, uint8_t* pData);
uint32_t CQ_PopString(PCQ_BUFFER pCQ, uint8_t* pData, uint32_t count);

#endif	// #ifndef __CIRCULAR_QUEUE_H__

