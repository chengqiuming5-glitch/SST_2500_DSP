//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcGridCtrl.h
 * @brief
 * The header file of PFC on&off grid control.
 *
 * Module      :                           \n
 * PfcGridCtrl
 *
 * Unit        :                           \n
 * PfcGridCtrl_Vrt                         \n
 * PfcGridCtrl_Dstbc                       \n
 * PfcGridCtrl_Det                         \n
 * PfcGridCtrl_ActvPower                   \n
 * PfcGridCtrl_ReactvPower
 *
 * Module Task :                           \n
 * v_PfcGridCtrl_Init()                    \n
 * v_PfcGridCtrl_1ms()                     \n
 * v_PfcGridCtrl_10ms()
 *
 * Unit Task   :                           \n
 * v_PfcGridCtrl_Vrt_Init()                \n
 * v_PfcGridCtrl_Vrt_1ms()                 \n
 * v_PfcGridCtrl_Dstbc_Init()              \n
 * v_PfcGridCtrl_Det_Init()                \n
 * v_PfcGridCtrl_Det_10ms()                \n
 * v_PfcGridCtrl_Actv_Init()               \n
 * v_PfcGridCtrl_Actv_10ms()               \n
 * v_PfcGridCtrl_Reactv_Init()             \n
 * v_PfcGridCtrl_Reactv_10ms()
 *
 * Sub Unit Task   :                       \n
 * v_PfcGridCtrl_Vrt_Lvrt_1ms()            \n
 * v_PfcGridCtrl_Vrt_Hvrt_1ms()            \n
 * v_PfcGridCtrl_Vrt_CurrLim_1ms()         \n
 * v_PfcGridCtrl_Vrt_FrqChkEn_1ms()        \n
 * v_PfcGridCtrl_Vrt_CurrLim_1ms()         \n
 *
 * v_PfcGridCtrl_Dstbc_10ms()
 * v_PfcGridCtrl_Dstbc_AI_10ms()           \n
 * v_PfcGridCtrl_Dstbc_CurrDc_10ms()       \n
 * v_PfcGridCtrl_Dstbc_VoltDc_10ms()       \n

 * v_PfcGridCtrl_Det_Volt_10ms()           \n
 * v_PfcGridCtrl_Det_Frq_10ms()            \n
 * v_PfcGridCtrl_Det_V10min_10ms()         \n
 *
 * v_PfcGridCtrl_Actv_HF_10ms()            \n
 * v_PfcGridCtrl_Actv_LF_10ms()            \n
 * v_PfcGridCtrl_Actv_PU_10ms()            \n
 * v_PfcGridCtrl_Actv_Cnct_10ms()          \n
 * v_PfcGridCtrl_Actv_ValSet_10ms()        \n
 * v_PfcGridCtrl_Actv_Ratio_10ms()         \n
 *
 * v_PfcGridCtrl_Reactv_PF_10ms()          \n
 * v_PfcGridCtrl_Reactv_QT_10ms()          \n
 * v_PfcGridCtrl_Reactv_QU_10ms()          \n
 * v_PfcGridCtrl_Reactv_QP_10ms()          \n
 * v_PfcGridCtrl_Reactv_Reset_10ms()       \n
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2023/12/08
 * @version
 * V1.0
 * @copyright
 * (c) Copyright 2000-2050, Wanbang New Energy Investment Co.,LTD..    \n
 *                            All Rights Reserved
 * @attention
 * MCU           : TMS320F2837xD           \n
 * Environment   : CCSv10.4.0
 * @note
 * <table>
 * <tr><th>Date        <th>Version         <th>Author       <th>Description
 * <tr><td>2023/12/08  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef PFCGRIDCTRL_H_
#define PFCGRIDCTRL_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcGridCtrlExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "PowLimExt.h"
#include "PfcDataCalcExt.h"
#include "PfcDiagExt.h"
#include "PfcStMacExt.h"
#include "PfcPowCtrlExt.h"
#include "GridStdData.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define PWR_RATE_10MS_COEFF          600000.0f                     ///< 10ms power rate coefficient; 100*60*1000/10
#define PWR_RATE_10MS_COEFF_RECPR    (1.0f/PWR_RATE_10MS_COEFF)    ///< Reciprocal of PWR_RATE_10MS_COEFF

#define PROTN_HYS_ENA              0U                              ///< Voltage protection compensation
#define VOLT_PROTN_TIME_COMP       4UL                             ///< Voltage protection compensation
#define FRQ_PROTN_TIME_COMP        6UL                             ///< Frequency protection compensation
#define VOLT_PROTN_TIME_COMP_EQ    1UL                             ///< Voltage protection compensation(real time equal set time)
#define FRQ_PROTN_TIME_COMP_EQ     5UL                             ///< Frequency protection compensation(real time equal set time)
#define VOLT_PROTN_HYS             0.5f                            ///< Voltage protection hysteresis
#define FRQ_PROTN_HYS              0.005f                          ///< Frequency protection hysteresis

