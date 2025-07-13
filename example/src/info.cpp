/**---------------------------------------------------------------------------
 *
 * @file   info.cpp
 * @brief  Print some information for the libHALWrapper example
 *
 * Print some memory locations. Most symbols are defined in the linker script.
 *
 * @date   20250719
 * @author Maximilian Seesslen <development@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <stdio.h>


/*--- Declarations ---------------------------------------------------------*/


extern char __heap_start;
extern char __heap_end;
register int *sp asm ("sp");
extern char _sdata;
extern char _edata;
extern char _sidata;


/*--- Implementation -------------------------------------------------------*/


void info()
{
   char* string=nullptr;
   char* string2=nullptr;
   
   // Allocate some memory to check if _sbrk works correctly.
   string=new char[10];
   string[0]=0;
   string2=new char[10];
   
   printf("Malloc 1:    %p\n", string );
   printf("Malloc 2:    %p\n", string2 );
   printf("SP           %p\n", sp );
   printf("Heap Start:  %p\n", &__heap_start );
   printf("Heap End:    %p\n", &__heap_end );
   printf("sidata  :    %p\n", &_sidata );
   printf("sdata   :    %p\n", &_sdata );
   printf("edata   :    %p\n", &_edata );
   
   return;
};


/*--- Fin ------------------------------------------------------------------*/
