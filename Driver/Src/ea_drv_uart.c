
/**
  ******************************************************************************
  * @Company: Eder Andrade Ltda.
  * @file	: ea_drv_uart.c
  * @author : Eder Andrade
  * @version: V0.0
  * @date   : 23/02/2021
  * @brief  : Source file of driver that controls UART
   *****************************************************************************
*/
#ifdef UART_ENABLED

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
#include "string.h"
// Eder Andrade driver library
#include "ea_drv_uart.h"

/*******************************************************************************
							HOW TO USE THIS DRIVER
********************************************************************************

1. 	First, you should include in your .c file: "ea_drv_uart.h" and call UART object,
	after that, you can use the follow resources of the driver

	- UART: this is the object that will control the peripheral;	

	Data -----------------------------------------------------------------------

	- UART.bFlagEnable	===================> It informs if UART driver is enabled
	- UART.bFlagIsTxDone ==================> Informs if TX process was completed
	- UART.cTxBuffer[x] ===================> Stores bytes sent	

	Methods --------------------------------------------------------------------

	- UART.Open() =========================> Initializes the UART driver;
	- UART.Close() ========================> Finishes the UART driver;
	- UART.Write() ========================> Write a byte or string to sent and stores in the TX buffer

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* Private function prototypes -----------------------------------------------*/
static int8_t ea_uart_open	(void);				// Initializes UART peripheral
static int8_t ea_uart_close	(void);				// Finishes UART peripheral
static int8_t ea_uart_write	(char*, uint16_t);	// Write the content in TX buffer to transmit

/* Public objects ------------------------------------------------------------*/
st_uart_t UART = 
{
    /* UART disabled **********************************************************/
    .FlagEnable 	= RESET			,	
	.FlagIsTxDone 	= RESET			,	// Flags is setted because in begining nothing was sent
    
    /* All buffers are cleared ************************************************/
	.cTxBuffer		= {0}			,
    
    /* Function pointers loaded ***********************************************/
    .Open   		= &ea_uart_open ,
    .Close  		= &ea_uart_close,
    .Write  		= &ea_uart_write	
      
};

/* Bodies of private functions -----------------------------------------------*/
/**
  * @Func       : USART1_IRQHandler    
  * @brief      : This function handles USART1 global interrupt.
  * @pre-cond.  : ea_uart_open() must be called first
  * @post-cond. : Attends interrupts and invoke callbacks if it's enabled
  * @parameters : void
  * @retval     : void
  */
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart1);
}

/**
  * @Func       : HAL_UART_TxCpltCallback    
  * @brief      : Tx Transfer completed callbacksk
  * @pre-cond.  : ea_uart_open() must be called first
  * @post-cond. : Invoked by UART IRQ indicating the sending is completed.
  * @parameters : *huart
  * @retval     : void
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
    */

    // This interrupt is called when the whole TX process is done.
	// Data transmition was completed !!!
    UART.FlagIsTxDone = SET;  
}

/**
  * @Func       : ea_uart_open    
  * @brief      : Initializes UART peripheral
  * @pre-cond.  : SysClk configured
  * @post-cond. : UART configured by interruption and already running
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_uart_open(void)
{
	/* Configuring UART1 ******************************************************/   
    huart1.Instance             = USART1;
    huart1.Init.BaudRate        = 115200;
    huart1.Init.WordLength      = UART_WORDLENGTH_8B;
    huart1.Init.StopBits        = UART_STOPBITS_1;
    huart1.Init.Parity          = UART_PARITY_NONE;
    huart1.Init.Mode            = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling    = UART_OVERSAMPLING_16;
    if(HAL_UART_Init(&huart1) != HAL_OK)
    {
        return -1;
    }
  	// UART enabled
	UART.FlagEnable = SET;
	// OK
	return 0;
}

/**
  * @Func       : ea_uart_close    
  * @brief      : Disable UART peripheral
  * @pre-cond.  : ea_uart_open() already called
  * @post-cond. : UART disabled and stopped
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_uart_close(void)
{
	// Check if UART was enabled
	if(UART.FlagEnable)
	{
		// Deinit. UART
		if(HAL_UART_DeInit(&huart1) != HAL_OK)
        {
            return -1;
        }
		// Clear all flags
		UART.FlagEnable	    = RESET;
		UART.FlagIsTxDone	= RESET;
		// Clear all buffers
		memset(UART.cTxBuffer, 0, sizeof(UART.cTxBuffer));			
		// OK
		return 0;
	}
	// UART is disabled
	return -2;
}

/**
  * @Func       : ea_uart_write    
  * @brief      : Send a string on the communication bus
  * @pre-cond.  : ea_uart_open() already called
  * @post-cond. : String sent
  * @param      : *pvVal	-> Point to buffer to transmit data
  * @param      : uiSize	-> Lenght of buffer to transmit
  * @retval     : int8_t 	-> (value == 0) = OK; (value < 0) = ERROR
  */
static int8_t ea_uart_write(char *pvVal, uint16_t uiSize)
{
	// Check if UART was enabled
	if(UART.FlagEnable)
	{
		// Test the pointer and others...
		if(pvVal != NULL && ((uiSize != 0) && uiSize < LENGHT_TX_BUFFER))
		{						
            // TX in process
            UART.FlagIsTxDone = RESET;				
            // Store in TX buffer the data to be transmitted
            memset(UART.cTxBuffer, 0, LENGHT_TX_BUFFER);
            memcpy(UART.cTxBuffer, (const char*)pvVal, uiSize);
            
            // if(HAL_UART_GetState(&huart2) == HAL_UART_STATE_READY)
            if(HAL_UART_GetState(&huart1) == HAL_UART_STATE_READY)
            {
                // Transmit by interruption               
                if(HAL_UART_Transmit_IT(&huart1, (uint8_t*)UART.cTxBuffer, uiSize) != HAL_OK)     
                {
                    return -1;
                }
                // OK
                return 0;
            }
            // UART is busy
            return -2;
        }
		// Pointer pvVal is NULL, or Size equals to 0 or uiSize is bigger than buffer
		return -3;
	}
	// UART is not enabled
	return -4;	
}

#endif /* UART_ENABLED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*****************************END OF FILE**************************************/