#define AI_ACTV_CURR_DSTBC_MIN     (0.6f*RATED_AC_CURR_RMS)        ///< AI min Id-disturbance
#define AI_FRQ_MAX                 ((float32)GRID_FRQ_MAX-0.2f)    ///< AI frequency disturbance up-limit
#define AI_FRQ_MIN                 ((float32)GRID_FRQ_MIN+0.2f)    ///< AI frequency disturbance down-limit
#define AI_IQ_DSTBC_COEFF_LIM      0.2f                            ///< AI Q-axis current disturbance limitation coefficient
#define AI_ID_DSTBC_COEFF          0.015f                          ///< AI D-axis current disturbance coefficient
#define AI_DSTBC_PERD              7U                              ///< AI disturbance period/10ms
#define AI_DSTBC_FRQ_ERR           0.03f                           ///< AI disturbance frequency error
#define AI_IQ_DSTBC_COEFF_FAST     0.05f                           ///< AI Q-axis current disturbance coefficient(Fast 500ms);0.05*3+0.015=0.165
#define AI_IQ_DSTBC_COEFF_SLOW     0.02f                           ///< AI Q-axis current disturbance coefficient(Slow 2000ms);0.02*9+0.015=0.195
#define AI_DSTBC_NUM_FAST          4U                              ///< AI disturbance number(Fast 500ms)
#define AI_DSTBC_NUM_SLOW          10U                             ///< AI disturbance number(Slow 2000ms)
#define AI_FRQ_INC_SUM             0.5f                            ///< AI frequency increase summary
#define AI_FRQ_DEC                 0.25f                           ///< AI frequency decrease

#define ST_INIT                    0U                              ///< State machine initial
#define ST_DATAREC                 1U                              ///< State machine data record
#define ST_ADJ                     2U                              ///< State machine power adjust
#define ST_END                     3U                              ///< State machine end

#define POW_RAT_ERR_SAMPLE         0.02f                           ///< Sample power ratio error

#define VRT_ACTV_POW_PRIO          0U                              ///< VRT active power priority
#define VRT_REACTV_POW_PRIO        1U                              ///< VRT reactive power priority
#define FLT_RCV_PRIO_HIGH          0U                              ///< 0-priority low;1-priority high
#define VRT_ACTV_CURR_RCV_1MS_STEP     (1.414f*RATED_AC_CURR_RMS/50.0f)    ///< VRT active current recovery 1ms step:50ms from 0 to rated

#define DET_TI_OV                  0U        ///< Detection time over set time
#define DET_TI_UN                  1U        ///< Detection time under set time
#define DET_TI_EQ                  2U        ///< Detection time equal set time

#define DET_SEL_LN                 0U        ///< Detection mode select-phase voltage protect(L-N)
#define DET_SEL_LL                 1U        ///< Detection mode select-line voltage protect(L-L)

#define SELF_TEST_VOLT_STEP        0.1f                         ///< Self-test function voltage ramp step: 0.1V/10ms
#define SELF_TEST_FRQ_STEP         0.0002f                      ///< Self-test function frequency ramp step: 0.0002Hz/10ms
#define SELF_TEST_VOLT_LMT         (0.05f*RATED_AC_VOLT_RMS)    ///< Self-test function voltage ramp limit relative to real voltage
#define SELF_TEST_FRQ_LMT          0.05f                        ///< Self-test function frequency ramp limit relative to real frequency

#if(1U == GRID_PHASE_NUMBER)
#define HYS_IDC_CTRL               0.0f                  ///< Idc control hysteresis
#elif(2U == GRID_PHASE_NUMBER)
#define HYS_IDC_CTRL               200.0f                ///< Idc control hysteresis
#else
#define HYS_IDC_CTRL               40.0f                 ///< Idc control hysteresis
#endif
#define DLY_IDC_PRT                500U                  ///< Idc protect delay

#define VOLT10MIN_ARY_SIZE         200U                                ///< 10min over-voltage protect array length
#define VOLT10MIN_ARY_SIZE_RECI    1.0f/(float32)VOLT10MIN_ARY_SIZE    ///< 10min over-voltage protect array length reciprocal
#define FLOAT_ERROR                0.005f                              ///< Float data judgment accuracy
#define VOLT_FLOAT_ERROR           0.2f                                ///< Voltage float data judgment accuracy
#define PFMAX                      1.0f                                ///< Power factor maximum

#define FRQ_CURVE_A                0U       ///< Frequency response curve A
#define FRQ_CURVE_B                1U       ///< Frequency response curve B
#define FRQ_CURVE_ONE_SLOPE        0U       ///< Frequency response curve- Single slope
#define FRQ_CURVE_TWO_SLOPE        1U       ///< Frequency response curve- Double slope

