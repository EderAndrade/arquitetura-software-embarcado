
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_battery.c
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 24/02/2021
  * @brief      : API of battery
  ******************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
#include "stdint.h"
// Eder Andrade driver library
#include "ea_drv_adc.h"
// API library
#include "ea_api_battery.h"

/*******************************************************************************
							HOW TO USE THIS API
********************************************************************************

1. 	First, you should include in your .c file the "ea_api_battery.h" file.

2.  Call ea_api_battery_init() to initialize the driver;

3.  Call ea_api_battery_value() to get the battery value.

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
#define BATTERY_API_OK          (int8_t) 0
#define BATTERY_API_ERROR       (int8_t)-1
#define BATTERY_API_READ_ERROR  (int8_t)-2

/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/    
int8_t   ea_api_battery_init     (void);// Initialize the battery API
int8_t   ea_api_battery_deinit   (void);// Deinitialize the battery API
int32_t  ea_api_battery_value    (void);// Read battery value

/* Public objects ------------------------------------------------------------*/
/* Body of private functions -------------------------------------------------*/
/**
  * @Func       : ea_api_battery_init    
  * @brief      : Init. battery driver
  * @pre-cond.  : SysClk function
  * @post-cond. : Battery driver init. and ready to be used
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_battery_init(void)
{
    // Init. battery driver
    if(AD.Open() != 0)
    {
        return BATTERY_API_ERROR;
    }    
	// OK
	return BATTERY_API_OK;	
}

/**
  * @Func       : ea_api_battery_deinit    
  * @brief      : Deinitializes battery driver
  * @pre-cond.  : ea_api_battery_init
  * @post-cond. : Battery API deinit.
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_battery_deinit(void)
{
    // Deinit. battery driver
    if(AD.Close() != 0)
    {
        return BATTERY_API_ERROR;
    }    
	// OK
	return BATTERY_API_OK;	
}

/**
  * @Func       : ea_api_battery_value    
  * @brief      : Read battery value
  * @pre-cond.  : ea_api_battery_init
  * @post-cond. : Get the battery value
  * @parameters : void
  * @retval     : Battery value in milivolts
  */
int32_t ea_api_battery_value(void)
{    	
    return AD.uiAdcValue[eBattery];
}
/*****************************END OF FILE**************************************/