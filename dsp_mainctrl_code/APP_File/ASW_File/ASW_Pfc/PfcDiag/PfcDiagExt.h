//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcDiagExt.h
* TITLE         : Header file of PFC fault diagnosis external parameter and function
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2024.03.20
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

#ifndef PFC_FILE_PFCDIAG_PFCDIAGEXT_H_
#define PFC_FILE_PFCDIAG_PFCDIAGEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Pfc.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define PFC_DIAG_DBG    0U    // Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef union
{
    Uint16 all;

    struct
    {
        Uint16 uiGridHwPosOC : 1;    /* bit0: Grid hardware positive over-current fault */
        Uint16 uiGridHwNegOC : 1;    /* bit1: Grid hardware negative over-current fault */
        Uint16 uiBusHwOV     : 1;    /* bit2: Bus hardware over-voltage fault */
        Uint16 uiGridOV      : 1;    /* bit3: Grid over-voltage fault */
        Uint16 uiChkStOT     : 1;    /* bit4: Check state over-time fault */
        Uint16 uiCBCOT       : 1;    /* bit5: CBC over-time fault */
        Uint16 uiGridOC      : 1;    /* bit6: Grid over-current fault */
        Uint16 uiTzHwSum     : 1;    /* bit7: TZ hardware fault summary */
        Uint16 uiWiring      : 1;    /* bit8: Wiring fault */
        Uint16 uiRsvd9       : 1;    /* bit9: Reserved 9 */
        Uint16 uiPosBusHwOV  : 1;    /* bit10: Positive Bus hardware over-voltage fault */
        Uint16 uiNegBusHwOV  : 1;    /* bit11: Negative Bus hardware over-voltage fault */
        Uint16 uiAcOL        : 1;    /* bit12: AC over-load fault */
        Uint16 uiRsvd13      : 1;    /* bit13: Reserved 13 */
        Uint16 uiRsvd14      : 1;    /* bit14: Reserved 14 */
        Uint16 uiRsvd15      : 1;    /* bit15: Reserved 15 */
    }bit;
}UN_PFC_DIAG_FLT;

typedef struct
{
    UN_PFC_DIAG_FLT unFlt;    ///< Diagnose fault

    Uint16  uiMaxFltLevel;            ///< Maximum fault level
    Uint16  uiCmdRstHW;               ///< Hardware fault reset command
    Uint16  uiBusUVProt10Times;       ///< Bus under protection 10 times
    Uint16  uiBusOVProt10Times;       ///< Bus under protection 10 times
    Uint16  uiHalfBusOVProt10Times;   ///< Half Bus over voltage protect value 10 times
    Uint16  uiMidBusOVProt10Times;    ///< Mid-point bus voltage imbalance protect value 10 times
    Uint16  uiAcRmsOCProt100Times;    ///< AC RMS Over current protection
    Uint16  uiVgDcProt1000Times;      ///< Vg DC protection
    Uint16  uiIgDcProt1000Times;      ///< Vg DC protection
    Uint16  uiVoltAcImBal10Times;     ///< AC voltage imbalance protect value 10 times
    Uint16  uiCurrAcImBal100Times;    ///< AC current imbalance protect value 100 times
    Uint16  uiTiAcOCProt;             ///< AC over current protect time
    Uint16  uiTiAcOVProt;             ///< AC over voltage protect time
    Uint16  uiTiCbcProt;              ///< CBC protect time
    float32 ftRatPwrOvLoadLim;        ///< AC power over load protect value: power ratio
    float32 ftAcOVProt;               ///< AC Over voltage protection
    float32 ftAcOCProt;               ///< AC Over current protection
}ST_PFC_DIAG;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PFC_DIAG stPfcDiag;

#if (1U == PFC_DIAG_DBG)
extern ST_PFC_DIAG stPfcDiagDbg;
#endif

#endif /* PFC_FILE_PFCDIAG_PFCDIAGEXT_H_ */