/* Reactive power control mode Macro Definition */
#define PF_MODE                    REACTV_POW_PF_MODE         /// Reactive power mode PF
#define QU_MODE                    REACTV_POW_QU_MODE         /// Reactive power mode QU
#define QP_MODE                    REACTV_POW_QP_MODE         /// Reactive power mode QP
#define QT_MODE                    REACTV_POW_QT_MODE         /// Reactive power mode QT
#define OFF_MODE                   REACTV_POW_DISABLE_MODE    /// Reactive power mode OFF

/* QU Macro Definition */
#define QU_NO_LIM                  0U       ///< QU no limit in mode
#define QU_IN_OUT_LIM              1U       ///< QU Pin/Pout mode
#define QU_PF_LIM                  2U       ///< QU PF limit mode

#define QU_CURVE_A                 0U       ///< QU mode curve A
#define QU_CURVE_B                 1U       ///< QU mode curve B

/* QP Macro Definition */
#define QP_CURVE_A                 0U       ///< QP mode curve A
#define QP_CURVE_B                 1U       ///< QP mode curve B

#define QP_NO_LIM                  0U       ///< QP no limit in mode
#define QP_IN_OUT_LIM              1U       ///< QP Uin/Uout mode

#if(1U == GRID_PHASE_NUMBER)
#define VDC_CTRL_DLY               1U       ///< Voltage DC component control delay
#define VDC_CTRL_INP_LMT           0.0f     ///< Voltage DC component control input limit
#else
#define VDC_CTRL_DLY               100U     ///< Voltage DC component control delay
#define VDC_CTRL_INP_LMT           60.0f    ///< Voltage DC component control input limit
#endif

#define RAMP_10MS_CTRL_CYC         0.01f          ///< 10ms control cycle

/* PU Macro Definition */
#define PU_CURVE_A                 0U             ///< PU mode curve A- normal mode
#define PU_CURVE_B                 1U             ///< PU mode curve B- decrease from current power
#define PU_TI_COEFF                0.01f          ///< PU time coefficient
#define TI_CONST_RECP_90PERC       (1.0f/2.3f)    ///< Reciprocal of response to 90% time constant
#define TI_CONST_RECP_95PERC       (1.0f/3.0f)    ///< Reciprocal of response to 95% time constant

#define GRID_FLT_RCV_TI            5U                           ///< Grid fault recovery time/s
#define GRID_FLT_RCV_TI_1MS_PRD    (GRID_FLT_RCV_TI * 1000U)    ///< Grid fault recovery time/1ms
#define GRID_FLT_RCV_TI_10MS_PRD   (GRID_FLT_RCV_TI * 100U)     ///< Grid fault recovery time/10ms

#define NARROW_FRQ_PRT             0U                  ///< Narrow frequency protect, with 1st OF/UF
#define BROAD_FRQ_PRT              1U                  ///< Broad frequency protect, without 1st OF/UF
#define LOC_FRQ_PRT_CMD_NARROW     1U                  ///< Local frequency protect command - narrow frequency
#define LOC_FRQ_PRT_CMD_BROAD      0U                  ///< Local frequency protect command - broad frequency

#define RAT_DCHG_PWR_LIM           RAT_AC_CURR_LIM     ///< Discharge mode AC power ratio limit
#define RAT_CHRG_PWR_LIM           (1.0f/EFF_PL_CHRG)  ///< Charge mode AC power ratio limit

#define TI_ROCOF_PRT_50549         0.52f               ///< EN50549 RoCoF protection time: 0.52s
#define TI_ROCOF_PRT_POL           0.42f               ///< Poland RoCoF protection time: 0.42s

