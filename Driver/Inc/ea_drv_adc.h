
/**
  ******************************************************************************
  * @Company: Eder Andrade Ltda.
  * @file	: ea_drv_adc.h
  * @author : Eder Andrade
  * @version: V0.0
  * @date   : 22/02/2021
  * @brief  : Header file of ADC driver
   *****************************************************************************
*/
#ifdef ADC_ENABLED

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EA_DRV_ADC_H
#define __EA_DRV_ADC_H
     
/* Includes ------------------------------------------------------------------*/
// STMicroelctronics
#include "stm32f1xx_hal.h"
/* Define --------------------------------------------------------------------*/
#define NUM_OF_ADC_CHANNELS	(uint8_t)1

/* Typedef -------------------------------------------------------------------*/
typedef enum
{
    eBattery = 0, // Battery measuring
	
}e_adc_t;

typedef struct
{
    /* Flags ******************************************************************/
    uint8_t     FlagEnable; 					// State of peripheral
    
    /* Variables **************************************************************/
	e_adc_t		eChannel;						// Wich channel is been used
    uint32_t    uiAdcValue[NUM_OF_ADC_CHANNELS];// Retains ADC channel value
    
    /* Function Pointers ******************************************************/
    int8_t    	(*Open) (void);				                 
    int8_t  	(*Close)(void);                               	
    int32_t 	(*Read) (e_adc_t);       
    
}st_adc_t;

/* Public objects ------------------------------------------------------------*/  
extern st_adc_t AD;

#endif /* __EA_DRV_ADC_H */
#endif /* ADC_ENABLED */
/*****************************END OF FILE**************************************/