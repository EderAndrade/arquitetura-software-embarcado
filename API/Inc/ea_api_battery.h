
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_battery.h
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 24/02/2021
  * @brief      : Header file of battery API
  ******************************************************************************
*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EA_API_BATTERY_H
#define __EA_API_BATTERY_H

/* Includes ------------------------------------------------------------------*/  
/* Define --------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Public objects ------------------------------------------------------------*/
int8_t   ea_api_battery_init     (void);// Initialize the battery API
int8_t   ea_api_battery_deinit   (void);// Deinitialize the battery API
int32_t  ea_api_battery_value    (void);// Read battery value

#endif /* __EA_API_BATTERY_H */
/*****************************END OF FILE**************************************/