#define PWR_RESP_SLOP_BASE_P_MAX   0U                  ///< Power response slope based on Pmax
#define PWR_RESP_SLOP_BASE_P_CURR  1U                  ///< Power response slope based on Pcurrent
//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16   uiModReactvPwr;       ///< Reactive power mode
    float32  ftFrqRtd;             ///< Grid rated frequency
    float32  ftVoltRtd;            ///< Grid rated voltage
    int16    siPwrRtdReactv;       ///< Rated reactive power
    int16    siPwrRtdActv;         ///< Rated active power
    float32  ftPwrRtdRecpr;        ///< Reciprocal of rated active power

    int16    siVaDcCpt;            ///< Phase A voltage DC component, 1=1mV
    int16    siVbDcCpt;            ///< Phase B voltage DC component, 1=1mV
    int16    siVcDcCpt;            ///< Phase C voltage DC component, 1=1mV
    int16    siIaDcCpt;            ///< Phase A current DC component, 1=1mA
    int16    siIbDcCpt;            ///< Phase B current DC component, 1=1mA
    int16    siIcDcCpt;            ///< Phase C current DC component, 1=1mA

    float32  ftRatActvPwr;         ///< Active power ratio
    float32  ftActvPwrCmd;         ///< Active power command
    float32  ftRatActvPwrCmd;      ///< Active power command ratio
    float32  ftRatGridVolt;        ///< Grid voltage ratio
    float32  ftFrqEcapAvg;         ///< Average frequency from ECAP module, 160ms average, 1= 1Hz
    float32  ftFrqEcap;            ///< Frequency from ECAP module
    float32  ftPwrReactvMax;       ///< Max reactive power

    float32  ftVoltMax;            ///< Maximum grid voltage, 1=1V
    float32  ftVoltMin;            ///< Minimum grid voltage, 1=1V
    float32  ftVoltMaxPrt;         ///< Maximum grid voltage, 1=1V
    float32  ftVoltMinPrt;         ///< Minimum grid voltage, 1=1V
    float32  ftFrqMax;             ///< Maximum grid frequency, 1=1Hz
    float32  ftFrqMin;             ///< Minimum grid frequency, 1=1Hz

    float32  ftRatVoltVrtMax;      ///< Voltage Ride Through use maximum grid voltage ratio
    float32  ftRatVoltVrtMin;      ///< VRT use minimum grid voltage ratio
    float32  ftRatVdVrt;           ///< VRT use D-axis grid voltage ratio

    float32 ftIdRef;               ///< D-axis current reference
    float32 ftIdRef20msAvg;        ///< 20ms average of D-axis current reference
    float32 ftIdLim;               ///< D-axis current limit
    float32 ftIdLimRecpr;          ///< Reciprocal of D-axis current limit
    float32 ftVoltRtdRecpr;        ///< Reciprocal of rated grid voltage
}ST_PFC_GRIDCTRL_INP;

typedef struct
{
    ST_PFC_GRIDCTRL_ACTVPOWER_OUTP  stActvExt;
    Uint16  uiFlgFltRcv;            ///< Fault recovery power slow starting flag
    Uint16  uiFlgHFCtrlRst;         ///< HF control reset flag
    Uint16  uiFlgLFCtrlRst;         ///< LF control reset flag
    Uint16  uiFlgPUCtrlRst;         ///< PU control reset flag

    Uint16  uiStPUCtrl;             ///< PU control state for Curve B

    float32 ftRatePwrUpRampHF;      ///< Up rate of HF power ramp; %Pn/min
    float32 ftRatePwrDwnRampHF;     ///< Down rate of HF power ramp; %Pn/min
    float32 ftRatePwrUpRampLF;      ///< Up rate of LF power ramp; %Pn/min
    float32 ftRatePwrDwnRampLF;     ///< Down rate of LF power ramp; %Pn/min
    float32 ftRatePwrRampGridCnct;  ///< Grid connect power ramp rate; %Pn/min

    Uint16  uiStHFCtrl;            ///< HF control state
    Uint16  uiCntrHFHappen;        ///< HF happen counter
    Uint32  ulCntrHFStSwt;         ///< HF state exit counter
    float32 ftRatPwrRecHFEntr;     ///< Power ratio record when HF enter
    float32 ftFrqHFUsed;           ///< HF used frequency based on curve A or B

    Uint16  uiStLFCtrl;            ///< LF control state
    Uint16  uiCntrLFHappen;        ///< LF happen counter
    Uint32  ulCntrLFStSwt;         ///< LF state switch counter
    float32 ftRatPwrRecLFEntr;     ///< Power ratio record when LF enter
    float32 ftFrqLFUsed;           ///< LF used frequency based on curve A or B

    float32 ftRatVoltHystPU;       ///< PU voltage hysteresis ratio
    float32 ftStepPwrPU;           ///< PU power step
    float32 ftTiRcvPU;             ///< PU recovery time

    Uint32  ulCntrOnGridStrt;      ///< On-Grid start counter
    Uint32  ulTiGridCnct;          ///< Grid connect time
    Uint16  uiCntrCnctFltClr;      ///< Connect fault clear counter
    Uint16  uiCntrGridCnctOk;      ///< Connect OK counter
    Uint16  uiCntrGridCnctNo;      ///< Connect NO counter

    float32 ftVoltGridCnctMax;     ///< Connect voltage max-limit
    float32 ftVoltGridCnctMin;     ///< Connect voltage min-limit
    float32 ftFrqGridCnctMax;      ///< Connect frequency max-limit
    float32 ftFrqGridCnctMin;      ///< Connect frequency min-limit

    float32 ftRatPwrLimHF;         ///< HF power limitation ratio
    float32 ftRatPwrHF;            ///< HF power ratio
    float32 ftRatPwrLimLF;         ///< LF power limitation ratio
    float32 ftRatPwrLF;            ///< LF power ratio
    float32 ftRatPwrLimPU;         ///< PU power limitation ratio
    float32 ftRatPwrPU;            ///< PU power ratio
    float32 ftRatAcPwrLim;         ///< AC Power limitation ratio

    float32 ftSlopCurveHF1;        ///<High frequency power response curve slope1
    float32 ftSlopCurveHF2;        ///<High frequency power response curve slope2
    float32 ftSlopCurveLF1;        ///<Low frequency power response curve slope1
    float32 ftSlopCurveLF2;        ///<Low frequency power response curve slope2
	float32 ftCoeffHF1stLpf;       ///< High frequency power response 1st order LPF coefficient
    float32 ftCoeffLF1stLpf;       ///< Low frequency power response 1st order LPF coefficient
    float32 ftRatPwrMidHF;         ///< HF F-mid point power ratio
    float32 ftRatPwrMidLF;         ///< LF F-mid point power ratio
    float32 ftRatPwrAddHF;         ///< HF additional power ratio for Austria
    float32 ftRatPwrAddLF;         ///< LF additional power ratio for Austria

    float32 ftSlopPuCurve;         ///< PU power response curve slope for Austria
    float32 ftRatPwrRecPUEntr;     ///< Power ratio record when PU enter

}ST_PFC_GRIDCTRL_ACTVPOWER_LOC;

