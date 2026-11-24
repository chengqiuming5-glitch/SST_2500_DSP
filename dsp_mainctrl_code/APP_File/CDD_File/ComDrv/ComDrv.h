//==============================================================================================
//    File description
//==============================================================================================
/**@file         ComDrv.h
 * @brief
 * Header file of Com drive.
 *
 * Module      :                       \n
 * ComDrv
 *
 * Module Task :                       \n
 * v_ComDrv_Init()                     \n
 * v_ComDrv_TxOkFlg()                  \n
 * v_ComDrv_Rx()                       \n
 * v_ComDrv_Tx()                       \n
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

#ifndef COMDRV_H_
#define COMDRV_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "ComDrvExt.h"
#include "BSW_Cfg.h"
#include "ComExt.h"

//=====================================================
//   Local Macro Definition
//=====================================================

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_COM_DRV stPrmExt;    ///< Parameter to extern

}ST_COM_DRV_LOC;

//=====================================================
//   Local Function Declaration
//=====================================================
//Driver
static void v_ComDrv_Rx_Msg_Data(Uint16 *piData, Uint16 uiSize);
static void v_ComDrv_Tx_Msg_Data(Uint16 *piData, Uint16 uiSize);
static void v_ComDrv_Rx_Msg(Uint16 uiObjID, Uint16 uiMsgLen);
static void v_ComDrv_Tx_Msg(Uint16 uiObjID, Uint32 ulMsgID, Uint16 uiMsgLen, Uint16 *piMsgData);

#endif /* COMDRV_H_ */
//===========================================================================
// End of file.
//===========================================================================

