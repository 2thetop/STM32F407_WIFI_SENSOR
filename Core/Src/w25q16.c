
#include "w25q16.h"

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t buffer1[128];
uint8_t buffer2[128];
uint8_t uniqID[8];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
#if 0
int _write(int file, char* p, int len)
{
	//HAL_UART_Transmit(&huart1, p, len, 10);
	return len;
}
#endif
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t flash_spi(uint8_t data)
{
	uint8_t ret;
	HAL_SPI_TransmitReceive(&hspi1, &data, &ret, 1, 100);
	return ret;
}


void flash_write_enable(void)
{
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x06);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	HAL_Delay(1);
}

void flash_write_disable(void)
{
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x04);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	HAL_Delay(1);
}

void flash_write_byte(uint8_t pBuffer, uint32_t WriteAddr_inBytes)
{
	flash_wait_end();
	flash_write_enable();
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x02);
	flash_spi((WriteAddr_inBytes & 0xFF0000) >> 16);
	flash_spi((WriteAddr_inBytes & 0xFF00) >> 8);
	flash_spi(WriteAddr_inBytes & 0xFF);
	flash_spi(pBuffer);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	flash_wait_end();
}

void flash_write_page(uint8_t* pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_PageSize)
{
	if(((NumByteToWrite_up_to_PageSize + OffsetInByte) > PageSize) || (NumByteToWrite_up_to_PageSize == 0))
		NumByteToWrite_up_to_PageSize = PageSize - OffsetInByte;
	if((OffsetInByte + NumByteToWrite_up_to_PageSize) > PageSize)
		NumByteToWrite_up_to_PageSize = PageSize - OffsetInByte;

	flash_wait_end();
	flash_write_enable();
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x02);
	Page_Address = (Page_Address * PageSize) + OffsetInByte;
	flash_spi((Page_Address & 0xFF0000) >> 16);
	flash_spi((Page_Address & 0xFF00) >> 8);
	flash_spi(Page_Address & 0xFF);
	HAL_SPI_Transmit(&hspi1, pBuffer, NumByteToWrite_up_to_PageSize, 100);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	flash_wait_end();
	HAL_Delay(1);
}

void flash_write_sector(uint8_t* pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize)
{
	if((NumByteToWrite_up_to_SectorSize > SectorSize) || (NumByteToWrite_up_to_SectorSize == 0))
		NumByteToWrite_up_to_SectorSize = SectorSize;

	uint32_t StartPage;
	int32_t BytesToWrite;
	uint32_t LocalOffset;
	if((OffsetInByte + NumByteToWrite_up_to_SectorSize) > SectorSize)
		BytesToWrite = SectorSize - OffsetInByte;
	else
		BytesToWrite = NumByteToWrite_up_to_SectorSize;
	StartPage = flash_SectorToPage(Sector_Address) + (OffsetInByte / PageSize);
	LocalOffset = OffsetInByte % PageSize;

	do
	{
		flash_write_page(pBuffer, StartPage, LocalOffset, BytesToWrite);
		StartPage++;
		BytesToWrite -= PageSize - LocalOffset;
		pBuffer += PageSize - LocalOffset;
		LocalOffset = 0;
	}while(BytesToWrite > 0);
}

void flash_write_block(uint8_t* pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_BlockSize)
{
	if((NumByteToWrite_up_to_BlockSize > BlockSize) || (NumByteToWrite_up_to_BlockSize == 0))
		NumByteToWrite_up_to_BlockSize = BlockSize;

	uint32_t	StartPage;
	int32_t		BytesToWrite;
	uint32_t	LocalOffset;

	if((OffsetInByte + NumByteToWrite_up_to_BlockSize) > BlockSize)
		BytesToWrite = BlockSize - OffsetInByte;
	else
		BytesToWrite = NumByteToWrite_up_to_BlockSize;
	StartPage = flash_BloackToPage(Block_Address) + (OffsetInByte / PageSize);
	LocalOffset = OffsetInByte % PageSize;
	do
	{
		flash_write_page(pBuffer, StartPage, LocalOffset, BytesToWrite);
		StartPage++;
		BytesToWrite -= PageSize-LocalOffset;
		pBuffer += PageSize - LocalOffset;
		LocalOffset=0;
	}while(BytesToWrite > 0);
}

uint32_t flash_SectorToPage(uint32_t SectorAddress)
{
	return (SectorAddress * SectorSize) / PageSize;
}

uint32_t flash_BlockToPage(uint32_t BlockAddress)
{
	return (BlockAddress * BlockSize) / PageSize;
}

void flash_wait_end(void)
{
	uint8_t stat = 0;

	HAL_Delay(1);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x05);
	do
	{
		stat = flash_spi(0xA5);
		HAL_Delay(1);
	}
	while((stat & 0x01) == 0x01);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
}


void flash_read_byte(uint8_t* pBuffer, uint32_t Bytes_Address)
{
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x0B);
	flash_spi((Bytes_Address & 0xFF0000) >> 16);
	flash_spi((Bytes_Address & 0xFF00) >> 8);
	flash_spi(Bytes_Address & 0xFF);
	flash_spi(0);
	*pBuffer = flash_spi(0xA5);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();

	printf("read 0x%02X\n", *pBuffer);
}

