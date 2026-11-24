//==============================================================================================
//    File description
//==============================================================================================
/**@file         AdcCfg.h
* TITLE         : Adc configuration Header File
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
#ifndef ADCCFG_H_
#define ADCCFG_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "BSW_Cfg.h"

//=====================================================
//    Macro Definition
//=====================================================
#define AD_REF_VOLT           3.0f

//ADC
#define AD_ACQPS      19U        // SH:(AD_ACQPS+1)*SYSCLK;19U;39
#define AD_TRI_SRC    0x7U       // Trigger Source: EPWM2_SOCA

/* D2D AD Macro definition */
#define AD_ACQPS              19U        // SH:(AD_ACQPS+1)*SYSCLK;19U;39
#define D2D_AD_TRI_SRC        0xFU       // Trigger Source: EPWM6_SOCA

//D2D Channel Select
#define CH_P12V               0x3
#define CH_P1V5               0x2
#define CH_D2D_OUT_CURR       0xF
#define CH_D2D_OUT_VOLT       0x0
#define CH_D2D_OUT_DWN_CURR   0x4
#define CH_D2D_OUT_DWN_VOLT   0x1

/* PFC AD Macro definition */
#define PFC_AD_TRI_SRC        AD_TRI_SRC   // Trigger Source: EPWM2_SOCA

// PFC Channel Select
#define CH_PFC_VBUS           0x4
#define CH_DSP_CORE           0xD
#define CH_DSP_BOARD          0x3
#define CH_PFC_IAC_A          0x3
#define CH_PFC_IAC_B          0x2
#define CH_PFC_IAC_C          0x1
#define CH_PFC_VDC            0x0
#define CH_PFC_VAC_CA         0x5
#define CH_PFC_VAC_AB         0x4
#define CH_PFC_VAC_BC         0x3
#define CH_PFC_VAC_DC_A       0xF
#define CH_PFC_VAC_DC_B       0xE
#define CH_PFC_VAC_DC_C       0x2
#define CH_PFC_TMP_PT1        0x1
#define CH_PFC_TMP_PT2        0x0


//definitions for DAC number
#define DACA                  1
#define DACB                  2
#define DACC                  3


//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================

//=====================================================
//    Variable Declaration
//=====================================================

//=====================================================
//    Function Declaration
//=====================================================
static void v_AdcCfg_Cmn_Init(void);
static void v_AdcCfg_Pfc_Init(void);
static void v_AdcCfg_D2d_Init(void);

#endif /* ADCCFG_H_ */
//===========================================================================
// End of file.
//===========================================================================
