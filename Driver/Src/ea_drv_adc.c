
/**
  ******************************************************************************
  * @Company: Eder Andrade Ltda.
  * @file	: ea_drv_adc.c
  * @author : Eder Andrade
  * @version: V0.0
  * @date   : 22/02/2021
  * @brief  : Source file of driver that controls ADC perfipheral 
   *****************************************************************************
*/
#ifdef ADC_ENABLED

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
// Eder Andrade driver library
#include "ea_drv_adc.h"	 

/*******************************************************************************
							HOW TO USE THIS DRIVER
********************************************************************************

1. 	First, you should include in your .c file: "ea_drv_adc.h" and call ADC object,
	after that, you can use the follow resources of the driver

	- AD: this is the object that will control the peripheral;	

	Data -----------------------------------------------------------------------

	- AD.bFlagEnable ====================> It informs if ADC driver is enabled
	- AD.eChannel  ======================> Indicates which ADC channel is been used
	- AD.uiAdcValue[x] ==================> Stores ADC channel value read

	Methods --------------------------------------------------------------------

	- AD.Open() =========================> Initializes the ADC driver;
	- AD.Close() ========================> Finishes the ADC driver;
	- AD.Read() =========================> Get the value read of a specific channel

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static ADC_HandleTypeDef hadc1;

/* Private function prototypes -----------------------------------------------*/    
static int8_t 	ea_adc_open (void);	    // Opens ADC peripheral
static int8_t   ea_adc_close(void); 	// Closes ADC peripheral
static int32_t  ea_adc_read (e_adc_t);	// Read ADC channel value

/* Public objects ------------------------------------------------------------*/
st_adc_t AD = 
{
    /* ADC is disabled ********************************************************/
    .FlagEnable	= RESET             ,
    
    /* Variable are resetted **************************************************/
	.eChannel		= eBattery		,	
    .uiAdcValue		= 0				,
    
    /* Function pointer loaded ************************************************/
    .Open   		= &ea_adc_open	,
    .Close  		= &ea_adc_close	,
    .Read    		= &ea_adc_read  
    
};

/* Bodies of private functions -----------------------------------------------*/ 
/**
  * @Func       : ADC1_2_IRQHandler    
  * @brief      : This function handles ADC1 and ADC2 global interrupts
  * @pre-cond.  : ea_adc_open() must be called first
  * @post-cond. : Attends interrupts and invoke callbacks if it's enabled
  * @parameters : void
  * @retval     : void
  */
void ADC1_2_IRQHandler(void)
{
    HAL_ADC_IRQHandler(&hadc1);
}

/**
  * @Func       : HAL_ADC_ConvCpltCallback    
  * @brief      : ADC conversion complete callback
  * @pre-cond.  : ea_adc_open() must be called first
  * @post-cond. : Invoked by ADC IRQ indicating the conversion is completed.
  * @parameters : *hadc
  * @retval     : void
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
    */
    // Store ADC value of channel 0. 
    AD.uiAdcValue[AD.eChannel] = HAL_ADC_GetValue(&hadc1);
}

/**
  * @Func       : ea_adc_open    
  * @brief      : Initializes ADC peripheral
  * @pre-cond.  : SysClk configured
  * @post-cond. : ADC1 configured by interruption and already running
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_adc_open(void)
{    
    /* Clear the ADC struct ***************************************************/
    ADC_ChannelConfTypeDef sConfig = {0};

    /** Common config *********************************************************/
    hadc1.Instance                      = ADC1;
    hadc1.Init.ScanConvMode             = ADC_SCAN_ENABLE;
    hadc1.Init.ContinuousConvMode       = ENABLE;
    hadc1.Init.DiscontinuousConvMode    = DISABLE;
    hadc1.Init.ExternalTrigConv         = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign                = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion          = 4;
    
    if(HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        return -1;
    }
    /** Configure Regular Channel *********************************************/
    sConfig.Channel         = ADC_CHANNEL_0;
    sConfig.Rank            = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime    = ADC_SAMPLETIME_1CYCLE_5;
    
    if(HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        return -2;
    }
    /** Configure Regular Channel *********************************************/
    sConfig.Rank            = ADC_REGULAR_RANK_2;
    
    if(HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        return -3;
    }
    /** Configure Regular Channel *********************************************/
    sConfig.Rank            = ADC_REGULAR_RANK_3;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        return -4;
    }
    /** Configure Regular Channel *********************************************/
    sConfig.Rank            = ADC_REGULAR_RANK_4;
    if(HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        return -5;
    }
    // Start ADC convertion
    if(HAL_ADC_Start_IT(&hadc1)!= HAL_OK)
    {
        return -6;
    }
    // ADC enabled!
    AD.FlagEnable = SET;
	// OK
	return 0;
}

/**
  * @Func       : ea_adc_close    
  * @brief      : Disable ADC peripheral
  * @pre-cond.  : ea_adc_open() already called
  * @post-cond. : ADC1 disabled and stopped
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_adc_close(void)
{
    // Check if ADC was enabled
    if(AD.FlagEnable)
    {
		// ADC disabled
		AD.FlagEnable = RESET;		
		// Clear ADC variable
		for(uint8_t i = 0; i < NUM_OF_ADC_CHANNELS; i++)
		{
			AD.uiAdcValue[i] = 0;		
		}
		// Disable ADC1
		if(HAL_ADC_DeInit(&hadc1) != HAL_OK)
        {
            return -1;
        }
        // Stop
        if(HAL_ADC_Stop_IT(&hadc1) != HAL_OK)
        {
          return -2;
        }
		// OK
		return 0;
    }
	// ADC is not enabled
	return -3;
}

/**
  * @Func       : ea_adc_read    
  * @brief      : Read ADC channel value configured 
  * @pre-cond.  : ea_adc_open() already called
  * @post-cond. : ADC channel value read
  * @parameters : eChannel
  * @retval     : int8_t -> (value >= 0) = OK; (value < 0) = ERROR
  */
static int32_t ea_adc_read(e_adc_t eChannel)
{    
    // Check if ADC was enabled
    if(AD.FlagEnable)
    {			
        // Set the channel 
        AD.eChannel = eChannel;
        // This variable is filled in interrupt
        return AD.uiAdcValue[AD.eChannel];
    }
	// ADC is not enabled
	return -1;
}
#endif /* ADC_ENABLED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*****************************END OF FILE**************************************/
