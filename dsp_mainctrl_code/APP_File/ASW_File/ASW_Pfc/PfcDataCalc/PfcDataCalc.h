//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcDataCalc.h
 * @brief
 * The header file of PFC measurement and control parameter calculation.
 *
 * Module      :                           \n
 * PfcDataCalc
 *
 * Unit        :                           \n
 * PfcDataCalc_PhaSeqChk                   \n
 * PfcDataCalc_SysPrmChg                   \n
 * PfcDataCalc_FrqChk                      \n
 * PfcDataCalc_PrmUpd                      \n
 * PfcDataCalc_PrmChgUpd                   \n
 * PfcDataCalc_PrmClr                      \n
 * PfcDataCalc_PwrCalc                     \n
 * PfcDataCalc_VCRmsCalc                   \n
 * PfcDataCalc_DcCptCalc                   \n
 * PfcDataCalc_FrqCalc                     \n
 * PfcDataCalc_Acm                         \n
 * PfcDataCalc_FrqCalc                     \n
 *
 *
 * Module Task :                           \n
 * v_PfcDataCalc_Init()                    \n
 * v_PfcDataCalc_Isr()                     \n
 * v_PfcDataCalc_1ms()                     \n
 * v_PfcDataCalc_10ms()                    \n
 *
 * Unit Task   :                           \n
 * v_PfcDataCalc_PhaSeqChk_Init()          \n
 * v_PfcDataCalc_PhaSeqChk_1ms()           \n
 * v_PfcDataCalc_FrqChk_Init()             \n
 * v_PfcDataCalc_FrqChk_10ms()             \n
 * v_PfcDataCalc_PrmChgUpd_Init()          \n
 * v_PfcDataCalc_PrmChgUpd_10ms()          \n
 * v_PfcDataCalc_PrmUpd_Isr()              \n
 * v_PfcDataCalc_PrmClr_1ms()              \n
 * v_PfcDataCalc_PwrCalc_Init()            \n
 * v_PfcDataCalc_PwrCalc_1ms()             \n
 * v_PfcDataCalc_RmsCalc_Init()            \n
 * v_PfcDataCalc_RmsCalc_1ms()             \n
 * v_PfcDataCalc_DcCptCalc_Init()          \n
 * v_PfcDataCalc_DcCptCalc_1ms()           \n
 * v_PfcDataCalc_FrqCalc_Init()            \n
 * v_PfcDataCalc_FrqCalc_1ms()             \n
 * v_PfcDataCalc_Acm_Init()                \n
 * v_PfcDataCalc_Acm_Isr()                 \n
 * v_PfcDataCalc_SysPrmChg_Init()          \n
 *
 * Sub Unit Task   :                       \n
 * v_PfcDataCalc_PhaSeqChk_3P_1ms()
 * v_PfcDataCalc_FrqChk_OnGrid()
 * v_PfcDataCalc_FrqChk_OffGrid()
 * v_PfcDataCalc_PwrCalc_AVG_1ms()
 * v_PfcDataCalc_PwrCalc_LPF_1ms()
 * v_PfcDataCalc_RmsCalc_Volt_1ms()
 * v_PfcDataCalc_RmsCalc_VoltLPF()
 * v_PfcDataCalc_RmsCalc_Curr_1ms()
 * v_PfcDataCalc_RmsCalc_CurrLPF()
 * v_PfcDataCalc_RmsCalc_MaxMin()
 * v_PfcDataCalc_DcCptCalc_Volt()
 * v_PfcDataCalc_DcCptCalc_Curr_1ms()
 * v_PfcDataCalc_FrqCalc_Avg_1ms()
 * v_PfcDataCalc_Acm_Pwr_Isr()
 * v_PfcDataCalc_Acm_VFPoint_Isr()
 * v_PfcDataCalc_Acm_Rms3P_Isr()
 * v_PfcDataCalc_Acm_Rms_Isr()
 * v_PfcDataCalc_Acm_Avg3P_Isr()
 * v_PfcDataCalc_PrmUpd_Rtd1_Eep()
 * v_PfcDataCalc_PrmUpd_Frq_Eep()
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2024/01/24
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
 * <tr><td>2024/01/24  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef PFCDATACALC_H_
