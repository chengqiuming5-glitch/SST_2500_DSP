//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcPowCtrl.c
 * @brief
 * The header file of PFC power control module.
 *
 * Module      :                           \n
 * PfcPowCtrl
 *
 * Unit        :                           \n
 *
 *
 *
 * Module Task :                           \n
 * v_PfcPowCtrl_Init()                     \n
 * v_PfcPowCtrl_Isr()                      \n
 *
 * Unit Task   :                           \n
 *
 *
 * Sub Unit Task   :                       \n
 *
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2024/03/14
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
 * <tr><td>2024/03/14  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef PFCPOWCTRL_H_
#define PFCPOWCTRL_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "CmnDiagExt.h"
#include "ComExt.h"
#include "ComIfExt.h"
#include "PowLimExt.h"
#include "OnOffGridSwtExt.h"
#include "PfcStMacExt.h"
#include "PfcDataCalcExt.h"
#include "PfcGridCtrlExt.h"
#include "PfcDiagExt.h"
#include "PfcAdcExt.h"
#include "PfcPowCtrlExt.h"
#include "PfcPowPreCtrlExt.h"
#include "D2dPowCtrlExt.h"
#include "D2dStMac.h"
//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define PFC_DCBUS_CTRL        0U  ///< PFC DC-Bus control mode
#define PFC_3PCURRDQ_CTRL     1U  ///< PFC 3-phase current DQ balance control mode
#define PFC_3PCURRABC_CTRL    2U  ///< PFC 3-phase current ABC imbalance control mode
#define PFC_1PCURR_CTRL       3U  ///< PFC 1-phase current control mode
#define PFC_V2L_CTRL          4U  ///< PFC V2L control mode
#define PFC_DBG_CTRL          5U  ///< PFC Debug control mode

#define  TI_FLT_CLR   16000U        ///< ISR fault clear time
#define  CURR_OCP_RCV 5.0f          ///< OCP recovery current
#define  VOLT_OVP_RCV 360.0f        ///< OVP recovery voltage

#define VOLT_LIM_BUS_OV   860.0f
#define CNTR_LIM_BUS_OV   100U

#define LPF_40HZ_ISR_COEFF     (1.0f / (1.0f + PI_2_CONST * 40.0f / (float32)FRQ_PFC_CTRL))    ///< Cof1:1/(1+wT)
#define LPF_100HZ_ISR_COEFF    (1.0f / (1.0f + PI_2_CONST * 100.0f / (float32)FRQ_PFC_CTRL))    ///< Cof1:1/(1+wT)
#define LPF_750HZ_ISR_COEFF    (1.0f / (1.0f + PI_2_CONST * 750.0f / (float32)FRQ_PFC_CTRL))    ///< Cof1:1/(1+wT)

#define IREACTV_ZERO_THETA_MIN    (-0.02f)
#define IREACTV_ZERO_THETA_MAX    (0.02f)

#define COEFF_KP_VOLT_FF   0.5f

#define  COMPARE(a,b,c,max,min)          \
         {                               \
            if((a) > (b))                \
            {                            \
                if((c) > (a))            \
                {                        \
                    (max) = (c);         \
                    (min) = (b);         \
                }else if((c) > (b))      \
                {                        \
                    (max) = (a);         \
                    (min) = (b);         \
                }else                    \
                {                        \
                    (max) = (a);         \
                    (min) = (c);         \
                }                        \
            }                            \
            else                         \
            {                            \
                if((c) > (b))            \
                {                        \
                    (max) = (c);         \
                    (min) = (a);         \
                }else if((c) > (a))      \
                {                        \
                    (max) = (b);         \
                    (min) = (a);         \
                }else                    \
                {                        \
                    (max) = (b);         \
                    (min) = (c);         \
                }                        \
            }                            \
        }

#define VQ_LIMN_PLL_OK         (0.1f * RATED_AC_VOLT_AMP)   ///< PLL OK Vq limitation
#define FRQ_LPF_REPEAT         600.0f
//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    float32 ftAlfa;                             ///< Alfa-axis value
    float32 ftBeta;                             ///< Beta-axis value
    float32 ftD_axis;                           ///< D-axis value
    float32 ftQ_axis;                           ///< Q-axis value
    float32 ftD_axis_P;                         ///< D-axis positive sequence value
    float32 ftQ_axis_P;                         ///< Q-axis positive sequence value
    float32 ftD_axis_N;                         ///< D-axis negitive sequence value
    float32 ftQ_axis_N;                         ///< Q-axis negitive sequence value
}ST_3P_PARK;

