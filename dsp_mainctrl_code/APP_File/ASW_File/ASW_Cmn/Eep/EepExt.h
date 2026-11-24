/**
*******************************************************************************
**************************
*                                       Application source files
*                                          EEpromPara function
*
*
*                     (c) Copyright 2010-2040, Wanbang New Energy Investment Co.,LTD.
*                                        All Rights Reserved
*
*
* Name       : EepExt.h
* Version    : v100
* Author     : sdd
*
* Aim        : TMS320F2837xD
* Mode       : LARG_MODEL
* Environment: CCS v10.4
* Description: Main loop function
;**--------------------------------------------------------------------------
----------------------------
;** Created by:
;** Created date:   07:31:2023   11:15
** Version:  v100
;** Descriptions:   Initial version
;**
;**--------------------------------------------------------------------------
----------------------------
;** Modified by:
;** Modified date:
;** Version:
;** Descriptions:
;**

*******************************************************************************
**************************
*/
/**
* @file            EepExt.h
* @brief           EepExt
* @details         Control parameters are saved to EEPROM
* @author         sdd
* @date              2023-7-31
* @version        V1.0
* @copyright     (c) Copyright 2010-2040, Wanbang New Energy Investment Co.,LTD.
*                                 All Rights Reserved
*******************************************************************************
***
* @attention
* CPU  :DSP2837xD \n
* Environment:    CCS v10.4
* @par update record :
* <table>
* <tr><th>Date         <th>Version        <th>Author        <th>Description
* <tr><td>2023/07/23   <td>1.0          <td>sdd           <td>Initial version
* </table>
*
*******************************************************************************
***
*/
#ifndef EEPEXT_H_
#define EEPEXT_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "CDD_Drv.h"
#include "ASW_Cmn.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define EEP_DBG    					0U    ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16  uiCmd;
    Uint16  uiNumSaved;
    Uint16  uiIndexPrm[NUM_EEPROM_DATA_QUE_OPER];
}ST_CMD_PRM;

typedef union
{
     Uint16 all;
     struct
     {
 /*bit00*/   Uint16 uiErrWr              :1;
 /*bit01*/   Uint16 uiErrRead            :1;
 /*bit02*/   Uint16 uiErrAddrOver        :1;
 /*bit03*/   Uint16 uiErrInit            :1;
 /*bit04*/   Uint16 uiErrEep             :1;
 /*bit05*/   Uint16 uiErrIniFirstWr      :1;
 /*bit06*/   Uint16 uiErrIniSecWr        :1;
 /*bit07*/   Uint16 uiErrIniThrdWr       :1;
 /*bit08*/   Uint16 uiResvd8             :1;
 /*bit09*/   Uint16 uiErrMaiFirstRead    :1;
 /*bit10*/   Uint16 uiErrMaiSecRead      :1;
 /*bit11*/   Uint16 uiErrMaiThrdRead     :1;
 /*bit12*/   Uint16 uiResvd12            :1;
 /*bit13*/   Uint16 uiErrFirstRead       :1;
 /*bit14*/   Uint16 uiErrSecRead         :1;
 /*bit15*/   Uint16 uiErrThrdRead        :1;
     }bit;
}ST_EEPROM_ERR;

typedef struct
{
    Uint16 uiStdGridSel;    ///< Grid standard select

    ST_CMD_PRM    stCmdPrm;
    ST_EEPROM_ERR stEepErr;
    ST_EEP_DATA_QUE   stQuePrmChg;
}ST_EEP;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_EEP stEep;                  ///< Eep global struct

#if (1U == EEP_DBG)
extern ST_EEP stEepDbg;               ///< Eep debug global struct
#endif

#endif /* EEPEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
