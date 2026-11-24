//==============================================================================================
//    File description
//==============================================================================================
/**@file         main.h
 * @brief
 * The header file of main is designed to call main function C Source File.
 *
 * Module      :                 \n
 * AppInit
 *
 * Unit        :                 \n
 * null
 *
 * Unit Task   :                 \n
 * v_AppInit()                   \n
 * ServiceDog()                  \n
 * v_ComDrv_Rx()                 \n
 * v_Com_Rx()                    \n
 * v_ComDrv_TxOkFlg()            \n
 * v_Com_Tx()                    \n
 * v_ComDrv_Tx()                 \n
 * v_PerdTsk_MainLoop()          \n
 *
 * Unit Task   :                 \n
 * null
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

#ifndef INCLUDE_USER_INCLUDE_MAIN_H_
#define INCLUDE_USER_INCLUDE_MAIN_H_
//=====================================================
//    Include Header Files
//=====================================================
#include "SDL.h"
#include "CDD_Drv.h"
#include "ASW_Cmn.h"
#include "ComExt.h"

//=====================================================
//    Macro Definition
//=====================================================


//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================
/* APP property typedef */
typedef struct
{
    Uint16 uiCodeFlg;    // APP Program existence flag
    Uint16 uiSwVer;    // APP software version
}ST_APP_PROPERTY;

//=====================================================
//    Variable Declaration
//=====================================================
extern const ST_APP_PROPERTY stAppProperty;
extern const Uint16 g_uiMdlProd;

//=====================================================
//    Function Declaration
//=====================================================
extern void ServiceDog(void);

#endif /* INCLUDE_USER_INCLUDE_MAIN_H_ */
//===========================================================================
// End of file.
//===========================================================================
