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
* Name       : Eep.h
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
;** Descriptions: 	Initial version
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
* @file            Eep.h
* @brief	       Eep
* @details	       Control parameters are saved to EEPROM 
* @author	      sdd
* @date 	         2023-7-31
* @version	      V1.0
* @copyright	 (c) Copyright 2010-2040, Wanbang New Energy Investment Co.,LTD.
*                                 All Rights Reserved
*******************************************************************************
***
* @attention
* CPU  :DSP2837xD \n
* Environment:    CCS v10.4
* @par update record :
* <table>
* <tr><th>Date		   <th>Version        <th>Author	    <th>Description
* <tr><td>2023/07/23   <td>1.0	        <td>sdd           <td>Initial version
* </table>
*
*******************************************************************************
***
*/
#ifndef EEP_H_
#define EEP_H_

/*
*******************************************************************************
**************************
* @biref                      Include files
*******************************************************************************
**************************
*/
#include "EepExt.h"
#include "ComExt.h"
#include "ComIfExt.h"
#include "PfcStMacExt.h"
#include "SDL.h"
#include "GridStdData.h"
#include "DSPParaData.h"

/*
*******************************************************************************
**************************
*                       Local macro Defines (#define)
*******************************************************************************
**************************
*/
#define WIRTEPARA_BUFF_SIZE              30U

#define DATA_TYPE_MASK                   (Uint16)((Uint16)7U<<6)
#define DATA_NONERASE_FLAG               (Uint16)((Uint16)1U<<9)

#define DATA_INT16                       (TYPE_INT16<<6)
#define DATA_UINT16                      (TYPE_UINT16<<6)
#define DATA_INT32                       (TYPE_INT32<<6)
#define DATA_UINT32                      (TYPE_UINT32<<6)
#define DATA_FLOAT32                     (TYPE_FLOAT32<<6)
#define DATA_STRING                      (TYPE_STRING<<6)

#define NUM_WORD_16BIT                   1U                  ///< Word number of 16 bit data
#define NUM_WORD_32BIT                   2U                  ///< Word number of 32 bit data
#define NUM_WORD_STRING                  20U                 ///< Word number of string data

#define EEPROM_SAVED                     0xAAAAU
#define NONERASED_SAVED                  0xAEAEU

#define GET_PARA_EEPROM_SLAVE_ADDR(x)      (sFuncCode[MasterSaveEEPromIndex[(x)]].MasterSaveAddr)
#define EEPROM_GET_PARA_TYPE(x)            (sFuncCode[MasterSaveEEPromIndex[(x)]].uiModifyAndDataType & DATA_TYPE_MASK)
#define GET_PARA_ADDR(x)                   (sFuncCode[MasterSaveEEPromIndex[(x)]].ParaAddr)

#define GET_NONERASE_EEPROM_SLAVE_ADDR(x)  (sFuncCode[MasterNonEraseEEPromIndex[(x)]].MasterSaveAddr)
#define EEPROM_GET_NONERASE_TYPE(x)        (sFuncCode[MasterNonEraseEEPromIndex[(x)]].uiModifyAndDataType & DATA_TYPE_MASK)
#define GET_NONERASE_ADDR(x)               (sFuncCode[MasterNonEraseEEPromIndex[(x)]].ParaAddr)

#define GET_DATA_TYPE(x)                   (sFuncCode[(x)].uiModifyAndDataType & DATA_TYPE_MASK)
#define GET_DATA_EEPROM_ADDR(x)            (sFuncCode[(x)].MasterSaveAddr)

/** Parameter recovery status*/
#define RCV_FIRST_WRITE                     0U
#define RCV_SECOND_WRITE                    1U
#define RCV_THIRD_WRITE                     2U
#define RCV_END_WRITE                       3U

/** Parameter processing status*/
#define WAIT_CHECK                          0U
#define READ_EEPROM                         1U
#define WRITE_EEPROM                        2U

/** Parameter write 3 times status*/
#define FIRST_WRITE                         0U
#define FIRST_READ                          1U
#define SECOND_WRITE                        2U
#define SECOND_READ                         3U
#define THIRD_WRITE                         4U
#define THIRD_READ                          5U

/** Sector size of eeprom*/
#define PARA_SAVED_ADDR                     0U
#define PARA_VER_ADDR                       4U
#define SOFT_VER_ADDR                       8U
#if(2U == GRID_PHASE_NUMBER)
#define PARA_NONERASE_ADDR                  24U
#else
#define PARA_NONERASE_ADDR                  12U
#endif

#define I2C_SLAVE_ADDR                      0x50U
#define I2C_EEPROM_HIGH_ADDR                0x00
#define I2C_EEPROM_LOW_ADDR                 0x00

