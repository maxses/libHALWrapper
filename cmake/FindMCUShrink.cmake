#------------------------------------------------------------------------------
#
# \brief    CMake package MCUShrink
#
#           Set compiler/linker options to produce tiny binary size.
#           Exceptions get disabled, some symbols get removed.
#
# \author   Maximilian Seesslen <m@seesslen.net>
#
#------------------------------------------------------------------------------


# gcc-ranlib/gcc-ar are needed to let -flto work.
set ( CMAKE_RANLIB ${CMAKE_CXX_COMPILER_RANLIB} )
set ( CMAKE_AR ${CMAKE_CXX_COMPILER_AR} )
   
add_compile_options(
   $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
   -flto
   -ffat-lto-objects
   
   -fno-exceptions
   $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
   -Wall
   
   -ffunction-sections
   -fdata-sections
   
   # Does not produce usefull errors for CExti of libbiwak:
   # -Wsuggest-final-types
   # -Wsuggest-final-methods
   -nostdlib
)

add_definitions(
   -DNDEBUG
)

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

add_link_options(
      -flto
      -fdevirtualize-at-ltrans
      -fno-exceptions
      -Wl,--sort-section=alignment
      -Wl,--gc-sections
      -Wl,--just-symbols=${CMAKE_CURRENT_LIST_DIR}/skipSymbols.map
      -fno-use-cxa-atexit
)

# Only 'real' nedwlib has the 'nano.specs' configuration
if( HAVE_NEWLIB_H AND NOT HAVE_PICOLIBC_H )
   add_link_options(
      --specs=nano.specs
   )
endif( )

# Absolutely no optimization is way too big
set ( CMAKE_CXX_FLAGS_DEBUG "-Og -g" )
set ( CMAKE_C_FLAGS_DEBUG "-Og -g" )


#------------------------------------------------------------------------------