typedef struct
{
    float32  ftMax;                             ///< Modulation value max value
    float32  ftMin;                             ///< Modulation value min value
    float32  ftHarm;                            ///< Harmonic value : 3th-component
    float32  ftD_axis;                          ///< D-axis value
    float32  ftQ_axis;                          ///< Q-axis value
    float32  ftZero;                            ///< Zero-sequence value
    float32  ftVectorAmp;                       ///< Amplitude value
    float32  ftAlfa;                            ///< Alfa-axis value
    float32  ftBeta;                            ///< Beta-axis value
    float32  ftA;                               ///< A-phase vaule
    float32  ftB;                               ///< B-phase vaule
    float32  ftC;                               ///< C-phase vaule
//    float32  ftN;                               ///< N-phase vaule
}ST_PWM_DRIVE;

typedef struct
{
    float32  ftNeg_D;                            ///< Negative sequence inhibition
    float32  ftNeg_Q;
    float32  ftHarm_D;                           ///< 5&7&11&13th harmonic inhibition
    float32  ftHarm_Q;
    float32  ftRepet_D;                          ///< Repetitive control output
    float32  ftRepet_Q;
}ST_HARM_CTRL;

/*ÃüÁî*/
typedef union
{
    Uint16 uiD2dPwmValDutyPowCell;
    struct
    {
        Uint16 DIS1EN:1;
        Uint16 DIS2EN:1;
        Uint16 REDUNEN:2;
        Uint16 rsvd:4;
        Uint16 DIS1N:4;
        Uint16 DIS2N:4;
    };
}CMD_WORD1;

typedef union
{
    Uint16 all;
    struct
    {
        Uint16 PfcRunMode:4;
        Uint16 DabRunMode:4;
        Uint16 BURSTNUM:8;
    };
}CMD_WORD2;

typedef union
{
    Uint16 all;
    struct
    {
        Uint16 CTRL_MODE:2;
        Uint16 OVER_CURR:1;
        Uint16 PreRelay_Ctrl:1;
        Uint16 rsvd:12;
    };
}CMD_WORD3;

typedef union
{
    Uint16 all;
    struct
    {
        Uint16 rsvd:16;
    };
}CMD_WORD4;

typedef union
{
    Uint16 all;
    struct
    {
        Uint16 DIS1EN:1; ///< redundant1 Enable
        Uint16 DIS2EN:1; ///< redundant2 Enable
        Uint16 rsvd:6;
        Uint16 DIS1N:4; ///< redundant1
        Uint16 DIS2N:4; ///< redundant2
    };
}CMD_WORD5;

typedef  struct
{
    Uint16      uiFrameHead; ///<FrameHead 0xAAAA
    CMD_WORD1   unRunCmd1;
    CMD_WORD2   unRunCmd2;
    CMD_WORD3   unRunCmd3;
    CMD_WORD4   unRunCmd4;
    Uint16      uiModulEnablA;
    Uint16      uiModulEnablB;
    Uint16      uiModulEnablC;
    Uint16      uiCmpA;
    Uint16      uiCmpB;
    Uint16      uiCmpC;
    int16       siId;
    int16       siIq;
    int16       siSinTheta;
    int16       siCosTheta;
    CMD_WORD5   unARedCmd;
    CMD_WORD5   unBRedCmd;
    CMD_WORD5   unCRedCmd;
    Uint16      uiFGridA;
    Uint16      uiFGridB;
    Uint16      uiFGridC;
    int16       siPollAddr;
    int16       siPollData;
    int16       siSOCCtrlA1;
    int16       siSOCCtrlB1;
    int16       siSOCCtrlC1;
    int16       siHalfVbusCtrlA1;
    int16       siHalfVbusCtrlB1;
    int16       siHalfVbusCtrlC1;
    int16       siSOCCtrlA2;
    int16       siSOCCtrlB2;
    int16       siSOCCtrlC2;
    int16       siHalfVbusCtrlA2;
    int16       siHalfVbusCtrlB2;
    int16       siHalfVbusCtrlC2;
    int16       siSOCCtrlA3;
    int16       siSOCCtrlB3;
    int16       siSOCCtrlC3;
    int16       siHalfVbusCtrlA3;
    int16       siHalfVbusCtrlB3;
    int16       siHalfVbusCtrlC3;
    int16       siSOCCtrlA4;
    int16       siSOCCtrlB4;
    int16       siSOCCtrlC4;
    int16       siHalfVbusCtrlA4;
    int16       siHalfVbusCtrlB4;
    int16       siHalfVbusCtrlC4;
    int16       siSOCCtrlA5;
    int16       siSOCCtrlB5;
    int16       siSOCCtrlC5;
    int16       siHalfVbusCtrlA5;
    int16       siHalfVbusCtrlB5;
    int16       siHalfVbusCtrlC5;
    int16       siSOCCtrlA6;
    int16       siSOCCtrlB6;
    int16       siSOCCtrlC6;
    int16       siHalfVbusCtrlA6;
    int16       siHalfVbusCtrlB6;
    int16       siHalfVbusCtrlC6;
    Uint16      uiCkeckSum;
}ST_EMIF_TOFPGA;

