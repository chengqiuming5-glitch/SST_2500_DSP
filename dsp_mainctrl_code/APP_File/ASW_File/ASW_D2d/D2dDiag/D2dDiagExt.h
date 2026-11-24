//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dDiag.c
 * @brief
 * The external header file of D2D diagnosis is designed to realize D2d diagnosis function.
 *
 * Module      :                       \n
 * D2dDiag                             \n
 *
 * Unit        :                       \n
 * BattUV                              \n
 * BattUVAndSC                         \n
 * BattCurrImbal                       \n
 * BattVoltImbal                       \n
 * BldCtrl                             \n
 * SPRlyOT                             \n
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
 * * Unit Task   :                     \n
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

#ifndef D2DDIAGEXT_H_
#define D2DDIAGEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_D2d.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define D2D_DIAG_DBG                0U       ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16 uiFltCpu;             ///< D2D Cpu fault
    Uint16 uiFltCla;             ///< D2D Cla fault
    Uint16 uiFlgPwmEnJdgDone;    ///< PWM_EN state judgment done flag
    Uint16 uiFlgBldCmd;          ///< Bleeder resister command
}ST_D2D_DIAG;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_D2D_DIAG stD2dDiag;

#if (1U == D2D_DIAG_DBG)
extern ST_D2D_DIAG stD2dDiagDbg;
#endif

#endif /* D2DDIAGEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
