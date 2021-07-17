
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_accel.h
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 26/04/2021
  * @brief      : Header file of accelerometer API
  ******************************************************************************
*/  

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EA_API_ACCEL_H
#define __EA_API_ACCEL_H

/* Includes ------------------------------------------------------------------*/       
/* Define --------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Public objects ------------------------------------------------------------*/
int8_t   ea_api_accel_init   (void);
int8_t   ea_api_accel_reset  (void);
int8_t   ea_api_accel_get_xyz(int16_t*);

#endif /* __EA_API_ACCEL_H */

/*****************************END OF FILE**************************************/