typedef struct
{
    int16  uiDebugData[11];
}ST_EMIF_DEBUG;

typedef struct
{
    ST_PFC_POW_CTRL   stPowCtrlExt;
    ST_3P_PARK        stVg;
    ST_3P_PARK        stIg;
    ST_PWM_DRIVE      stPWMdrive;
    ST_HARM_CTRL      stHarmCtrl;

    ST_PI_PRM         stPIVbus;                  ///< Bus Voltage loop PI
    ST_PI_PRM         stPICurrA;                 ///< Phase A current loop PI
    ST_PI_PRM         stPICurrB;                 ///< Phase B current loop PI
    ST_PI_PRM         stPICurrC;                 ///< Phase C current loop PI
    ST_PI_PRM         stPICurrD_P;               ///< D-axis positive current loop PI
    ST_PI_PRM         stPICurrQ_P;               ///< Q-axis positive current loop PI
    ST_PI_PRM         stPICurrD_N;               ///< D-axis negative current loop PI
    ST_PI_PRM         stPICurrQ_N;               ///< Q-axis negative current loop PI
    ST_PI_PRM         stPIVoltD_P;               ///< D-axis positive voltage loop PI
    ST_PI_PRM         stPIVoltQ_P;               ///< Q-axis positive voltage loop PI
    ST_PI_PRM         stPIVoltD_N;               ///< D-axis negative voltage loop PI
    ST_PI_PRM         stPIVoltQ_N;               ///< Q-axis negative voltage loop PI
    ST_PI_PRM         stPI_PLL;
    ST_PI_PRM         stPICellCtrlA[NUM_EMIF_POW_CELL];
    ST_PI_PRM         stPICellCtrlB[NUM_EMIF_POW_CELL];
    ST_PI_PRM         stPICellCtrlC[NUM_EMIF_POW_CELL];
    ST_PI_PRM         stPISOCCtrl[NUM_EMIF_POW_CELL];
    ST_PFC_REPEAT_PRM stVdRep;
    ST_PFC_REPEAT_PRM stVqRep;
    ST_2ND_ORD_LPF_PRM stId_Lpf2;     ///< Id 2nd order LPF
    ST_2ND_ORD_LPF_PRM stIq_Lpf2;     ///< Iq 2nd order LPF

    ST_EMIF_TOFPGA stEmifWr;          ///< Data to fpga for control
    ST_EMIF_TOFPGA stEmifWrPre;
    ST_EMIF_DEBUG  stEmifDebugWr;

    Uint16  uiCntrBusOV;                         ///< Bus OV counter
    Uint16  uiFlgBusOV;                          ///< Bus OV flag
    Uint16  uiCntrCbcTz;                         ///< CBC TZ counter
    Uint16  uiFlgCbcTz;                          ///< CBC TZ flag
    Uint16  uiModLoop;                           ///< PFC control loop mode
    Uint16  uiModPwm;                            ///< PFC PWM mode

    Uint16  uiFlgLoopClr;                        ///< Loop control clear flag
    float32 ftStartDelay;                        ///< Control loop start delay

    float32 ftVbusRecpr;                         ///< Vbus reciprocal
    float32 ftStepTheta;                         ///< Grid frequency theta by control frequency
    float32 ftPLLTheta;                          ///< PLL output theta
    float32 ftSinTheta;                          ///< PLL output sin-theta
    float32 ftCosTheta;                          ///< PLL output cos-theta
    float32 ftSinThetaB;                         ///< PLL output Phase-B sin-theta
    float32 ftCosThetaB;                         ///< PLL output Phase-B cos-theta
    float32 ftSinThetaC;                         ///< PLL output Phase-C sin-theta
    float32 ftCosThetaC;                         ///< PLL output Phase-C cos-theta

//    float32 ftIalfaRef;                          ///< Current alfa-axis reference
//    float32 ftIbetaRef;                          ///< Current beta-axis reference
    float32 ftZeroOut;                           ///< Zero sequence control output

    float32 ftVaDcInhb;                          ///< Voltage dc component inhibition module output phase A disturbance
    float32 ftVbDcInhb;                          ///< Voltage dc component inhibition module output phase B disturbance
    float32 ftVcDcInhb;                          ///< Voltage dc component inhibition module output phase C disturbance

    float32 ftIdRef;                             ///< D-axis current loop reference
    float32 ftIqRef;                             ///< Q-axis current loop reference
    float32 ftIqDstbcAi;                         ///< Anti-Island reactive current disturbance
    float32 ftVgFF;                              ///< Grid voltage feed forward, used for single phase control

    float32 ftVdLpf;
    float32 ftVqLpf;
    float32 ftVbusLpf;
    float32 ftId_Lpf2;
    float32 ftIq_Lpf2;

}ST_PFC_POW_CTRL_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PfcPowCtrl_PwmEn_Init(void);
static void v_PfcPowCtrl_PwmEn_Isr(void);

