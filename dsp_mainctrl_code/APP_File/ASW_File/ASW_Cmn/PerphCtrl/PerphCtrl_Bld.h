//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrl_Bld.h
 * @brief
 * The source file of bleed control is designed to realize bleed function.
 *
 * Unit        :                       \n
 * Led                                 \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_Bld_Init()              \n
 * v_PerphCtrl_Bld_1ms()               \n
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

#ifndef PERPHCTRL_BLD_H_
#define PERPHCTRL_BLD_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PerphCtrl.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define VOLT_BATT_BLD_ON               20.0f      ///< Bleed Resistor Turn on Voltage
#define VOLT_ERR_V2L_AUX_POW_BLD_ON    2.0f       ///< V2L Aux-power bleed resistor turn on voltage error

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	ST_BLD stPrmExt;              ///< Parameter to extern
	Uint16 uiCntr;                ///< Counter
	Uint16 uiFlgDoneV2LAuxPow;    ///< V2L Aux power done flag
}ST_BLD_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PerphCtrl_Bld_StMacStb_1ms(void);
static void v_PerphCtrl_Bld_StMacEn_1ms(void);
static void v_PerphCtrl_Bld_StMacV2L_1ms(void);

#endif /* PERPHCTRL_SPRLY_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
