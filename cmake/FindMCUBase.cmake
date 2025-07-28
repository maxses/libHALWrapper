#------------------------------------------------------------------------------
#
# \brief    CMake package MCUBase
#
#           Set compiler/linker options to produce usable binaries for STM32.
#
# \author   Maximilian Seesslen <m@seesslen.net>
#
#------------------------------------------------------------------------------

   
include(CheckIncludeFile)

# Detect implementation of libc
check_include_file( newlib.h HAVE_NEWLIB_H "-shared" )
check_include_file( picolibc.h HAVE_PICOLIBC_H "-shared" )

if( HAVE_NEWLIB_H )
   message( STATUS "newlib: Yes" )
else( HAVE_NEWLIB_H )
   message( STATUS "newlib: No" )
endif( HAVE_NEWLIB_H )

if( HAVE_PICOLIBC_H )
   message( STATUS "picolibc: Yes" )
else( HAVE_PICOLIBC_H )
   message( STATUS "picolibc: No" )
endif( HAVE_PICOLIBC_H )


#------------------------------------------------------------------------------
