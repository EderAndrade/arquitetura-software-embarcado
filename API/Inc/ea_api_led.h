
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_led.h
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 24/02/2021
  * @brief      : Header file of LED API
  ******************************************************************************
*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EA_API_LED_H
#define __EA_API_LED_H

/* Includes ------------------------------------------------------------------*/  
/* Define --------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Public objects ------------------------------------------------------------*/
int8_t   ea_api_led_init    (void);// Initialize LED API
int8_t   ea_api_led_deinit  (void);// Deinitialize LED API
void     ea_api_led_set     (void);// Set LED
void     ea_api_led_reset   (void);// Reset LED

#endif /* __EA_API_LED_H */
/*****************************END OF FILE**************************************/