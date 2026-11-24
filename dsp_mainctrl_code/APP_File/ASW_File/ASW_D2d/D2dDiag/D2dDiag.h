//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dDiag.h
 * @brief
 * The header file of D2D diagnosis is designed to realize D2d diagnosis function.
 *
 * Module      :                       \n
 * D2dDiag                             \n
 *
 * Unit        :                       \n
 * BattUV                              \n
 * BattUVAndSC                         \n
 * BattCurrImbal                       \n
 * BattVoltImbal                       \n
 * Bld                                 \n
 * SPRly                               \n
 * RstFlt                              \n
 * XInt4Isr                            \n
 * XInt5Isr                            \n
 * Epwm6Isr                            \n
 * Epwm7TzIsr                          \n
 *
 * Module Task :                       \n
 * v_D2dDiag_Init()                    \n
 * v_D2dDiag_1ms()                     \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BattUV_Init()             \n
 * v_D2dDiag_BattUV_1ms()              \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BattUVAndSC_Init()        \n
 * v_D2dDiag_BattUVAndSC_1ms()         \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BattCurrImbal_Init()      \n
 * v_D2dDiag_BattCurrImbal_1ms()       \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BattVoltImbal_Init()      \n
 * v_D2dDiag_BattVoltImbal_1ms()       \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_BldCtrl_1ms()             \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_Bld_Init()                \n
 * v_D2dDiag_Bld_1ms()                 \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_RstFlt_1ms()              \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_XInt_PriUpOC_Isr()        \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_XInt_PriDwnOC_Isr()       \n
 *
 * Unit Task   :                       \n
 * v_D2dDiag_EpwmTz_Hw_Isr()           \n
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

#ifndef D2DDIAG_H_
#define D2DDIAG_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "D2dDiagExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "D2dAdcExt.h"
#include "D2dStMacExt.h"
#include "PerphCtrlExt.h"
#include "PowLimExt.h"
#include "PfcPowCtrlExt.h"
#include "D2dPowPreCtrlExt.h"
//#include "D2dPowCtrlExt.h"
#include "CDD_Drv.h"
#include "PerdTskExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
/* Bus voltage under voltage */
#define DURN_DCHA_BUS_UV_SLOW               3000U     ///< Discharge Output UV Protection Number; ms

/* Battery voltage under voltage */
#define DURN_CHRG_BATT_UV                   150U      ///< Charge Output UV Protection Number; ms
#define DURN_BIDIR_BATT_UV                  3U        ///< Discharge Output UV Protection Number; ms

/* Battery current short current */
#define VOLT_BATT_TH_SC                     20.0f     ///< Output Short Circuit Voltage threshold value

/* Battery current imbalance */
#define CURR_BATT_IMBAL_DELTA               5.0f      ///< Current Imbalance Delta
#define DURN_BATT_CURR_IMBAL_MAX            1000.0f   ///< Imbalance protection Max Time
#define DURN_BATT_CURR_IMBAL_MIN            200.0f    ///< Imbalance protection Min Time;5.0f
#define COEFF_BATT_CURR_IMBAL               ((DURN_BATT_CURR_IMBAL_MAX - DURN_BATT_CURR_IMBAL_MIN) / CURR_BATT_IMBAL_DELTA)

/* Battery voltage imbalance */
#define VOLT_BATT_IMBAL_DELTA               20.0f     ///< Voltage Imbalance Delta
#define DURN_BATT_VOLT_IMBAL_MAX            1000.0f   ///< Imbalance protection Max Time
#define DURN_BATT_VOLT_IMBAL_MIN            200.0f    ///< Imbalance protection Min Time;5.0f
#define COEFF_BATT_VOLT_IMBAL               ((DURN_BATT_VOLT_IMBAL_MAX - DURN_BATT_VOLT_IMBAL_MIN) / VOLT_BATT_IMBAL_DELTA)

/* SP Relay */
#define DURN_SP_RLY_CMD_BLD                 500U      ///< SP Relay Turn on Bleed Resistor duration;5s
#define DURN_SP_RLY_OT                      1000U     ///< SP Relay OverTime duration;10s

/* Bleeder */
#define DURN_BLD_OT                         2500U     ///< Bleed Resistor OverTime duration;2000ms
#define DURN_BLD_VOLT_FLT                   500U      ///< Bleed voltage fault duration;500ms

