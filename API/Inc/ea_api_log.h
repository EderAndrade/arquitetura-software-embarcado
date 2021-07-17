
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_log.h
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 24/02/2021
  * @brief      : Header file of log API
  ******************************************************************************
*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EA_API_LOG_H
#define __EA_API_LOG_H

/* Includes ------------------------------------------------------------------*/  
/* Define --------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Public objects ------------------------------------------------------------*/
int8_t  ea_api_log_init     (void);// Initialize log API
int8_t  ea_api_log_deinit   (void);// Deinitialize log API
int8_t  ea_api_log_print    (void);// Print the log about battery

#endif /* __EA_API_LOG_H */
/*****************************END OF FILE**************************************/