
/**
  ******************************************************************************
  * @Company: Eder Andrade Ltda.
  * @file	: ea_drv_gpio.c
  * @author : Eder Andrade
  * @version: V0.0
  * @date   : 12/03/2021
  * @brief  : Source file of driver that controls GPIO peripheral
   *****************************************************************************
*/
#ifdef GPIO_ENABLED

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
// Eder Andrade driver library
#include "ea_drv_gpio.h"

/*******************************************************************************
							HOW TO USE THIS DRIVER
********************************************************************************

1. 	First, you should include in your .c file: "ea_drv_gpio.h" and call GPIO object,
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
    {LED_GREEN_GPIO_Port, LED_GREEN_Pin},    
};

/* Private function prototypes -----------------------------------------------*/    
static int8_t   ea_gpio_open   (void);					    // Initialize the peripheral
static int8_t   ea_gpio_close  (void);                      // Close the peripheral
static int8_t   ea_gpio_write  (e_gpio_t, GPIO_PinState); 	// Write (0 or 1) on a specific pin
static int8_t   ea_gpio_read   (e_gpio_t);             	    // Read state of a specific pin

/* Public objects ------------------------------------------------------------*/
st_gpio_t GPIO = 
{
    /* Peripheral disabled ****************************************************/
    .FlagEnable			    = RESET, 
    
    /* All pins are reseted ***************************************************/
    .State[eLedGreen] 		= GPIO_PIN_RESET,   
    
    /* Function pointers loaded ***********************************************/
    .Open   				= &ea_gpio_open ,
    .Close  				= &ea_gpio_close,
    .Write  				= &ea_gpio_write,
    .Read   				= &ea_gpio_read
    
};

/* Body of private functions -------------------------------------------------*/
/**
  * @Func       : EXTI15_10_IRQHandler    
  * @brief      : This function handles EXTI line[15:10] interrupts.
  * @pre-cond.  : ea_gpio_open() must be called first
  * @post-cond. : Attends interrupts and invoke callbacks if it's enabled
  * @parameters : void
  * @retval     : void
  */
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

/**
  * @Func       : HAL_GPIO_EXTI_Callback    
  * @brief      : It is invoked when a hardware event occurred
  * @pre-cond.  : ea_gpio_open() must be called first
  * @post-cond. : Callback related to hardware event is attended 
  * @parameters : Pin configured for external hardware interrupt 
  * @retval     : Void
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
    */
}

/**
  * @Func       : ea_gpio_open    
  * @brief      : Initializes GPIO peripheral
  * @pre-cond.  : System Clock Config must be called first
  * @post-cond. : All GPIOs and its related sources clocks are enabled
  * @parameters : void 
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_gpio_open(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable ************************************************/
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level *****************************************/
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : LED_GREEN_Pin **************************************/
    GPIO_InitStruct.Pin     = LED_GREEN_Pin;
    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull    = GPIO_NOPULL;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);
	  
	// Enabling GPIO peripheral
    GPIO.FlagEnable = SET;
	
	// GPIO enabled!
	return 0;	
}

/**
  * @Func       : ea_gpio_close    
  * @brief      : Disable all GPIO ports
  * @pre-cond.  : ea_gpio_open() must be called first
  * @post-cond. : All GPIOs and its related sources clocks are disabled
  * @parameters : void 
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_gpio_close(void)
{
	// Check if GPIO was enabled
    if(GPIO.FlagEnable)
    {            
        // Clean up the pin state vector
        for(uint8_t i = 0; i < NUM_OF_IOS; i++)
        {
            // Reset the values
            GPIO.State[i] = GPIO_PIN_RESET;
        }        
		
		// Clear all ports
		HAL_GPIO_DeInit(LED_GREEN_GPIO_Port, LED_GREEN_Pin);

		// IOs disable
        GPIO.FlagEnable = RESET; 		
		
		// OK
		return 0;
    }
	// GPIO is disabled
	return -1;
}

/**
  * @Func       : ea_gpio_write    
  * @brief      : Write on a specific port and pin
  * @pre-cond.  : ea_gpio_open() must be called first
  * @post-cond. : Set/reset specific pin and its value is stored
  * @parameters : eHw       -> pin to be write / clear
  * @parameters : bValue    -> RESET or SET 
  * @retval     : int8_t    -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_gpio_write(e_gpio_t eHw, GPIO_PinState Value)
{    
    // Check if GPIO is enabled
    if(GPIO.FlagEnable)
    {        
		// Verifies which action is gonna happens
		if((Value == GPIO_PIN_SET) || (Value == GPIO_PIN_RESET))
		{
            if(eHw == eLedGreen)
            {
                // Set/reset pin            
                HAL_GPIO_WritePin(IO[eHw].port, (uint16_t)IO[eHw].pin, Value);
            }
            else
            {
                // It is not a output!
                return -1;
            }
		}       
		else
		{
			// Some other value different of "0" or "1" was passed 
			return -2;
		}
		// Update the state of pin chosen
        GPIO.State[eHw] = Value;				
		// OK
		return 0;		
    }
	// GPIO is disabled
    return -3;
}



/**
  * @Func       : ea_gpio_read    
  * @brief      : Read the state of a specific pin
  * @pre-cond.  : ea_gpio_open() must be called first
  * @post-cond. : Specific pin informed is readed and its state is stored
  * @parameters : eHw - specific pin
  * @retval     : state of pin : RESET or SET 
  */
static int8_t ea_gpio_read(e_gpio_t eHw)
{        
    // Check if GPIO was enabled
    if(GPIO.FlagEnable)
    {
        // Load the buffer with value of pin specified
        GPIO.State[eHw] = HAL_GPIO_ReadPin(IO[eHw].port, (uint16_t)IO[eHw].pin);
		
	    // retun the state
    	return GPIO.State[eHw];
    }
	// GPIO is disabled
    return -1;
}
#endif /* GPIO_ENABLED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*****************************END OF FILE**************************************/