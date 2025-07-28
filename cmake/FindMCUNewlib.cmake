#------------------------------------------------------------------------------
#
# \brief    CMake package MCUShrink
#
#           Tricks to get a binary smaller when using an toolchain containing 
#           newlib.
#
# \author   Maximilian Seesslen <m@seesslen.net>
#
#------------------------------------------------------------------------------


# Only 'real' nedwlib has the 'nano.specs' configuration

add_link_options(
   --specs=nano.specs
)

add_compile_options(
   --specs=nano.specs
)


#------------------------------------------------------------------------------
