#include "stm32f4xx.h"
#include "CircularQueue.h"


// CQ Buffer�� �ʱ�ȭ �ϴ� �Լ�.
// CQ�� ����ϱ� ���� �ѹ� ȣ���ϴ� �Լ�.
// CQ Buffer�� ����ť�� �����Ǿ��� MAX_CQ_BUFFER_COUNT-1�� ���� ���۸��� ������.
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

// ���� �Լ�.
// CQ Buffer�� ä���� ��Ŷ �������� ������ ���ϴ� �Լ�.
uint32_t CQ_GetDataCount(PCQ_BUFFER pCQ)
{
	uint32_t _count = 0;

	if(pCQ->nHead != pCQ->nTail) 
	{
		if(pCQ->nTail < pCQ->nHead) {
			_count = pCQ->nHead - pCQ->nTail;
		}
		else { 												
			_count = pCQ->nHead - pCQ->nTail + MAX_CQ_BUFFER_COUNT;
		}
	}
	
	return _count;
}

// ���� �Լ�.
// CQ Buffer�� ��� �ִ� ������ ������ ���ϴ� �Լ�.
uint32_t CQ_GetFreeCount(PCQ_BUFFER pCQ)
{
	uint32_t _count = MAX_CQ_BUFFER_COUNT-1;

	if(pCQ->nHead != pCQ->nTail) 
	{
		if(pCQ->nTail < pCQ->nHead) {
			_count = (pCQ->nTail+MAX_CQ_BUFFER_COUNT-1) - pCQ->nHead;
		}
		else {
			_count = (pCQ->nTail-1) - pCQ->nHead;
		}
	}
	
	return _count;
}

//���� �Լ�
// CQ Buffer�� Head�� ���ϴ� �Լ�.
uint32_t CQ_GetHead(PCQ_BUFFER pCQ)
{
	return pCQ->nHead;
}

//���� �Լ�
// CQ Buffer�� Tail�����ϴ� �Լ�.
uint32_t CQ_GetTail(PCQ_BUFFER pCQ)
{
	return pCQ->nTail;
}

//���� �Լ�
// CQ Buffer�� Head�� ������Ű�� �Լ�.
uint32_t CQ_IncreaseHead(PCQ_BUFFER pCQ)
{
	pCQ->nHead++;
	if(pCQ->nHead >= MAX_CQ_BUFFER_COUNT) {
		pCQ->nHead = 0;
	}
	return pCQ->nHead;
}

//���� �Լ�
// CQ Buffer�� Tail�� ������Ű�� �Լ�.
uint32_t CQ_IncreaseTail(PCQ_BUFFER pCQ)
{
	pCQ->nTail++;
	if(pCQ->nTail >= MAX_CQ_BUFFER_COUNT) {
		pCQ->nTail = 0;
	}
	return pCQ->nTail;
}

//���� �Լ�
// CQ Buffer�� ����ִ��� Ȯ���ϴ� �Լ�.
uint32_t CQ_IsEmpty(PCQ_BUFFER pCQ)
{
	return ((uint32_t)(pCQ->nHead == pCQ->nTail));
}

//���� �Լ�
// CQ Buffer�� Full���� Ȯ���ϴ� �Լ�.
uint32_t CQ_IsFull(PCQ_BUFFER pCQ)
{
	uint32_t nNewHead = pCQ->nHead + 1;
	if(nNewHead >= MAX_CQ_BUFFER_COUNT) {
		nNewHead = 0;
	}
	return ((uint32_t)(pCQ->nTail == nNewHead));
}

//���� �Լ�
// CQ Buffer���� ��� �ִ� ������ �����͸� ��� �Լ�.
// �� ���۰� ���ٸ� NULL�� ��ȯ.
volatile uint8_t* CQ_GetFreeBuffer(PCQ_BUFFER pCQ)
{
	volatile uint8_t* _pBuffer = NULL;

	if(0 == CQ_IsFull(pCQ))
	{
		_pBuffer = &pCQ->aQuque[pCQ->nHead];
	}
	return _pBuffer;
}

//���� �Լ�
// CQ Buffer���� �����Ͱ� ä���� ������ �����͸� ��� �Լ�.
// �����Ͱ� ä���� ���۰� ���ٸ� NULL�� ��ȯ.
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