#define PFCDATACALC_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcDataCalcExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "AdcDrvExt.h"
#include "ECapDrvExt.h"
#include "PfcAdcExt.h"
#include "PfcGridCtrlExt.h"
#include "PfcStMacExt.h"
#include "PfcPowPreCtrlExt.h"
#include "PfcPowCtrlExt.h"
#include "ASW_D2d.h"
#include "PerdTskExt.h"
#include "D2dAdcExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define FRQCALC_VOLT_LIM       30.0f
#define SEQCHK_VOLT_LIM        50.0f
#define SEQCHK_OK_TIME         1000U
#define SEQCHK_TIMEOUT_TIME    10000U
#ifndef _SIMULATION_NO_DSP_
    #define FRQ_CHK_OK_TIME     50U
    #define FRQ_CHK_NO_TIME     50U
#else
    #define FRQ_CHK_OK_TIME     5U
    #define FRQ_CHK_NO_TIME     5U
#endif

#define DIVNUM_FRQ_AVG     1U
#define FRQ_ARRAY_LEN      2U    ///< Frequency average number
#define COEFF_ECAP         200000000UL
#define MAX_PERIOD_ECAP    (COEFF_ECAP/(Uint32)(GRID_FRQ_MIN-5U))
#define MIN_PERIOD_ECAP    (COEFF_ECAP/(Uint32)(GRID_FRQ_MAX+5U))

#define VOLT_ERROR         0.5f
#define CURR_ERROR         0.05f
#define PWR_ERROR          1.0f

#define CAP_FRQ_UPD_ERR   0.05f
/* PLL Macro define */
#define PLL_OK_FRQ_ERR    0.3f
#define PLL_FLT_FRQ_ERR   0.35f

#define PLL_OK_VOLT_ERR_COEFF_MAX    1.1f
#define PLL_OK_VOLT_ERR_COEFF_MIN    0.9f

/* AD bias Macro define */
#define AD_BIAS_GRID_VOLT_MAX    (AD_BIAS_GRID_VOLT + 512)
#define AD_BIAS_GRID_VOLT_MIN    (AD_BIAS_GRID_VOLT - 512)
#define AD_BIAS_GRID_CURR_MAX    (AD_BIAS_GRID_CURR + 512)
#define AD_BIAS_GRID_CURR_MIN    (AD_BIAS_GRID_CURR - 512)
#define AD_BIAS_DC_VOLT_MAX      (AD_BIAS_DC_VOLT + 1024)
#define AD_BIAS_DC_VOLT_MIN      (AD_BIAS_DC_VOLT - 1024)
#define AD_BIAS_DC_CURR_MAX      (AD_BIAS_DC_CURR + 1024)
#define AD_BIAS_DC_CURR_MIN      (AD_BIAS_DC_CURR - 1024)

#define AD_BIAS_ST_WAIT          0U
#define AD_BIAS_ST_BUS_CHK       1U
#define AD_BIAS_ST_RLYN_OFF      2U
#define AD_BIAS_ST_RLYN_ON       3U
#define AD_BIAS_ST_END           4U

/* Reactive power calculation compensation */
#define COEFF_REACTV_POW_CALC_COMP    0.013f    ///< Reactive power calculation compensation coefficient

#if(2U == GRID_PHASE_NUMBER)
#define RAT_D2D_SAMPTI_BASE_PFC       0.5f      ///< D2D sample time based on PFC sample time
#else
#define RAT_D2D_SAMPTI_BASE_PFC       1.0f
#endif

/* RoCoF Macro define */
#define ROCOF_ARRAY_LEN         20U    ///< RoCoF array length
#define ROCOF_FLAG_PHASE_A      1U     ///< RoCoF use phase A frequency flag
#define ROCOF_FLAG_PHASE_B      2U     ///< RoCoF use phase B frequency flag
#define ROCOF_FLAG_PHASE_C      3U     ///< RoCoF use phase C frequency flag

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint32   ulPHT;                     ///< Positive half cycle time
    Uint32   ulPHTSum;                  ///< Sum of PHT
    Uint32   ulPHTArray[FRQ_ARRAY_LEN]; ///< PHT array
    Uint32   ulPHTAvg;                  ///< PHT average
    float32  ftFrqVal;                  ///< Ecap grid frequency calculation value
    Uint16   uiIndex;
}ST_FRQ_CALC;

