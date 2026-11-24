//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcPowPreCtrl.h
* TITLE         : Header file of PFC power pre-control
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

/*
************************************************************************************************
* Module        : PfcPowPreCtrl
* 1st Unit      : PfcPowPreCtrl_RefRamp
*
* Module Task   : v_PfcPowPreCtrl_Init()
*                 v_PfcPowPreCtrl_1ms()
*
* 1st Unit Task : v_PfcPowPreCtrl_RefRamp_Init()
*                 v_PfcPowPreCtrl_RefRamp_1ms()
*
************************************************************************************************
*/
#ifndef PFCPOWPRECTRL_H_
#define PFCPOWPRECTRL_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcPowPreCtrlExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "PowLimExt.h"
#include "PfcDataCalcExt.h"
#include "PfcGridCtrl.h"
#include "PfcStMacExt.h"
#include "PfcPowCtrlExt.h"
#include "PfcAdcExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define PFC_VOLT_BUS_1MS_STEP          0.1f                              ///< Bus voltage Reference 1ms Step
#if(1U == GRID_PHASE_NUMBER)
#define PFC_DUTY_AMP_STEP              (1.0f/500.0f)                     ///< Duty amplitude 1ms Step; 500ms to 1.0
#else
#define PFC_DUTY_AMP_STEP              0.1f                              ///< Duty amplitude 1ms Step
#endif
#define PFC_VOLT_AC_RMS_POW_CAL_MIN    5.0f                              ///< PFC power calculation voltage RMS Min
#define PFC_RAMP_CTRL_CYC              0.001f                            ///< Ramp control cycle: 1ms
#define PFC_VOLT_AC_AMP_1MS_STEP       (RATED_AC_VOLT_AMP/1.0f)          ///< AC voltage Reference 1ms Step; 1ms to rated voltage

#if(1U == GRID_PHASE_NUMBER)
#define PFC_ACTV_POW_COMP              -30.0f                            ///< Active power compensation for AuxPower
#elif(2U == GRID_PHASE_NUMBER)
#define PFC_ACTV_POW_COMP              0.0f                              ///< Active power compensation for AuxPower
#elif(3U == GRID_PHASE_NUMBER)
#define PFC_ACTV_POW_COMP              0.0f                              ///< Active power compensation for AuxPower
#endif

#define AC_INPUT_CAP_COEFF             (PI_2_CONST*PFC_INPUT_X_CAP)      ///< AC input X-capacitor coefficient

/* Power compensation Macro Definition */
#define KP_POW_COMP                    0.2f                              ///< Kp of active power compensation
#define KI_POW_COMP                    0.05f                             ///< Ki of active power compensation accrding to current
#define MAX_POW_COMP                   (0.015f * RATED_POW)              ///< Max active power limitation of PI output; 1.5% rated power
#define MIN_POW_COMP                   (-MAX_POW_COMP)                   ///< Min active power limitation of PI output

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    float32 ftPa;        ///< Phase A power
    float32 ftPb;        ///< Phase B power
    float32 ftPc;        ///< Phase C power
}ST_BATT_CURR_LIM;

typedef struct
{
	ST_PFC_POW_PRE_CTRL stPrmExt;    ///< Parameter to extern

	ST_BATT_CURR_LIM   stCurrBattChrgLim;    ///< Charge power limitation according to battery current request
	ST_BATT_CURR_LIM   stCurrBattDchaLim;    ///< Discharge power limitation according to battery current request
	ST_PI_PRM          stPaCompPI;           ///< Pa compensation PI
    ST_PI_PRM          stQaCompPI;           ///< Qa compensation PI

	float32 ftVoltRms;            ///< Voltage RMS
	float32 ftCoeffVoltRecpr;     ///< Voltage reciprocal coefficient
	float32 ftPaRef;              ///< Phase A active power reference
	float32 ftPbRef;              ///< Phase B active power reference
	float32 ftPcRef;              ///< Phase C active power reference
	float32 ftQaRef;              ///< Phase A reactive power reference
	float32 ftQbRef;              ///< Phase B reactive power reference
	float32 ftQcRef;              ///< Phase C reactive power reference
    float32 ftVoltBusStep;        ///< Bus voltage step
    float32 ftVoltAcAmpStep;      ///< AC voltage amplitude step
    float32 ftTi1stOrdLpfResp;    ///< 1st order LPF response time
    float32 ftTc1stOrdLpf;        ///< 1st order LPF time constant
    float32 ftCoeff1stOrdLpf;     ///< 1st order LPF coefficient
}ST_PFC_POW_PRE_CTRL_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PfcPowPreCtrl_PrmUpd_Init(void);
static void v_PfcPowPreCtrl_PrmUpd_10ms(void);

static void v_PfcPowPreCtrl_RefRamp_Init(void);
static void v_PfcPowPreCtrl_RefRamp_1ms(void);

static void v_PfcPowPreCtrl_XCapComp(void);
static void v_PfcPowPreCtrl_RefRamp_Chrg(void);
static void v_PfcPowPreCtrl_RefRamp_Bidir(void);
static void v_PfcPowPreCtrl_CurrBattLim(void);
static void v_PfcPowPreCtrl_RefRamp_OffGrid(void);
static void v_PfcPowPreCtrl_RefRamp_OL(void);
#if(1U == GRID_PHASE_NUMBER)
static void v_PfcPowPreCtrl_PowComp(float32 *ftPRef, float32 *ftQRef, float32 ftP,  float32 ftQ, ST_PI_PRM *stPCompPI, ST_PI_PRM *stQCompPI);
#endif
static void v_PfcPowPreCtrl_CurrRefCalc(float32 ftVacRms, float32 ftPRef, float32 ftQRef, float32 *ftIActvAmpRef, float32 *ftIReactvAmpRef);

#endif /* PFCPOWPRECTRL_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
