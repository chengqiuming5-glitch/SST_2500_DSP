//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dPowPreCtrlExt.h
 * @brief
 * The external header file of D2d power pre-control is designed to realize preparation for loop control.
 *
 * Module      :                       \n
 * D2dPowPreCtrl                       \n
 *
 * Unit        :                       \n
 * PrmUpd                              \n
 * Ramp                                \n
 * FrqJit                              \n
 *
 * Module Task :                       \n
 * v_D2dPowPreCtrl_Init()              \n
 * v_D2dPowPreCtrl_1ms()               \n
 *
 * Unit Task   :                       \n
 * v_D2dPowPreCtrl_PrmUpd_Init()       \n
 * v_D2dPowPreCtrl_PrmUpd_1ms()        \n
 *
 * v_D2dPowPreCtrl_Ramp_Init ()        \n
 * v_D2dPowPreCtrl_Ramp_1ms()          \n
 *
 * v_D2dPowPreCtrl_FrqJit_Init()       \n
 * v_D2dPowPreCtrl_FrqJit_1ms()
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2023/11/22
 * @version
 * V1.0
 * @copyright
 * (c) Copyright 2000-2050, Wanbang New Energy Investment Co.,LTD..    \n
 *                            All Rights Reserved
 * @attention
 * MCU           : TMS320F2837xD     \n
 * Environment   : CCSv10.4.0
 * @note
 * <table>
 * <tr><th>Date        <th>Version         <th>Author       <th>Description
 * <tr><td>2023/11/22  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef D2DPOWPRECTRLEXT_H_
#define D2DPOWPRECTRLEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_D2d.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define D2D_POW_PRE_CTRL_DBG       0U     ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    float32 ftVoltBattBurst;              ///< Battery burst voltage
    float32 ftCurrBattBurst;              ///< Battery burst current
    float32 ftVoltBusBurst;               ///< Bus burst voltage

    float32 ftVoltBattChrgRef;            ///< Battery voltage loop Reference
    float32 ftCurrBattChrgRef;            ///< Battery current loop Reference
    float32 ftVoltBusRef;                 ///< Bus voltage reference
    
    float32 ftOutpOLRef;                  ///< Open-loop output Reference
	float32 ftFrqJit;                     ///< MOS frequency
	float32 ftDp3OLRef;                   ///< Open-loop Dp3 Reference

	float32 ftOutpPwmDuty;                ///< Soft-start PWM Duty

    Uint16  uiFlgDp3OLDone;               ///< flag of DP3 ramp done in open-loop mode
	Uint16  uiFlgRampDone;                ///< flag of ramp done
}ST_D2D_POW_PRE_CTRL;                     ///< Definition of module D2dPowPreCtrl global Struct

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_D2D_POW_PRE_CTRL stD2dPowPreCtrl;

#if (1U == D2D_POW_PRE_CTRL_DBG)
extern ST_D2D_POW_PRE_CTRL stD2dPowPreCtrlDbg;
#endif

#endif /* D2DPOWPRECTRLEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================

