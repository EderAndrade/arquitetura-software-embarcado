
/**
  ******************************************************************************
  * @Company: Eder Andrade Ltda.
  * @file	: ea_drv_i2c.c
  * @author : Eder Andrade
  * @version: V0.0
  * @date   : 26/04/2021
  * @brief  : Source file of driver that controls I2C peripheral
   *****************************************************************************
*/
#ifdef I2C_ENABLED

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
// Eder Andrade driver library
#include "ea_drv_i2c.h"
// Application

/*******************************************************************************
                           HOW TO USE THIS DRIVER
********************************************************************************

1. 	First, you should include in your .c file: "ea_drv_i2c.h" and call I2C object,
	after that, you can use the follow resources of the driver

	- I2C: this is the object that will control the peripheral;	

	Data -----------------------------------------------------------------------

	- I2C.bFlagEnable	===================> It informs if GPIO driver is enabled

	Methods --------------------------------------------------------------------

	- I2C.Open() =========================> Initializes the I2C driver;
	- I2C.Close() ========================> Finishes the I2C driver;
	- I2C.Write() ========================> Writes a value in a specific memory location
	- I2C.Read() =========================> Reads a value from a specific memory location

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
static I2C_HandleTypeDef hi2c1;
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/    
static int8_t   ea_i2c_open     (void);					
static int8_t   ea_i2c_close    (void);                   
static int8_t   ea_i2c_write    (uint16_t, uint8_t, uint8_t);   	
static int8_t   ea_i2c_read     (uint16_t, uint8_t);   

/* Public objects ------------------------------------------------------------*/
st_i2c_t I2C = 
{
    /* Peripheral disabled ****************************************************/
    .bFlagEnable			= RESET,
    
    /* All axis values resetted ***********************************************/
    .uiXyz[eAxisX]          = 0, 
    .uiXyz[eAxisY]          = 0, 
    .uiXyz[eAxisZ]          = 0, 
    
    /* Function pointers loaded ***********************************************/
    .Open   				= &ea_i2c_open	,
    .Close  				= &ea_i2c_close	,
    .Write  				= &ea_i2c_write	,
    .Read   				= &ea_i2c_read  ,
    
};

/* Body of private functions -------------------------------------------------*/
/**
  * @Func       : I2C1_EV_IRQHandler    
  * @brief      : This function handles I2C1 event global interrupt / I2C1 wake-up interrupt through EXTI line 23.
  * @pre-cond.  : ea_i2c_open() must be called first
  * @post-cond. : Callback related to hardware event is attended 
  * @parameters : Void
  * @retval     : Void
  */
void I2C1_EV_IRQHandler(void)
{
  HAL_I2C_EV_IRQHandler(&hi2c1);
}

/**
  * @Func       : I2C1_ER_IRQHandler    
  * @brief      : This function handles I2C1 error interrupt.
  * @pre-cond.  : ea_i2c_open() must be called first
  * @post-cond. : Callback related to hardware event is attended 
  * @parameters : Void
  * @retval     : Void
  */
void I2C1_ER_IRQHandler(void)
{
  HAL_I2C_ER_IRQHandler(&hi2c1);
}

/**
  * @Func       : ea_i2c_open    
  * @brief      : Initializes I2C peripheral
  * @pre-cond.  : System Clock Config must be called first
  * @post-cond. : I2C peripheral and its related source clock is enabled
  * @parameters : void 
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_i2c_open(void)
{
    hi2c1.Instance              = I2C1;
    hi2c1.Init.ClockSpeed       = 100000;
    hi2c1.Init.DutyCycle        = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1      = 0;
    hi2c1.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2      = 0;
    hi2c1.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
    if(HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        return -1;
    }
	// Enabling GPIO peripheral
    I2C.bFlagEnable = SET;	
    
	// GPIO enabled!
	return 0;	
}

/**
  * @Func       : ea_i2c_close    
  * @brief      : Disable I2C peripheral
  * @pre-cond.  : ea_i2c_open() must be called first
  * @post-cond. : I2C is disabled and it is not possible to communicate.
  * @parameters : void 
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_i2c_close(void)
{
	// Check if GPIO was enabled
    if(I2C.bFlagEnable != RESET)
    {        
        if(HAL_I2C_DeInit(&hi2c1) != HAL_OK)
        {
            return -1;
        }
		// IOs disable
        I2C.bFlagEnable = RESET; 		
		
		// OK
		return 0;
    }
	// GPIO is disabled
	return -2;
}

/**
  * @Func       : ea_i2c_write    
  * @brief      : Write a data in a specific memory area 
  * @pre-cond.  : ea_i2c_open() must be called first
  * @post-cond. : Data written in a memory area informed
  * @parameters : ucDeviceAddr      -> device
  * @parameters : ucRegisterAddr    -> register
  * @parameters : ucRegisterAddr    -> value
  * @retval     : int8_t    -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_i2c_write(uint16_t ucDeviceAddr, uint8_t ucRegisterAddr, uint8_t ucValue)
{    
    // Check if GPIO is enabled
    if(I2C.bFlagEnable != RESET)
    {        
        // Writes in a specific memory
        if(HAL_I2C_Mem_Write(&hi2c1                     , 
                             ucDeviceAddr               , 
                             (uint16_t)ucRegisterAddr   , 
                             I2C_MEMADD_SIZE_8BIT       , 
                             &ucValue                   , 
                             1                          , 
                             0x10000) != HAL_OK)
        {
            // Error
            return -1;
        }			
		// OK
		return 0;		
    }
	// GPIO is disabled
    return -2;
}

/**
  * @Func       : ea_i2c_read    
  * @brief      : Read a data from a specific memory area
  * @pre-cond.  : ea_i2c_open() must be called first
  * @post-cond. : Data read from a memory area informed
  * @parameters : uiAddress -> address
  * @parameters : ucValue   -> value
  * @retval     : int8_t    -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_i2c_read(uint16_t ucDeviceAddr, uint8_t ucRegisterAddr)
{        
    // Check if GPIO was enabled
    if(I2C.bFlagEnable != RESET)
    {
        // Local
        uint8_t ucValue = 0;
        HAL_StatusTypeDef status = HAL_OK;
        
        // Read memory informed
        status = HAL_I2C_Mem_Read (&hi2c1                 , 
                             ucDeviceAddr           , 
                             ucRegisterAddr         , 
                             I2C_MEMADD_SIZE_8BIT   , 
                             &ucValue               , 
                             1                      , 
                             0x10000);
        if(status != HAL_OK)
        {
            /* Execute user timeout callback */
            return -1;      
        }
        return ucValue;
    }
	// GPIO is disabled
    return -2;
}
#endif /* GPIO_ENABLED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*****************************END OF FILE**************************************/