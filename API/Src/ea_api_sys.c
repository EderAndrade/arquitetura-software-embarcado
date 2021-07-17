
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_sys.c
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 24/02/2021
  * @brief      : API of HW
  ******************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
#include "stdint.h"
// Eder Andrade driver library
#include "ea_drv_system_clock.h"
// API library
#include "ea_api_sys.h"

/*******************************************************************************
							HOW TO USE THIS API
********************************************************************************

1. 	First, you should include in your .c file the "ea_api_sys.h" file.

2.  Call ea_api_sys_init() to initialize all drivers used in the project;

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
#define  SYS_API_OK      (int8_t) 0      
#define  SYS_API_ERROR   (int8_t)-1

/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/    
int8_t  ea_api_sys_init  (void);     // Initialize HW API
void    ea_api_sys_delay (uint32_t); // Delay

/* Public objects ------------------------------------------------------------*/
/* Body of private functions -------------------------------------------------*/
/**
  * @Func       : ea_api_sys_init    
  * @brief      : Init. system clock of microcontroller
  * @pre-cond.  : Vcc, SP and vector table
  * @post-cond. : System clock ready
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_sys_init(void)
{
    // Init. battery driver
    if(SYS.Open() != 0)
    {
        return SYS_API_ERROR;
    }
	// OK
	return SYS_API_OK;	
}

/**
  * @Func       : ea_api_sys_init    
  * @brief      : Init. system clock of microcontroller
  * @pre-cond.  : Vcc, SP and vector table
  * @post-cond. : System clock ready
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
void ea_api_sys_delay(uint32_t uiDelay)
{
    SYS.Delay(uiDelay);
}

/*****************************END OF FILE**************************************/