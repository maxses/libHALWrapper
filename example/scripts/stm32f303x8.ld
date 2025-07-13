/*----------------------------------------------------------------------------
 *
 * \brief   Minimal linker script for libHALWrapper example
 *
 * \author  Maximilian Seesslen
 *
 *---------------------------------------------------------------------------*/

/*
 *  Number of total properties: 28
 */

__flash_page_size = 0x800;
__flash_size = 128K;
__heap_size = ( LENGTH(RAM) / 32 ) * 20;
__ram_size = 12K;
__stack_size = MIN ( ( LENGTH(RAM) / 32 ) * 8, 1536 );

INCLUDE "stm32_biwak.ld"


/*---fin----------------------------------------------------------------------*/
