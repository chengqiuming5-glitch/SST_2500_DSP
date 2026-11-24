//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrlExt.h
 * @brief
 * The header file of peripheral control is designed to realize peripheral function.
 *
 * Module      :                       \n
 * PerphCtrl
 *
 * Unit        :                       \n
 * SPRly                               \n
 * Bld                                 \n
 * Led                                 \n
 * V2LAuxPow
 *
 * Module Task :                       \n
 * v_PerphCtrl_Init()                  \n
 * v_PerphCtrl_1ms()                   \n
 * v_PerphCtrl_10ms()                  \n
 * v_PerphCtrl_100ms()                 \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_SPRly_Init()            \n
 * v_PerphCtrl_SPRly_10ms()            \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_Bld_Init()              \n
 * v_PerphCtrl_Bld_1ms()               \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_Led_Init()              \n
 * v_PerphCtrl_Led_100ms()             \n
 *
 * Unit Task   :                       \n
 * v_PerphCtrl_V2LAuxPow_Init()        \n
 * v_PerphCtrl_V2LAuxPow_1ms()         \n
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

#ifndef PERPHCTRL_H_
#define PERPHCTRL_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PerphCtrlExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "D2dAdcExt.h"
#include "D2dDiagExt.h"
#include "PfcStMacExt.h"
#include "D2dStMacExt.h"
#include "PerdTskExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================

//==============================================================================================
//    Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_PERPH_CTRL stPrmExt;                                        ///< Parameter to extern

}ST_PERPH_CTRL_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================


#endif /* PERPHCTRL_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
