//==============================================================================================
//    File description
//==============================================================================================
/**@file         EPwmCfg.h
* TITLE         : Epwm configuration Header File
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

#ifndef EPWMCFG_H_
#define EPWMCFG_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "BSW_Cfg.h"
#include "ComExt.h"
#include "CDD_Drv.h"
//=====================================================
//    Macro Definition
//=====================================================
#define PWM_DCEVT_EN                  1U    ///< PWM DCEVT Enabled
//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================

//=====================================================
//    Variable Declaration
//=====================================================

//=====================================================
//    Function Declaration
//=====================================================
static void v_EPwmCfg_Pfc_Init(void);
static void v_EPwmCfg_Pfc_PhaD_Init(void);
static void v_EPwmCfg_Pfc_PhaA_Init(void);
static void v_EPwmCfg_Pfc_PhaB_Init(void);
static void v_EPwmCfg_Pfc_PhaC_Init(void);
extern void v_EPwmCfg_Pfc_TzTrig_Init(void);

static void v_EPwmCfg_D2d_Init(void);
static void v_EPwmCfg_D2d_PriBrdgL_Init(void);
static void v_EPwmCfg_D2d_PriBrdgR_Init(void);
static void v_EPwmCfg_D2d_SecUpBrdgL_Init(void);
static void v_EPwmCfg_D2d_SecUpBrdgR_Init(void);
static void v_EPwmCfg_D2d_SecDwnBrdgL_Init(void);
static void v_EPwmCfg_D2d_SecDwnBrdgR_Init(void);
static void v_EPwmCfg_D2d_ClaPerd_Init(void);
static void v_EPwmCfg_D2d_Cmn_Init(volatile struct EPWM_REGS *stEpwmX);
#endif /* EPWMCFG_H_ */
//===========================================================================
// End of file.
//===========================================================================
