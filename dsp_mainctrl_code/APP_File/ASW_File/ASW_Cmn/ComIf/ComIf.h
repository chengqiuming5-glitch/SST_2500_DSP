//==============================================================================================
//    File description
//==============================================================================================
/**@file         ComIf.h
 * @brief
 * The header file of communication interface is designed to realize interface between customer and platform .
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
 * v_ComIf_D2dRunCmd_1ms()             \n
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

#ifndef COMIF_H_
#define COMIF_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ComIfExt.h"

#include "BSW_Cfg.h"
#include "ComExt.h"
#include "CmnDiagExt.h"
#include "PfcDiagExt.h"
#include "D2dDiagExt.h"
#include "PfcStMacExt.h"
#include "D2dStMacExt.h"
#include "PerphCtrlExt.h"
#include "PowLimExt.h"
#include "PfcDataCalcExt.h"
#include "PfcGridCtrlExt.h"
#include "PfcPowCtrlExt.h"
//#include "D2dPowCtrlExt.h"
#include "PerdTskExt.h"
#include "FltRstrtExt.h"
#include "SpiExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define POW_PFC_V2H_1MS_STEP           (2.0f*POW_ACTV_1P_RTD/800.0f)                ///< V2H mode power step:800ms for changing power from positive Max to negative Max

#define RAT_AC_OV_LOAD_STRT   1.05f                                                 ///< 1.05Pn over load curve start
#define RAT_AC_OV_LOAD_END    1.3f                                                  ///< 1.3Pn over load curve end
#define RAT_AC_OV_LOAD1       1.1f                                                  ///< 1.1Pn
#define TI_AC_OV_LOAD1        10.0f                                                 ///< 10.0min
#define RAT_AC_OV_LOAD2       1.2f                                                  ///< 1.2Pn
#define TI_AC_OV_LOAD2        1.0f                                                  ///< 1.0min
#define INV_TI_CURVE_R        (logf(TI_AC_OV_LOAD2/TI_AC_OV_LOAD1)/logf(RAT_AC_OV_LOAD1/RAT_AC_OV_LOAD2))  ///< 26.463f
#define INV_TI_CURVE_K        (TI_AC_OV_LOAD1 * powf(RAT_AC_OV_LOAD1,INV_TI_CURVE_R))                      ///< 124.558f

#define TI_1MIN_BASE_100MS    600.0f
#define TI_AC_OV_LOAD_RCV     (60.0f * TI_1MIN_BASE_100MS)                          ///< AC over load recovery time

#define AC_OL_TI_K           100.0f
#define AC_OL_TI_TBL_CNT     25U

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	ST_COM_IF stPrmExt;               ///< Parameter to extern

	Uint16  uiCntrRunTime;
	Uint16  uiFlagRunOk;
	Uint16  uiCntrCmdRst;
	Uint16  uiFlgPowOnFltRst;         ///< Flag of fault reset after power on
	Uint16  uiCntrPfcRecy;
	Uint16  uiCntrPowOn;
    float32 ftPwrActvReq;             ///< Total active power request
    float32 ftPowStepUp;              ///< Power up step
    float32 ftPowStepDwn;             ///< Power down step
#if(3U != GRID_PHASE_NUMBER)
    float32 ftFrqOLAbs;               ///< Open-loop frequency absolute
    float32 ftOutpOLAbsReq;           ///< Open-loop request output absolute
#endif

}ST_COM_IF_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_ComIf_RunMod_1ms(void);
static void v_ComIf_RunCmd_1ms(void);
static void v_ComIf_RunCmd_Pfc_1ms(void);
static Uint16 ui_ComIf_RunCmd_Pfc_Chrg_1ms(void);
static Uint16 ui_ComIf_RunCmd_Pfc_BiDir_1ms(void);
static Uint16 ui_ComIf_RunCmd_Pfc_OffGrid_1ms(void);
static Uint16 ui_ComIf_RunCmd_Pfc_OL_1ms(void);
static void v_ComIf_RunCmd_D2d_1ms(void);
static Uint16 ui_ComIf_RunCmd_D2d_Chrg_1ms(void);
static Uint16 ui_ComIf_RunCmd_D2d_Bidir_1ms(void);
static Uint16 ui_ComIf_RunCmd_D2d_OL_1ms(void);
static void v_ComIf_PfcPwrReq_1ms(void);
static void v_ComIf_PfcPwrReq_Chrg_1ms(void);
static void v_ComIf_PfcPwrReq_Bidir_1ms(void);
static void v_ComIf_D2dReq_1ms(void);
static void v_ComIf_D2dReq_Chrg_1ms(void);
static void v_ComIf_D2dReq_Dcha_1ms(void);
static void v_ComIf_D2dReq_OL_1ms(void);
static void v_ComIf_RstFlt_10ms(void);
static void v_ComIf_ArmReq_10ms(void);
static void v_ComIf_Bms_10ms(void);
#if(3U == GRID_PHASE_NUMBER)
static void v_ComIf_PfcReq_10ms(void);
#endif
static void v_ComIf_PowOnJudg_100ms(void);
static void v_ComIf_Temp_100ms(void);
static void v_ComIf_AcOvLoad_100ms(void);
static void v_ComIf_AcOvLoad_TiAcm(float32 ftAprtPwr, float32 *ftRatSumTi);
static float32 ft_ComIf_AcOL_Time(float32 ftRatAprtPwr, float32 *ftpTable);
#endif /* COMIF_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