static void v_PfcPowCtrl_Calc_Init(void);
static void v_PfcPowCtrl_Calc_Isr(void);
static void v_PfcPowCtrl_Calc_Filter_Isr(void);
static void v_PfcPowCtrl_Calc_PARK_Isr(void);

static void v_PfcPowCtrl_PLL_Init(void);
static void v_PfcPowCtrl_PLL_Isr(void);

static void v_PfcPowCtrl_Loop_Init(void);
static void v_PfcPowCtrl_Loop_PWM_Init(void);
static void v_PfcPowCtrl_Loop_Curr_Init(void);
static void v_PfcPowCtrl_Loop_ACVolt_Init(void);
static void v_PfcPowCtrl_Loop_BalBrdg_Init(void);
static void v_PfcPowCtrl_Loop_Inner_Init(void);
static void v_PfcPowCtrl_Loop_CellBusVoltBal_Init(void);
static void v_PfcPowCtrl_Loop_CellSOCBal_Init(void);
static void v_PfcPowCtrl_Loop_Isr(void);
static void v_PfcPowCtrl_Loop_Clr_Isr(void);
static void v_PfcPowCtrl_Loop_BusOVBurp_Isr(void);
static void v_PfcPowCtrl_Loop_Dbg_Isr(void);
static void v_PfcPowCtrl_Loop_Bus_Isr(void);
static void v_PfcPowCtrl_Loop_3PDQ_Isr(void);
#ifndef SST_1250kW
static void v_PfcPowCtrl_Loop_3PABC_Isr(void);
#endif
static void v_PfcPowCtrl_Loop_1PCurr_Isr(void);
static void v_PfcPowCtrl_Loop_ACVolt_Isr(void);
static void v_PfcPowCtrl_Loop_Inner_Isr(void);
static void v_PfcPowCtrl_Loop_Inner_3P_Isr(void);
static void v_PfcPowCtrl_Loop_Inner_1P_Isr(void);
static void v_PfcPowCtrl_Loop_BalBrdg_Isr(void);
static void v_PfcPowCtrl_Loop_PWM_Isr(void);
static void v_PfcPowCtrl_Loop_PWM_1P_Isr(void);
static void v_PfcPowCtrl_Loop_PWM_3P_Isr(void);

static void v_PfcPowCtrl_Loop_CellSOCBal_1ms(void);
static void v_PfcPowCtrl_Loop_CellBusVoltBal_1ms(void);
static void v_PfcPowCtrl_CtrlMod_1ms(void);
static void v_PfcPowCtrl_PrmClr_1ms(void);
static void v_PfcPowCtrl_DataCalc_1ms(void);
static void v_PfcPowCtrl_V2LCBC_1ms(void);

static void v_PfcPowCtrl_Emif_Fpga_Wr_Isr(void);
static void v_PfcPowCtrl_Emif_Prm_Calc_Isr(void);

static void NOTCH_INIT(NOTCH *v,float32 Ts);
static void NOTCH_CALC(NOTCH *v);
static void NOTCH_UPD(NOTCH *v,float32 Ts);
static void DSOGI_INIT(DSOGI_TYPE *p, float32 Ts);
static void DSOGI_CALC(DSOGI_TYPE *p);
static void DSOGI_UPD(DSOGI_TYPE *p, float32 Ts);
static void PR_INIT(PR *p,float32 Ts);
static void PR_CALC(PR *p);
static void PR_CLC(PR *p);
static void PR_UPD(PR *p,float32 Ts);
static void MPF_INIT(MPF_TYPE *p,float32 Ts);
static void MPF_CALC(MPF_TYPE *p);
static void MPF_UPD(MPF_TYPE *p,float32 Ts);
static void v_PfcPowCtrl_InitPfcRepPrm(ST_PFC_REPEAT_PRM *stRepPfc);
static void v_PfcPowCtrl_InitPfcRepLpfPrm(ST_2ND_ORD_LPF_PRM *p);

#endif /* PFCPOWCTRL_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
