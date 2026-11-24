//==============================================================================================
//    File description
//==============================================================================================
/**@file         EPwmDrv.h
 * @brief
 * Header file of EPwm drive.
 *
 * Module      :                       \n
 * EPwmDrv
 *
 * Module Task :                       \n
 * v_EPwmDrv_Init()                    \n
 * v_EPwmDrv_Isr()                     \n
 * v_EPwmDrv_1ms()                     \n
 * v_EPwmDrv_Pfc_TurnOff()             \n
 * v_EPwmDrv_Pfc_ClrTzFlg()            \n
 * v_EPwmDrv_D2d_TurnOff()             \n
 * v_EPwmDrv_D2d_ClrTzFlg()            \n
 *
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

#ifndef EPWMDRV_H_
#define EPWMDRV_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "EPwmDrvExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "PfcDiagExt.h"
#include "PfcDataCalcExt.h"
#include "PfcPowCtrlExt.h"
#include "PfcStMacExt.h"
#include "D2dDiagExt.h"
#include "D2dStMacExt.h"
//#include "D2dPowCtrlExt.h"
#include "GridStdData.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#if(2U == GRID_PHASE_NUMBER)
#define  LOCK_BALANCE_PWM()        GpioDataRegs.GPCCLEAR.bit.GPIO80 = 1U
#define  UNLOCK_BALANCE_PWM()      GpioDataRegs.GPCSET.bit.GPIO80   = 1U
#endif
#define  PERD_FRQ_JIT              3U

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
#ifndef SST_1250kW
typedef struct
{
    ST_EPWM_DRV stPrmExt;    ///< Parameter to extern

    Uint16 uiCntrCmp;        ///< PFC EPwm compare counter
    Uint16 uiDirModln;       ///< PFC modulation direction; 0-positive, 1-negative
    Uint16 uiCntrDriveEn;    ///< Pwm drive counter
    Uint16 uiCntrBalEn;      ///< Balance bridge pwm drive counter

    Uint16 uiPrdMaxFast;     ///< Fast bridge EPWM maximum jitter frequency period value
    Uint16 uiPrdMinFast;     ///< Fast bridge EPWM minimum jitter frequency period value
}ST_EPWM_DRV_LOC;
#endif
//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_EPwmDrv_Pfc_Isr(void);
static void v_EPwmDrv_D2d_Isr(void);
static void v_EPwmDrv_Pfc_PwmEn(void);
static void v_EPwmDrv_Pfc_PwmDis(void);
#if(1U != GRID_PHASE_NUMBER)
static void v_EPwmDrv_Bal_PwmEn(void);
static void v_EPwmDrv_Bal_PwmDis(void);
#else
static void v_EPwmDrv_PfcFrqJit_1ms(void);
#endif

#endif /* EPWMDRV_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
