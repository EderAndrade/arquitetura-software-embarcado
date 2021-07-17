
/**
  ******************************************************************************
  * @Company    : Eder Andrade Ltda.
  * @file       : ea_api_accel.c
  * @author     : Eder Andrade
  * @version	: V0.0 
  * @date       : 26/04/2021
  * @brief      : API of accelerometer
  ******************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
#include "stdint.h"
#include "string.h"
// Eder Andrade driver library
// API library
#include "ea_api_accel.h"
// Third party library
#include "lsm303dlhc.h"

/*******************************************************************************
							HOW TO USE THIS DRIVER
********************************************************************************

1. 	First, you should include in your .c file the "ea_api_accel.h" file.

2.  Call ea_api_accel_init() to initialize the driver;

3.  Call ea_api_accel_get_xyz() to get the accelerometer values.


*******************************************************************************/

/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum 
{
  ACCELERO_OK       = 0,
  ACCELERO_ERROR    = 1,
  ACCELERO_TIMEOUT  = 2,
      
} 
ACCELERO_StatusTypeDef;

/* Private variables ---------------------------------------------------------*/
static ACCELERO_DrvTypeDef *AccelerometerDrv;

/* Private function prototypes -----------------------------------------------*/    
int8_t   ea_api_accel_init   (void);    // Initialize the API
int8_t   ea_api_accel_reset  (void);    // Deinitialize the API
int8_t   ea_api_accel_get_xyz(int16_t*);// Executes some functionality

/* Public objects ------------------------------------------------------------*/
/* Body of private functions -------------------------------------------------*/

/**
  * @Func       : ea_api_accel_init    
  * @brief      : Init. accel driver
  * @pre-cond.  : SysClk function
  * @post-cond. : Accel ready to use if everthing went right
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_accel_init(void)
{
    uint8_t     ret     = ACCELERO_ERROR;
    uint16_t    ctrl    = 0x0000;
    ACCELERO_InitTypeDef            LSM303DLHC_InitStructure    = {0};
    ACCELERO_FilterConfigTypeDef    LSM303DLHC_FilterStructure  = {0};

    if(Lsm303dlhcDrv.ReadID() == I_AM_LMS303DLHC)
    {
        /* Initialize the gyroscope driver structure */
        AccelerometerDrv = &Lsm303dlhcDrv;

        /* MEMS configuration ------------------------------------------------*/
        /* Fill the accelerometer structure */
        LSM303DLHC_InitStructure.Power_Mode         = LSM303DLHC_NORMAL_MODE;
        LSM303DLHC_InitStructure.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
        LSM303DLHC_InitStructure.Axes_Enable        = LSM303DLHC_AXES_ENABLE;
        LSM303DLHC_InitStructure.AccFull_Scale      = LSM303DLHC_FULLSCALE_2G;
        LSM303DLHC_InitStructure.BlockData_Update   = LSM303DLHC_BlockUpdate_Continous;
        LSM303DLHC_InitStructure.Endianness         = LSM303DLHC_BLE_LSB;
        LSM303DLHC_InitStructure.High_Resolution    = LSM303DLHC_HR_ENABLE;

        /* Configure MEMS: data rate, power mode, full scale and axes --------*/
        ctrl |= (LSM303DLHC_InitStructure.Power_Mode | LSM303DLHC_InitStructure.AccOutput_DataRate | \
                           LSM303DLHC_InitStructure.Axes_Enable);

        ctrl |= ((LSM303DLHC_InitStructure.BlockData_Update | LSM303DLHC_InitStructure.Endianness | \
                          LSM303DLHC_InitStructure.AccFull_Scale | LSM303DLHC_InitStructure.High_Resolution) << 8);

        /* Configure the accelerometer main parameters -----------------------*/
        AccelerometerDrv->Init(ctrl);

        /* Fill the accelerometer LPF structure ------------------------------*/
        LSM303DLHC_FilterStructure.HighPassFilter_Mode_Selection    = LSM303DLHC_HPM_NORMAL_MODE;
        LSM303DLHC_FilterStructure.HighPassFilter_CutOff_Frequency  = LSM303DLHC_HPFCF_16;
        LSM303DLHC_FilterStructure.HighPassFilter_AOI1              = LSM303DLHC_HPF_AOI1_DISABLE;
        LSM303DLHC_FilterStructure.HighPassFilter_AOI2              = LSM303DLHC_HPF_AOI2_DISABLE;

        /* Configure MEMS: mode, cutoff frquency, Filter status, Click, AOI1 and AOI2 */
        ctrl = (uint8_t) (LSM303DLHC_FilterStructure.HighPassFilter_Mode_Selection |\
                          LSM303DLHC_FilterStructure.HighPassFilter_CutOff_Frequency|\
                          LSM303DLHC_FilterStructure.HighPassFilter_AOI1|\
                          LSM303DLHC_FilterStructure.HighPassFilter_AOI2);

        /* Configure the accelerometer LPF main parameters -------------------*/
        AccelerometerDrv->FilterConfig(ctrl);
        ret = ACCELERO_OK;
    }  
    else
    {
        ret = ACCELERO_ERROR;
    }
    return ret;	
}

/**
  * @Func       : ea_api_accel_reset    
  * @brief      : Reset accel
  * @pre-cond.  : Call ea_api_accel_init() first
  * @post-cond. : Accel reseted
  * @parameters : void
  * @retval     : int8_t -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_accel_reset(void)
{
    if(AccelerometerDrv->Reset != NULL)
    {
        AccelerometerDrv->Reset();
        // OK
        return 0;
    }
    // Error
    return -1;
}

/**
  * @Func       : ea_api_accel_get_xyz    
  * @brief      : Read x, y and z axis values
  * @pre-cond.  : Call ea_api_accel_init() first
  * @post-cond. : All axis values stored in variable passed
  * @parameters : pDataXYZ  -> vector to store the values
  * @retval     : int8_t    -> (value == 0) = OK; (value < 0) = ERROR
  */
int8_t ea_api_accel_get_xyz(int16_t *pDataXYZ)
{   
    if(AccelerometerDrv->GetXYZ!= NULL)
    {   
        AccelerometerDrv->GetXYZ(pDataXYZ);
        // OK
        return 0;
    }
    // Error
    return -1;
}
/*****************************END OF FILE**************************************/