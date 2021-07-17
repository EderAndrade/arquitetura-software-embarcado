
/**
  ******************************************************************************
  * @Company    : Name of company
  * @file       : name_of_file.h
  * @author     : Name of author
  * @version	  : version of driver, API or application files 
  * @date       : Data of the file was created
  * @brief      : What this file does
  ******************************************************************************
*/ 
#ifdef GPIO_ENABLED

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __file_name_drv_gpio_H
#define __file_name_drv_gpio_H

/* Includes ------------------------------------------------------------------*/       
/* Define --------------------------------------------------------------------*/
#define NUM_OF_IOS  44

/* DEFINING PORT AND PINS FOR THE DIGITAL I/Os USED --------------------------*/
/* OUTPUTS -------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* INPUTS --------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/
// These values helps to understand the code
typedef enum
{                       
    /* Output *****************************************************************/	
    /* Input ******************************************************************/
    
}e_gpio_t;

// This struct combines port and pin in one location
typedef struct
{
    InsertPortType    *port;
    InsertPintType     pin;        
    
}st_gpio_pin_t;

// Struct that retains all information about GPIOs of application
typedef struct
{
    /* Flags ******************************************************************/
    InsertBitType bFlagEnable;			// State of peripheral
    
    /* Variables **************************************************************/
	 InsertBitType bState[NUM_OF_IOS];	// Vector of GPIOs values stored
    
    /* Function Pointers ******************************************************/
    int8_t  (*Open) (void);                        
    int8_t  (*Close)(void);                    
    int8_t  (*Write)(e_gpio_t, BitStatus);              
    int8_t  (*Read) (e_gpio_t);               
    
}st_gpio_t;

/* Public objects ------------------------------------------------------------*/
extern st_gpio_t GPIO;

#endif /* __file_name_drv_gpio_H */
#endif /* GPIO_ENABLED */

/*****************************END OF FILE**************************************/