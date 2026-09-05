/**
 * \author Mr.Nobody
 * \file StartUp_Types.h
 * \ingroup StartUp
 * \brief StartUp module global types definition
 *
 * This file contains the types definitions used across the module and are 
 * available for other modules through Port file.
 *
 */

#ifndef STARTUP_STARTUP_TYPES_H
#define STARTUP_STARTUP_TYPES_H
/* ============================== INCLUDES ================================== */
#include "stdint.h"                         /* Module types definition        */
/* ========================== SYMBOLIC CONSTANTS ============================ */

/** Null pointer definition */
#define STARTUP_NULL_PTR                        ( ( void* ) 0u )

/* ========================== EXPORTED MACROS =============================== */

/* ============================== TYPEDEFS ================================== */

/** \brief Type signaling major version of SW module */
typedef uint8_t startUp_MajorVersion_t;


/** \brief Type signaling minor version of SW module */
typedef uint8_t startUp_MinorVersion_t;


/** \brief Type signaling patch version of SW module */
typedef uint8_t startUp_PatchVersion_t;


/** \brief Type signaling actual version of SW module */
typedef struct
{
    startUp_MajorVersion_t Major; /**< Major version */
    startUp_MinorVersion_t Minor; /**< Minor version */
    startUp_PatchVersion_t Patch; /**< Patch version */
}   startUp_ModuleVersion_t;


/** Function status enumeration */
typedef enum
{
    STARTUP_FUNCTION_INACTIVE = 0u, /**< Function status is inactive */
    STARTUP_FUNCTION_ACTIVE         /**< Function status is active   */
}   startUp_FunctionState_t;


/** I2C bus flag states enumeration */
typedef enum
{
    STARTUP_FLAG_INACTIVE = 0u, /**< Inactive flag state */
    STARTUP_FLAG_ACTIVE         /**< Active flag state   */
}   startUp_FlagState_t;


/* ========================== EXPORTED VARIABLES ============================ */

/* ========================= EXPORTED FUNCTIONS ============================= */


#endif /* STARTUP_STARTUP_TYPES_H */
