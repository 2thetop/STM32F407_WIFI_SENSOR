#include "spinor.h"

bool spinor_init()
{
  bool bret = false;
  bret = W25qxx_Init();
  return bret;
}


int spinor_read_block(uint32_t address, uint8_t *buffer, uint32_t length)
{
    uint8_t  block_num;
    uint32_t block_addr = 0;
    uint32_t block_size = W25qxx_GetBlockSize();

    if((address % block_size) != 0)
    {
        //printf("ERROR :: %s() : address does  not align by %ldKb\r\n", __func__, block_size / 1024);
        return -1;
    }

    if((length % block_size) == 0)
        block_num = (length / block_size);
    else
        block_num  = (length / block_size) + 1;
    block_addr = address / block_size;

    for(int i = 0 ; i < block_num ; i++)
    {
        if(i == (block_num - 1))
            W25qxx_ReadBlock(&buffer[i*block_size], i+block_addr, 0, length);
        else
        {
            W25qxx_ReadBlock(&buffer[i*block_size], i+block_addr, 0, block_size);
            length -= block_size;
        }
    }

    return 0;
}

/*
    spinor_write_block() 함수에서 FLASH 특성에 따라 
    W25qx_WriteBlock() 함수를 호출하기 전에 
    W25qxx_EraseBlock() 함수를 호출해야 하는 것을 명심하도록 한다.
*/
int spinor_write_block(uint32_t address, uint8_t *buffer, uint32_t length)
{
    uint8_t  block_num;
    uint32_t block_addr = 0;
    uint32_t block_size = W25qxx_GetBlockSize();

    if((address % block_size) != 0)
    {
        //printf("ERROR :: %s() : address does  not align by %ldKb\r\n", __func__, block_size / 1024);
        return -1;
    }

    if((length % block_size) == 0)
        block_num = (length / block_size);
    else
        block_num  = (length / block_size) + 1;
    block_addr = address / block_size;

    for(int i = 0 ; i < block_num ; i++)
    {
        W25qxx_EraseBlock(i+block_addr);

        if(i == (block_num - 1))
            W25qxx_WriteBlock(&buffer[i*block_size], i+block_addr, 0, length);
        else
        {
            W25qxx_WriteBlock(&buffer[i*block_size], i+block_addr, 0, block_size);
            length -= block_size;
        }
    }

    return 0;
}


void check_nor_command(char *command)
{
#if 0
    if(strncmp(command, "info", 4) == 0)
    {
        printf("NOR info ======================\r\n");
        printf("FLASH size   = 0x%lx\r\n", spinor_get_size());
        printf("Block size   = 0x%lx\r\n", spinor_get_block_size());
        printf("Sector size  = 0x%lx\r\n", spinor_get_sector_size());
    }    
    else if(strncmp(command, "bread", 5) == 0)
    {
        uint32_t check_time;
        uint32_t length = spinor_get_block_size()*16;

        memset(block1, 0x00, length);
        check_time  = HAL_GetTick();
        spinor_read_block(0x10000, block1, length);
        printf("1MB(16 Block) Read  :: proc_time = %ld\r\n", (HAL_GetTick() - check_time));
        if(memcmp(block0, block1, length) != 0) printf("block does not same !!!\r\n");
    }
    else if(strncmp(command, "bwrite", 6) == 0)
    {
        uint32_t check_time;
        uint32_t length = spinor_get_block_size() * 16;

        memset(block0, 0xA0, length);
        check_time  = HAL_GetTick();
        spinor_write_block(0x10000, block0, length);
        printf("1MB(16 Block) Write :: proc_time = %ld\r\n", (HAL_GetTick() - check_time));
    }
#endif
}