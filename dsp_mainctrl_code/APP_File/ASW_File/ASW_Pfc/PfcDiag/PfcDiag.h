//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcDiag.c
 * @brief
 * The header file of PFC fault diagnosis module.
 *
 * Module      :                           \n
 * PfcDiag
 *
 * Unit        :                           \n
 *
 *
 *
 * Module Task :                           \n
 * v_PfcDiag_Init()                        \n
 * v_PfcDiag_1ms()                         \n
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
 * 2024/03/20
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
 * <tr><td>2024/03/20  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef PFC_FILE_PFCDIAG_PFCDIAG_H_
#define PFC_FILE_PFCDIAG_PFCDIAG_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcDiagExt.h"
#include "CmnDiagExt.h"
#include "ComExt.h"
#include "ComIfExt.h"
#include "PowLimExt.h"
#include "PfcAdcExt.h"
#include "PfcDataCalcExt.h"
#include "PfcStMacExt.h"
#include "CDD_Drv.h"
#include "FaultData.h"
#include "GridStdData.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define PFC_OV_AMP_PROT_COEFF    (1.33f * CON_SQRT_2)        ///< AC AMP OV protection coefficient: 1.33*1.414
#define PFC_OV_RMS_IMBAL_PROT    40.0f                       ///< PFC RMS OV imbalance protection
#define PFC_OC_RMS_IMBAL_PROT    6.0f                        ///< PFC RMS OC imbalance protection
#define PFC_OV_AMP_PROT_TI       3U                          ///< AC AMP OV protection time: 3 times ISR
#define PFC_OC_AMP_PROT_TI       3U                          ///< AC AMP OC protection time: 3 times ISR
#define PFC_ZV_RMS_LIM           (0.2f*RATED_AC_VOLT_RMS)    ///< AC RMS ZV limit
#define PFC_PWR_PROT_COEFF       1.15f                       ///< PFC Over power protection coefficient

#if(1U == GRID_PHASE_NUMBER)
#ifdef _SIMULATION_NO_DSP_
#define PFC_OC_RMS_PROT_COEFF    2.0f                        ///< AC RMS OC protection coefficient
#define PFC_OC_AMP_PROT          150.0f                      ///< AC AMP OC protection: 78A
#else
#define PFC_OC_RMS_PROT_COEFF    1.15f                       ///< AC RMS OC protection coefficient
#define PFC_OC_AMP_PROT          80.0f                       ///< AC AMP OC protection: 78A->80A
#endif
#define PFC_BUS_UV_PROT          310.0f                      ///< PFC bus UV protection
#define PFC_BUS_OV_PROT          460.0f                      ///< PFC bus OV protection
#define PFC_HALF_BUS_OV_PROT     245.0f                      ///< PFC half bus OV protection
#define PFC_MID_BUS_OV_PROT      50.0f                       ///< PFC mid-point bus OV protection
#define PFC_VOLT_DC_PROT         0.3f                        ///< PFC DC voltage protection
#define PFC_CURR_DC_PROT         0.8f                        ///< PFC DC current protection
#define PFC_CBC_TI               200U                        ///< PFC CBC protection time: 50 times ISR -> 200 times ISR
#define PFC_CBC_PERD             1U                          ///< PFC CBC operation period
#define PFC_ST_OV_TI             50U                         ///< PFC State Machine over time
#elif(2U == GRID_PHASE_NUMBER)
#define PFC_OC_RMS_PROT_COEFF    1.05f                       ///< AC RMS OC protection coefficient
#define PFC_OC_AMP_PROT          160.0f                      ///< AC AMP OC protection: 160A
#define PFC_BUS_UV_PROT          320.0f                      ///< PFC bus UV protection
#define PFC_BUS_OV_PROT          475.0f                      ///< PFC bus OV protection
#define PFC_HALF_BUS_OV_PROT     245.0f                      ///< PFC half bus OV protection
#define PFC_MID_BUS_OV_PROT      40.0f                       ///< PFC mid-point bus OV protection
#define PFC_VOLT_DC_PROT         1.0f                        ///< PFC DC voltage protection
#define PFC_CURR_DC_PROT         0.8f                        ///< PFC DC current protection
#define PFC_CBC_TI               200U                        ///< PFC CBC protection time: 200 times ISR
#define PFC_CBC_PERD             8U                          ///< PFC CBC operation period
#define PFC_ST_OV_TI             200U                        ///< PFC State Machine over time
#elif(3U == GRID_PHASE_NUMBER)
#define PFC_OC_RMS_PROT_COEFF    1.20f                       ///< AC RMS OC protection coefficient
#define PFC_OC_AMP_PROT          48.0f                       ///< AC AMP OC protection: 48A
#define PFC_BUS_UV_PROT          500.0f                      ///< PFC bus UV protection
#define PFC_BUS_OV_PROT          870.0f                      ///< PFC bus OV protection
#define PFC_HALF_BUS_OV_PROT     450.0f                      ///< PFC half bus OV protection
#define PFC_MID_BUS_OV_PROT      50.0f                       ///< PFC mid-point bus OV protection
#define PFC_VOLT_DC_PROT         1.0f                        ///< PFC DC voltage protection
#define PFC_CURR_DC_PROT         0.8f                        ///< PFC DC current protection
#define PFC_CBC_TI               200U                        ///< PFC CBC protection time: 200 times ISR
#define PFC_CBC_PERD             8U                          ///< PFC CBC operation period
#define PFC_ST_OV_TI             200U                        ///< PFC State Machine over time
#endif

