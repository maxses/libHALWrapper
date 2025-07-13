/*----------------------------------------------------------------------------
 *
 * \brief   Minimal linker script for libHALWrapper example
 *
 * \author  Maximilian Seesslen
 *
 *---------------------------------------------------------------------------*/


__flash_page_size = 0x800;
__flash_size = 32K;
__heap_size = ( LENGTH(RAM) / 32 ) * 20;
__ram_size = 8K;
__stack_size = MIN ( ( LENGTH(RAM) / 32 ) * 8, 1536 );

INCLUDE "stm32_biwak.ld"


/*---fin----------------------------------------------------------------------*/