typedef struct
{
    ST_PFC_GRIDCTRL_REACTVPOWER_OUTP  stReactvExt;

    float32  ftPfOutp;             ///< PF Output
    float32  ftQuOutp;             ///< QU Output
    float32  ftQpOutp;             ///< QP Output
    float32  ftQtOutp;             ///< QT Output
    float32  ftQpOutpTmp;          ///< QP Output temporary value

    float32  ftQP_X1;              ///< QP X-axis X1
    float32  ftQP_X2;              ///< QP X-axis X2
    float32  ftQP_XMid;            ///< QP X-axis X-Mid,PF=1
    float32  ftQP_X3;              ///< QP X-axis X3
    float32  ftQP_X4;              ///< QP X-axis X4
    float32  ftQP_X5;              ///< QP X-axis X5
    float32  ftQP_X6;              ///< QP X-axis X6

    float32  ftQP_Y1;              ///< QP Y-axis Y1
    float32  ftQP_Y2;              ///< QP Y-axis Y2
    float32  ftQP_Y3;              ///< QP Y-axis Y3
    float32  ftQP_Y4;              ///< QP Y-axis Y4
    float32  ftQP_Y5;              ///< QP Y-axis Y5
    float32  ftQP_Y6;              ///< QP Y-axis Y6

    float32  ftRatioK1;            ///< QP curve K1
    float32  ftRatioK2;            ///< QP curve K2
    float32  ftRatioK3;            ///< QP curve K3
    float32  ftRatioK4;            ///< QP curve K4
    float32  ftRatioK5;            ///< QP curve K5

    float32  ftQU_X1;              ///< QU X-axis X1
    float32  ftQU_X2;              ///< QU X-axis X2
    float32  ftQU_X3;              ///< QU X-axis X3
    float32  ftQU_X4;              ///< QU X-axis X4

    float32  ftQU_Y1;              ///< QU X-axis Y1
    float32  ftQU_Y2;              ///< QU X-axis Y2
    float32  ftQU_Y3;              ///< QU X-axis Y3
    float32  ftQU_Y4;              ///< QU X-axis Y4

    float32  ftRatQuK1;            ///< QU curve K1
    float32  ftRatQuK2;            ///< QU curve K2
    float32  ftCoeffVrefLpf;       ///< Vref first order LPF coefficient
    float32  ftRatVref;            ///< Vref ratio
}ST_PFC_GRIDCTRL_REACTVPOWER_LOC;

