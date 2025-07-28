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
   # -nostdlib
   # -Wl,-nostdlib

   -fno-asynchronous-unwind-tables
   -fno-math-errno
)

add_definitions(
   -DNDEBUG
)


add_link_options(
      -flto
      -fdevirtualize-at-ltrans
      -fno-exceptions
      -Wl,--sort-section=alignment
      -Wl,--gc-sections
)

# Was package 'MCUBase' already included?
if( NOT MCUBase_FOUND )
   include( ${CMAKE_CURRENT_LIST_DIR}/FindMCUBase.cmake )
endif()

if( HAVE_NEWLIB_H AND NOT HAVE_PICOLIBC_H )
   include( ${CMAKE_CURRENT_LIST_DIR}/FindMCUNewlib.cmake )
endif( )

# Absolutely no optimization is way too big
set ( CMAKE_CXX_FLAGS_DEBUG "-Og -g" )
set ( CMAKE_C_FLAGS_DEBUG "-Og -g" )


#------------------------------------------------------------------------------
