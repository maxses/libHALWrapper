/*----------------------------------------------------------------------------

   \brief   linker script include file for stm32 controllers

            This version has to be used when application is running in
            flash memory.

   \author  Maximilian Seesslen <mes@seesslen.net>
   \date    <20130403> file created

----------------------------------------------------------------------------*/


OUTPUT_FORMAT( "elf32-littlearm", "elf32-bigarm", "elf32-littlearm" )
OUTPUT_ARCH( arm )

/* Entry Point */
ENTRY(Reset_Handler)

/* 16K is 0x4000; assume the bootloader is small enough to have one more erase 
   page available for the application: 0x3C00
*/
/* bootloader_size = DEFINED(__bootloader_size) ? __bootloader_size : 0x4000; */

flash_origin = DEFINED(__flash) ? __flash : 0x08000000;

/*
   Input defines:

   BOOTLOADER_IVT_RAM:
      If bootloader is used, the ISR-Table is needed to be copied to RAM due to
      MCU limitations.
   BOOTLOADER:
      The created binary s an bootloader at the start of the flash.
   APPLICATION_WITH_BOOTLOADER:
      The created binary s an aplpication thats located after an bootloader in
      the flash.
*/

/* The functionality DEFINED( ) only works in the "MEMORY" block. 
   An dummy "RAM_IVT" region has to be created to check if an vector 
   table block in RAM has to be reserved afterwards when custom bootloader is 
   used.
*/
MEMORY
{
   FLASH_TOTAL(rx) : ORIGIN = flash_origin, LENGTH = __flash_size
   FLASH_BL(rx)    : ORIGIN = flash_origin, LENGTH = DEFINED(__bootloader_size) ? __bootloader_size : 0x4000
   FLASH_APP(rx)   : ORIGIN = flash_origin + LENGTH( FLASH_BL )
                   , LENGTH = __flash_size - LENGTH( FLASH_BL )
   
   FLASH(rx)       : ORIGIN = DEFINED( BOOTLOADER ) ?   ORIGIN( FLASH_BL )
                            : DEFINED( APPLICATION_WITH_BOOTLOADER ) ?  ORIGIN( FLASH_APP )
                            : ORIGIN( FLASH_TOTAL )
                   , LENGTH = DEFINED( BOOTLOADER ) ? LENGTH( FLASH_BL )
                            : DEFINED( APPLICATION_WITH_BOOTLOADER ) ? ( __flash_size - LENGTH( FLASH_BL ) )
                            : LENGTH( FLASH_TOTAL )
                            
   RAM(rw)         : ORIGIN = ( DEFINED(__ram) ? __ram : 0x20000000 )
                   , LENGTH =  __ram_size
                              
   /* Just a dummy length, calculate it in the section itself.
    * The fixed size of "0x100" just means "ivt in ram present"
    */
   RAM_IVT(rw)     : ORIGIN = 0x20000000
                   , LENGTH = DEFINED( BOOTLOADER_IVT_RAM ) ?  (
                              DEFINED( BOOTLOADER ) ?  ( 0x100  ) :
                              DEFINED( APPLICATION_WITH_BOOTLOADER ) ? ( 0x100 ) : 0x0 ) : 0x0
}

 
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size =  __heap_size;      /* required amount of heap  */
_Min_Stack_Size = __stack_size;     /* required amount of stack */

_FLASH_CURRENT = ORIGIN(FLASH);
_FLASH_APP = ORIGIN(FLASH_APP);
_FLASH_BOOTLOADER = ORIGIN(FLASH_BL);
_FLASH = ORIGIN(FLASH_TOTAL);
_FLASH_SIZE_TOTAL = LENGTH( FLASH_TOTAL );

_sflash = ORIGIN(FLASH);
_eflash = ORIGIN(FLASH) + LENGTH(FLASH);
_eram = ORIGIN(RAM) + LENGTH(RAM);
bootloader_size = LENGTH( FLASH_BL );
__heap_end = _eram - _Min_Stack_Size;

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM); /* Used by libstm startup code*/

/* Do not support proper exit in newlib. Otherwise the .fini section can not
 * be discarded.
 */
__libc_fini_array = 0;


