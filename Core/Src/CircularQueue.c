#include "stm32f1xx.h"
#include "CircularQueue.h"


// CQ Buffer를 초기화 하는 함수.
// CQ를 사용하기 전에 한번 호출하는 함수.
// CQ Buffer는 원형큐로 구현되었고 MAX_CQ_BUFFER_COUNT-1개 까지 버퍼링이 가능함.
void CQ_InitBuffer(PCQ_BUFFER pCQ)
{
	uint32_t	i;

	//pCQ_ = pCQ;
	
	pCQ->nHead = 0;
	pCQ->nTail = 0;

	for(i=0; i<MAX_CQ_BUFFER_COUNT; i++)
	{
		pCQ->aQuque[i] = 0;
	}
}

void CQ_RemoveAll(PCQ_BUFFER pCQ)
{
	pCQ->nHead = 0;
	pCQ->nTail = 0;
}

// 내부 함수.
// CQ Buffer에 채워진 패킷 데이터의 개수를 구하는 함수.
uint32_t CQ_GetDataCount(PCQ_BUFFER pCQ)
{
	uint32_t _count = 0;

	if(pCQ->nHead != pCQ->nTail) 
	{
		if(pCQ->nTail < pCQ->nHead) _count = pCQ->nHead - pCQ->nTail;
		else 												_count = pCQ->nHead - pCQ->nTail + MAX_CQ_BUFFER_COUNT;
	}
	
	return _count;
}

// 내부 함수.
// CQ Buffer에 비어 있는 버퍼의 개수를 구하는 함수.
uint32_t CQ_GetFreeCount(PCQ_BUFFER pCQ)
{
	uint32_t _count = MAX_CQ_BUFFER_COUNT-1;

	if(pCQ->nHead != pCQ->nTail) 
	{
		if(pCQ->nTail < pCQ->nHead) _count = (pCQ->nTail+MAX_CQ_BUFFER_COUNT-1) - pCQ->nHead;
		else 												_count = (pCQ->nTail-1) - pCQ->nHead;
	}
	
	return _count;
}

//내부 함수
// CQ Buffer의 Head를 구하는 함수.
uint32_t CQ_GetHead(PCQ_BUFFER pCQ)
{
	return pCQ->nHead;
}

//내부 함수
// CQ Buffer의 Tail을구하는 함수.
uint32_t CQ_GetTail(PCQ_BUFFER pCQ)
{
	return pCQ->nTail;
}

//내부 함수
// CQ Buffer의 Head를 증가시키는 함수.
uint32_t CQ_IncreaseHead(PCQ_BUFFER pCQ)
{
	pCQ->nHead++;
	if(pCQ->nHead >= MAX_CQ_BUFFER_COUNT) {
		pCQ->nHead = 0;
	}
	return pCQ->nHead;
}

//내부 함수
// CQ Buffer의 Tail을 증가시키는 함수.
uint32_t CQ_IncreaseTail(PCQ_BUFFER pCQ)
{
	pCQ->nTail++;
	if(pCQ->nTail >= MAX_CQ_BUFFER_COUNT) {
		pCQ->nTail = 0;
	}
	return pCQ->nTail;
}

//내부 함수
// CQ Buffer가 비어있는지 확인하는 함수.
uint32_t CQ_IsEmpty(PCQ_BUFFER pCQ)
{
	return ((uint32_t)(pCQ->nHead == pCQ->nTail));
}

//내부 함수
// CQ Buffer가 Full인지 확인하는 함수.
uint32_t CQ_IsFull(PCQ_BUFFER pCQ)
{
	uint32_t nNewHead = pCQ->nHead + 1;
	if(nNewHead >= MAX_CQ_BUFFER_COUNT) {
		nNewHead = 0;
	}
	return ((uint32_t)(pCQ->nTail == nNewHead));
}

//내부 함수
// CQ Buffer에서 비어 있는 버퍼의 포인터를 얻는 함수.
// 빈 버퍼가 없다면 NULL을 반환.
volatile uint8_t* CQ_GetFreeBuffer(PCQ_BUFFER pCQ)
{
	volatile uint8_t* _pBuffer = NULL;

	if(0 == CQ_IsFull(pCQ))
	{
		_pBuffer = &pCQ->aQuque[pCQ->nHead];
	}
	return _pBuffer;
}

//내부 함수
// CQ Buffer에서 데이터가 채워진 버퍼의 포인터를 얻는 함수.
// 데이터가 채워진 버퍼가 없다면 NULL을 반환.
volatile uint8_t* CQ_GetDataBuffer(PCQ_BUFFER pCQ)
{
	volatile uint8_t* _pBuffer = NULL;

	if(0 == CQ_IsEmpty(pCQ))
	{
		_pBuffer = &pCQ->aQuque[pCQ->nTail];
	}
	return _pBuffer;
}


uint32_t CQ_PushChar(PCQ_BUFFER pCQ, uint8_t data)
{
	uint32_t _bRet = 0;
	
	if(0 == CQ_IsFull(pCQ))
	{
		pCQ->aQuque[pCQ->nHead] = data;
		CQ_IncreaseHead(pCQ);
		_bRet = 1;
	}

	return _bRet;
}


uint32_t CQ_PushString(PCQ_BUFFER pCQ, uint8_t* pData, uint32_t count)
{
	uint8_t* _pDest = pData;
	uint32_t _nFreeCount = MAX_CQ_BUFFER_COUNT - CQ_GetDataCount(pCQ);
	uint32_t _nCopyCount = (_nFreeCount>count)?count:_nFreeCount;
	
	uint32_t i;

	for(i = 0; i<_nCopyCount; i++)
	{
		pCQ->aQuque[pCQ->nHead++] = *_pDest++;
		if(pCQ->nHead >= MAX_CQ_BUFFER_COUNT) {
			pCQ->nHead = 0;
		}
	}

	return _nCopyCount;
}

uint32_t CQ_PopChar(PCQ_BUFFER pCQ, uint8_t* pData)
{
	uint32_t _bRet = 0;

	if(0 == CQ_IsEmpty(pCQ))
	{
		*pData = pCQ->aQuque[pCQ->nTail];
		CQ_IncreaseTail(pCQ);
		_bRet = 1;
	}

	return _bRet;
}

uint32_t CQ_PopString(PCQ_BUFFER pCQ, uint8_t* pData, uint32_t count)
{
	uint8_t* _pDest = pData;
	uint32_t _nDataCount = CQ_GetDataCount(pCQ);
	uint32_t _nCopyCount = (_nDataCount>count)?count:_nDataCount;
	
	uint32_t i;

	for(i = 0; i<_nCopyCount; i++)
	{
		*_pDest++ = pCQ->aQuque[pCQ->nTail++];
		if(pCQ->nTail >= MAX_CQ_BUFFER_COUNT) {
			pCQ->nTail = 0;
		}
	}

	return _nCopyCount;
}