#define EXT_INIT                      0U
#define EXT_TRIG                      1U
#define EXT_WAIT                      2U
#define EXT_RESET                     3U

#ifndef _SIMULATION_NO_DSP_
#define RESET_TIME_DELAY              1500U
#define RESET_TIME_DURN               100U
#else
#define RESET_TIME_DELAY              20
#define RESET_TIME_DURN               10
#endif

#define FREQ_CBC_DET                  (Uint16)RATED_AC_FRQ
#define NUM_CBC_PERD                  (FRQ_PFC_CTRL/FREQ_CBC_DET)
#define NUM_CBC_TRIG                  (10U*FREQ_CBC_DET/PFC_CBC_PERD)   ///< 10s

///> Determine whether the fault is prohibited for internal detection
#define INNER_DIS_CHK()             ((stPfcDiagLoc.stSingleFlt.uiDisDetByPfcSt)&(stPfcDiagLoc.stSingleFlt.uiPfcStsWord))
///> Determine whether the fault is masked
#define EXT_MASK_DIS_CHK()          ((stPfcDiagLoc.stSingleFlt.uiMaskWord)&(stPfcDiagLoc.stSingleFlt.uiFltWordBit))

///> Separate related information from the fault category word
///> Fault type A/D  0-digital fault, 1-analog fault
#define GET_AD_FLT_TYPE()           (stPfcDiagLoc.stSingleFlt.unProperty.bit.uiADFltCategory)
///> Fault level
#define GET_FLT_LVL()               (stPfcDiagLoc.stSingleFlt.unProperty.bit.uiFltLvl)
///> External fault type
#define GET_EXT_FLT_TYPE()          (stPfcDiagLoc.stSingleFlt.unProperty.bit.uiExtFltCategory)
///> Fault bit in fault word
#define GET_FLT_BIT()               (stPfcDiagLoc.stSingleFlt.unProperty.bit.uiFltBit)

///> Separate related information from the fault mode word
///> Latch flag: 0-no latch, 1-latch
#define GET_LATCH_FLG()             (stPfcDiagLoc.stSingleFlt.unProperty.bit.uiFlgLatch)
///> Fault detect type: 0~9
#define GET_DET_MOD()               (stPfcDiagLoc.stSingleFlt.unFaultMode.bit.uiChkMod)
///> Digital fault status word real bit number
#define GET_DIG_FLT_STS_BIT()       (stPfcDiagLoc.stSingleFlt.unFaultMode.bit.uiSTS_BitNum)
///> Digital fault command word real bit number
#define GET_DIG_FLT_CMD_BIT()       (stPfcDiagLoc.stSingleFlt.unFaultMode.bit.uiCMD_BitNum)


