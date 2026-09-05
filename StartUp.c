/**
 * \author Mr.Nobody
 * \file StartUp.c
 * \ingroup StartUp
 * \brief System initialization and startUp functionality.
 */


/* ============================= INCLUDES =================================== */
#include "StartUp.h"                        /* Self include                   */
#include "StartUp_Port.h"                   /* StartUp module functionality   */
#include "Nvic_Port.h"                      /* NVIC module public interface   */
#include "Rcc_Port.h"                       /* RCC module public interface    */
#include "BspMain.h"                        /* BSP main function              */
/* ============================== TYPEDEFS ================================== */

typedef void (* startUp_void_func_t)( void );

/* ======================== FORWARD DECLARATIONS ============================ */

static void StartUp_RunClassConstructors( void );
static void StartUp_RunClassDestructors( void );
static void StartUp_InitGlobalVariables( void );
static void StartUp_InitNullGlobalVariables( void );

/* ========================== SYMBOLIC CONSTANTS ============================ */

/** Value of major version of SW module */
#define STARTUP_MAJOR_VERSION           ( 1u )

/** Value of minor version of SW module */
#define STARTUP_MINOR_VERSION           ( 0u )

/** Value of patch version of SW module */
#define STARTUP_PATCH_VERSION           ( 0u )

/* =============================== MACROS =================================== */

/* ========================== EXPORTED VARIABLES ============================ */

/* =========================== LOCAL VARIABLES ============================== */

/* ========================= EXPORTED FUNCTIONS ============================= */

/**
 * \brief Returns module SW version
 *
 * \return Module SW version
 */
startUp_ModuleVersion_t StartUp_Get_ModuleVersion( void )
{
    startUp_ModuleVersion_t retVersion;

    retVersion.Major = STARTUP_MAJOR_VERSION;
    retVersion.Minor = STARTUP_MINOR_VERSION;
    retVersion.Patch = STARTUP_PATCH_VERSION;

    return (retVersion);
}


/**
 * \brief First function executed after reset.
 *
 * \note ST Microelectronics name for this function is OnResetHandler.
 */
void StartUp_Handler( void )
{
    /* 1: Initialize global variables */
    StartUp_InitGlobalVariables();
    StartUp_InitNullGlobalVariables();

    /* 2: Execute static class constructors */
    StartUp_RunClassConstructors();
    
    /* 3: Disable all interrupts */
    Nvic_Set_InterruptsInactive();

    /* 4: Initialize stack pointer, vector table and StartUp handler through NVIC driver */
    Nvic_Init();

    /* 5: Initialize default clock */
    rcc_ConfigStruct_t defaultClockConfig;
    Rcc_Get_DefaultConfig( &defaultClockConfig );
    Rcc_Init( &defaultClockConfig );

    /* Prevent compiler optimization */
    __asm volatile("":::"memory");

    /* 6: Enable all interrupts */
    Nvic_Set_InterruptsActive();

    /* 7: Jump to main function */
    BspMain();

    /* 8: Execute static class destructors */
    StartUp_RunClassDestructors();

    /* 9: De-initialize Vector table */
    Nvic_Deinit();
}

/* ================================ TASKS =================================== */

/* =========================== LOCAL FUNCTIONS ============================== */

/**
 * \brief Executes all static class constructors.
 */
static void StartUp_RunClassConstructors( void )
{
    extern const startUp_void_func_t __preinit_array_start[];
    extern const startUp_void_func_t __preinit_array_end[];

    extern const startUp_void_func_t __init_array_start[];
    extern const startUp_void_func_t __init_array_end[];

    for( const startUp_void_func_t* preinitAddr = __preinit_array_start; preinitAddr < __preinit_array_end; preinitAddr++ )
    {
        (*preinitAddr)();
    }


    for( const startUp_void_func_t* constructorAddr = __init_array_start; constructorAddr < __init_array_end; constructorAddr++ )
    {
        (*constructorAddr)();
    }
}


/**
 * \brief Executes all static class destructors.
 */
static void StartUp_RunClassDestructors( void )
{
    extern const startUp_void_func_t __fini_array_start[];
    extern const startUp_void_func_t __fini_array_end[];

    for( const startUp_void_func_t* destructorAddr = __fini_array_start; destructorAddr < __fini_array_end; destructorAddr++ )
    {
        (*destructorAddr)();
    }
}


/**
 * \brief Initializes global variables with values specified by the data section.
 *
 * \note This function initializes all global variables from .data section
 *       (initialized values).
 *
 * \note This function is called before main() function.
 */
static void StartUp_InitGlobalVariables( void )
{
    /* Starting address of .data section in FLASH memory */
    extern uint32_t _sidata;
    /* Starting address of .data section in RAM */
    extern uint32_t _sdata;
    /* Ending address of .data section in RAM */
    extern uint32_t _edata;

    uint32_t* dst_base = &_sdata;
    uint32_t* src_base = &_sidata;
    uint32_t size = (&_edata - &_sdata);

    for( uint32_t dataIndex = 0u; dataIndex < size; dataIndex++ )
    {
        dst_base[dataIndex] = src_base[dataIndex];
    }
}


/**
 * \brief Initializes all global variables with null values.
 *
 * \note This function initializes all global variables from .bss section
 *       (uninitialized values).
 *
 * \note This function is called before main() function.
 */
static void StartUp_InitNullGlobalVariables( void )
{
    /* Starting address of .bss section in RAM memory */
    extern uint32_t _sbss;
    /* Ending address of .bss section in RAM memory */
    extern uint32_t _ebss;

    uint32_t* bss_base = &_sbss;
    uint32_t size = (&_ebss - &_sbss);

    for( uint32_t dataIndex = 0u; dataIndex < size; dataIndex++ )
    {
        bss_base[dataIndex] = 0u;
    }
}