void flash_read_bytes(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x0B);
	flash_spi((ReadAddr & 0xFF0000) >> 16);
	flash_spi((ReadAddr& 0xFF00) >> 8);
	flash_spi(ReadAddr & 0xFF);
	flash_spi(0);
	HAL_SPI_Receive(&hspi1, pBuffer, NumByteToRead, 2000);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	HAL_Delay(1);
}

void flash_read_page(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize)
{
	if((NumByteToRead_up_to_PageSize > PageSize) || (NumByteToRead_up_to_PageSize == 0))
		NumByteToRead_up_to_PageSize = PageSize;
	if((OffsetInByte + NumByteToRead_up_to_PageSize) > PageSize)
		NumByteToRead_up_to_PageSize = PageSize - OffsetInByte;

	Page_Address = Page_Address * PageSize + OffsetInByte;
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x0B);
	flash_spi((Page_Address & 0xFF0000) >> 16);
	flash_spi((Page_Address& 0xFF00) >> 8);
	flash_spi(Page_Address & 0xFF);
	flash_spi(0);
	HAL_SPI_Receive(&hspi1, pBuffer, NumByteToRead_up_to_PageSize, 100);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	HAL_Delay(1);
}

void flash_read_sector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize)
{
	if((NumByteToRead_up_to_SectorSize > SectorSize) || (NumByteToRead_up_to_SectorSize == 0))
		NumByteToRead_up_to_SectorSize = SectorSize;

	uint32_t	StartPage;
	int32_t		BytesToRead;
	uint32_t	LocalOffset;
	if((OffsetInByte + NumByteToRead_up_to_SectorSize) > SectorSize)
		BytesToRead = SectorSize - OffsetInByte;
	else
		BytesToRead = NumByteToRead_up_to_SectorSize;
	StartPage = flash_SectorToPage(Sector_Address) + (OffsetInByte / PageSize);
	LocalOffset = OffsetInByte % PageSize;
	do
	{
		flash_read_page(pBuffer, StartPage, LocalOffset, BytesToRead);
		StartPage++;
		BytesToRead -= PageSize - LocalOffset;
		pBuffer += PageSize - LocalOffset;
		LocalOffset=0;
	}while(BytesToRead>0);
}

void flash_read_block(uint8_t* pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t	NumByteToRead_up_to_BlockSize)
{
	if((NumByteToRead_up_to_BlockSize > BlockSize) || (NumByteToRead_up_to_BlockSize == 0))
		NumByteToRead_up_to_BlockSize = BlockSize;

	uint32_t	StartPage;
	int32_t		BytesToRead;
	uint32_t	LocalOffset;
	if((OffsetInByte + NumByteToRead_up_to_BlockSize) > BlockSize)
		BytesToRead = BlockSize - OffsetInByte;
	else
		BytesToRead = NumByteToRead_up_to_BlockSize;
	StartPage = flash_BlockToPage(Block_Address) + (OffsetInByte / PageSize);
	LocalOffset = OffsetInByte % PageSize;
	do
	{
		flash_read_page(pBuffer, StartPage, LocalOffset, BytesToRead);
		StartPage++;
		BytesToRead -= PageSize-LocalOffset;
		pBuffer += PageSize - LocalOffset;
		LocalOffset=0;
	}while(BytesToRead > 0);
}

uint8_t flash_read_Status(uint8_t register_num)
{
	uint8_t status = 0;
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	if(register_num == 1)
	{
		flash_spi(0x05);
		status = flash_spi(0xA5);
	}
	else if(register_num == 2)
	{
		flash_spi(0x35);
		status = flash_spi(0xA5);
	}
	else
	{
		flash_spi(0x15);
		status = flash_spi(0xA5);
	}
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	return status;
}

void flash_erase_chip(void)
{
	flash_write_enable();
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0xC7);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	flash_wait_end();
	HAL_Delay(10);
}

void flash_erase_sector(uint32_t SectorAddr)
{
	flash_wait_end();
	SectorAddr = SectorAddr * SectorSize;
	flash_write_enable();
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x20);
	flash_spi((SectorAddr & 0xFF0000) >> 16);
	flash_spi((SectorAddr & 0xFF00) >> 8);
	flash_spi(SectorAddr & 0xFF);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	flash_wait_end();
	HAL_Delay(1);
}

void flash_erase_block(uint32_t BlockAddr)
{
	flash_wait_end();
	BlockAddr = BlockAddr * SectorSize * 16;
	flash_write_enable();
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0xD8);
	flash_spi((BlockAddr & 0xFF0000) >> 16);
	flash_spi((BlockAddr & 0xFF00) >> 8);
	flash_spi(BlockAddr & 0xFF);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	flash_wait_end();
	HAL_Delay(1);
}

uint32_t flash_read_ID(void)
{
	uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x9F);
	Temp0 = flash_spi(0xA5);
	Temp1 = flash_spi(0xA5);
	Temp2 = flash_spi(0xA5);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();
	Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
	return Temp;
}

void flash_read_uniqID(void)
{
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);   		// CS to low
	W25qxxSet();
	flash_spi(0x4B);
	for(uint8_t i=0; i<4; i++)
		flash_spi(0x4B);
	for(uint8_t i=0; i<8; i++)
		uniqID[i] = flash_spi(0x4B);;
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	W25qxxUnset();

	for(uint8_t i=0; i<8; i++)
		printf("%X", uniqID[i]);
	printf("\n");
}

/* USER CODE END 0 */