typedef struct
{
    Uint16  uiFlgPha;                   ///< Phase flag
    Uint16  uiFlgZeroCross;             ///< Zero cross flag
    Uint16  uiIdxArry;                  ///< Array index
    float32 ftFrqArry[ROCOF_ARRAY_LEN]; ///< Frequency array
}ST_ROCOF_CALC;

typedef struct
{
    Uint16   uiCurrPoints;              ///< RMS calculation current points
    Uint16   uiCntrBuf;                 ///< RMS calculation buffer counter
    Uint16   uiPosnLastVal;             ///< Last value position
    Uint16   uiPosnLastLastVal;         ///< Last-last value position
    Uint16   uiSts;                     ///< RMS calculation status
    float32  ftRecprRMSPoints;          ///< Reciprocal of RMS calculation points
}ST_RMS_SAMP_ISR;

typedef struct
{
    float32  ftARmsSum;                 ///< Phase A RMS calculation sum-value
    float32  ftARmsStore[MAX_RMS_NUM];  ///< Phase A RMS calculation storage array
    float32  ftBRmsSum;                 ///< Phase B RMS calculation sum-value
    float32  ftBRmsStore[MAX_RMS_NUM];  ///< Phase B RMS calculation storage array
    float32  ftCRmsSum;                 ///< Phase C RMS calculation sum-value
    float32  ftCRmsStore[MAX_RMS_NUM];  ///< Phase C RMS calculation storage array
}ST_3P_RMS_CALC;

typedef struct
{
    float32  ftRmsSum;                  ///< RMS calculation sum-value
    float32  ftRmsStore[MAX_RMS_NUM];   ///< RMS calculation storage array
}ST_1P_RMS_CALC;

typedef struct
{
    float32  ftASum;                    ///< Phase A average calculation sum-value
    float32  ftAStore[MAX_RMS_NUM];     ///< Phase A average calculation storage array
    float32  ftBSum;                    ///< Phase B average calculation sum-value
    float32  ftBStore[MAX_RMS_NUM];     ///< Phase B average calculation storage array
    float32  ftCSum;                    ///< Phase C average calculation sum-value
    float32  ftCStore[MAX_RMS_NUM];     ///< Phase C average calculation storage array
}ST_3P_AVG_CALC;

typedef struct
{
    float32  ftPASum;                    ///< Phase A active power calculation sum-value
    float32  ftPAStore[MAX_RMS_NUM];     ///< Phase A active power calculation storage array
    float32  ftPBSum;                    ///< Phase B active power calculation sum-value
    float32  ftPBStore[MAX_RMS_NUM];     ///< Phase B active power calculation storage array
    float32  ftPCSum;                    ///< Phase C active power calculation sum-value
    float32  ftPCStore[MAX_RMS_NUM];     ///< Phase C active power calculation storage array

    float32  ftQASum;                    ///< Phase A reactive power calculation sum-value
    float32  ftQAStore[MAX_RMS_NUM];     ///< Phase A reactive power calculation storage array
    float32  ftQBSum;                    ///< Phase B reactive power calculation sum-value
    float32  ftQBStore[MAX_RMS_NUM];     ///< Phase B reactive power calculation storage array
    float32  ftQCSum;                    ///< Phase C reactive power calculation sum-value
    float32  ftQCStore[MAX_RMS_NUM];     ///< Phase C reactive power calculation storage array
}ST_3P_PWR_CALC;

typedef struct
{
    float32 ftVaLpf;
    float32 ftVaMpf;
    float32 ftVbLpf;
    float32 ftVbMpf;
    float32 ftVcLpf;
    float32 ftVcMpf;
}ST_GRID_VOLT_CURR;

