//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcStMac.c
 * @brief
 * The header file of PFC state machine module.
 *
 * Module      :                           \n
 * PfcStMac
 *
 * Unit        :                           \n
 *
 *
 *
 * Module Task :                           \n
 * v_PfcStMac_Init()                       \n
 * v_PfcStMac_1ms()                        \n
 *
 * Unit Task   :                           \n
 *
 *
 * Sub Unit Task   :                       \n
 *
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2024/03/19
 * @version
 * V1.0
 * @copyright
 * (c) Copyright 2000-2050, Wanbang New Energy Investment Co.,LTD..    \n
 *                            All Rights Reserved
 * @attention
 * MCU           : TMS320F2837xD           \n
 * Environment   : CCSv10.4.0
 * @note
 * <table>
 * <tr><th>Date        <th>Version         <th>Author       <th>Description
 * <tr><td>2024/03/19  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef PFC_FILE_PFCSTMAC_PFCSTMAC_H_
#define PFC_FILE_PFCSTMAC_PFCSTMAC_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcStMacExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "PowLimExt.h"
#include "OnOffGridSwtExt.h"
#include "PfcDataCalcExt.h"
#include "PfcGridCtrlExt.h"
#include "PfcDiagExt.h"
#include "PerdTskExt.h"
#include "D2dAdcExt.h"
#include "PrmDispExt.h"
#include "PfcAdcExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define PFC_RLY_OFF           0U    ///< All relay off state
#define PFC_RLY_ON            1U    ///< All relay on state
#define PFC_RLY_N_LINE_ON     2U    ///< N line relay control state

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_PFC_ST_MAC    stExt;

    Uint16 uiCntrBusChk;             ///< PFC check status bus voltage counter
    Uint16 uiCntrPfcRly;             ///< PFC relay turn-on counter
    Uint16 uiCntrBusRdy;             ///< PFC ready status bus voltage counter
    Uint16 uiFlgModChg;              ///< Run mode change flag
    Uint16 uiCntrModChg;             ///< Run mode change counter
    Uint16 uiCmdRly;                 ///< PFC control relay command
    float32 ftBusVoltRdyToRun;       ///< RDY_ST to RUN_ST bus voltage value
}ST_PFC_ST_MAC_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_PfcStMac_ST_1ms(void);

static void v_PfcStMac_Outp_1ms(void);
static void v_PfcStMac_Outp_ARM_1ms(void);
static void v_PfcStMac_Outp_Rly_1ms(void);

static void v_PfcStMac_ST_Flt_1ms(void);
static void v_PfcStMac_ST_Stb_1ms(void);
static void v_PfcStMac_ST_Chk_1ms(void);
static Uint16 v_PfcStMac_ST_Chk_GridCdn_1ms(void);
static void v_PfcStMac_ST_Chk_BusChk_1ms(void);
static void v_PfcStMac_ST_PwmEn_1ms(void);
static void v_PfcStMac_ST_NormRun_1ms(void);
static void v_PfcStMac_ST_PwmEn_RunOk_1ms(void);

#endif /* PFC_FILE_PFCSTMAC_PFCSTMAC_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
