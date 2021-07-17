
/**
  ******************************************************************************
  * @Company    : Name of company
  * @file       : name_of_file.c
  * @author     : Name of author
  * @version	: version of driver, API or application files 
  * @date       : Data of the file was created
  * @brief      : What this file does
  ******************************************************************************
*/ 
#ifdef GPIO_ENABLED

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
// Eder Andrade driver library
#include "company_name_drv_gpio.h"
// Application

/*******************************************************************************
							               HOW TO USE THIS DRIVER
********************************************************************************

1. 	First, you should include in your .c file: "company_name_drv_gpio.h" and call GPIO object,
	after that, you can use the follow resources of the driver

	- GPIO: this is the object that will control the peripheral;	

	Data -----------------------------------------------------------------------

	- GPIO.bFlagEnable	===================> It informs if GPIO driver is enabled
	- GPIO.bState[x]	===================> Stores the state of a specific pin

	Methods --------------------------------------------------------------------

	- GPIO.Open() =========================> Initializes the GPIO driver;
	- GPIO.Close() ========================> Finishes the GPIO driver;
	- GPIO.Write() ========================> Writes "0" or "1" on a specific pin
	- GPIO.Read() =========================> Read the state of a specific pin

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const static st_gpio_pin_t IO[NUM_OF_IOS] = 
{
	{PORT_OF_PIN, PIN},	

};

/* Private function prototypes -----------------------------------------------*/    
static int8_t   company_name_gpio_open   (void);					// Initialize the peripheral
static int8_t   company_name_gpio_close  (void);                    // Close the peripheral
static int8_t   company_name_gpio_write  (e_gpio_t, BitStatus);  	// Write (0 or 1) on a specific pin
static int8_t   company_name_gpio_read   (e_gpio_t);             	// Read state of a specific pin

/* Public objects ------------------------------------------------------------*/
st_gpio_t GPIO = 
{
    /* Peripheral disabled ****************************************************/
    .bFlagEnable			= RESET,
    
    /* All pins are reseted ***************************************************/
    .bState[enum_type_index]= {RESET}, 
    
    /* Function pointers loaded ***********************************************/
    .Open   				= &company_name_gpio_open	,
    .Close  				= &company_name_gpio_close	,
    .Write  				= &company_name_gpio_write	,
    .Read   				= &company_name_gpio_read
    
};

/* Body of private functions -------------------------------------------------*/
/**
  * @Func       : name of function    
  * @brief      : Put your description here
  * @pre-cond.  : Conditions needed to APIs/drivers work
  * @post-cond. : Conditions achieved after API/drivers executed
  * @parameters : Fill this field wherever there is or not parameter / returning
  * @retval     : Fill this field wherever there is or not parameter / returning
  */
static int8_t company_name_gpio_open(void)
{
	/* Clear all ports ********************************************************/  
    /* Enabling port clock ****************************************************/		
	/* OUTPUTS FIRST **********************************************************/	
	/* INPUTS *****************************************************************/	
	/* INTERRUPTS *************************************************************/	  
	// Enabling GPIO peripheral
    GPIO.bFlagEnable = SET;	
	// GPIO enabled!
	return 0;	
}

/**
  * @Func       : name of function    
  * @brief      : Put your description here
  * @pre-cond.  : Conditions needed to APIs/drivers work
  * @post-cond. : Conditions achieved after API/drivers executed
  * @parameters : Fill this field wherever there is or not parameter / returning
  * @retval     : Fill this field wherever there is or not parameter / returning
  */
static int8_t company_name_gpio_close(void)
{
	// Check if GPIO was enabled
    if(GPIO.bFlagEnable != RESET)
    {        
        // Clean up the pin state vector
        for(uint8_t i = 0; i < NUM_OF_IOS; i++)
        {
            // Reset the values
            GPIO.bState[i] = RESET;
        }        
		
		// Clear all ports

		// IOs disable
        GPIO.bFlagEnable = RESET; 		
		
		// OK
		return 0;
    }
	// GPIO is disabled
	return -1;
}

/**
  * @Func       : name of function    
  * @brief      : Put your description here
  * @pre-cond.  : Conditions needed to APIs/drivers work
  * @post-cond. : Conditions achieved after API/drivers executed
  * @parameters : Fill this field wherever there is or not parameter / returning
  * @retval     : Fill this field wherever there is or not parameter / returning
  */
static int8_t company_name_gpio_write(e_gpio_t eHw, BitStatus bValue)
{    
    // Check if GPIO is enabled
    if(GPIO.bFlagEnable != RESET)
    {        
		// Verifies which action is gonna happens
		if(bValue == SET)
		{
			// Set pin
		}
		else if(bValue == RESET)
		{
			// Reset pin
		}        
		else
		{
			// Some other value different of "0" or "1" was passed 
			return -1;
		}
		// Update the state of pin chosen
        GPIO.bState[eHw] = bValue;				
		// OK
		return 0;		
    }
	// GPIO is disabled
    return -2;
}

/**
  * @Func       : name of function    
  * @brief      : Put your description here
  * @pre-cond.  : Conditions needed to APIs/drivers work
  * @post-cond. : Conditions achieved after API/drivers executed
  * @parameters : Fill this field wherever there is or not parameter / returning
  * @retval     : Fill this field wherever there is or not parameter / returning
  */
static int8_t company_name_gpio_read(e_gpio_t eHw)
{        
    // Check if GPIO was enabled
    if(GPIO.bFlagEnable != RESET)
    {
        // Load the buffer with value of pin specified
		
	    // retun the state
    	return GPIO.bState[eHw];
    }
	// GPIO is disabled
    return -1;
}
#endif /* GPIO_ENABLED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*****************************END OF FILE**************************************/