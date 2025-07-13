/**---------------------------------------------------------------------------
 *
 * @file   stdioUart.cpp
 * @brief  Sloppy implementation of syscall functions
 *
 * Just let examples for libHALWrapper work. "printf" should print on UART.
 *
 * @date   20250719
 * @author Maximilian Seesslen <development@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <sys/stat.h>
#include <stdio.h>                     // stdout
#include <newlib.h>
#include <HALWrapper/stm32_sup.h>      // Error_Handler
#include <HALWrapper/stm32_uart.h>     // UART_HandleTypeDef
#include <unistd.h>                    // _exit, _write

#include <syscallsUart.hpp>

#if ! defined _PICOLIBC__
#include <string.h>                    // memset
#endif


/*--- Implementation -------------------------------------------------------*/


UART_HandleTypeDef* stdioUartHandle=nullptr;

#if defined _PICOLIBC__
extern "C"
{
   int _putc(char ch, FILE* f);
}

int _putc(char ch, FILE* f)
{
   if( stdioUartHandle )
   {
      HAL_UART_Transmit( stdioUartHandle, (const uint8_t*)&ch, 1, 100000 );
      if( ch == '\n' )
      {
         ch='\r';
         HAL_UART_Transmit( stdioUartHandle, (const uint8_t*)&ch, 1, 100000 );
      }
   }
   return(0);
};

static FILE __stdio =
    FDEV_SETUP_STREAM(_putc, NULL, NULL, _FDEV_SETUP_RW);

__attribute__ ((used))
FILE *const stdout = &__stdio;

#else

extern "C" {
   //__attribute__ ((externally_visible))
   int _write (int __fd, const void *__buf, size_t __nbyte);
   int _isatty (int __fildes);
   _off_t   _lseek (int __fildes, _off_t __offset, int __whence);
   int _read (int __fd, void *__buf, size_t __nbyte);
   pid_t _getpid();
   void _kill(pid_t pid, int sig);
   void *  _sbrk (ptrdiff_t __incr);
   int _close (int __fildes);
   int _fstat (int __fd, struct stat *__sbuf );
};

extern char __heap_start;
void *  _sbrk (ptrdiff_t __incr)
{
   static char* p=&__heap_start;
   void* op=(void*)p;
   p+=__incr;
   return( op );
}

void _kill(pid_t pid, int sig)
{
    return;
}

int kill (pid_t pid, int sig)
{
    return(0);
}

pid_t _getpid()
{
    return(0);
}

pid_t getpid()
{
    return(0);
}

extern "C" {
__attribute__ ((externally_visible))
int _write (int __fd, const void *__buf, size_t __nbyte)
{
   if( stdioUartHandle )
   {
      HAL_UART_Transmit( stdioUartHandle, (const uint8_t*)__buf,
                        __nbyte, 100000 );
      HAL_UART_Transmit( stdioUartHandle, (const uint8_t*)"\r", 1, 100000 );
   }
   return(0);
};

}
__attribute__ ((externally_visible))
int _isatty (int __fildes)
{
   return(1);
};

__attribute__ ((externally_visible))
int _close (int __fildes)
{
   return(0);
}

__attribute__ ((externally_visible))
_off_t   _lseek (int __fildes, _off_t __offset, int __whence)
{
   return( __offset );
};


__attribute__ ((externally_visible))
int _read (int __fd, void *__buf, size_t __nbyte)
{
   return(0);
}

__attribute__ ((externally_visible))
int _fstat (int __fd, struct stat *__sbuf )
{
   memset(__sbuf, 0, sizeof(*__sbuf));
   return(0);
}


__attribute__ ((externally_visible))
void Dummy_Handler()
{
   return;
}

#endif // ! __PICOLIBC__


// newlib and pico need this
void _exit(int ec)
{
   Error_Handler();
}

void setStdioUart( UART_HandleTypeDef* uartHandle )
{
   stdioUartHandle = uartHandle;
}


/*--- Fin ------------------------------------------------------------------*/
