//==============================================================================================
//    File description
//==============================================================================================
/**@file         CmpssCfg.h
* TITLE         : Cmpss configuration Header File
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

#ifndef CMPSSCFG_H_
#define CMPSSCFG_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "BSW_Cfg.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "PfcStMacExt.h"

//=====================================================
//    Macro Definition
//=====================================================

/* CMPSS Macro definition */
#define REFERENCE_VDDA                 0U
#define REFERENCE_VDAC                 1U
//definitions for COMPH input selection
#define NEGIN_DAC                      0U
#define NEGIN_PIN                      1U
//definitions for OR gate  INput selection
#define ORGATE_ASYNCH_DIS              0U
#define ORGATE_ASYNCH_EN               1U
//definitions for CTRIPH/CTRIPOUTH output selection
#define CTRIP_ASYNCH                   0U
#define CTRIP_SYNCH                    1U
#define CTRIP_FILTER                   2U
#define CTRIP_LATCH                    3U

#define MAX_CMPSS_DACVAL               4095U

//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================

//=====================================================
//    Variable Declaration
//=====================================================

//=====================================================
//    Function Declaration
//=====================================================
static void v_CmpssCfg_Pfc_Init(void);
static void v_CmpssCfg_D2d_Init(void);

#endif /* CMPSSCFG_H_ */
//===========================================================================
// End of file.
//===========================================================================