/* D2D CMPSS Register Definition */
#if(1U == GRID_PHASE_NUMBER)
#define FLG_CMPSS_XBAR_BATT_OC_POS          (XbarRegs.XBARFLG1.bit.CMPSS8_CTRIPH)    ///< D2D battery positive OC CMPSS configuration
#define FLG_CMPSS_XBAR_BATT_OC_NEG          (XbarRegs.XBARFLG1.bit.CMPSS8_CTRIPL)    ///< D2D battery negative OC CMPSS configuration
#elif (2U == GRID_PHASE_NUMBER)
#define FLG_CMPSS_XBAR_BATT_OC_POS          (XbarRegs.XBARFLG1.bit.CMPSS3_CTRIPH)    ///< D2D battery positive OC CMPSS configuration
#define FLG_CMPSS_XBAR_BATT_OC_NEG          (XbarRegs.XBARFLG1.bit.CMPSS3_CTRIPL)    ///< D2D battery negative OC CMPSS configuration
#elif (3U == GRID_PHASE_NUMBER)
#define FLG_CMPSS_XBAR_BATT_OC_POS          (XbarRegs.XBARFLG1.bit.CMPSS6_CTRIPH)    ///< D2D battery positive OC CMPSS configuration
#define FLG_CMPSS_XBAR_BATT_OC_NEG          (XbarRegs.XBARFLG1.bit.CMPSS6_CTRIPL)    ///< D2D battery negative OC CMPSS configuration
#endif