typedef struct
{
    UN_VOLTPROT_OUT unVoltProtExt;
    UN_FRQPROT_OUT  unFrqProtExt;

    ST_SELF_TEST_OUTP st59S1Ext;   ///< Grid over voltage protection-S1
    ST_SELF_TEST_OUTP st59S2Ext;   ///< Grid over voltage protection-S2
    ST_SELF_TEST_OUTP st27S1Ext;   ///< Grid under voltage protection-S1
    ST_SELF_TEST_OUTP st27S2Ext;   ///< Grid under voltage protection-S2
    ST_SELF_TEST_OUTP st81OvS1Ext; ///< Grid over frequency protection-S1
    ST_SELF_TEST_OUTP st81OvS2Ext; ///< Grid over frequency protection-S2
    ST_SELF_TEST_OUTP st81UnS1Ext; ///< Grid under frequency protection-S1
    ST_SELF_TEST_OUTP st81UnS2Ext; ///< Grid under frequency protection-S2

    Uint16  uiFltRoCoF;            ///< RoCoF fault protection
    Uint16  uiCntrRoCoF;           ///< RoCoF counter
    Uint16  uiFlgRoCoF;            ///< RoCoF flag
    Uint16  uiStsSelfTest;         ///< Self test status
    Uint16  uiFrqPrtMode;          ///< Frequency protection mode: 0-Narrow frequency protect; 1-Board frequency control
    Uint16  uiFltIdcOv;            ///< Idc over fault
    Uint16  uiIdc1000TimesOv1;     ///< Idc over value1 1000 times
    Uint16  uiIdc1000TimesOv2;     ///< Idc over value2 1000 times
    Uint16  uiCntrIdcPrtDly;       ///< Idc protect delay counter
    Uint16  uiCntrFltClc;          ///< Idc fault recovery counter
    Uint16  uiFlg10minArry;        ///< 10min grid voltage array is full
    Uint32  ulCntrIdcOv1;          ///< Idc over1 counter
    Uint32  ulCntrIdcOv2;          ///< Idc over2 counter
    Uint32  ulTiIdcOv1;            ///< Idc over1 protect time
    Uint32  ulTiIdcOv2;            ///< Idc over2 protect time
    float32 ftVoltAvg10minVal;     ///< 10min grid voltage value
    float32 ftTimProtRoCoF;        ///< RoCoF protect time
    float32 ftTiRoCoFPrtSet;       ///< RoCoF protection time set

    Uint16  uiClassVoltProt;       ///< Voltage protection class
    float32 ftVoltOVProtVal[3];    ///< Over Voltage protection value
    float32 ftVoltUVProtVal[3];    ///< Under Voltage protection value
    float32 ftVoltOVProtRcv;       ///< OV protection recovery value
    float32 ftVoltUVProtRcv;       ///< UV protection recovery value
    Uint32  ulTiOVProt[3];         ///< OV protection time
    Uint32  ulTiUVProt[3];         ///< UV protection time
    Uint32  ulCntrOV[3];           ///< OV protection counter
    Uint32  ulCntrUV[3];           ///< UV protection counter
    Uint16  uiCntrVoltRcv;         ///< Voltage protection recovery counter

    Uint16  uiClassFrqProt;        ///< Frequency protection class
    float32 ftFrqOFProtVal[3];     ///< Over Frequency protection value
    float32 ftFrqUFProtVal[3];     ///< Under Frequency protection value
    float32 ftFrqOFProtRcv;        ///< OF protection recovery value
    float32 ftFrqUFProtRcv;        ///< UF protection recovery value
    Uint32  ulTiOFProt[3];         ///< OF protection time
    Uint32  ulTiUFProt[3];         ///< UF protection time
    Uint32  ulCntrOF[3];           ///< OF protection counter
    Uint32  ulCntrUF[3];           ///< UF protection counter
    Uint16  uiCntrFrqRcv;          ///< Frequency protection recovery counter
    Uint16  ui3sCntr;              ///< 3s counter for 10min voltage calculation
    Uint16  uiIdxVolt10min;        ///< Index of voltage 10min array

    float32 ftValOver10min;        ///< On grid 10min over voltage protect value
    float32 ftValOver10minRcv;     ///< On grid 10min over voltage recovery value
}ST_PFC_GRIDCTRL_DET_LOC;

typedef struct
{
    float32 ftRatIq;               ///< VRT Iq ratio (to Imax)
    float32 ftRatId;               ///< VRT Id ratio (to Imax)
    float32 ftIdPosLim;            ///< VRT Id_p limit
    Uint32  ulCntrOT1;             ///< VRT over time counter1
    Uint32  ulCntrOT2;             ///< VRT over time counter2
    Uint32  ulCntrOT3;             ///< VRT over time counter3
    Uint16  uiCntrRcv;             ///< VRT recovery counter
    Uint16  uiFlgZeroPow;          ///< VRT zero power flag
    Uint16  uiIdxIdRecAry;         ///< VRT Id record array index
    Uint16  uiCntr2ms;             ///< VRT 2ms counter
    Uint16  uiCntr10ms;            ///< VRT 10ms counter
    Uint16  uiCntrKeep;            ///< VRT keep counter; min 20ms
    Uint16  uiCntrFltClc;          ///< VRT fault clear counter
    Uint16  uiFlgKeep;             ///< VRT keep counter up to 20ms flag

    Uint32  ulTiProt1;             ///< VRT protection time1
    Uint32  ulTiProt2;             ///< VRT protection time2
    Uint32  ulTiProt3;             ///< VRT protection time3
    float32 ftRatVoltRcv;          ///< VRT recovery voltage ratio
    float32 ftRatVoltRcvZeroPwr;   ///< VRT zero power recovery voltage
}ST_PFC_GRIDCTRL_VRT_SHARE;

