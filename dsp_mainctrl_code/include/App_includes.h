/*
###########################################################################
* FILE          : App_includes.h
* TITLE         : APP Include Head File
###########################################################################
* Copyright (C) 2020-2050, Wanbang Digital Energy Co.,LTD.
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Created by    :
* Created date  : 2023.07.06
* Version       : v1.0
* Descriptions  : Include Header Files & Macro Definition &
*                 Variable Declaration & Function Declaration
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
* Descriptions  :
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
* Descriptions  :
###########################################################################
*/

/*
###########################################################################
* @file         App_includes.h
* @brief        APP Include Header File
* @details
* @author
* @date         2023.07.06
* @version      v1.0
* @copyright    (C) 2020-2050, Wanbang Digital Energy Co.,LTD.
--------------------------------------------------------------------------
--------------------------------------------------------------------------
* @attention
* MCU:          TMS320F2837xD \n
* Environment:  CCS v10.4.0
* @par Log Information:
* <table>
* <tr><th>Date         <th>Version       <th>Author       <th>Description
* <tr><td>2023.07.06   <td>1.0           <td>Ricky        <td>Initial Version
* </table>
*
###########################################################################
*/

#ifndef INCLUDE_USER_INC_APP_INCLUDES_H_
#define INCLUDE_USER_INC_APP_INCLUDES_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "ASW_Cmn.h"
#include "ASW_D2d.h"
#include "ASW_Pfc.h"

#include "EepExt.h"
#include "EepDrv.h"
#include "EPwmCfg.h"
#include "SwVersExt.h"

#include "PerdTskExt.h"
#include "ComExt.h"
#include "ComIfExt.h"
#include "PerphCtrlExt.h"
#include "PowLimExt.h"
#include "CmnAdcExt.h"
#include "CmnDiagExt.h"

#include "D2dAdcExt.h"
#include "D2dDiagExt.h"
#include "D2dPowCtrlExt.h"
#include "D2dPowPreCtrlExt.h"
#include "D2dStMacExt.h"

#include "PfcAdcExt.h"
#include "PfcStMacExt.h"
#include "PfcDataCalcExt.h"
#include "PfcGridCtrlExt.h"
#include "PfcDiagExt.h"
#include "PfcPowCtrlExt.h"
#include "PfcPowPreCtrlExt.h"
//=====================================================
//    Macro Definition
//=====================================================
/* Power limitation calculation typedef */
//typedef struct
//{
//    float32 ftAcVoltLmtCoef;    // Limit coefficient according to AC voltage
//    float32 ftDcVoltLmtCoef;    // Limit coefficient according to DC voltage
//    float32 ftHTLmtCoef;    // Limit coefficient according to High temperature
//    float32 ftLmtCoef;    // Limit coefficient
//
//    float32 ftDcCurrLmtPow;    // Limit coefficient according to DC current
//    float32 ftLmtPow;    // Limit power
//}ST_LMT_PARAM;

//typedef struct
//{
//    float32 ftOutVoltCal;    // Out Voltage calculation
//    float32 ftLTLmtCoef;    //  Limit coefficient according to Low temperature
//    float32 ftChgCurrLmt;    // Charge current limitation
//    float32 ftDischCurrLmt;    // Discharge current limitation
//    float32 ftChgCurrMaxToBms;    // Max charge current to BMS
//    float32 ftDischCurrMaxToBms;    // Max discharge current to BMS
//    float32 ftChgPowMaxToBms;    // Max charge power to BMS
//    float32 ftDischPowMaxToBms;    // Max discharge power to BMS
//
//    ST_LMT_PARAM stChgLmtParam;    // Charge limit parameter
//    ST_LMT_PARAM stDischLmtParam;    // Discharge limit parameter
//}ST_POW_LMT;

/* Temperature Macro Definition */
//#define AIR_Temp_TBL_CNT    166U    // Air Temperature Table Counter
//#define AIR_Temp_TBL_BIAS    -40    // Air Temperature Table Bias

//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================
/* Temperature process typedef */
//typedef enum
//{
//    LOW_POW_INIT_STS, LOW_POW_RUN_STS, ADD_POW_RUN_STS, ADD_POW_OK_STS
//}EN_LOW_TEMP_STS;

