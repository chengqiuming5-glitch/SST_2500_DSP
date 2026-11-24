//==============================================================================================
//    File description
//==============================================================================================
/**@file         ComIfExt.h
 * @brief
 * The external header file of communication interface is designed to realize interface between customer and platform .
 *
 * Module      :                       \n
 * ComIf                               \n
 *
 * Unit        :                       \n
 * D2dRunMod                           \n
 * D2dRunCmd                           \n
 * ChrgReq                             \n
 * DchaReq                             \n
 * OLReq                               \n
 * PowCtrl                             \n
 * ArmFlt                              \n
 * BldReq                              \n
 *
 * Module Task :                       \n
 * v_ComIf_Init()                      \n
 * v_ComIf_1ms()                       \n
 *
 * Unit Task   :                       \n
 * v_ComIf_D2dRunMod_1ms()             \n
 * v_ComIf_RunCmd_D2d_1ms()            \n
 * v_ComIf_D2dReq_Chrg_1ms()           \n
 * v_ComIf_D2dReq_Dcha_1ms()           \n
 * v_ComIf_D2dReq_OL_1ms()             \n
 * v_ComIf_PowCtrl_1ms()               \n
 * v_ComIf_ArmFlt_1ms()                \n
 * v_ComIf_ArmReq_10ms()                \n
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

#ifndef COMIFEXT_H_
#define COMIFEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define COM_IF_DBG                0U              ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	Uint16 uiModRun;              ///< Run mode
	Uint16 uiModPfcRun;           ///< PFC mode
	Uint16 uiModD2dRun;           ///< D2D Run mode
	Uint16 uiCmdRun;              ///< Run command
	Uint16 uiCmdPfcRun;           ///< PFC command
	Uint16 uiCmdD2dRun;           ///< D2D Run command
	Uint16 uiModPfcImBal;         ///< PFC Imbalance run mode
	Uint16 uiModPfcPhaLoss;       ///< Phase loss run mode
	Uint16 uiModPfcNonPhaN;       ///< None Phase N mode
	Uint16 uiFlgPfcTz;            ///< PFC TZ flag
	Uint16 uiFlgPfcTzToDC;        ///< PFC TZ flag to DC module
	Uint16 uiFlgPowOn;            ///< Power on flag
    Uint16 uiFlgBldPtd;           ///< Flag of bleed permitted
    Uint16 uiCmdV2LAuxPow;        ///< V2L Aux power command
    Uint16 uiFlgFltRst;           ///< Fault reset flag
    Uint16 uiEnaAcOvLoad;         ///< Enable signal of AC over load
    Uint16 uiValRunTimeMs;        ///< Run Time for debug

	float32 ftVoltBattChrgReq;    ///< Battery charge voltage request
	float32 ftCurrBattChrgReq;    ///< Battery charge current request
	float32 ftVoltBattDchaReq;    ///< Battery discharge voltage request
	float32 ftCurrBattDchaReq;    ///< Battery discharge current request
	float32 ftOutpOLReq;          ///< Open-loop output request
	float32 ftPwrChrgReq;         ///< Charge active power request
    float32 ftPaReq;              ///< Phase A active power request
    float32 ftPbReq;              ///< Phase B active power request
    float32 ftPcReq;              ///< Phase C active power request
    float32 ftQaReq;              ///< Phase A reactive power request
    float32 ftQbReq;              ///< Phase B reactive power request
    float32 ftQcReq;              ///< Phase C reactive power request
    float32 ftVoltBattBms;        ///< Battery voltage from BMS
    float32 ftVoltBattBmsMax;     ///< Max battery voltage from BMS
    float32 ftCoeffBusPreChrg;    ///< PFC bus voltage pre-charge coefficient
    float32 ftTempArmBd;          ///< ARM board temperature
    float32 ftTempNtc0;           ///< NTC0 temperature: AC Terminal temperature
    float32 ftTempNtc1;           ///< NTC1 temperature: 7.4-PFC slow MOS NTC temperature, 11-reserved
    float32 ftTempNtc2;           ///< NTC2 temperature: 7.4-PFC quick MOS NTC temperature, 11-PFC-MOS
    float32 ftTempNtc3;           ///< NTC3 temperature: 7.4-D2D up NTC temperature, 11-D2D primary side MOS
    float32 ftTempNtc4;           ///< NTC4 temperature: 7.4-D2D down NTC temperature, 11-D2D secondary side MOS
    float32 ftTempNtc5;           ///< NTC5 temperature: 7.4-D2D transformer NTC temperature, 11-D2D magnetic medium
    float32 ftTempNtc6;           ///< NTC6 temperature: 7.4-D2D inductor NTC temperature, 11-reserved

    float32 ftRatSumTiOvLoad;     ///< AC over load time accumulation ratio
    float32 ftPAcMax;             ///< AC Max power
    float32 ftPOnePhaMax;         ///< One phase Max active power
    float32 ftIdAcMax;            ///< Max AC active current amplitude
    float32 ftCurrAcRmsMax;       ///< Max AC current RMS
}ST_COM_IF;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_COM_IF stComIf;

#if (1U == COM_IF_DBG)
extern ST_COM_IF stComIfDbg;
#endif


#endif /* COMIFEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
