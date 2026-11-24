//==============================================================================================
//    File description
//==============================================================================================
/**@file         D2dStMac.h
 * @brief
 * The header file of D2d state machine is designed to judge D2d running state.
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

#ifndef D2DSTMAC_H_
#define D2DSTMAC_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "D2dStMacExt.h"

#include "EPwmDrvExt.h"
#include "ComIfExt.h"
#include "D2dDiagExt.h"
#include "PerphCtrlExt.h"
#include "D2dPowPreCtrlExt.h"
//#include "D2dPowCtrlExt.h"
#include "PerdTskExt.h"
#include "EmifExt.h"
#include "PrmDispExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================


//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	ST_D2D_ST_MAC stPrmExt;      // Parameter to extern
}ST_D2D_ST_MAC_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_D2dStMac_Flt_1ms(void);
static void v_D2dStMac_Stb_1ms(void);
static void v_D2dStMac_PwmEnPre_1ms(void);
static void v_D2dStMac_PwmEn_1ms(void);
static void v_D2dStMac_SoftStrt_1ms(void);
static void v_D2dStMac_NormRun_1ms(void);

static Uint16 ui_D2dStMac_PwmEn_CellCheck(void);

#endif /* D2DSTMAC_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