/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector_ins (READONLY):
  {
    . = ALIGN(4);
    KEEP( *(.isr_vector) ) /* Startup code */
    . = ALIGN(4);
    _end_vectors = .;
  } >FLASH
  
  /* The program code and other data goes into FLASH */
  .text (READONLY):
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    /* *(.glue_7) */        /* glue arm to thumb code */
    /* *(.glue_7t) */       /* glue thumb to arm code */
    *(.eh_frame)

    /* referenced by newlib */
    /* *(.fini) */

    KEEP (*(.init))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
    
  } >FLASH

/*
   .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
    .ARM : {
    __exidx_start = .;
      *(.ARM.exidx*)
      __exidx_end = .;
    } >FLASH
*/

  .preinit_array (READONLY):
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  
  .init_array (READONLY):
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  
   /*
   Is not needed, does not finish/exit.
  .fini_array (READONLY):
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array*))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH
  */

  /* used by the startup to initialize data */
  _sidata = .;

   .ram_ivt :
   {
     . += LENGTH( RAM_IVT ) ? SIZEOF( .isr_vector_ins ) : 0x0;
   } >RAM
   
   PROVIDE( _sizeof_ram_ivt = SIZEOF( .ram_ivt ) );

  /* Initialized data sections goes into RAM, load LMA copy after code */
  /*.dynamic        : { *(.dynamic) }*/
  /*.got            : { *(.got.plt) *(.got) }*/
  .data_all : AT ( _sidata )
  {
    . = .;
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    /* *(.dynamic) */
    *(.got*)           /* linking breaks when missing without expressive message on miniminutnik.
                        * No ".got" section was found in miniminutnik or libraries.
                        */
    /* *(.got.plt) */
    /* *(.got) */
    
    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM

	.tbss (NOLOAD) : {
		*(.tbss .tbss.* .gnu.linkonce.tb.*)
		*(.tcommon)
		PROVIDE( __tls_end = . );
	} >RAM AT>RAM
	/* :tls :ram */
	PROVIDE( __bss_start = ADDR(.tbss));
	PROVIDE( __tbss_size = SIZEOF(.tbss) );
	PROVIDE( __tls_size = __tls_end - __tls_base );

  .marker (NOLOAD) :
  {
     
     /* Bug? flash address is not increased by flash/ram copied section */
     /* We have to adjust it manually to find the end of used flash */
     /* Don't really increase pointer; provide symbols that may point to */
     /* region outside of flash */
     PROVIDE (_end_data_flash = . + SIZEOF(.data_all) );
     PROVIDE (_start_user_flash = ALIGN ( __flash_page_size ) );

  } >FLASH

  /* Uninitialized data section */
  . = ALIGN(4);
  .bss (NOLOAD) :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(COMMON)
    *(.bss*)
  }

   .bss.iobjects (NOLOAD) : {
         PROVIDE ( iobjects_uart = . );
         PROVIDE ( iobject_uart = . );
         *(.iobject.uart*);
         PROVIDE ( iobjects_end_uart = . );

         PROVIDE ( iobjects_dac = . );
         PROVIDE ( iobject_dac = . );
         *(.iobject.dac*);
         PROVIDE ( iobjects_end_dac = . );

         PROVIDE ( iobjects_exti = . );
         PROVIDE ( iobject_exti = . );
         *(.iobject.exti*);
         PROVIDE ( iobjects_end_exti = . );
   }
   
  .ebss (NOLOAD) : {
    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack (NOLOAD) :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    PROVIDE ( __end__ = . );
    
	 __heap_start = . ;
	 . = . + _Min_Heap_Size;

  } >RAM

	._user_stack (NOLOAD) :
	{
	  PROVIDE ( _user_stack = . );
	  /*. = ALIGN(4); */
	  . = . + _Min_Stack_Size;
	} >RAM

   /* Remove information from the standard libraries */
   /DISCARD/ :
   {
      libc.a ( * )
      libstdc++.a ( * )
      libm.a ( * )
      libgcc.a ( * )
      *(.ARM.attributes)
      *(.note .note.*)
      *(.eh_frame .eh_frame.*)
      *(.ARM.extab* .gnu.linkonce.armextab.*)
      *(.ARM.exidx*)
      
      *(.glue_7)
      *(.glue_7t)
      /* *(.eh_frame) */

      *(.dynamic)
      *(.got*)
      *(.got.plt)
      *(.got)

      *(.fini)
      *(.fini_array)
   }
}


/*---fin--------------------------------------------------------------------*/
