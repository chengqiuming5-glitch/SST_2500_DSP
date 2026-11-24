//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl_AcRly.h
 * @brief
 * The source file of AC relay control is designed to realize function.
 *
 * Unit        :                       \n
 * AC relay                            \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_AcRly_Init()            \n
 * v_PerphCtrl_AcRly_10ms()             \n
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

#ifndef PERPHCTRL_ACRLY_H_
#define PERPHCTRL_ACRLY_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PerphCtrl.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define STB_AC_RLY_ST_MAC              0U         ///< AC relay state machine Standby state
#define EN_AC_RLY_ST_MAC               1U         ///< AC relay state machine Enable state
#define PWM_AC_RLY_ST_MAC              2U         ///< AC relay state machine PWM state

#ifndef _SIMULATION_NO_DSP_
#define DURN_ACRLY_EN_ST               100U       ///< AC relay state Enable duration; 100U-1s
#else
#define DURN_ACRLY_EN_ST               1U         ///< AC relay state Enable duration;
#endif

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_ACRLY stPrmExt;     ///< Parameter to extern

    Uint16 uiCntrEn;       ///< Enable state counter
}ST_ACRLY_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PerphCtrl_AcRly_StMacStb_10ms(void);
static void v_PerphCtrl_AcRly_StMacEn_10ms(void);
static void v_PerphCtrl_AcRly_StMacPwm_10ms(void);

#endif /* PERPHCTRL_ACRLY_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
