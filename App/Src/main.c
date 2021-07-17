/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ea_api_battery.h"
#include "ea_api_sys.h"
#include "ea_api_led.h"
#include "ea_api_log.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define APP_NUM_OF_STATES   (uint8_t)2

// States of Finite State Machine of Application
typedef enum
{
    eAPP_BAT_STATE = 0  ,
    eAPP_LOG_STATE      ,
    
}e_app_fsm_t;

// Application struct that contains all information related
typedef struct
{
    /* Data *******************************************************************/
    // LED on or off
    GPIO_PinState   ucLedState;
    
    // Battery value in milli Volts
    uint32_t        uiBatteryLevel;  
    uint32_t        uiStateDelay[APP_NUM_OF_STATES];
    
    /* Functions **************************************************************/
    // Pointer function vector of application
    void            (*pFunc[APP_NUM_OF_STATES])(void);                                                      
  
}st_app_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
st_app_t App;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void ea_app_verify_bat  (void);
void ea_app_log         (void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
  * @Func       : ea_app_log    
  * @brief      : Send to host/console the battery value
  * @pre-cond.  : SysClk, battery and log APIs
  * @post-cond. : String sent with battery value
  * @parameters : void
  * @retval     : void
  */
void ea_app_log(void)
{
    // Update the host/console with battery value
    ea_api_log_print();  
    // Delay of this state
    ea_api_sys_delay(App.uiStateDelay[eAPP_LOG_STATE]);
}

/**
  * @Func       : ea_app_verify_bat    
  * @brief      : Read battery value and based on turn on or off the LED
  * @pre-cond.  : SysClk, LED and Battery APIs
  * @post-cond. : Battery value and LED state uptdated
  * @parameters : void
  * @retval     : void
  */
void ea_app_verify_bat(void)
{
    // Updating battery value to the application
    App.uiBatteryLevel = ea_api_battery_value();
    
    // If battery voltagem is under 2.5V
    if(App.uiBatteryLevel < 2500)
    {
        // Turn ON the LED
        ea_api_led_set();
    }
    else
    {
        // Turn OFF the LED
        ea_api_led_reset();
    }
    // Delay of this state
    ea_api_sys_delay(App.uiStateDelay[eAPP_BAT_STATE]);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Application struct loading initial values
st_app_t App = 
{
    .ucLedState                     = GPIO_PIN_RESET    , // LED OFF
    .uiBatteryLevel                 = 0                 , // 0 mV
    
    .uiStateDelay[eAPP_BAT_STATE]   = 20                , // Bat.  state 20ms
    .uiStateDelay[eAPP_LOG_STATE]   = 200               , // Log   state 200ms 
    
    .pFunc[eAPP_BAT_STATE]          = &ea_app_verify_bat, // Index "0" loaded  
    .pFunc[eAPP_LOG_STATE]          = &ea_app_log       , // Index "1" loaded     
    
};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN Init */      
    if(ea_api_sys_init() != RESET)
    {
        Error_Handler();
    }
    //
    if(ea_api_battery_init() != RESET)
    {
        Error_Handler();
    }
    //
    if(ea_api_led_init() != RESET)
    {
        Error_Handler();
    } 
    //
    if(ea_api_log_init() != RESET)
    {
        Error_Handler();
    } 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    (void)App.pFunc[eAPP_BAT_STATE]();  
    (void)App.pFunc[eAPP_LOG_STATE](); 
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
