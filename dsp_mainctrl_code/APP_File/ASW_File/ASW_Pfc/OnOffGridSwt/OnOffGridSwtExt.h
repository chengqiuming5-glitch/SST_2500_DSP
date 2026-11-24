//==============================================================================================
//    File description
//==============================================================================================
/**@file         OnOffGridSwtExt.h
 * @brief
 * The external header file of On&Off grid switch module.
 *
 * Module      :                           \n
 * OnOffGridSwt
 *
 * Unit        :                           \n
 *                                         \n
 *
 *
 * Module Task :                           \n
 * v_OnOffGridSwt_Init()                   \n
 * v_OnOffGridSwt_1ms()                    \n
 * v_OnOffGridSwt_Isr()
 *
 * Unit Task   :                           \n
 *                                         \n
 *
 * Sub Unit Task   :                       \n
 *
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2025/05/15
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
 * <tr><td>2025/05/15  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef ONOFFGRIDSWTEXT_H_
#define ONOFFGRIDSWTEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Pfc.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define ON_OFF_GRID_SWT_FLG_DBG    0U  ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16 uiFlgSwt;   ///< On&off grid switch flag
}ST_ON_OFF_GRID_SWT;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================

extern ST_ON_OFF_GRID_SWT stOnOffGridSwt;

#if (1U == ON_OFF_GRID_SWT_FLG_DBG)
extern ST_ON_OFF_GRID_SWT stOnOffGridSwtDbg;
#endif
#endif /* ONOFFGRIDSWT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