///> Set fault word
#define SET_FLT_WORD()              ((*stPfcDiagLoc.stSingleFlt.puiFaultWord)|=(stPfcDiagLoc.stSingleFlt.uiFltWordBit))
///> Clear fault word
#define CLR_FLT_WORD()              ((*stPfcDiagLoc.stSingleFlt.puiFaultWord)&=(~(stPfcDiagLoc.stSingleFlt.uiFltWordBit)))
///> Set fault status word
#define SET_FLT_STS_WORD()          ((*stPfcDiagLoc.stSingleFlt.puiFaultStWord)|=(stPfcDiagLoc.stSingleFlt.uiFltWordBit))
///> Clear fault status word
#define CLR_FLT_STS_WORD()          ((*stPfcDiagLoc.stSingleFlt.puiFaultStWord)&=(~(stPfcDiagLoc.stSingleFlt.uiFltWordBit)))
///> Get fault word
#define GET_FLT_WORD()              ((*stPfcDiagLoc.stSingleFlt.puiFaultWord)&(stPfcDiagLoc.stSingleFlt.uiFltWordBit))
///> Get fault status word
#define GET_FLT_STS_WORD()          ((*stPfcDiagLoc.stSingleFlt.puiFaultStWord)&(stPfcDiagLoc.stSingleFlt.uiFltWordBit))
///> Fault diagnosis internal reset command
//#define IN_RESET_CMD                stPfcDiagLoc.stExtFltReset.uiResetCmd


///> Get digital fault status value
#define GET_DIG_STS_VAL()           (((Uint16)stPfcDiagLoc.stSingleFlt.siLmtVal)&(stPfcDiagLoc.stSingleFlt.uiDigFltStsBit))
///> Get digital fault command value
#define GET_DIG_CMD_VAL()           (((Uint16)stPfcDiagLoc.stSingleFlt.siActualVal)&(stPfcDiagLoc.stSingleFlt.uiDigFltCmdBit))
///> Get fault detect target real value
#define GET_ACT_VAL()               (stPfcDiagLoc.stSingleFlt.siActualVal)
///> Get fault detect target absolute value
#define GET_ACT_VAL_ABS()           (abs(stPfcDiagLoc.stSingleFlt.siActualVal))
///> Get fault detect target limit value
#define GET_LMT_VAL()               (stPfcDiagLoc.stSingleFlt.siLmtVal)
///> Get fault detect target absolute limit value
#define GET_LMT_VAL_ABS()           (abs(stPfcDiagLoc.stSingleFlt.siLmtVal))

///> Set fault level
#define SET_FLT_LVL()               (stPfcDiagLoc.stSingleFlt.uiFltLvlCmbnTemp |= stPfcDiagLoc.stSingleFlt.uiFltLvlBit)
///> Fault counter
#define FLT_CNTR()                  (*stPfcDiagLoc.stSingleFlt.puiCntr)
///> Fault clear time
#define FLT_CLR_TI()                (stPfcDiagLoc.stSingleFlt.uiTiClr)
///> Fault confirm time
#define FLT_CFM_TI()                (stPfcDiagLoc.stSingleFlt.uiTiCfm)
///> Fault hysteresis value
#define FLT_HYS_VAL()               (stPfcDiagLoc.stSingleFlt.uiHysVal)
///> Fault clear set
#define FLT_CLR_SET()               CLR_FLT_STS_WORD();\
                                    FLT_CNTR() = 0;

#define PFC_OCP_A_HW_FLT_IS_ON      (1U == GpioDataRegs.GPBDAT.bit.GPIO32)   ///< PFC Phase A OC Hardware Fault is on
#define PFC_OCP_A_HW_FLT_IS_OFF     (0U == GpioDataRegs.GPBDAT.bit.GPIO32)   ///< PFC Phase A OC Hardware Fault is off
#define PFC_OCP_B_HW_FLT_IS_ON      (1U == GpioDataRegs.GPADAT.bit.GPIO29)   ///< PFC Phase B OC Hardware Fault is on
#define PFC_OCP_B_HW_FLT_IS_OFF     (0U == GpioDataRegs.GPADAT.bit.GPIO29)   ///< PFC Phase B OC Hardware Fault is off
#define PFC_OCP_C_HW_FLT_IS_ON      (1U == GpioDataRegs.GPADAT.bit.GPIO28)   ///< PFC Phase C OC Hardware Fault is on
#define PFC_OCP_C_HW_FLT_IS_OFF     (0U == GpioDataRegs.GPADAT.bit.GPIO28)   ///< PFC Phase C OC Hardware Fault is off
//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef Uint16  (*P_FUNCTION_RETURN)(void);
typedef struct
{
    P_FUNCTION_RETURN pui_fun;
}ST_FLT_MOD_SEL;