//typedef struct
//{
//    float32 ftDspCore;    // DSP core temperature
//    float32 ftDspBd;    // DSP Board temperature
//    float32 ftArmBd;    // ARM Board temperature
//    float32 ftPfcSlowNtc;    // PFC slow MOS NTC temperature
//    float32 ftPfcQuickNtc;    // PFC quick MOS NTC temperature
//    float32 ftD2dUpNtc;    // D2D up NTC temperature
//    float32 ftD2dDnNtc;    // D2D down NTC temperature
//    float32 ftD2dTr;    // D2D transformer NTC temperature
//    float32 ftD2dLr;    // D2D inductor NTC temperature
//    float32 ftNtc1;
//    float32 ftNtc2;
//    float32 ftNtc3;
//    float32 ftNtc4;
//}ST_TEMP_MEM;

//typedef struct
//{
//    Uint16 u16LowTempFlg;    // Low Temperature Flag
//    Uint16 u16LowTempCnt;    // Low Temperature Counter
//    Uint16 u16LowTempTim;    // Low Temperature Time
//
//    float32 ftDspCoreAD;    // DSP internal temperature AD result
//    float32 ftDspBdAD;      // DSP board AD result
//
//    float32 f32HighTempCofTgt;    // High Temperature Coefficient Target
//    float32 f32HighTempCof;    // High Temperature Coefficient
//    float32 f32LowTempPowLmt;    // Low Temperature Power Limit
//
//    float32 ftTempStrtPwrLimNtc1;  ///<temperature when NTC1 start reduce power
//    float32 ftTempStrtPwrLimNtc2;  ///<temperature when NTC2 start reduce power
//    float32 ftTempStrtPwrLimNtc3;  ///<temperature when NTC3 start reduce power
//    float32 ftTempStrtPwrLimNtc4;  ///<temperature when NTC4 start reduce power
//
//    int16  siTempChipMax;    // Temperature Maximum
//    int16  siTempNtcDletaMax;     // Temperature Maximum
//    int16  siTempMin;    // Temperature Minimum
//
//    int16  siTempDeltaNtcOTPrt;   ///<radiator NTC over temperature protect delta value
//    int16  siTempChipOTPrt;       ///<chips(DSP/ARM) over temperature protect value
//    int16  siTempUTPrt;           ///under temperature protect value
//
//    EN_LOW_TEMP_STS enLowTempSts;    // Low Temperature Statu
//    ST_TEMP_MEM stMemTemp;    // Member temperature
//}ST_TEMP_PARAM;

//=====================================================
//    Variable Declaration
//=====================================================
/* Power limitation calculation typedef */
//extern ST_POW_LMT stPowLmt;
/* Temperature Parameter Declaration */
//extern int16 siAirTempAdTbl[AIR_Temp_TBL_CNT];
//extern ST_TEMP_PARAM stTempParam;

//=====================================================
//    Function Declaration
//=====================================================
/* GPIO_Xbar function Declaration */
//extern void vGpioInit(void);
//extern void vXBarInit(void);
/* ADC_CMPSS function Declaration */
//extern void vAdcInit(void);
//extern void vDacInit(void);
//extern void vCmpssInit(void);
/* PWM function Declaration */
//extern void vEPwmInit(void);
/* CAP function Declaration */
//extern void vECapInit(void);
/* APP Parameter Initialization Declaration */
//extern void vAppParamInit(void);
//extern void vI2CInit(void);
/* Loop target calculation Declaration */
//extern void vBusVoltTgtCal(void);
/* Temperature process Declaration */
//extern void vTempPowLmt(void);
//extern void vLowTempStart(void);
//extern float32 ftTempTblLU(int16 siTempAD, int16 *sipTable, Uint16 uiTblCnt, int16 siTempBias);
//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================


//=====================================================
//    Variable Declaration
//=====================================================

//=====================================================
//    Function Declaration
//=====================================================

#endif    // INCLUDE_USER_INC_APP_INCLUDES_H_
//===========================================================================
// End of file.
//===========================================================================
