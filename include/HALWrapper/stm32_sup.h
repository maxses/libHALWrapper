#ifndef HALWRAPPER_STM32_SUB_H
#define HALWRAPPER_STM32_SUB_H
/**---------------------------------------------------------------------------
 *
 * @file       stm32_sup.h
 * @brief      Generic supplementary funcitons
 *
 * Just some default handlers.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

// Just freeze
__attribute__(( noreturn )) void Error_Handler(void);
void SysTick_Handler();


#ifdef __cplusplus
}
#endif

// let stuff defines like '-DUSE_LSE=Yes' work
#define CONFIGARG_y     1
#define CONFIGARG_Y     1
#define CONFIGARG_YES   1
#define CONFIGARG_Yes   1
#define CONFIGARG_yes   1
#define CONFIGARG_true  1
#define CONFIGARG_1     1
#define CONFIGARG_n     0
#define CONFIGARG_N     0      // CMIS code uses 'N' as variable
#define CONFIGARG_NO    0
#define CONFIGARG_No    0
#define CONFIGARG_no    0
#define CONFIGARG_false 0
#define CONFIGARG_0     0
#define ENABLED_S2( a ) ( ( 7-a-7 == 14 ) || ( 0 + CONFIGARG_##a + 0 ) )
#define ENABLED( a ) ENABLED_S2( a )

// Test the ENABLED macro

#define TEST_No No
#define TEST_0  0
#undef TEST_undef
#define TEST_false false

#if ENABLED( TEST_No ) || ENABLED( TEST_0 ) || ENABLED( TEST_undef ) || ENABLED( TEST_false )
#error ENABLED-Macro does not work correctly
#endif

#define TEST_Yes Yes
#define TEST_1  1
#define TEST_defined
#define TEST_true true

#if ! ( ENABLED( TEST_Yes ) && ENABLED( TEST_1 ) && ENABLED( TEST_defined ) && ENABLED( TEST_true ) )
#error ENABLED-Macro does not work correctly
#endif

#ifdef __cplusplus

#if ! ENABLED( TEST_true )
#error ENABLED-Macro does not work correctly
#endif

#endif


#ifdef __cplusplus
extern "C" {
#endif

void SystemClock_Config_f0();
void SystemClock_Config_f1();
void SystemClock_Config_f3();
void SystemClock_Config_f4();
void SystemClock_Config_l0();
void SystemClock_Config_l1();
void SystemClock_Config_l4();
void SystemClock_Config_g0();
void SystemClock_Config_g4();

#ifdef __cplusplus
}
#endif

// Doxygen does not like multiple functions with the same name. Involve the MCU
// in the function name (e.g. SystemClock_Config_f3() ) but still provide
// SystemClock_Config()
#define SystemClock_Config_for_MCU( mcu ) SystemClock_Config_for_MCU_2( mcu )
#define SystemClock_Config_for_MCU_2( mcu ) SystemClock_Config_ ## mcu()
#define SystemClock_Config() SystemClock_Config_for_MCU( MCU_REV )


/*--- fin -------------------------------------------------------------------*/
#endif // ? ! HALWRAPPER_STM32_SUB_H