typedef void  (*P_FUNCTION_NO_RETURN)(void);
typedef struct
{
    P_FUNCTION_NO_RETURN pv_fun;
}ST_FLT_TI_CALC;

typedef union
{
    Uint16 all;
    struct
    {
    /*00*/    Uint16 uiRsvd0       :1;
    /*01*/    Uint16 uiPfcStOff    :1;
    /*02*/    Uint16 uiRsvd2       :1;
    /*03*/    Uint16 uiPfcStChk    :1;
    /*04*/    Uint16 uiRsvd4       :1;
    /*05*/    Uint16 uiPfcStRdy    :1;
    /*06*/    Uint16 uiRsvd6       :1;
    /*07*/    Uint16 uiPfcStRun    :1;
    /*08*/    Uint16 uiRsvd8       :1;
    /*09*/    Uint16 uiRsvd9       :1;
    /*10*/    Uint16 uiRsvd10      :1;
    /*11*/    Uint16 uiRsvd11      :1;
    /*12*/    Uint16 uiRsvd12      :1;
    /*13*/    Uint16 uiRsvd13      :1;
    /*14*/    Uint16 uiRsvd14      :1;
    /*15*/    Uint16 uiRsvd15      :1;
    }bit;
}ST_FLT_SYS_STS_WORD;

typedef struct
{
      Uint16 uiCntr;                ///< external fault reset counter
      Uint16 uiStatus;              ///< external fault reset status
      Uint16 uiResetCmd;            ///< external fault reset command
}ST_EXTFLT_RESET;

typedef union
{
    Uint16 all;
    struct
    {
     /*00-03*/Uint16 uiFltBit         :4; ///< fault bit
     /*04-04*/Uint16 uiFlgLatch       :1; ///< latch flag
     /*05-07*/Uint16 uiExtFltCategory :3; ///< fault category: 0-internal fault, 1-grid fault, 2-external fault
     /*08-09*/Uint16 uiDetPerd        :2; ///< fault detect period, no use
     /*10-13*/Uint16 uiFltLvl         :4; ///< fault level
     /*14-15*/Uint16 uiADFltCategory  :2; ///< fault category: 0-digital fault, 1-analog fault
    }bit;
}ST_FLT_PROPERTY_WORD;

typedef union
{
    Uint16 all;
    struct
    {
     /*00-03*/Uint16 uiCMD_BitNum :4;  ///< digital fault command bit
     /*04-07*/Uint16 uiSTS_BitNum :4;  ///< digital fault status bit
     /*08-11*/Uint16 uiChkMod     :4;  ///< fault detect mode/method
     /*12-14*/Uint16 uiFRT_Fltlvl :3;  ///< FRT fault level, no use
     /*15-15*/Uint16 uiResvd      :1;  ///< reserved
    }bit;
}ST_FLT_MODE_WORD;

typedef struct
{
    ST_FLT_PROPERTY_WORD unProperty;  ///< fault property word
    ST_FLT_MODE_WORD    unFaultMode;  ///< fault mode word
    Uint16 uiDisDetByPfcSt;           ///< disable fault detection according by PFC status
    Uint16 uiMaskWord;                ///< fault mask word
    Uint16 *puiFaultWord;             ///< fault word pointer
    Uint16 *puiFaultStWord;           ///< fault status word pointer
    Uint16 uiFltWordBit;              ///< fault word bit number
    Uint16 uiFlgDisDet;               ///< Disable fault detect flag
    int16  siActualVal;               ///< actual value of detected object
    int16  siLmtVal;                  ///< limit value of detected object
    int16  siHysLmtVal;               ///< limit hysteresis value of detected object
    Uint16 uiHysVal;                  ///< hysteresis value
    Uint16 uiTiCfm;                   ///< fault confirm time
    Uint16 uiTiClr;                   ///< fault clear time
    Uint16 *puiCntr;                  ///< fault counter pointer
    Uint16 uiFlgFltOccur;             ///< fault occur flag

    Uint16 uiExtFltTypeBit;           ///< external fault bit type: 000:internal fault,010:grid fault,100:other external fault
    Uint16 uiFltLvlBit;               ///< fault level bit type
    Uint16 uiADFltType;               ///< fault type: 0:digital fault, 1:analog fault
    Uint16 uiFltDetType;              ///< fault detect type:0~9
    Uint16 uiDigFltCmdBit;            ///< digital fault command bit
    Uint16 uiDigFltStsBit;            ///< digital fault status bit

    Uint16 uiPfcStsWord;              ///< PFC status word
    Uint16 uiFltLvlCmbnTemp;              ///< fault level combine temperature value
    Uint16 uiFltLvlCmbn;              ///< fault level combine
}ST_SINGLE_FLT_TYPE;

