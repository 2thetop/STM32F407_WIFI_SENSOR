/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_NOR_H_
#define __SPI_NOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "w25qxx.h"
#include "w25qxxConf.h"
  
#include "string.h"
/* USER CODE BEGIN Includes */
//#include "CircularQueue.h"
/* USER CODE END Includes */


#define MAX_DUST_DATA_COUNT  32


bool spinor_init();
int spinor_read_block(uint32_t address, uint8_t *buffer, uint32_t length);
int spinor_write_block(uint32_t address, uint8_t *buffer, uint32_t length);
void check_nor_command(char *command);


/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_NOR_H_ */



