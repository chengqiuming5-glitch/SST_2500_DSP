//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcDataCalcExt.h
* TITLE         : Header file of PFC measurement and control parameter calculation external parameter and function
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2024.01.24
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

#ifndef PFCDATACALCEXT_H_
#define PFCDATACALCEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Pfc.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define PFC_DATACALC_DBG    0U

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    int16   siPaAvg;                                ///< 20ms Average active power of phase A
    int16   siPbAvg;                                ///< 20ms Average active  power of phase B
    int16   siPcAvg;                                ///< 20ms Average active  power of phase C
    int16   siQaAvg;                                ///< 20ms Average reactive  power of phase A
    int16   siQbAvg;                                ///< 20ms Average reactive  power of phase B
    int16   siQcAvg;                                ///< 20ms Average reactive  power of phase C
    int16   siPaAvgLPF;                             ///< LPF active power of phase A
    int16   siPbAvgLPF;                             ///< LPF active  power of phase B
    int16   siPcAvgLPF;                             ///< LPF active  power of phase C
    int16   siQaAvgLPF;                             ///< LPF reactive  power of phase A
    int16   siQbAvgLPF;                             ///< LPF reactive  power of phase B
    int16   siQcAvgLPF;                             ///< LPF reactive  power of phase C
    int32   slActvPower;                            ///< total active power
    int32   slRePower;                              ///< total reactive power
    int32   slAprtPower;                            ///< total apparent power
    float32 ftPf;                                   ///< total power factor
    int32   slActvPowerLPF;                         ///< total active power LPF
    int32   slRePowerLPF;                           ///< total reactive  power LPF
    int32   slAprtPowerLPF;                         ///< total apparent power LPF
    float32 ftPfLPF;                                ///< total power factor LPF
    float32 ftVbusLPF;                              ///< LPF value of bus voltage; 10Hz
    float32 ftVbusPosLPF;                           ///< LPF value of upper bus voltage
    float32 ftAprtPwrPhALPF;                        ///< Phase A apparent power LPF; 50Hz
    float32 ftAprtPwrPhBLPF;                        ///< Phase B apparent power LPF; 50Hz
    float32 ftAprtPwrPhCLPF;                        ///< Phase C apparent power LPF; 50Hz
    float32 ftAprtPwr1PLPFMax;                      ///< Single phase max apparent power LPF; 50Hz

    float32 ftVaRms;                                ///< RMS value of phase A grid voltage
    float32 ftVbRms;                                ///< RMS value of phase B grid voltage
    float32 ftVcRms;                                ///< RMS value of phase C grid voltage
    float32 ftVabRms;                               ///< RMS value of line AB grid voltage
    float32 ftVbcRms;                               ///< RMS value of line BC grid voltage
    float32 ftVacRms;                               ///< RMS value of line AC grid voltage
    float32 ftVaInvRms;                             ///< RMS value of phase A invert voltage
    float32 ftVbInvRms;                             ///< RMS value of phase B invert voltage
    float32 ftIaRms;                                ///< RMS value of phase A grid current
    float32 ftIbRms;                                ///< RMS value of phase B grid current
    float32 ftIcRms;                                ///< RMS value of phase C grid current
    float32 ftInRms;                                ///< RMS value of balance bridge current

    float32 ftVdRmsLPF;                             ///< LPF value of Vd-Rms
    float32 ftVaRmsLPF;                             ///< 20Hz LPF value of phase A grid voltage
    float32 ftVbRmsLPF;                             ///< 20Hz LPF value of phase B grid voltage
    float32 ftVcRmsLPF;                             ///< 20Hz LPF value of phase C grid voltage
    float32 ftVaInvRmsLPF;                          ///< 20Hz LPF value of phase A invert voltage
    float32 ftVbInvRmsLPF;                          ///< 20Hz LPF value of phase B invert voltage
    float32 ftIaRmsLPF;                             ///< 20Hz LPF value of phase A grid current
    float32 ftIbRmsLPF;                             ///< 20Hz LPF value of phase B grid current
    float32 ftIcRmsLPF;                             ///< 20Hz LPF value of phase C grid current
    float32 ftInRmsLPF;                             ///< 20Hz LPF value of balance bridge current

    float32 ftVgMaxRms;                             ///< Maximum grid voltage RMS value
    float32 ftVgMinRms;                             ///< Minimum grid voltage RMS value
    float32 ftVLineMaxRms;                          ///< Maximum grid voltage RMS value
    float32 ftVLineMinRms;                          ///< Minimum grid voltage RMS value
    float32 ftVgAvgRms;                             ///< Average grid voltage RMS value
    float32 ftVgAvgRmsLPF;                          ///< Average grid voltage RMS-LPF value
    float32 ftRatVoltVrtMax;                        ///< Ratio of maximum grid voltage for VRT
    float32 ftRatVoltVrtMin;                        ///< Ratio of minimum grid voltage for VRT

    float32 ftFrqVaCap;                             ///< Phase A grid frequency Ecap value
    float32 ftFrqVbCap;                             ///< Phase B grid frequency Ecap value
    float32 ftFrqVcCap;                             ///< Phase C grid frequency Ecap value
    float32 ftFrqCapMax;                            ///< Grid frequency Ecap maximum value
    float32 ftFrqCapMin;                            ///< Grid frequency Ecap minimum value
    float32 ftFrqCapAvgLPF;                         ///< Grid frequency Ecap average LPF value; 50Hz LPF
    float32 ftFrqCap6HzLPF;                         ///< Grid frequency Ecap 6Hz-cutoff frequency LPF value for PfcGridCtrl module
    float32 ftFrqPllLPF;                            ///< Grid PLL frequency 10Hz LPF value
    float32 ftIdRefLPF;                             ///< LPF value of IdRef
    float32 ftRoCoF;                                ///< RoCoF
    float32 ftTiSumRoCof;                           ///< Sum time of RoCoF

    int16 siVaADBiasLPF;                            ///< AD bias LPF of Va
    int16 siVbADBiasLPF;                            ///< AD bias LPF of Vb
    int16 siVcADBiasLPF;                            ///< AD bias LPF of Vc
    int16 siVaInvADBiasLPF;                         ///< AD bias LPF of VaInv
    int16 siVbInvADBiasLPF;                         ///< AD bias LPF of VbInv
    int16 siIaADBiasLPF;                            ///< AD bias LPF of Ia
    int16 siIbADBiasLPF;                            ///< AD bias LPF of Ib
    int16 siIcADBiasLPF;                            ///< AD bias LPF of Ic
