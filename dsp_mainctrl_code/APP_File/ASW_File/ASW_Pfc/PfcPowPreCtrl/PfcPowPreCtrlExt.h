//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcPowPreCtrlExt.h
* TITLE         : Header file of PFC power pre-control extern parameter and function
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2023.11.09
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

#ifndef PFCPOWPRECTRLEXT_H_
#define PFCPOWPRECTRLEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Pfc.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define PFC_POW_PRE_CTRL_FLG_DBG    0U    // Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    float32 ftVoltBusRef;        ///< Bus voltage reference charge in mode or bidirection mode
    float32 ftIaActvAmpRef;      ///< Active Ia amplitude reference in bidirection mode
    float32 ftIbActvAmpRef;      ///< Active Ib amplitude reference in bidirection mode
    float32 ftIcActvAmpRef;      ///< Active Ic amplitude reference in bidirection mode
    float32 ftIaReactvAmpRef;    ///< Reactive Ia amplitude reference in bidirection mode
    float32 ftIbReactvAmpRef;    ///< Reactive Ib amplitude reference in bidirection mode
    float32 ftIcReactvAmpRef;    ///< Reactive Ic amplitude reference in bidirection mode
    float32 ftVoltAcAmpRef;      ///< AC voltage amplitude reference in off-grid mode
    float32 ftDutyAmpRef;        ///< Duty amplitude reference in open-loop mode
    float32 ftReactvPowComp;     ///< Reactive power compensation
}ST_PFC_POW_PRE_CTRL;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PFC_POW_PRE_CTRL stPfcPowPreCtrl;

#if (1U == PFC_POW_PRE_CTRL_FLG_DBG)
extern ST_PFC_POW_PRE_CTRL stPfcPowPreCtrlDbg;
#endif

#endif /* PFCPOWPRECTRLEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
