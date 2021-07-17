
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_sys.h
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 24/02/2021
  * @brief      : Header file of SYS API
  ******************************************************************************
*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EA_API_SYS_H
#define __EA_API_SYS_H

/* Includes ------------------------------------------------------------------*/  
/* Define --------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Public objects ------------------------------------------------------------*/
int8_t  ea_api_sys_init  (void);     // Initialize HW API
void    ea_api_sys_delay (uint32_t); // Delay

#endif /* __EA_API_SYS_H */
/*****************************END OF FILE**************************************/