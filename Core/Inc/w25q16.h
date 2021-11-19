/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W25Q16_H__
#define __W25Q16_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "spi.h"
  
#define SectorSize			0x1000
#define PageSize			256
#define SectorCount			15 * 16
#define PageCount			(SectorCount * SectorSize) / PageSize
#define BlockSize			SectorSize * 16
#define CapacityInKiloByte	SectorCount * SectorSize / 1024;


#define _W25QXX_SPI                   hspi1
#define _W25QXX_CS_GPIO               FLASH_CS_GPIO_Port
#define _W25QXX_CS_PIN                FLASH_CS_Pin
#define _W25QXX_USE_FREERTOS          0
#define _W25QXX_DEBUG                 0
#define _W25QXX_USE_DMA           1

#define W25qxx_Wait() __NOP()  /* wait only a little */

#define W25qxx_Lock() (w25qxx.Lock = 1)
#define W25qxx_Unlock() (w25qxx.Lock = 0)
#define W25qxx_IsLocked() (w25qxx.Lock)
#define W25qxx_WaitAndLock() do { if(!W25qxx_IsLocked()) { W25qxx_Lock(); break; } else W25qxx_Wait(); } while(true)

// re-#define often used HAL function for speedup (esp. with constant PinState)
#define HAL_GPIO_WritePin(GPIOx,GPIO_Pin,PinState) \
((GPIOx)->BSRR = ((PinState) != GPIO_PIN_RESET)?(GPIO_Pin):((uint32_t)(GPIO_Pin) << 16U))

#define W25qxxSet() HAL_GPIO_WritePin(_W25QXX_CS_GPIO,_W25QXX_CS_PIN,GPIO_PIN_RESET)
#define W25qxxUnset() HAL_GPIO_WritePin(_W25QXX_CS_GPIO,_W25QXX_CS_PIN,GPIO_PIN_SET)

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern uint8_t buffer1[128];
extern uint8_t buffer2[128];
extern uint8_t uniqID[8];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

uint8_t flash_spi(uint8_t data);
void flash_write_enable(void);
void flash_write_disable(void);
void flash_write_byte(uint8_t pBuffer, uint32_t WriteAddr_inBytes);
void flash_write_page(uint8_t* pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_PageSize);
void flash_write_sector(uint8_t* pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize);
void flash_write_block(uint8_t* pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_BlockSize);
uint32_t flash_SectorToPage(uint32_t SectorAddress);
uint32_t flash_BlockToPage(uint32_t BlockAddress);
void flash_wait_end(void);
void flash_read_byte(uint8_t* pBuffer, uint32_t Bytes_Address);
void flash_read_bytes(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
void flash_read_page(uint8_t *pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize);
void flash_read_sector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize);
void flash_read_block(uint8_t* pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t	NumByteToRead_up_to_BlockSize);
uint8_t flash_read_Status(uint8_t register_num);
void flash_erase_chip(void);
void flash_erase_sector(uint32_t SectorAddr);
void flash_erase_block(uint32_t BlockAddr);
uint32_t flash_read_ID(void);
void flash_read_uniqID(void);

#ifdef __cplusplus
}
#endif

#endif /* __W25Q16_H__ */