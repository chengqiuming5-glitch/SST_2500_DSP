//==============================================================================================
//    File description
//==============================================================================================
/**@file         GpioCfg.h
* TITLE         : Gpio configuration Header File
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2023.11.10
* Version       : V1.0
* Descriptions  :
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
* Descriptions  :
************************************************************************************************
*/

/*
************************************************************************************************
* Module        :
* 1st Unit      :
* 2nd Unit      :
* 3rd Unit      :
*
* Module Task   :

*
* 1st Unit Task :
*
* 2nd Unit Task :
*
* 3rd Unit Task :
*
************************************************************************************************
*/

#ifndef GPIOCFG_H_
#define GPIOCFG_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "BSW_Cfg.h"

//=====================================================
//    Macro Definition
//=====================================================
//PFC
#define PFC_ECAP1                      16U
#define PFC_ECAP2                      17U
#define PFC_ECAP3                      18U

//PFC OCP GPIO
#define PFC_OCPA_HW                    32U
#define PFC_OCPB_HW                    29U
#define PFC_OCPC_HW                    28U

//D2D
#define HW_FLT_GPIO_QUAL    GPIO_QUAL6    // 3 Samples

//Public
#define DSP_TO_ARM_EMG_ON     GpioDataRegs.GPASET.bit.GPIO8 = 1U       // Turn on DSP to ARM Emergence signal
#define DSP_TO_ARM_EMG_OFF    GpioDataRegs.GPACLEAR.bit.GPIO8 = 1U     // Turn off DSP to ARM Emergence signal
#define ARM_TO_DSP_EMG_IS_ON  (0U == GpioDataRegs.GPDDAT.bit.GPIO99)   // ARM to DSP Emergence is on
#define ARM_TO_DSP_EMG_IS_OFF (1U == GpioDataRegs.GPDDAT.bit.GPIO99)   // ARM to DSP Emergence is off

//COMMON SPI GPIO
#define CMN_SPI_SIMO                    54U
#define CMN_SPI_SOMI                    55U
#define CMN_SPI_CLK                     56U
#define CMN_SPI_STE                     57U
#define MUX_OPTION_SPI_SIMO             1U
#define MUX_OPTION_SPI_SOMI             1U
#define MUX_OPTION_SPI_CLK              1U
#define MUX_OPTION_SPI_STE              0U

//COMMON IIC GPIO
#define CMN_I2C_SDA                     0U
#define CMN_I2C_SCL                     1U
#define CMN_I2C_WP                      2U
#define MUX_OPTION_I2C_SDA              6U
#define MUX_OPTION_I2C_SCL              6U
#define MUX_OPTION_I2C_WP               0U

//COMMON SCI GPIO
#define CMN_SCI_TX                      22U
#define CMN_SCI_RX                      23U
#define MUX_OPTION_SCI_TX               3U
#define MUX_OPTION_SCI_RX               3U

//COMMON LED GPIO
#define DSP_RUN_LED                     63U
#define DSP_FAULT_LED                   62U

//COMMON HARDWARE FAULT GPIO
#define CMN_FAULT_HW                    14U
#define CMN_FAULT_RST                   15U

//HARDWARE WATCHDOG INPUT
#define CMN_FEED_DOG                    91U
#define CMN_OCP_A                       5U
#define CMN_OCP_B                       6U
#define CMN_OCP_C                       7U
#define CMN_TEST4                       8U

#define GPIO_QUAL_SYNC        0U    // Sync
#define GPIO_QUAL_3SAMPLES    1U    // 3 Samples
#define GPIO_QUAL_6SAMPLES    2U    // 6 Samples
#define GPIO_QUAL_ASYNC       3U    // Async

#define FLG_TEST_GPIO_EN      0U    ///< GPIO Debug Enabled

//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================

//=====================================================
//    Variable Declaration
//=====================================================

//=====================================================
//    Function Declaration
//=====================================================
//PFC
static void v_GpioCfg_Pfc_Init(void);
static void v_GpioCfg_Pfc_DCSwitch_Init(void);
static void v_GpioCfg_Pfc_Rst_Init(void);
static void v_GpioCfg_Pfc_SW_Init(void);
static void v_GpioCfg_Pfc_ZCD_Init(void);
static void v_GpioCfg_Pfc_HwFlt_Init(void);
static void v_GpioCfg_Pfc_Rly_Init(void);
static void v_GpioCfg_Pfc_BusAux_Init(void);
static void v_GpioCfg_Pfc_Tz_Init(void);
static void v_GpioCfg_Pfc_EPwm_Init(void);
static void v_GpioCfg_Pfc_ECap_Init(void);
static void v_GpioCfg_Pfc_Led_Init(void);

//D2D
static void v_GpioCfg_D2d_Init(void);
static void v_GpioCfg_D2d_EPwm_Init(void);
static void v_GpioCfg_D2d_Bleed_Init(void);
static void v_GpioCfg_D2d_Rly_Init(void);
static void v_GpioCfg_D2d_Led_Init(void);
static void v_GpioCfg_D2d_HwFlt_Init(void);
#if GRID_PHASE_NUMBER > 1U
static void v_GpioCfg_D2d_V2L_Init(void);
#endif

//Commom
static void v_GpioCfg_Cmn_Init(void);
static void v_GpioCfg_Cmn_Spi_Init(void);
static void v_GpioCfg_Cmn_Can_Init(void);
static void v_GpioCfg_Cmn_I2c_Init(void);
static void v_GpioCfg_Cmn_Led_Init(void);
static void v_GpioCfg_Cmn_HwFlt_Init(void);
static void v_GpioCfg_Cmn_Sci_Init(void);
static void v_GpioCfg_Cmn_Emif_Init(void);
static void v_GpioCfg_Cmn_WDog_Init(void);
#endif /* GPIOCFG_H_ */
//===========================================================================
// End of file.
//===========================================================================
