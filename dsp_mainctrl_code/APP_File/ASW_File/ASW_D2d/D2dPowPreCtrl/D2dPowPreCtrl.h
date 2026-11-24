//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dPowPreCtrl.h
 * @brief
 * The header file of D2d power pre-control is designed to realize preparation for loop control.
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
#ifndef D2DPOWPRECTRL_H_
#define D2DPOWPRECTRL_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "D2dPowPreCtrlExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "D2dAdcExt.h"
#include "D2dStMacExt.h"
#include "PerphCtrlExt.h"
#include "PowLimExt.h"
#include "OnOffGridSwtExt.h"
#include "PfcPowCtrlExt.h"
#include "PerdTskExt.h"
#include "PfcDataCalcExt.h"
//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define VOLT_BATT_BURST_DELTA_MAX               20.0f                           ///< Battery max burst voltage delta
#define VOLT_BUS_D2D_BURST_MAX                  VOLT_BUS_BURST_MAX              ///< Bus max burst voltage

#ifndef _SIMULATION_NO_DSP_
#define VOLT_BATT_PARL_STEP                     0.5f                            ///< Parallel battery Voltage Reference Step,0.25f
#define VOLT_BUS_D2D_SLOW_STEP                  0.25f                           ///< Bus voltage Reference Slow Step;0.25f
#define VOLT_BUS_D2D_FAST_STEP                  5.0f                            ///< Bus voltage Reference Fast Step;5.0f
#define STEP_D2D_OL                             0.00025f                        ///< D2D Open Loop Reference Step;0.00025f
#define STEP_POW_CELL_PWM_DUTY                  0.01f                           ///< Power Cell D2d PWM duty Reference Step;0.01f
#define DURN_BUS_VOLT_D2D_OK                    200U                            ///< Bus voltage OK duration;200ms
#else
#define VOLT_BATT_PARL_STEP                     2.5f                            ///< Parallel battery Voltage Reference Step,2.5f in simulink
#define VOLT_BUS_D2D_SLOW_STEP                  5.0f                           ///< Bus voltage Reference Slow Step;0.25f
#define VOLT_BUS_D2D_FAST_STEP                  5.0f                            ///< Bus voltage Reference Fast Step;5.0f
#define STEP_D2D_OL                             0.0025f                         ///< D2D Open Loop Reference Step;0.0025f in simulink
#define DURN_BUS_VOLT_D2D_OK                    20U                             ///< Bus voltage OK duration;20ms in simulink
#define STEP_POW_CELL_PWM_DUTY                  0.01f                           ///< Power Cell D2d PWM duty Reference Step;0.01f
#endif
#define VOLT_BATT_SERIES_STEP                   (2.0f * VOLT_BATT_PARL_STEP)    ///< Series battery Voltage Reference Step
#define CURR_BATT_CHRG_REF_MIN                  CURR_BATT_TGT_MIN               ///< Output Current Reference Min

#define VOLT_BUS_D2D_OK_DELTA                   10.0f                           ///< Bus voltage OK delta to target
#define LIM_POW_CELL_PWM_DUTY                   1.0f                            ///< Cell PWM duty target

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	ST_D2D_POW_PRE_CTRL stPrmExt;                                               ///< Parameter to extern

    Uint16  uiCntrBusVoltOk;                                                    ///< Counter of bus voltage ramp OK
  	Uint16  uiFlgFrqJitDir;                                                     ///< Direction of frequency jitter

    float32 ftVoltBattBurstMax;                                                 ///< Max burst battery voltage
    float32 ftVoltBattBurstDelta;                                               ///< Delta burst battery voltage

    float32 ftVoltBattChrgStep;                                                 ///< Battery voltage loop step value
    float32 ftCurrBattChrgStep;                                                 ///< Battery current loop step value
    float32 ftVoltBusStep;                                                      ///< Bus voltage step value
    float32 ftOutpOLStep;                                                       ///< Open-loop output(Ds1) step value
	float32 ftDp3OLStep;                                                        ///< Open-loop Dp3 step value
	float32 ftPwmDutyStep;                                                      ///< PWM Duty step value
	float32 ftPwmDutyTarget;                                                    ///< PWM Duty target value
    float32 ftGainFrq;                                                          ///< Gain of frequency
    float32 ftGainFrqMax;                                                       ///< Max Gain of frequency
    float32 ftGainFrqMin;                                                       ///< Min Gain of frequency
    float32 ftGainFrqStep;                                                      ///< Step Gain of frequency
}ST_D2D_POW_PRE_CTRL_LOC;                                                       ///< Definition of module D2dPowPreCtrl local Struct

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_D2dPowPreCtrl_PrmUpd_Init(void);
static void v_D2dPowPreCtrl_PrmUpd_1ms(void);

static void v_D2dPowPreCtrl_RefRamp_Init(void);
static void v_D2dPowPreCtrl_RefRamp_1ms(void);
static void v_D2dPowPreCtrl_RefRamp_Chrg(void);
static void v_D2dPowPreCtrl_RefRamp_Bidir(void);
static void v_D2dPowPreCtrl_RefRamp_OL(void);

#if(3U == GRID_PHASE_NUMBER)
static void v_D2dPowPreCtrl_FrqJit_Init(void);
static void v_D2dPowPreCtrl_FrqJit_1ms(void);
#endif

#endif /* D2DPOWPRECTRL_H_*/
//==============================================================================================
// End of file.
//==============================================================================================