/* D2D Hardware Fault Definition */
#if(1U == GRID_PHASE_NUMBER)
#define D2D_SUM_HW_FLT_IS_ON                (1U == GpioDataRegs.GPBDAT.bit.GPIO54)   ///< D2D Sum Hardware Fault is on
#define D2D_SUM_HW_FLT_IS_OFF               (0U == GpioDataRegs.GPBDAT.bit.GPIO54)   ///< D2D Sum Hardware Fault is off
#define D2D_OUT_OV_HW_FLT_IS_ON             (1U == GpioDataRegs.GPBDAT.bit.GPIO56)   ///< D2D Output OV Hardware Fault is on
#define D2D_OUT_OV_HW_FLT_IS_OFF            (0U == GpioDataRegs.GPBDAT.bit.GPIO56)   ///< D2D Output OV Hardware Fault is off
#define D2D_OUT_DN_OV_HW_FLT_IS_ON          (1U == GpioDataRegs.GPBDAT.bit.GPIO55)   ///< D2D Output Down OV Hardware Fault is on
#define D2D_OUT_DN_OV_HW_FLT_IS_OFF         (0U == GpioDataRegs.GPBDAT.bit.GPIO55)   ///< D2D Output Down OV Hardware Fault is off
#define D2D_POS_OUT_OC_HW_FLT_IS_ON         (1U == GpioDataRegs.GPBDAT.bit.GPIO57)   ///< D2D Positive Output OC Hardware Fault is on
#define D2D_POS_OUT_OC_HW_FLT_IS_OFF        (0U == GpioDataRegs.GPBDAT.bit.GPIO57)   ///< D2D Positive Output OC Hardware Fault is off
#define D2D_NEG_OUT_OC_HW_FLT_IS_ON         (1U == GpioDataRegs.GPBDAT.bit.GPIO58)   ///< D2D Negative Output OC Hardware Fault is on
#define D2D_NEG_OUT_OC_HW_FLT_IS_OFF        (0U == GpioDataRegs.GPBDAT.bit.GPIO58)   ///< D2D Negative Output OC Hardware Fault is off
#define D2D_PRI_UP_OC_HW_FLT_IS_ON          (1U == GpioDataRegs.GPADAT.bit.GPIO22)   ///< D2D Primary Up OC Hardware Fault is on
#define D2D_PRI_UP_OC_HW_FLT_IS_OFF         (0U == GpioDataRegs.GPADAT.bit.GPIO22)   ///< D2D Primary Up OC Hardware Fault is off
#define D2D_PRI_DN_OC_HW_FLT_IS_ON          (1U == GpioDataRegs.GPADAT.bit.GPIO23)   ///< D2D Primary Down OC Hardware Fault is on
#define D2D_PRI_DN_OC_HW_FLT_IS_OFF         (0U == GpioDataRegs.GPADAT.bit.GPIO23)   ///< D2D Primary Down OC Hardware Fault is off
#define D2D_BUS_OV_HW_FLT_IS_ON             (1U == GpioDataRegs.GPADAT.bit.GPIO27)   ///< D2D Bus OV Hardware Fault is on
#define D2D_BUS_OV_HW_FLT_IS_OFF            (0U == GpioDataRegs.GPADAT.bit.GPIO27)   ///< D2D Bus OV Hardware Fault is off
#elif (2U == GRID_PHASE_NUMBER)
#define D2D_SUM_HW_FLT_IS_ON                (1U == GpioDataRegs.GPBDAT.bit.GPIO58)   ///< D2D Sum Hardware Fault is on
#define D2D_SUM_HW_FLT_IS_OFF               (0U == GpioDataRegs.GPBDAT.bit.GPIO58)   ///< D2D Sum Hardware Fault is off
#define D2D_OUT_OV_HW_FLT_IS_ON             (1U == GpioDataRegs.GPADAT.bit.GPIO28)   ///< D2D Output OV Hardware Fault is on
#define D2D_OUT_OV_HW_FLT_IS_OFF            (0U == GpioDataRegs.GPADAT.bit.GPIO28)   ///< D2D Output OV Hardware Fault is off
#define D2D_OUT_DN_OV_HW_FLT_IS_ON          (1U == GpioDataRegs.GPADAT.bit.GPIO29)   ///< D2D Output Down OV Hardware Fault is on
#define D2D_OUT_DN_OV_HW_FLT_IS_OFF         (0U == GpioDataRegs.GPADAT.bit.GPIO29)   ///< D2D Output Down OV Hardware Fault is off
#define D2D_POS_OUT_OC_HW_FLT_IS_ON         (1U == GpioDataRegs.GPADAT.bit.GPIO30)   ///< D2D Positive Output OC Hardware Fault is on
#define D2D_POS_OUT_OC_HW_FLT_IS_OFF        (0U == GpioDataRegs.GPADAT.bit.GPIO30)   ///< D2D Positive Output OC Hardware Fault is off
#define D2D_NEG_OUT_OC_HW_FLT_IS_ON         (1U == GpioDataRegs.GPADAT.bit.GPIO31)   ///< D2D Negative Output OC Hardware Fault is on
#define D2D_NEG_OUT_OC_HW_FLT_IS_OFF        (0U == GpioDataRegs.GPADAT.bit.GPIO31)   ///< D2D Negative Output OC Hardware Fault is off
#define D2D_PRI_UP_OC_HW_FLT_IS_ON          (1U == GpioDataRegs.GPBDAT.bit.GPIO53)   ///< D2D Primary LLC OC Hardware Fault is on
#define D2D_PRI_UP_OC_HW_FLT_IS_OFF         (0U == GpioDataRegs.GPBDAT.bit.GPIO53)   ///< D2D Primary LLC OC Hardware Fault is off
#define D2D_PRI_DN_OC_HW_FLT_IS_ON          (1U == GpioDataRegs.GPBDAT.bit.GPIO52)   ///< D2D Secondary LLC OC Hardware Fault is on
#define D2D_PRI_DN_OC_HW_FLT_IS_OFF         (0U == GpioDataRegs.GPBDAT.bit.GPIO52)   ///< D2D Secondary LLC OC Hardware Fault is off
#define D2D_BUS_L_OV_HW_FLT_IS_ON           (1U == GpioDataRegs.GPCDAT.bit.GPIO92)   ///< D2D Bus_L OV Hardware Fault is on
#define D2D_BUS_L_OV_HW_FLT_IS_OFF          (0U == GpioDataRegs.GPCDAT.bit.GPIO92)   ///< D2D Bus_L OV Hardware Fault is off
#define D2D_BUS_H_OV_HW_FLT_IS_ON           (1U == GpioDataRegs.GPCDAT.bit.GPIO93)   ///< D2D Bus_H OV Hardware Fault is on
#define D2D_BUS_H_OV_HW_FLT_IS_OFF          (0U == GpioDataRegs.GPCDAT.bit.GPIO93)   ///< D2D Bus_H OV Hardware Fault is off
#elif (3U == GRID_PHASE_NUMBER)
#define D2D_SUM_HW_FLT_IS_ON                (1U == GpioDataRegs.GPCDAT.bit.GPIO94)   ///< D2D Sum Hardware Fault is on
#define D2D_SUM_HW_FLT_IS_OFF               (0U == GpioDataRegs.GPCDAT.bit.GPIO94)   ///< D2D Sum Hardware Fault is off
#define D2D_OUT_OV_HW_FLT_IS_ON             (0U == GpioDataRegs.GPADAT.bit.GPIO24)   ///< D2D Output OV Hardware Fault is on
#define D2D_OUT_OV_HW_FLT_IS_OFF            (1U == GpioDataRegs.GPADAT.bit.GPIO24)   ///< D2D Output OV Hardware Fault is off
#define D2D_POS_OUT_OC_HW_FLT_IS_ON         (0U == GpioDataRegs.GPADAT.bit.GPIO30)   ///< D2D Positive Output OC Hardware Fault is on
#define D2D_POS_OUT_OC_HW_FLT_IS_OFF        (1U == GpioDataRegs.GPADAT.bit.GPIO30)   ///< D2D Positive Output OC Hardware Fault is off
#define D2D_NEG_OUT_OC_HW_FLT_IS_ON         (0U == GpioDataRegs.GPADAT.bit.GPIO25)   ///< D2D Negative Output OC Hardware Fault is on
#define D2D_NEG_OUT_OC_HW_FLT_IS_OFF        (1U == GpioDataRegs.GPADAT.bit.GPIO25)   ///< D2D Negative Output OC Hardware Fault is off
#define D2D_PRI_UP_OC_HW_FLT_IS_ON          (0U == GpioDataRegs.GPADAT.bit.GPIO27)   ///< D2D Primary OC Hardware Fault is on
#define D2D_PRI_UP_OC_HW_FLT_IS_OFF         (1U == GpioDataRegs.GPADAT.bit.GPIO27)   ///< D2D Primary OC Hardware Fault is off
#define D2D_BUS_OV_HW_FLT_IS_ON             0U                                       ///< D2D Bus OV Hardware Fault is on
#define D2D_BUS_OV_HW_FLT_IS_OFF                                                     ///< D2D Bus OV Hardware Fault is off
#endif
//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	ST_D2D_DIAG stPrmExt;           ///< Parameter to extern

	Uint16 uiCntrBusUV;             ///< Bus UV counter
	Uint16 uiDurnBattUV;            ///< Battery UV number
	Uint16 uiStBattUV;              ///< Battery UV start state
	Uint16 uiCntrBattUV;            ///< Battery UV counter
    Uint16 uiFlgBattUVAndSCEn;      ///< Battery UV and SC flag
	Uint16 uiCntrBattCurrImbal;     ///< Battery imbalance current counter
	Uint16 uiCntrBattVoltImbal;     ///< Battery imbalance voltage counter
	Uint16 uiCntrSPRlyOT;           ///< SP relay overtime counter
	Uint16 uiCntrBldOT;             ///< Bleeder resister overtime counter
    Uint16 uiCntrBldVoltFlt;        ///< Bleeder voltage fault counter
}ST_D2D_DIAG_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_D2dDiag_BusUV_Init(void);
static void v_D2dDiag_BusUV_1ms(void);

static void v_D2dDiag_BattUV_Init(void);
static void v_D2dDiag_BattUV_1ms(void);

static void v_D2dDiag_BattUVAndSC_Init(void);
static void v_D2dDiag_BattUVAndSC_1ms(void);

static void v_D2dDiag_BattCurrImbal_Init(void);
static void v_D2dDiag_BattCurrImbal_1ms(void);

static void v_D2dDiag_BattVoltImbal_Init(void);
static void v_D2dDiag_BattVoltImbal_1ms(void);

static void v_D2dDiag_BldCtrl_1ms(void);

static void v_D2dDiag_Bld_Init(void);
static void v_D2dDiag_Bld_1ms(void);

static void v_D2dDiag_SPRly_Init(void);
static void v_D2dDiag_SPRly_10ms(void);

static void v_D2dDiag_RstFlt_1ms(void);
static void v_D2dDiag_HwFltDet(void);

#endif /* D2DDIAG_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
