//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dPowCtrl.h
 * @brief
 * The header file of D2d power control is designed to realize power control strategy.
 *
 * Module      :                       \n
 * D2dPowCtrl                          \n
 *
 * Unit        :                       \n
 * PRPrmUpd                            \n
 * PrmToCla                            \n
 * Cla                                 \n
 *
 * Module Task :                       \n
 * v_D2dPowCtrl_Init()                 \n
 * v_D2dPowCtrl_1ms()                  \n
 * v_D2dPowCtrl_10ms()                 \n
 * v_D2dPowCtrl_Isr()                 \n
 *
 * Unit Task   :                       \n
 * v_D2dPowCtrl_PrmToCla_Init()        \n
 * v_D2dPowCtrl_PrmToCla_1ms()         \n
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
#ifndef D2DPOWCTRL_H_
#define D2DPOWCTRL_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "D2dPowCtrlExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "CmnDiagExt.h"
#include "D2dStMacExt.h"
#include "PerphCtrlExt.h"
#include "PowLimExt.h"
#include "PfcDataCalcExt.h"
#include "PfcPowCtrlExt.h"
#include "PfcGridCtrlExt.h"
#include "D2dAdcExt.h"
#include "D2dDiagExt.h"
#include "D2dPowPreCtrlExt.h"
#include "CDD_Drv.h"
#include "PerdTskExt.h"
#include "GridStdData.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define CELL_D2D_MOD_POWER_OFF                         0x0U
#define CELL_D2D_MOD_CMD_CLEAR_REDUNDANT_FAULT         0x1U
#define CELL_D2D_MOD_DCHA_BURST                        0x2U
#define CELL_D2D_MOD_QUASI_CHRG                        0x3U
#define CELL_D2D_MOD_SYNC                              0x4U
#define CELL_D2D_MOD_CMD_CLEAR_SYS_FAULT               0x5U
#define CELL_D2D_MOD_CHRG                              0x6U
#define CELL_D2D_MOD_CHRG_BURST                        0x7U
#define CELL_D2D_MOD_QUASI_DCHA                        0x8U
#define CELL_D2D_MOD_DCHA                              0x9U
#define CELL_D2D_MOD_CELL_FPGA_UPDATE                  0xfU
//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_D2D_POW_CTRL stPrmExt;
}ST_D2D_POW_CTRL_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_D2dPowCtrl_Mod_1ms(void);
static void v_D2dPowCtrl_PrmUpd_1ms(void);

#endif /* D2DPOWCTRL_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
