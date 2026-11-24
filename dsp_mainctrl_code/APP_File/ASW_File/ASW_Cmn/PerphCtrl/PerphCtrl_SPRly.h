//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl_SPRly.h
 * @brief
 * The header file of SP relay control is designed to realize SP relay function.
 *
 * Unit        :                       \n
 * Led                                 \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_SPRly_Init()            \n
 * v_PerphCtrl_SPRly_10ms()            \n
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

#ifndef PERPHCTRL_SPRLY_H_
#define PERPHCTRL_SPRLY_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PerphCtrl.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
/* SP Relay Macro Definition */
#define SP_SWITCH_MODE            2U        ///< 0U-according to charge require voltage; 1U-according to battery voltage; 2U-according to battery max voltage;
#define SP_SWITCH_ON_RUN_EN       0U        ///< 1U-Enable SP Relay Switch on Running

#ifndef _SIMULATION_NO_DSP_
#define VOLT_BATT_SP_RLY_ON       30.0f     ///< SP Relay Turn on Voltage
#define DURN_SP_RLY_ON            50U       ///< SP Relay Turn on duration;500ms
#define DURN_SP_RLY_SWT           50U       ///< SP Relay Switch duration;500ms
#else
#define VOLT_BATT_SP_RLY_ON       500.0f    ///< SP Relay Turn on Voltage
#define DURN_SP_RLY_ON            2U        ///< SP Relay Turn on duration; Simulation:20ms
#define DURN_SP_RLY_SWT           2U        ///< SP Relay Switch duration; Simulation:20ms
#endif

#define SP_RLY_SER_SWITCH_VOLT    (VOLT_BATT_SERIES_MIN + 10.0f)

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	ST_SPRLY stPrmExt;                                               ///< Parameter to extern

    Uint16  uiCmdSPRly;                                              ///< SP Relay command
    Uint16  uiCntrParlRly;                                           ///< Counter of Parallel relay
    Uint16  uiCntrSeriesRly;                                         ///< Counter of Series relay
    Uint16  uiCntrSPRlySwt;                                          ///< Counter of SP relay switch operation
}ST_SPRLY_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PerphCtrl_SPRly_Cmd_10ms(void);
static void v_PerphCtrl_SPRly_Ctrl_10ms(void);
static void v_PerphCtrl_SPRly_StSwt_10ms(void);
static void v_PerphCtrl_SPRly_PrmUpd(void);

#endif /* PERPHCTRL_SPRLY_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
