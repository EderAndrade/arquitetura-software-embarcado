
/**
  ******************************************************************************
  * @Company: Eder Andrade Ltda.
  * @file	: ea_drv_system_clock.c
  * @author : Eder Andrade
  * @version: V0.0
  * @date   : 22/02/2021
  * @brief  : Source file of driver that controls SYSCLK perfipheral 
   *****************************************************************************
*/
#ifdef SYSTEM_CLOCK_ENABLED

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
// Eder Andrade driver library
#include "ea_drv_system_clock.h"

/*******************************************************************************
							HOW TO USE THIS DRIVER
********************************************************************************

1. 	First, you should include in your .c file: "ea_drv_system_clock.h" and call 
    SYSCLK object, after that, you can use the follow resources of the driver

	- SYSCLK: this is the object that will control the peripheral;	

	Data -----------------------------------------------------------------------

	- SYSCLK.bFlagEnable ===============> It informs if SYSCLK driver is enabled

	Methods --------------------------------------------------------------------

	- SYSCLK.Open() ====================> Initializes the SYSCLK driver;
    - SYSCLK.Delay() ===================> Time delayed as informed in parameter;

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/    
static int8_t   ea_system_clock_open    (void);     // Initialize the peripheral
static void     ea_system_clock_delay   (uint32_t); // Delay in ms

/* Public objects ------------------------------------------------------------*/
sysclk_gpio_t SYS = 
{
    /* Peripheral disabled ****************************************************/
    .FlagEnable = RESET,
    
    /* Function pointers loaded ***********************************************/
    .Open       = &ea_system_clock_open	,
    .Delay      = &ea_system_clock_delay,
    
};

/* Body of private functions -------------------------------------------------*/
/**
  * @Func       : SysTick_Handler    
  * @brief      : This function handles System tick timer.
  * @pre-cond.  : Vcc supplied, SP and vector table configured
  * @post-cond. : Tick of systimer ticked
  * @parameters : void 
  * @retval     : void
  */
void SysTick_Handler(void)
{
    HAL_IncTick();
}

/**
  * @Func       : ea_system_clock_open    
  * @brief      : Initializes system clock
  * @pre-cond.  : Vcc supplied, SP and vector table configured
  * @post-cond. : System clock configured to core and peripherals to running
  * @parameters : void 
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_system_clock_open(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct    = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct    = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit  = {0};

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
  
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType    = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState          = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState          = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState      = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource     = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL        = RCC_PLL_MUL9;
    
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        return -1;
    }
    /** Initializes the CPU, AHB and APB buses clocks *************************/
    RCC_ClkInitStruct.ClockType         = RCC_CLOCKTYPE_HCLK    |
                                          RCC_CLOCKTYPE_SYSCLK  |  
                                          RCC_CLOCKTYPE_PCLK1   |
                                          RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource      = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider     = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider    = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider    = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        return -2;
    }
    
    PeriphClkInit.PeriphClockSelection  = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection     = RCC_ADCPCLK2_DIV6;
    
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        return -3;
    }
    // SYSCLK is enabled!
    SYS.FlagEnable = SET;	
	return 0;	
}

/**
  * @Func       : ea_system_clock_delay    
  * @brief      : Delay in miliseconds
  * @pre-cond.  : ea_system_clock_open
  * @post-cond. : Time delays as informed through the parameter
  * @parameters : Delay value 
  * @retval     : void
  */
static void ea_system_clock_delay(uint32_t uiDelay)
{
    if(SYS.FlagEnable)
    {
        HAL_Delay(uiDelay);
    }    
}

#endif /* SYSTEM_CLOCK_ENABLED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*****************************END OF FILE**************************************/