typedef struct
{
    ST_PFC_DATACALC_MEASPARM_OUTP stMeasExt;
    ST_PFC_DATACALC_CTRLPARM_OUTP stCtrlExt;
    ST_PFC_DATACALC_SYSPARM_OUTP  stSysExt;

    ST_FRQ_CALC                   stFrqA;
    ST_FRQ_CALC                   stFrqB;
    ST_FRQ_CALC                   stFrqC;
    ST_ROCOF_CALC                 stRoCoF;     ///< Rate of change of frequency

    ST_RMS_SAMP_ISR               stVFcalc;

    ST_3P_RMS_CALC                stVolt;
    ST_3P_RMS_CALC                stVoltLine;
    ST_3P_RMS_CALC                stVoltInv;
    ST_3P_RMS_CALC                stCurr;
    ST_1P_RMS_CALC                stIn;
    ST_3P_AVG_CALC                stVdc;
    ST_3P_AVG_CALC                stIdc;
    ST_3P_PWR_CALC                stPwr;

    float32  ftErrEcapFrq;                       ///< Grid Ecap frequency variation
    float32  ftErrFrq;                           ///< Error between Ecap frequency and PLL frequency
    float32  ftFrqEcapOld;                       ///< Grid Ecap frequency old value
    float32  ftFrqUpdRef;                        ///< Frequency reference of parameter update
    float32  ftWoUpd;                            ///< Wo=2*pi*frequency
    Uint16   uiFlgGridFrqChg;                    ///< Grid frequency change flag
    Uint16   uiCntrPllChk;                       ///< PLL frequency check counter

    Uint16   uiFlgHwPrmChg;                      ///< System hardware parameter change flag
    Uint16   uiFlgCtrlFrqChg;                    ///< Control frequency change flag

    Uint16   uiFrqCtrl;                          ///< Control frequency
    Uint16   uiCntrSampIntl;                     ///< ISR sample interval counter

    Uint16   uiCntrPosSeq;                       ///< Positive sequence judgment counter
    Uint16   uiCntrNegSeq;                       ///< Negative sequence judgment counter
    Uint16   uiCntrSeqChkTiOut;                  ///< Phase sequence judgment time-out counter
    Uint16   uiCntrADBiasLpf;                    ///< AD bias calculation LPF counter
    Uint16   uiStADBias;                         ///< AD bias calculation status
}ST_PFC_DATACALC_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PfcDataCalc_PhaSeqChk_Init(void);
static void v_PfcDataCalc_PhaSeqChk_1ms(void);
static void v_PfcDataCalc_PhaSeqChk_3P_1ms(void);

static void v_PfcDataCalc_FrqChk_Init(void);
static void v_PfcDataCalc_FrqChk_10ms(void);
static void v_PfcDataCalc_FrqChk_OnGrid(void);
static void v_PfcDataCalc_FrqChk_OnGrid_Pll(void);
static void v_PfcDataCalc_FrqChk_OffGrid(void);

static void v_PfcDataCalc_PrmChgUpd_Init(void);
static void v_PfcDataCalc_PrmChgUpd_10ms(void);
static void v_PfcDataCalc_PrmChgUpd_GridFrq(void);

static void v_PfcDataCalc_SysPrmChg_Init(void);
static void v_PfcDataCalc_PrmUpd_Rtd1_Eep(void);
static void v_PfcDataCalc_PrmUpd_Frq_Eep(void);

static void v_PfcDataCalc_InstnsCalc_Init(void);
static void v_PfcDataCalc_InstnsCalc_1ms(void);

static void v_PfcDataCalc_PwrCalc_Init(void);
static void v_PfcDataCalc_PwrCalc_1ms(void);
static void v_PfcDataCalc_PwrCalc_AVG_1ms(void);
static void v_PfcDataCalc_PwrCalc_LPF_1ms(void);