typedef struct
{
    ST_PFC_GRIDCTRL_VRT_OUTP  stVrtExt;

    ST_PFC_GRIDCTRL_VRT_SHARE stHvrt;
    ST_PFC_GRIDCTRL_VRT_SHARE stLvrt;

    Uint16  uiCntrFrqFltNC;         ///< VRT frequency fault no check counter
    Uint16  uiFlgVrtEnd;            ///< VRT end flag

    float32 ftIdAvgRec;             ///< before VRT 20ms average of Id record
    float32 ftIdReqLim;             ///< Id request limitation
    float32 ftIdRamp;               ///< VRT end Id reference ramp
    float32 ftIdTmp;                ///< Id temporary
    float32 ftIqTmp;                ///< Iq temporary
}ST_PFC_GRIDCTRL_VRT_LOC;

typedef struct
{
    ST_PFC_GRIDCTRL_DSTBC_OUTP  stDstbcExt;
    ST_PI_PRM stIaDcPI;
    ST_PI_PRM stIbDcPI;
    ST_PI_PRM stIcDcPI;
    ST_PI_PRM stVaDcPI;
    ST_PI_PRM stVbDcPI;
    ST_PI_PRM stVcDcPI;

    float32 ftIqAiCompStep;         ///< Anti-Island Iq compensation step
    float32 ftIqAiLim;              ///< Anti-Island Iq limitation
    float32 ftFrqIncAi;             ///< Anti-Island frequency increase
    float32 ftFrqDecAi;             ///< Anti-Island frequency decrease
    float32 ftFrqErrAi;             ///< Anti-Island frequency error
    float32 ftReactvCompAi;         ///< Anti-Island reactive current compensation
    float32 ftFrqSumPosAi;          ///< Anti-Island positive disturb frequency sum
    float32 ftFrqSumNegAi;          ///< Anti-Island negative disturb frequency sum

    Uint16  uiNumAiJdg;             ///< Anti-Island judgment number
    Uint16  uiFlgAiJdg;             ///< Anti-Island judgment flag
    Uint16  uiCntrVoltDcDly;        ///< Voltage DC component control delay counter
    Uint16  uiIntlAiDstbc;          ///< Anti-Island disturbance interval
    Uint16  uiCntrAiFltRcv;         ///< Anti-Island fault recovery counter
    Uint16  uiFlgReactvNoise;       ///< Anti-Island disturb direction
    Uint16  uiCntrAiPos;            ///< Anti-Island positive disturb counter
    Uint16  uiCntrAiNeg;            ///< Anti-Island negative disturb counter
}ST_PFC_GRIDCTRL_DSTBC_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PfcGridCtrl_PrmUpd_Eep_PrtPrm(void);
static void v_PfcGridCtrl_InpPrm_Init(void);
static void v_PfcGridCtrl_Vrt_Init(void);
static void v_PfcGridCtrl_Vrt_1ms(void);
static void v_PfcGridCtrl_Vrt_Lvrt_1ms(void);
static void v_PfcGridCtrl_Vrt_Lvrt_Rcv_1ms(void);
static void v_PfcGridCtrl_Vrt_Lvrt_Resp_1ms(void);
static void v_PfcGridCtrl_Vrt_Lvrt_Entr_1ms(void);
static void v_PfcGridCtrl_Vrt_Lvrt_Clr_1ms(void);
static void v_PfcGridCtrl_Vrt_FrqChkEn_1ms(void);
static void v_PfcGridCtrl_Vrt_Hvrt_1ms(void);
static void v_PfcGridCtrl_Vrt_Hvrt_Rcv_1ms(void);
static void v_PfcGridCtrl_Vrt_Hvrt_Resp_1ms(void);
static void v_PfcGridCtrl_Vrt_Hvrt_Entr_1ms(void);
static void v_PfcGridCtrl_Vrt_Hvrt_Clr_1ms(void);
static void v_PfcGridCtrl_Vrt_CurrLim_1ms(void);

static void v_PfcGridCtrl_Dstbc_Init(void);
static void v_PfcGridCtrl_Dstbc_10ms(void);
static void v_PfcGridCtrl_Dstbc_AI_10ms(void);
static void v_PfcGridCtrl_Dstbc_AiIqComp(void);
static void v_PfcGridCtrl_Dstbc_AiFltRcv(void);
static void v_PfcGridCtrl_Dstbc_CurrDc_10ms(void);
static void v_PfcGridCtrl_Dstbc_VoltDc_10ms(void);