/** Eeprom data first address*/
#define I2C_EEPROM_ADDR                     100U
/** Gaps between multiple stored data areas*/
#if(2U == GRID_PHASE_NUMBER)
#define I2C_DATA_GAP                        20U
#else
#define I2C_DATA_GAP                        100U
#endif
/** the first address for AD parameter*/
#define I2C_EEPROM_NONERASE_ADDR            10000U
/** General parameter Maximum size*/
#define EEPROM_MAX_SAVE_NUM                 1900U
/** AD parameter Maximum size*/
#define EEPROM_NONERASE_MAX_SAVE_NUM        500U
/** Store 3 times, the address offset of the second pass compared with the first pass*/
#define I2C_EEPROM_ADDR1                    (EEPROM_MAX_SAVE_NUM + I2C_DATA_GAP)
/** Store 3 times, the address offset of the third pass compared with the second pass*/
#define I2C_EEPROM_ADDR2                    (EEPROM_MAX_SAVE_NUM + I2C_EEPROM_ADDR1 + I2C_DATA_GAP)
/** General parameter Maximum address*/
#define PARA_SAVE_END_ADDR                  (I2C_EEPROM_ADDR + EEPROM_MAX_SAVE_NUM + I2C_EEPROM_ADDR2)
/** AD parameter store 3 times, the address offset of the second pass compared with the first pass*/
#define I2C_EEPROM_NONERASE_ADDR1           (EEPROM_NONERASE_MAX_SAVE_NUM + I2C_DATA_GAP)
/** AD parameter store 3 times, the address offset of the third pass compared with the second pass*/
#define I2C_EEPROM_NONERASE_ADDR2           (EEPROM_NONERASE_MAX_SAVE_NUM + I2C_EEPROM_NONERASE_ADDR1 + I2C_DATA_GAP)
/** AD parameter Maximum address*/
#define PARA_SAVE_END_NONERASE_ADDR         (I2C_EEPROM_NONERASE_ADDR + EEPROM_NONERASE_MAX_SAVE_NUM + I2C_EEPROM_NONERASE_ADDR2)
/** I2C status definition of read and write operations in non-dead mode*/
#define I2C_BUS_FREE                        0U    ///<  Waiting state: indicates that the I2C is idle. Read and write operations can be performed*/
#define I2C_BUS_ON_PARA                     1U    ///<  Parameter read and write status: indicates that the I2C performs parameter read and write operations*/
#define I2C_BUS_ON_RECORD_SAVE              2U    ///<  Data record storage status: indicates that the I2C writes data to the EEPROM*/
#define I2C_BUS_ON_RECORD_READ              3U    ///<  Data record storage status: indicates that I2C reads EEPROM data*/

/* I2C status */
#define WAIT_CMD                            0U    ///< Wait
#define SAVE_ERASABLE_PARA                  1U    ///< Save erasable parameter
#define SAVE_NONERASE_PARA                  2U    ///< Save non-erasable parameter
#define RELOAD_ERASABLE_PARA                3U    ///< Initialize erasable parameter
#define RELOAD_NONERASE_PARA                4U    ///< Initialize AD parameter
#define RELOAD_V2G_PARA                     5U    ///< Initialize V2G parameter

//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================
typedef struct
{
    Uint16  uiStsPrmHndl;     /**< 0 - wait;1-writeeeprom; 2-read_eeprom;*/
    Uint16  uiPrmOper;        /**< 0 - read;1-write*/
    Uint16  uiAddrPrmEep;
    Uint16  uiPrmLen;
    Uint16  uiTypPrm;
    Uint16  uiStsWr;
    Uint16  uiAddrSecBas;
    Uint16  uiAddrThrdBas;
    Uint16  uiFlgNonErase;
}ST_I2C_ST;

typedef struct
{
    ST_EEP     stPrmExt;    ///< Parameter to extern
    ST_I2C_PRM stI2cPrm;    ///< I2C parameter
    ST_I2C_ST  stI2cSt;     ///< I2C state

    Uint16 uiIdxAry[NUM_EEPROM_DATA_QUE_OPER];  ///< Dequeue index array
}ST_EEP_LOC;

//=====================================================
//    Variable Declaration
//=====================================================


//=====================================================
//    Function Declaration
//=====================================================
static void v_Eep_Cmn_RldDftCtry(void);
static void v_Eep_RcvPrm_DataToRAM(Uint16 uiNum, Uint16 uiDataType, ST_I2C_handle p);
static void v_Eep_RcvPrm_NonErasePrm(void);
static void v_Eep_RcvPrm_ErasePrm(void);
static void v_Eep_RcvPrm_WrByIdx(ST_I2C_handle pI2C, Uint16 uiIndex);
static void v_Eep_RcvPrm_WrByIdx_StMac(ST_I2C_handle pI2C, Uint16 uiAddrDataInit, Uint16 uiNumWord);
static void v_Eep_RcvPrm_WrByIdx_StMac_1st(ST_I2C_handle pI2C, Uint16 uiAddrDataInit, Uint16 uiNumWord);
static void v_Eep_RcvPrm_WrByIdx_StMac_2nd(ST_I2C_handle pI2C, Uint16 uiAddrDataInit, Uint16 uiNumWord);
static void v_Eep_RcvPrm_WrByIdx_StMac_3rd(ST_I2C_handle pI2C, Uint16 uiAddrDataInit, Uint16 uiNumWord);
static void v_Eep_RcvPrm_WrErasePrm(void);
static void v_Eep_RcvPrm_WrNonErasePrm(void);
static void v_Eep_PrmHndl_StMac_1ms(void);
static void v_Eep_PrmHndl_StMac_Chk_1ms(void);
static void v_Eep_PrmHndl_StMac_Wr_1ms(void);
static Uint16 ui_Eep_DataDeQue(ST_EEP_DATA_QUE *Que, Uint16 *puiAddrDest, Uint16 uiNum);
static void v_Eep_MemCopy(Uint16 *puiAddrSrcStrt, Uint16 *puiAddrSrcEnd, Uint16 *puiAddrDest);

#endif /*EEP_H_*/
//===========================================================================
// End of file.
//===========================================================================
