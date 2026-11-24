//==============================================================================================
//    File description
//==============================================================================================
/**@file         AdcDrv.h
 * @brief
 * Header file of ADC drive.
 *
 * Module      :                       \n
 * AdcDrv
 *
 * Module Task :                       \n
 * v_PerphDrv_Init()                   \n
 * v_PerphDrv_Isr()                    \n
 * v_PerphDrv_1ms()                    \n
 * v_PerphDrv_10ms()                   \n
 * v_PerphDrv_100ms()                  \n
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

#ifndef PERPHDRV_H_
#define PERPHDRV_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PerphCtrlExt.h"
#include "CDD_Drv.h"
#include "BSW_Cfg.h"
#include "ComExt.h"
#include "ComIfExt.h"
#include "PfcDiagExt.h"
#include "PfcStMacExt.h"
//==============================================================================================
//    Local Macro Definition
//==============================================================================================


//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
#if(2U == GRID_PHASE_NUMBER)
typedef struct
{
    Uint16 uiCntrRlyOn;             ///< PFC relay turn-on counter
}ST_PERPH_DRV_LOC;
#endif
//==============================================================================================
//    Local Function Declaration
//==============================================================================================
#ifndef SST_1250kW
static void v_PerphDrv_AcRly_Init(void);
#endif
static void v_PerphDrv_SPRly_Init(void);
static void v_PerphDrv_Bld_Init(void);
static void v_PerphDrv_Led_Init(void);
static void v_PerphDrv_V2LAuxPow_Init(void);
static void v_PerphDrv_V2LAuxPow(void);
static void v_PerphDrv_AcRly(void);
static void v_PerphDrv_SPRly(void);
static void v_PerphDrv_Bld(void);
static void v_PerphDrv_Led(void);

#endif /* PERPHDRV_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
