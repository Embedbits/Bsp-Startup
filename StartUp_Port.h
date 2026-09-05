/**
 * \author Mr.Nobody
 * \file StartUp_Port.h
 * \ingroup StartUp
 * \brief StartUp module public functionality.
 *
 * This file contains all available public functionality, any other files shall
 * not used outside of the module.
 */


#ifndef BSP_STARTUP_STARTUP_PORT_H_
#define BSP_STARTUP_STARTUP_PORT_H_
/* ============================= INCLUDES =================================== */
#include "StartUp_Types.h"                  /* Module types definitions       */
/* ============================= TYPEDEFS =================================== */

/* ========================= SYMBOLIC CONSTANTS ============================= */

/* ========================= EXPORTED MACROS ================================ */

/* ========================= EXPORTED VARIABLES ============================= */

/* ======================== EXPORTED FUNCTIONS ============================== */

startUp_ModuleVersion_t     StartUp_Get_ModuleVersion   ( void );
void                        StartUp_Handler             ( void );

#endif /* BSP_STARTUP_STARTUP_PORT_H_ */

