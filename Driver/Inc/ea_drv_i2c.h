
/**
  ******************************************************************************
  * @Company: Eder Andrade Ltda.
  * @file	: ea_drv_i2c.h
  * @author : Eder Andrade
  * @version: V0.0
  * @date   : 26/04/2021
  * @brief  : Header of I2C driver
   *****************************************************************************
*/
#ifdef I2C_ENABLED

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EA_DRV_I2C_H
#define __EA_DRV_I2C_H

/* Includes ------------------------------------------------------------------*/ 
// STMicroelctronics
#include "stm32f1xx_hal.h"
/* Define --------------------------------------------------------------------*/
#define     NUM_OF_AXIS (uint8_t)3
/*----------------------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/
typedef enum
{
    eAxisX  = 0 ,
    eAxisY      ,
    eAxisZ      ,
    
}e_i2c_t;

// Class of I2C
typedef struct
{
    /* Flags ******************************************************************/
    uint8_t     bFlagEnable;			// State of peripheral
    
    /* Variables **************************************************************/
    uint16_t    uiXyz[NUM_OF_AXIS];    // Vector that stores values of each axis
    
    /* Function Pointers ******************************************************/
    int8_t      (*Open) (void);                        
    int8_t      (*Close)(void);                    
    int8_t      (*Write)(uint16_t, uint8_t, uint8_t);               
    int8_t      (*Read) (uint16_t, uint8_t);             
    
}st_i2c_t;

/* Public objects ------------------------------------------------------------*/
extern st_i2c_t I2C;

#endif /* __EA_DRV_I2C_H */
#endif /* I2C_ENABLED */

/*****************************END OF FILE**************************************/