//==============================================================================================
//    File description
//==============================================================================================
/**@file         PerphCtrlExt.h
 * @brief
 * The external header file of peripheral control is designed to realize peripheral function.
 *
 * Module      :                       \n
 * PerphCtrl
 *
 * Unit        :                       \n
 * SPRly                               \n
 * Bld                                 \n
 * Led                                 \n
 * V2LAuxPow                           \n
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


#ifndef PERPHCTRLEXT_H_
#define PERPHCTRLEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define PERPH_CTRL_DBG                0U         ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16 uiStMac;                              ///< AC relay state machine
    Uint16 uiCmpPwm;                             ///< PWM CMP
}ST_ACRLY;

typedef struct
{
	Uint16 uiCmd;                                ///< Command of SP Relay 
    Uint16 uiSt;                                 ///< State of SP Relay 
    Uint16 uiFlgOk;                              ///< Flag of SP Relay OK
}ST_SPRLY;

typedef struct
{
	Uint16 uiStMac;                              ///< Bleed state machine
	Uint16 uiCmd;                                ///< Bleed command
	Uint16 uiFlgDone;                            ///< Bleed done flag
	float32 ftVoltBattRec;                       ///< Battery voltage record
}ST_BLD;

typedef struct
{
    Uint16 uiCmdDspRun;                          ///< Led command based DSP run
    Uint16 uiCmdPfcRunSt;                        ///< Led command based PFC run state
	Uint16 uiCmdD2dRunSt;                        ///< Led command based D2d run state 
}ST_LED;

typedef struct
{
    Uint16 uiCmd;                                ///< V2L aux power command
    Uint16 uiFlgEn;                              ///< V2L aux power enable
}ST_V2L_AUX_POW;

typedef struct
{
    ST_ACRLY stAcRly;
    ST_SPRLY stSPRly;
	ST_BLD   stBld;
	ST_LED   stLed;
	ST_V2L_AUX_POW stV2LAuxPow;
}ST_PERPH_CTRL;
//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PERPH_CTRL stPerphCtrl;

#if (1U == PERPH_CTRL_DBG)
extern ST_PERPH_CTRL stPerphCtrlDbg;
#endif

#endif /* PERPHCTRLEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
