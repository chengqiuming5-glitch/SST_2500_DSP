//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dStMacExt.h
 * @brief
 * The external header file of D2d state machine is designed to judge D2d running state.
 *
 * Module      :        \n
 * D2dStMac
 *
 * Unit        :        \n
 * null
 *
 * Module Task :        \n
 * v_D2dStMac_Init()    \n
 * v_D2dStMac_1ms()
 *
 * Unit Task   :        \n
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

#ifndef D2DSTMACEXT_H_
#define D2DSTMACEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_D2d.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define D2D_ST_MAC_DBG          0U       ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16  uiStD2dRun;                  ///< D2D running status
}ST_D2D_ST_MAC;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_D2D_ST_MAC stD2dStMac;         ///< Output signals of Module D2dStMac

#if (1U == D2D_ST_MAC_DBG)
extern ST_D2D_ST_MAC stD2dStMacDbg;      ///< Output signals of Module D2dStMac for debug
#endif

#endif /* D2DSTMACEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================