//    int16 siInADBiasLPF;                            ///< AD bias LPF of In
    int16 siVaDcADBiasLPF;                          ///< AD bias LPF of Va DC
    int16 siVbDcADBiasLPF;                          ///< AD bias LPF of Vb DC
    int16 siVcDcADBiasLPF;                          ///< AD bias LPF of Vc DC
    int16 siIaDcADBiasLPF;                          ///< AD bias LPF of Ia DC
    int16 siIbDcADBiasLPF;                          ///< AD bias LPF of Ib DC
    int16 siIcDcADBiasLPF;                          ///< AD bias LPF of Ic DC
    int16 siIaDcADBiasLPF_N;                        ///< AD bias LPF of Ia DC(Relay N ON)
    int16 siIbDcADBiasLPF_N;                        ///< AD bias LPF of Ib DC(Relay N ON)
    int16 siIcDcADBiasLPF_N;                        ///< AD bias LPF of Ic DC(Relay N ON)
    Uint16 uiFlgADBiasOK;                           ///< AD bias LPF OK flag

    ///< Following parameters: DC component x1000, Voltage X10, Current x100
    int16  siVaDcAvg1000Times;                      ///< Average value of phase A grid voltage DC components
    int16  siVbDcAvg1000Times;                      ///< Average value of phase B grid voltage DC components
    int16  siVcDcAvg1000Times;                      ///< Average value of phase C grid voltage DC components
    int16  siIaDcAvg1000Times;                      ///< Average value of phase A grid current DC components
    int16  siIbDcAvg1000Times;                      ///< Average value of phase B grid current DC components
    int16  siIcDcAvg1000Times;                      ///< Average value of phase C grid current DC components

    Uint16 uiVoltDcMax1000Times;                    ///< Maximum value of grid voltage DC components for fault detect
    Uint16 uiCurrDcMax1000Times;                    ///< Maximum value of grid current DC components for fault detect
    Uint16 uiVgDiffRms10Times;                      ///< Deviation value of grid voltage 10 times for fault detect
    Uint16 uiIgDiffRms100Times;                     ///< Deviation value of grid current 100 times for fault detect
    Uint16 uiIgMaxRms100Times;                      ///< Maximum grid current RMS value 100 times for fault detect
    Uint16 uiIgMinRms100Times;                      ///< Minimum grid current RMS value 100 times for fault detect
    int16  siVbus10Times;                           ///< Bus voltage 10 times for fault detect
    int16  siVbusPos10Times;                        ///< Positive half bus voltage 10 times for fault detect
    Uint16 uiVbusMid10Times;                        ///< Mid-point bus voltage 10 times for fault detect
}ST_PFC_DATACALC_MEASPARM_OUTP;

typedef struct
{
    Uint16 uiFlgPhaSeqChkOk;                        ///< Grid sequence check ok flag
    Uint16 uiFlgPhaSeq;                             ///< Grid sequence: 0-positive; 1-negative
    Uint16 uiFlgPllOk;                              ///< PLL frequency Ok flag
    Uint16 uiFlgParmUpdIsr;                         ///< Control parameter ISR update flag
    Uint16 uiRepet_PiontsNew;                       ///< Repetitive control sample points
    Uint16 uiRms_PiontsNew;                         ///< RMS calculation points

    UN_PFC_GPIO_CMD unCmdADBiasRly;                 ///< Relay command for AD bias calculation
}ST_PFC_DATACALC_CTRLPARM_OUTP;

typedef struct
{
    float32 ftVoltRtdRecpr;                         ///< Reciprocal of rated grid voltage
    float32 ftPwrRtdRecpr;                          ///< Reciprocal of rated active power
    float32 ftRadFrqRtd;                            ///< Rated radian frequency
    float32 ftSampTime;                             ///< Control sample period
    float32 ftFrqCoeff;                             ///< Coefficient of PLL frequency calculation
    float32 ftPLL_DeltaTheta;                       ///< Cumulative value of Angle per control cycle of PLL
    Uint16  uiPerdPwmABC;                           ///< Phase A/B/C PWM timer period
    Uint16  uiPerdPwmN;                             ///< Phase N PWM timer period
}ST_PFC_DATACALC_SYSPARM_OUTP;

typedef struct
{
    ST_PFC_DATACALC_MEASPARM_OUTP   stMeasParm;
    ST_PFC_DATACALC_CTRLPARM_OUTP   stCtrlParm;
    ST_PFC_DATACALC_SYSPARM_OUTP    stSysParm;
}ST_PFC_DATACALC_OUTP;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PFC_DATACALC_OUTP stPfcDataCalc;

#if (1U == PFC_DATACALC_DBG)
extern ST_PFC_DATACALC_OUTP stPfcDataCalcDbg;
#endif

#endif /* PFCDATACALCEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