static void v_PfcGridCtrl_Det_Init(void);
static void v_PfcGridCtrl_Det_10ms(void);
static void v_PfcGridCtrl_Det_Volt_10ms(void);
static void v_PfcGridCtrl_Det_Volt_NoFlt(void);
static void v_PfcGridCtrl_Det_Volt_Rcv(void);
static void v_PfcGridCtrl_Det_Frq_10ms(void);
static void v_PfcGridCtrl_Det_Frq_NoFlt(void);
static void v_PfcGridCtrl_Det_Frq_Rcv(void);
static void v_PfcGridCtrl_Det_V10min_10ms(void);
static void v_PfcGridCtrl_Det_VTest_Init(void);
static void v_PfcGridCtrl_Det_FTest_Init(void);
static void v_PfcGridCtrl_Det_Test_10ms(void);
static void v_PfcGridCtrl_Det_Test_Init(void);
static void v_PfcGridCtrl_Det_Test_Volt(void);
static void v_PfcGridCtrl_Det_Test_Volt_OV(void);
static void v_PfcGridCtrl_Det_Test_Volt_UV(void);
static void v_PfcGridCtrl_Det_Test_Frq(void);
static void v_PfcGridCtrl_Det_Test_Frq_OF(void);
static void v_PfcGridCtrl_Det_Test_Frq_UF(void);
static void v_PfcGridCtrl_Det_Test_10Min(void);
static void v_PfcGridCtrl_Det_Test_End(void);
static void v_PfcGridCtrl_Det_IdcOv_10ms(void);
static void v_PfcGridCtrl_Det_RoCoF_10ms(void);

static void v_PfcGridCtrl_Actv_Init(void);
static void v_PfcGridCtrl_Actv_10ms(void);
static void v_PfcGridCtrl_Actv_Reset_10ms(void);
static void v_PfcGridCtrl_Actv_HF_10ms(void);
static void v_PfcGridCtrl_Actv_HF_PreProc(void);
static void v_PfcGridCtrl_Actv_HF_StInit(void);
static void v_PfcGridCtrl_Actv_HF_StRec(void);
static void v_PfcGridCtrl_Actv_HF_StAdj(void);
static void v_PfcGridCtrl_Actv_HF_StEnd(void);
static void v_PfcGridCtrl_Actv_HF_Ramp_10ms(void);
static void v_PfcGridCtrl_Actv_HF_Clr_10ms(void);

static void v_PfcGridCtrl_Actv_LF_10ms(void);
static void v_PfcGridCtrl_Actv_LF_PreProc(void);
static void v_PfcGridCtrl_Actv_LF_StInit(void);
static void v_PfcGridCtrl_Actv_LF_StRec(void);
static void v_PfcGridCtrl_Actv_LF_StAdj(void);
static void v_PfcGridCtrl_Actv_LF_StEnd(void);
static void v_PfcGridCtrl_Actv_LF_Ramp_10ms(void);
static void v_PfcGridCtrl_Actv_LF_Clr_10ms(void);
static void v_PfcGridCtrl_Actv_PF_PrmUpd(void);

static void v_PfcGridCtrl_Actv_PU_10ms(void);
static void v_PfcGridCtrl_Actv_PU_PrmUpd(void);
static void v_PfcGridCtrl_Actv_PU_Adj(void);
static void v_PfcGridCtrl_Actv_PU_Adj_Calc(float32 ftX1, float32 ftX2, float32 ftY1, float32 ftY2);
static void v_PfcGridCtrl_Actv_PU_StInit(void);
static void v_PfcGridCtrl_Actv_PU_StRec(void);
static void v_PfcGridCtrl_Actv_PU_StAdj(void);
static void v_PfcGridCtrl_Actv_PU_StEnd(void);

static void v_PfcGridCtrl_Actv_Cnct_10ms(void);
static void v_PfcGridCtrl_Actv_Cnct_PreProc(void);
static void v_PfcGridCtrl_Actv_Cnct_FltClr(void);
static void v_PfcGridCtrl_Actv_Cnct_ChkProc(void);
static void v_PfcGridCtrl_Actv_Cnct_FltRcv(void);

static void v_PfcGridCtrl_Actv_ValSet_10ms(void);
static void v_PfcGridCtrl_Actv_Ratio_10ms(void);

static void v_PfcGridCtrl_Reactv_Init(void);
static void v_PfcGridCtrl_Reactv_10ms(void);
static void v_PfcGridCtrl_Reactv_Reset_10ms(void);
static void v_PfcGridCtrl_Reactv_PF_10ms(void);
static void v_PfcGridCtrl_Reactv_QT_10ms(void);
static void v_PfcGridCtrl_Reactv_QP_PrmUpd(void);
static void v_PfcGridCtrl_Reactv_QP_A_10ms(void);
static void v_PfcGridCtrl_Reactv_QP_B_10ms(void);
static void v_PfcGridCtrl_Reactv_QP_10ms(void);
static void v_PfcGridCtrl_Reactv_QU_10ms(void);
static void v_PfcGridCtrl_Reactv_QU_PrmUpd(void);

#endif /* PFCGRIDCTRL_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
