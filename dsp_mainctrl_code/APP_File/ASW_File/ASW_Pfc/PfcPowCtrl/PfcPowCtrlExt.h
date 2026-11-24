//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcPowCtrlExt.h
* TITLE         : Header file of PFC power control external parameter and function
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2024.03.14
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

#ifndef PFCPOWCTRLEXT_H_
#define PFCPOWCTRLEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Pfc.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define PFC_POW_CTRL_FLG_DBG    0U    // Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================

typedef struct
{
    float32 ftVa_MPF;                    ///< A phase voltage MPF value
    float32 ftVb_MPF;                    ///< B phase voltage MPF value
    float32 ftVc_MPF;                    ///< C phase voltage MPF value
    float32 ftVbusNotch;                 ///< Bus voltage notch filtered value
    float32 ftVgDPllLpf;                 ///< D-axis voltage LPF value
#if 3U != GRID_PHASE_NUMBER
    float32 ftVaSogiBpf;                 ///< Va SOGI Band pass filter
    float32 ftVaSogiLpf;                 ///< Va SOGI Low pass filter
    float32 ftVaSqFrt;                   ///< Phase A voltage square for FRT only 19.2kW
    float32 ftVbSqFrt;                   ///< Phase B voltage square for FRT only 19.2kW
    int16   siOutpPwmModln;              ///< PWM modulation output
#endif
    float32 ftPosVoltSq;                 ///< Square(Positive component of grid voltage)
    float32 ftNegVoltSq;                 ///< Square(Negative component of grid voltage)
    float32 ftFrqPll;                    ///< PLL output frequency

    float32 ftIdRef;                     ///< D-axis current reference

    float32 ftOutpPwmModlnA;             ///< A Phase PWM modulation output
    float32 ftOutpPwmModlnB;             ///< B Phase PWM modulation output
    float32 ftOutpPwmModlnC;             ///< C Phase PWM modulation output
//    float32 ftOutpPwmModlnN;             ///< N Phase PWM modulation output

    float32 ftOutpCellBusVoltBalA[6];    ///< A Phase Cell bus voltage balance output
    float32 ftOutpCellBusVoltBalB[6];    ///< B Phase Cell bus voltage balance output
    float32 ftOutpCellBusVoltBalC[6];    ///< C Phase Cell bus voltage balance output

    float32 ftOutpCellSOCBal[3][6];         ///< SOC balance output

    Uint16  uiFlgPwmEn;                  ///< PFC pwm enable flag
    Uint16  uiEnaBalBrdgPwm;             ///< Balance bridge pwm enable
    Uint16  uiFlgBusOV;                  ///< Bus OV flag

    float32 ftVaCmn;                             ///< Common modulation wave of phase A
    float32 ftVbCmn;                             ///< Common modulation wave of phase B
    float32 ftVcCmn;                             ///< Common modulation wave of phase C
}ST_PFC_POW_CTRL;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PFC_POW_CTRL stPfcPowCtrl;
extern DSOGI_TYPE    stVg_Decompose;
extern DSOGI_TYPE    stIg_Decompose;

extern MPF_TYPE      stVaMpf;
extern MPF_TYPE      stVbMpf;
extern MPF_TYPE      stVcMpf;

extern NOTCH        BusVolt_Notch;

extern PR PR2_d;
extern PR PR2_q;
extern PR PR6_d;
extern PR PR6_q;
extern PR PR12_d;
extern PR PR12_q;

extern PR PR1_Ian;
extern PR PR2_Ian;
extern PR PR3_Ian;
extern PR PR5_Ian;
extern PR PR7_Ian;

extern PR ZeroVolt_PR1;
extern PR ZeroVolt_PR3;

//extern PR ZeroCurr_PR1;
//extern PR ZeroCurr_PR3;

extern PR MidBusVolt_PR;
extern PR MidBusCurr_PR;

extern ST_PI_PRM  stMidBusLoop;
extern ST_PI_PRM  stMidCurrLoop;

#if (1U == PFC_POW_CTRL_FLG_DBG)
extern ST_PFC_POW_CTRL stPfcPowCtrlDbg;
#endif

#endif /* PFCPOWCTRLEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
