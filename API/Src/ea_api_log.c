
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_log.c
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 24/02/2021
  * @brief      : API of log
  ******************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
#include "stdint.h"
#include "stdio.h"
#include "string.h"
// Eder Andrade driver library
#include "ea_drv_uart.h"
#include "ea_drv_adc.h"
// API library
#include "ea_api_log.h"

/*******************************************************************************
							HOW TO USE THIS API
********************************************************************************

1. 	First, you should include in your .c file the "ea_api_log.h" file.

2.  Call ea_api_log_init() to initialize the driver;

3.  Call ea_api_log_print() to print the battery value over UART.

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
#define LOG_API_OK      (int8_t) 0
#define LOG_API_ERROR   (int8_t)-1

/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/    
int8_t  ea_api_log_init     (void);// Initialize log API
int8_t  ea_api_log_deinit   (void);// Deinitialize log API
int8_t  ea_api_log_print    (void);// Print the log about battery

/* Public objects ------------------------------------------------------------*/
/* Body of private functions -------------------------------------------------*/
/**
  * @Func       : ea_api_log_init    
  * @brief      : Init. UART driver
  * @pre-cond.  : SysClk function and ADC driver opened
  * @post-cond. : Log driver init. and ready to be used
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_log_init(void)
{
    // Init. battery driver
    if((UART.Open() != 0) && (AD.FlagEnable == 0))
    {
        return LOG_API_ERROR;
    }
	// OK
	return LOG_API_OK;	
}

/**
  * @Func       : ea_api_log_deinit    
  * @brief      : Deinitializes log driver
  * @pre-cond.  : ea_api_log_init
  * @post-cond. : Log API deinit.
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_log_deinit(void)
{
    // Deinit. battery driver
    if(UART.Close() != 0)
    {
        return LOG_API_ERROR;
    }    
	// OK
	return LOG_API_OK;	
}

/**
  * @Func       : ea_api_log_print    
  * @brief      : Print battery value over UART
  * @pre-cond.  : ea_api_battery_init and UART driver opened
  * @post-cond. : Battery value sent over UART
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_log_print(void)
{    	       
    // Local vector
    char ucVet[32] = {0}; 
    
    // Formatting string to send over UART
    sprintf((char*)ucVet, "[LOG] Battery value in mV: %4d\r\n", (int)AD.uiAdcValue[eBattery]);
    // If user wants to user IAR terminal
    // printf("[LOG] Battery value in mV: %4d\r\n", AD.uiAdcValue[eBattery]); 
 
    return UART.Write(ucVet, strlen((const char*)ucVet));
}
/*****************************END OF FILE**************************************/
