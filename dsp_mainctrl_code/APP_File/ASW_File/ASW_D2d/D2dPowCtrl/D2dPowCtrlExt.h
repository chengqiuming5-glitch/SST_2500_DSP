//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dPowCtrlExt.h
 * @brief
 * The external header file of D2d power control is designed to realize power control strategy.
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
#ifndef D2DPOWCTRLEXT_H_
#define D2DPOWCTRLEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_D2d.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define D2D_POW_CTRL_DBG    0U    // Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    float32  ftD2dPwmValDutyPowCell;
    float32  ftD2dPwmPeriodPowCell;
    float32  ftD2dPwmDeadTimePowCell;
    Uint16  uiRunModPowCell;
}ST_D2D_POW_CTRL;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_D2D_POW_CTRL stD2dPowCtrl;

#if (1U == D2D_POW_CTRL_DBG)
extern ST_D2D_POW_CTRL stD2dPowCtrlDbg;
#endif

#endif /* D2DPOWCTRLEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
