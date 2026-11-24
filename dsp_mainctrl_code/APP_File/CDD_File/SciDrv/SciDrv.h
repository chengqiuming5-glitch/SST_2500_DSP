//==============================================================================================
//    File description
//==============================================================================================
/**@file         SciDrv.h
 * @brief
 * The header file of Spi Drive is designed to realize SCI communication.
 *
 * Module      :                       \n
 *
 *
 * Module Task :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2025/10/25
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
 * <tr><td>2025/10/25  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef SCIDRV_H_
#define SCIDRV_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "SciDrvExt.h"
#include "BSW_Cfg.h"
#include "ComExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#if(0U == COM_MODE)

#define SCI_FRAME_LEN        14U
#define SCI_DATA_LEN         10U
#define NUM_SCI_WHILE_OT     30000U
//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_COM_DRV stPrmExt;      ///< Parameter to extern
    Uint16  uiCntrRx;      ///< Counter of Receive data
    Uint16  uiFlgRxFrmOk;     ///< Flag of Receive a frame
    Uint16  uiRxBuf[14];      ///< Receive Buffer
    Uint16  uiTxBuf[14];      ///< Send Buffer
    Uint16  uiCntrRxEnd;   ///< Receive end counter
    Uint16  uiFlgTxReq;       ///< Flag of Send Require
    Uint16  uiCntrTx;      ///< Counter of send data
}ST_COM_DRV_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_SciDrv_Rx_Msg(Uint16 *puiData, Uint16 uiMsgLen);
static void v_SciDrv_Tx_Msg(Uint16 uiDataCmd, Uint16 uiMsgLen, Uint16 *puiMsgData);
static void v_ComDrv_Sci_Rx_Data(Uint16 *puiData, Uint16 uiSize);
static Uint16 v_ComDrv_Sci_Tx_Data(Uint16 *puiData, Uint16 uiSize);
static Uint16 ui_CRC16_Calc_Table(Uint16 *puiData, Uint16 uiLen);

#endif     // (0U == COM_MODE)

#endif /* SCIDRV_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