typedef struct
{
    ST_PFC_DIAG stPrmExt;
    ST_SINGLE_FLT_TYPE stSingleFlt;      ///< Single fault detect struct

    Uint16 uiCntrChkStOT;    ///< PFC check state over-time counter
    Uint16 uiCntrGridOV;     ///< PFC grid over-voltage diagnosis counter
    Uint16 uiCntrGridOC;     ///< PFC grid over-current diagnosis counter
    Uint16 uiCntrCBCSet;     ///< PFC grid current CBC set counter
    Uint16 uiCntrCBCClr;     ///< PFC grid current CBC clear counter
    Uint16 uiFlgCBCSet;      ///< PFC off grid current CBC set
    Uint16 uiFlgV2LCBCRec;   ///< PFC off grid current CBC record flag
    Uint16 uiCntrV2LCBCSum;  ///< PFC off grid current CBC summer
    Uint16 uiTiV2LCBCDet;    ///< PFC off grid current CBC time
    Uint16 uiCntrAprtOL;     ///< PFC apparent power over-load counter
    Uint16 uiCntrActvOL;     ///< PFC active power over-load counter
    Uint16 uiCntrWiringDet;  ///< Wiring detection counter
    Uint16 uiCntrCurrSum;

    float32 ftIgMax;         ///< Grid current maximum
    float32 ftVgMax;         ///< Grid voltage maximum
}ST_PFC_DIAG_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PfcDiag_GridOV_Isr(void);
static void v_PfcDiag_GridOC_Isr(void);
static void v_PfcDiag_CBCOT_Isr(void);
static void v_PfcDiag_CBCOT_Jdg_Isr(void);
static void v_PfcDiag_FltMod_1ms(void);
static void v_PfcDiag_FltDet_1ms(void);

static void v_SingleFaultDet(Uint16 uiFltIndex,const FaultDataType *pstFltDataTab,Uint16 *uiFaultConter);

static Uint16 ui_InvldChkMod(void);
static Uint16 ui_HighrThanLmtMod(void);
static Uint16 ui_LowrThanLmtMod(void);
static Uint16 ui_StEquOneMod(void);
#if 0U
static Uint16 ui_CmdEquStMod(void);
static Uint16 ui_CmdUnEquStMod(void);
static Uint16 ui_StEquZeroMod(void);
static Uint16 ui_CmdEquOneMod(void);
static Uint16 ui_CmdEquZeroMod(void);

static Uint16 ui_AbsHighrThanLmtMod(void);
static Uint16 ui_AbsLowrThanLmtMod(void);
#endif
static void v_DigFltTiCntr(void);
static void v_AnFltTiCntr(void);
static void v_PfcDiag_StMac_Chk_100ms(void);
static void v_PfcDiag_WiringFlt_100ms(void);
static void v_PfcDiag_OL_Flt_100ms(void);

#if 1U == GRID_PHASE_NUMBER
static void v_PfcDiag_WiringFlt_1Pha_100ms(void);
#elif 2U == GRID_PHASE_NUMBER
static void v_PfcDiag_WiringFlt_2Pha_100ms(void);
#elif 3U == GRID_PHASE_NUMBER
static void v_PfcDiag_WiringFlt_3Pha_100ms(void);
#endif

#endif /* PFC_FILE_PFCDIAG_PFCDIAG_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