static void v_PfcDataCalc_RmsCalc_Init(void);
static void v_PfcDataCalc_RmsCalc_1ms(void);
static void v_PfcDataCalc_RmsCalc_Volt_1ms(void);
static void v_PfcDataCalc_RmsCalc_VoltLPF(void);
static void v_PfcDataCalc_RmsCalc_Curr_1ms(void);
static void v_PfcDataCalc_RmsCalc_CurrLPF(void);
static void v_PfcDataCalc_RmsCalc_MaxMin(void);
static void v_PfcDataCalc_RmsCalc_MaxMin_3P(void);
static void v_PfcDataCalc_RmsCalc_MaxMin_2P(void);
static void v_PfcDataCalc_RmsCalc_MaxMin_1P(void);

static void v_PfcDataCalc_DcCptCalc_Init(void);
static void v_PfcDataCalc_DcCptCalc_1ms(void);
static void v_PfcDataCalc_DcCptCalc_Volt(void);
static void v_PfcDataCalc_DcCptCalc_Curr(void);

static void v_PfcDataCalc_FrqCalc_Init(void);
static void v_PfcDataCalc_FrqCalc_1ms(void);
static void v_PfcDataCalc_FrqCalc_Avg_1ms(ST_FRQ_CALC *pData);
static void v_PfcDataCalc_FrqCalc_RoCoF_1ms(void);

static void v_PfcDataCalc_FrqCalc_Samp_1ms(void);
static void v_PfcDataCalc_FrqCalc_Samp_Avg(ST_FRQ_CALC *pData);

static void v_PfcDataCalc_Acm_Init(void);
static void v_PfcDataCalc_Acm_Isr(void);
static void v_PfcDataCalc_Acm_VFPoint_Isr(void);
static void v_PfcDataCalc_Acm_Rms3P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_RMS_CALC *pstThreeRms, ST_RMS_SAMP_ISR *pstCalc);
static void v_PfcDataCalc_Acm_Rms2P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_RMS_CALC *pstThreeRms, ST_RMS_SAMP_ISR *pstCalc);
static void v_PfcDataCalc_Acm_Rms1P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_RMS_CALC *pstThreeRms, ST_RMS_SAMP_ISR *pstCalc);
static void v_PfcDataCalc_Acm_Rms_Isr(float32 ftData, ST_1P_RMS_CALC *pstOneRms, ST_RMS_SAMP_ISR *pstCalc);
static void v_PfcDataCalc_Acm_Avg3P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_AVG_CALC *pstThreeAvg, ST_RMS_SAMP_ISR *pstCalc);
static void v_PfcDataCalc_Acm_Avg2P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_AVG_CALC *pstThreeAvg, ST_RMS_SAMP_ISR *pstCalc);
static void v_PfcDataCalc_Acm_Avg1P_Isr(ST_THREE_PHASE_PARM *pstThreePhaseData, ST_3P_AVG_CALC *pstThreeAvg, ST_RMS_SAMP_ISR *pstCalc);
static void v_PfcDataCalc_Acm_Pwr3P_Isr(ST_3P_PWR_CALC *pstThreePwr, ST_RMS_SAMP_ISR *pstCalc);
static void v_PfcDataCalc_Acm_Pwr2P_Isr(ST_3P_PWR_CALC *pstThreePwr, ST_RMS_SAMP_ISR *pstCalc);
static void v_PfcDataCalc_Acm_Pwr1P_Isr(ST_3P_PWR_CALC *pstThreePwr, ST_RMS_SAMP_ISR *pstCalc);

static void v_PfcDataCalc_ADBiasCalc_Init(void);
static void v_PfcDataCalc_ADBiasCalc_1ms(void);
static void v_PfcDataCalc_ADBias_Volt(void);
static void v_PfcDataCalc_ADBias_Curr(void);
static void v_PfcDataCalc_ADBias_VoltDC(void);
static void v_PfcDataCalc_ADBias_CurrDC(void);
static void v_PfcDataCalc_ADBias_Outp(void);
static void v_PfcDataCalc_ADBias_StWait(void);
static void v_PfcDataCalc_ADBias_StBusChk(void);
static void v_PfcDataCalc_ADBias_StOffRlyN(void);
static void v_PfcDataCalc_ADBias_StOnRlyN(void);
static void v_PfcDataCalc_ADBias_StEnd(void);

static void v_PfcDataCalc_PrmUpd_Isr(void);

#endif /* PFCDATACALC_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
