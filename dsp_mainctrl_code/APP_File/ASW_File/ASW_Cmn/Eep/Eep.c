/**
 *******************************************************************************
 **************************
 *                                       Application source files
 *                                            EEpromPara function
 *
 *
 *                     (c) Copyright 2010-2040, Wanbang New Energy Investment Co.,LTD.
 *                                        All Rights Reserved
 *
 *
 * Name       : Eep.c
 * Version    : v100
 * Author     : sdd
 *
 * Aim        : TMS320F2837xD
 * Mode       : LARG_MODEL
 * Environment: CCS v10.4
 * Description: Control parameters are saved to EEPROM
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
 * @file           Eep.c
 * @brief	       EEpromPara
 * @details	       Control parameters are saved to EEPROM ;
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
 * <tr><td>2023/07/31   <td>1.0	        <td>sdd           <td>Initial version
 * </table>
 *
 *******************************************************************************
 ***
 */
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "Eep.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_EEP stEep;    ///< Eep global struct

#if (1U == EEP_DBG)
ST_EEP stEepDbg;               ///< Eep debug global struct
#endif

static ST_EEP_LOC stEepLoc;    ///< Eep global local struct
static const Uint16 uiTypPrmLen[7] = {0U, NUM_WORD_16BIT, NUM_WORD_16BIT, NUM_WORD_32BIT, NUM_WORD_32BIT, NUM_WORD_32BIT, NUM_WORD_STRING};
static Uint16 ParaChangeBuff[WIRTEPARA_BUFF_SIZE];

//==============================================================================================
//    Function definition
//==============================================================================================
/******************************************************************************************************/
/**
 * @brief   v_Eep_Init
 * @param [in]  EepromAddr p
 * @param [in]  DataLen
 * @param [in]  puiDataAddr
 * @param [out] I2C_RETURN_READ_SUCESS
 * @return
 */
/******************************************************************************************************/
void v_Eep_Init(void)
{
    Uint16 i = 0U;

    stEepLoc.stI2cPrm.uiStsMsgBus  = I2C_BUS_FREE;               ///< Bus status initial
    stEepLoc.stI2cPrm.uiAddrSlave  = I2C_SLAVE_ADDR;             ///< Slave address
    stEepLoc.stI2cPrm.uiAddrMem    = 0U;
    stEepLoc.stI2cPrm.uiNumOfWords = 0U;                         ///< Number of word
    stEepLoc.stI2cSt.uiStsPrmHndl  = WAIT_CHECK;
    stEepLoc.stI2cSt.uiPrmOper     = 0U;
    stEepLoc.stI2cSt.uiAddrPrmEep  = 0U;
    stEepLoc.stI2cSt.uiPrmLen      = 0U;
    stEepLoc.stI2cSt.uiTypPrm      = 0U;
    stEepLoc.stI2cSt.uiStsWr       = FIRST_WRITE;
    stEepLoc.stI2cSt.uiAddrSecBas  = I2C_EEPROM_NONERASE_ADDR1;
    stEepLoc.stI2cSt.uiAddrThrdBas = I2C_EEPROM_NONERASE_ADDR2;
    stEepLoc.stI2cSt.uiFlgNonErase = 0U;

    stEep.stQuePrmChg.puiQueBuf     = ParaChangeBuff;
    stEep.stQuePrmChg.uiDataLength  = 0U;
    stEep.stQuePrmChg.uiFront       = 0U;
    stEep.stQuePrmChg.uiRear        = 0U;
    stEep.stQuePrmChg.QueMax        = (Uint16)sizeof(ParaChangeBuff);

    /* Buffer initialization */
    for (i = 0U; i < WIRTEPARA_BUFF_SIZE; i++)
    {
        ParaChangeBuff[i] = 0U;
    }

    for (i = 0U; i < MAX_DATABUFF_SIZE; i++)
    {
        stEepLoc.stI2cPrm.uiBufMsgRead[i] = 0U;           ///< Read buffer
        stEepLoc.stI2cPrm.uiBufMsgWr[i]   = 0U;           ///< Write buffer
    }

    for (i = 0U; i < NUM_EEPROM_DATA_QUE_OPER; i++)
    {
        stEepLoc.uiIdxAry[i] = 0U;
    }

    v_Eep_Cmn_RldDftCtry();    ///< Reload default grid standard parameter

    stEepLoc.stPrmExt.uiStdGridSel           = stCom.uiStdGridSet;
    stEepLoc.stPrmExt.stEepErr.all           = 0U;
    stEepLoc.stPrmExt.stCmdPrm.uiCmd         = WAIT_CMD;
    stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0] = 0U;
    stEepLoc.stPrmExt.stCmdPrm.uiNumSaved    = 0U;

    /* Output parameter */
#if (1U == EEP_DBG)
    stEepDbg.uiStdGridSel           = stEepLoc.stPrmExt.uiStdGridSel;
    stEepDbg.stEepErr.all           = stEepLoc.stPrmExt.stEepErr.all;
    stEepDbg.stCmdPrm.uiCmd         = stEepLoc.stPrmExt.stCmdPrm.uiCmd;
    stEepDbg.stCmdPrm.uiIndexPrm[0] = stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0];
    stEepDbg.stCmdPrm.uiNumSaved    = stEepLoc.stPrmExt.stCmdPrm.uiNumSaved;

    stEep.uiStdGridSel           = stEepDbg.uiStdGridSel;
    stEep.stEepErr.all           = stEepDbg.stEepErr.all;
    stEep.stCmdPrm.uiCmd         = stEepDbg.stCmdPrm.uiCmd;
    stEep.stCmdPrm.uiIndexPrm[0] = stEepDbg.stCmdPrm.uiIndexPrm[0];
    stEep.stCmdPrm.uiNumSaved    = stEepDbg.stCmdPrm.uiNumSaved;
#else
    stEep.uiStdGridSel           = stEepLoc.stPrmExt.uiStdGridSel;
    stEep.stEepErr.all           = stEepLoc.stPrmExt.stEepErr.all;
    stEep.stCmdPrm.uiCmd         = stEepLoc.stPrmExt.stCmdPrm.uiCmd;
    stEep.stCmdPrm.uiIndexPrm[0] = stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0];
    stEep.stCmdPrm.uiNumSaved    = stEepLoc.stPrmExt.stCmdPrm.uiNumSaved;
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_Eep_Init() is running****\r\n");
#endif
}

/******************************************************************************************************/
/**
 * @brief:Reload the default values of national grid connection parameters
 * @param [in]  ST_I2C_handle p
 * @param [out]
 * @return
 */
static void v_Eep_Cmn_RldDftCtry(void)
{
    Tbl_Grid_Rated_Parameter_Init(stCom.uiStdGridSet);    ///< Initialize grid rated parameter
    Tbl_Power_Control_Init(stCom.uiStdGridSet);           ///< Initialize power control parameter
    Tbl_Grid_Protection_Init(stCom.uiStdGridSet);         ///< Initialize grid protection parameter
    Tbl_Frq_Power_Response_Init(stCom.uiStdGridSet);      ///< Initialize frequency power response parameter
    Tbl_Reactive_Qu_Mode_Init(stCom.uiStdGridSet);        ///< Initialize QU parameter
    Tbl_Reactive_Qp_Mode_Init(stCom.uiStdGridSet);        ///< Initialize QP parameter
    Tbl_HVRT_Init(stCom.uiStdGridSet);                    ///< Initialize HVRT parameter
    Tbl_LVRT_Init(stCom.uiStdGridSet);                    ///< Initialize LVRT parameter
    Tbl_Volt_Power_Response_Init(stCom.uiStdGridSet);     ///< Initialize voltage power response parameter

#ifdef _SIMULATION_NO_DSP_
    stComTbl.stPrmPfcRtd1.ftVoltGrid = 230.0f;
    stComTbl.stPrmPfcRtd1.ftFrqGrid  = 50.0f;

    stComTbl.stPrmPwrCtrl.ftRatePwrUpNorm  = 30000;
    stComTbl.stPrmPwrCtrl.ftRatePwrDwnNorm = 30000;
    stComTbl.stPrmPwrCtrl.ftRatePwrReload  = 30000;
    stComTbl.stPrmPwrCtrl.ftTiWaitRecnct   = 10;
    stComTbl.stPrmPwrCtrl.ftTiReactvRespPf = 0.2;
    stComTbl.stPrmPwrCtrl.ftTiReactvRespQu = 0.2;
    stComTbl.stPrmPwrCtrl.ftTiReactvRespQp = 0.2;
    stComTbl.stPrmPwrCtrl.ftTiReactvRespQt = 0.2;
    stComTbl.stPrmPwrCtrl.ftRatePwrLoad    = 30000;
    stComTbl.stPrmPwrCtrl.ftTiWaitCnct     = 10;

    stComTbl.stPrmPwrRespHF.ftTiOutWait    = 1;
    stComTbl.stPrmPwrRespHF.ftRatePwrRcv   = 12000;
    stComTbl.stPrmPwrRespHF.ftTiInWait     = 2;
    stComTbl.stPrmPwrRespHF.ftRatePwrResp  = 30000;

    stComTbl.stPrmPwrRespLF.ftTiOutWait    = 1;
    stComTbl.stPrmPwrRespLF.ftRatePwrRcv   = 15000;
    stComTbl.stPrmPwrRespLF.ftTiInWait     = 2;
    stComTbl.stPrmPwrRespLF.ftRatePwrResp  = 30000;

    stComTbl.stPrmPu.ftTiResp             = 2;

    stComTbl.stPrmHvrt.ftCoeffIq          = 5;
    stComTbl.stPrmHvrt.ftRatioZeroPwrVolt = 1.25;
    stComTbl.stPrmHvrt.ftValIqLim         = 0;
    stComTbl.stPrmHvrt.ftVolt1            = 1.2;
    stComTbl.stPrmHvrt.ftVolt2            = 1.25;
    stComTbl.stPrmHvrt.ftVolt3            = 1.25;
    stComTbl.stPrmHvrt.uiModePwr          = 0U;

    stComTbl.stPrmPu.ftVolt1 = 1.05;
    stComTbl.stPrmPu.ftVolt2 = 1.1;
    stComTbl.stPrmPu.ftVolt3 = 1.1;
    stComTbl.stPrmPu.ftVolt4 = 1.1;
    stComTbl.stPrmPu.ftPwr1  = 1;
    stComTbl.stPrmPu.ftPwr2  = -0.8;
    stComTbl.stPrmPu.ftPwr3  = -0.8;
    stComTbl.stPrmPu.ftPwr4  = -0.8;
#endif
}

/******************************************************************************************************/
/**
 * @brief   Recovery EEPROM parameter
 * @param [in]  NULL
 * @param [out] NULL
 * @return
 */
/******************************************************************************************************/
void v_Eep_RcvPrm(void)
{
    Uint16 l_uiFlgPrmSaved  = 0U;
    Uint16 l_uiFlgNonErased = 0U;

    stEepLoc.stI2cPrm.uiStsMsgBus  = I2C_BUS_ON_PARA;        ///< Bus status
    stEepLoc.stI2cPrm.uiAddrMem    = PARA_SAVED_ADDR;        ///< Memory address
    stEepLoc.stI2cPrm.uiNumOfWords = 1U;
    if(I2C_RETURN_READ_SUCESS == ui_EepDrv_RdWait(&stEepLoc.stI2cPrm))        ///< Read parameter OK
    {
        l_uiFlgPrmSaved = stEepLoc.stI2cPrm.uiBufMsgRead[0];
    }

    if(EEPROM_SAVED == l_uiFlgPrmSaved)
    {
        stEepLoc.stI2cPrm.uiStoredOK = 1U;      ///< Store OK flag
    }
    else
    {
        stEepLoc.stI2cPrm.uiStoredOK = 0U;
    }

    stEepLoc.stI2cPrm.uiAddrMem    = PARA_NONERASE_ADDR;    ///< Memory address
    stEepLoc.stI2cPrm.uiNumOfWords = 1U;
    if(I2C_RETURN_READ_SUCESS == ui_EepDrv_RdWait(&stEepLoc.stI2cPrm))        ///< Read parameter OK
    {
        l_uiFlgNonErased = stEepLoc.stI2cPrm.uiBufMsgRead[0];
    }

    if(NONERASED_SAVED == l_uiFlgNonErased)
    {
        stEepLoc.stI2cPrm.uiNonErasedOK = 1U;
    }
    else
    {
        stEepLoc.stI2cPrm.uiNonErasedOK = 0U;
    }

    /* EEprom Non-erase parameter read or recovery */
    v_Eep_RcvPrm_NonErasePrm();
    /* EEprom erasable parameter read or recovery */
    v_Eep_RcvPrm_ErasePrm();

    stEepLoc.stI2cPrm.uiStsMsgBus  = I2C_BUS_FREE;

    stEepLoc.stPrmExt.uiStdGridSel = stCom.uiStdGridSet;

    /* Output parameter */
#if (1U == EEP_DBG)
    stEep.stEepErr.all = stEepDbg.stEepErr.all;
    stEep.uiStdGridSel = stEepDbg.uiStdGridSel;
#else
    stEep.stEepErr.all = stEepLoc.stPrmExt.stEepErr.all;
    stEep.uiStdGridSel = stEepLoc.stPrmExt.uiStdGridSel;
#endif
}
/******************************************************************************************************/

/******************************************************************************************************/
/**
 * @brief   EEprom Non-erase parameter read or recovery
 * @param [in]  NULL
 * @param [out] NULL
 * @return
 */
static void v_Eep_RcvPrm_NonErasePrm(void)
{
    Uint16 i = 0U;
    Uint16 j = 0U;
    Uint16 l_uiTypeData = 0U;            ///< The type of data that you want to save
    Uint16 l_uiFlgRead  = 0U;
    Uint16 l_uiDataTmp1 = 0U;
    Uint16 l_uiDataTmp2 = 0U;
    Uint16 l_uiDataTmp3 = 0U;
    Uint16 l_uiAddrDataInit = 0U;
    Uint16 l_uiIdxDataTbl = 0U;          ///< Data table index
    Uint32 l_ulDataEep  = 0UL;
    Uint32 l_ulAddrData = 0UL;

    if(1U == stEepLoc.stI2cPrm.uiNonErasedOK)       ///< Non-Erase parameter handle
    {
        IIC_WRITE_ENABLE;
        for(i = 0U; i < MASTER_NONERASE_SAVE_NUM; i++)
        {
            l_uiFlgRead = 0U;

            l_uiIdxDataTbl = MasterNonEraseEEPromIndex[i];
            /** Read data type */
            l_uiTypeData = GET_DATA_TYPE(l_uiIdxDataTbl);
            /** The initial storage address of the current data */
            l_uiAddrDataInit = GET_DATA_EEPROM_ADDR(l_uiIdxDataTbl);

            if((DATA_INT16 == l_uiTypeData) || (DATA_UINT16 == l_uiTypeData))     ///< 16 bit Date type 
            {
                stEepLoc.stI2cPrm.uiNumOfWords = 1U;
            }
            else if((DATA_INT32 == l_uiTypeData) || (DATA_UINT32 == l_uiTypeData) || (DATA_FLOAT32 == l_uiTypeData))    ///< 32 bit ate type 
            {
                stEepLoc.stI2cPrm.uiNumOfWords = 2U;
            }
            else if(DATA_STRING == l_uiTypeData)               ///< String data type 
            {
                stEepLoc.stI2cPrm.uiNumOfWords = NUM_WORD_STRING;          ///< 20 words to be read
            }
            else
            {
                ///< No code
            }

            for(j = 0U; j < stEepLoc.stI2cPrm.uiNumOfWords; j++)
            {
                /* Read the data for the first time */
                stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit;
                (void)ui_EepDrv_RdWordData(&stEepLoc.stI2cPrm,j);
                l_uiDataTmp1 = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                /* Read the data for the second time */
                stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit + I2C_EEPROM_NONERASE_ADDR1;
                (void)ui_EepDrv_RdWordData(&stEepLoc.stI2cPrm,j);
                l_uiDataTmp2 = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                /* Read the data for the third time */
                stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit + I2C_EEPROM_NONERASE_ADDR2;
                (void)ui_EepDrv_RdWordData(&stEepLoc.stI2cPrm,j);
                l_uiDataTmp3 = stEepLoc.stI2cPrm.uiBufMsgRead[j];

                /* The data is equal all three times */
                if((l_uiDataTmp1 == l_uiDataTmp2) && (l_uiDataTmp1 == l_uiDataTmp3))
                {
                    stEepLoc.stI2cPrm.uiBufMsgRead[j] = l_uiDataTmp1;
                }
#if 0U == FLG_SWUT_EN
                /* First == Second, but != third */
                else if((l_uiDataTmp1 == l_uiDataTmp2) && (l_uiDataTmp1 != l_uiDataTmp3))
                {
                    stEepLoc.stI2cPrm.uiBufMsgRead[j] = l_uiDataTmp1;
                    /* The data is re-written for the third time */
                    stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit + I2C_EEPROM_NONERASE_ADDR2;
                    stEepLoc.stI2cPrm.uiBufMsgWr[j] = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                    (void)ui_EepDrv_WrWordData(&stEepLoc.stI2cPrm, j);
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrThrdRead = 1U;
                }
                /* First == third, but != Second */
                else if((l_uiDataTmp1 != l_uiDataTmp2) && (l_uiDataTmp1 == l_uiDataTmp3))
                {
                    stEepLoc.stI2cPrm.uiBufMsgRead[j] = l_uiDataTmp1;
                    /* The data is re-written for the second time */
                    stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit + I2C_EEPROM_NONERASE_ADDR1;
                    stEepLoc.stI2cPrm.uiBufMsgWr[j] = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                    (void)ui_EepDrv_WrWordData(&stEepLoc.stI2cPrm, j);
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrSecRead = 1U;
                }
                /* Second == third, but != First */
                else if((l_uiDataTmp1 != l_uiDataTmp2) && (l_uiDataTmp2 == l_uiDataTmp3))
                {
                    stEepLoc.stI2cPrm.uiBufMsgRead[j] = l_uiDataTmp2;
                    /* The data is re-written for the First time */
                    stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit;
                    stEepLoc.stI2cPrm.uiBufMsgWr[j] = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                    (void)ui_EepDrv_WrWordData(&stEepLoc.stI2cPrm, j);
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrFirstRead = 1U;
                }
                /* Three times the data are not equal */
                else
                {
                    l_uiFlgRead = 1U;
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrRead = 1U;
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrInit = 1U;
                }
#endif
            }

            /* If there are no errors in the data read, the data is saved to the address */
            if(0U == l_uiFlgRead)
            {
                /* After the data of a location is read, the read data is stored in the corresponding address */
                v_Eep_RcvPrm_DataToRAM(l_uiIdxDataTbl, l_uiTypeData, &stEepLoc.stI2cPrm);
            }
        }

        /* Prevents the newly added parameter from being read out incorrectly*/
        l_ulAddrData = (Uint32)(&stCom.ftCurrAcRmsLim);
        l_ulDataEep  = *(Uint32*)l_ulAddrData;
        if(0xFFFFFFFFU == l_ulDataEep)
        {
            stCom.ftCurrAcRmsLim = MAX_AC_CURR_RMS;        ///< AC current RMS limit
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, AC_CURR_RMS_LIM_NUM);
        }

#if(3U == GRID_PHASE_NUMBER)
        if(0xFFFFU == stCom.uiTypeGrid)
        {
            stCom.uiTypeGrid = TYPE_GRID_ABCN;                               ///< Grid type
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, GRID_TYPE_NUM);
        }
		
        if(0xFFFFU == (Uint16)stCom.stPrmPfcAdjCoeff.siIgDcZero_A_N)
        {
            stCom.stPrmPfcAdjCoeff.siIgDcZero_A_N = AD_BIAS_DC_CURR;         ///< Phase A DC current AD bias calculation
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, IA_DC_ADJ_ZERO_N_NUM);
		}

        if(0xFFFFU == (Uint16)stCom.stPrmPfcAdjCoeff.siIgDcZero_B_N)
        {		
            stCom.stPrmPfcAdjCoeff.siIgDcZero_B_N = AD_BIAS_DC_CURR;         ///< Phase B DC current AD bias calculation
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, IB_DC_ADJ_ZERO_N_NUM);
		}
		
        if(0xFFFFU == (Uint16)stCom.stPrmPfcAdjCoeff.siIgDcZero_C_N)
        {
            stCom.stPrmPfcAdjCoeff.siIgDcZero_C_N = AD_BIAS_DC_CURR;         ///< Phase C DC current AD bias calculation
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, IC_DC_ADJ_ZERO_N_NUM);
        }
#elif(2U == GRID_PHASE_NUMBER)
        if(0xFFFFU == stCom.uiTypeGrid)
        {
            stCom.uiTypeGrid = TYPE_GRID_ABN;                                ///< Grid type
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, GRID_TYPE_NUM);
        }
		
        if(0xFFFFU == (Uint16)stCom.stPrmPfcAdjCoeff.siVgInvZero_A)
        {
            stCom.stPrmPfcAdjCoeff.siVgInvZero_A = AD_BIAS_DC_CURR;          ///< Phase A inverter voltage AD bias calculation
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, VAINV_ADJ_ZERO_NUM);
        }
		
        if(0xFFFFU == (Uint16)stCom.stPrmPfcAdjCoeff.siVgInvZero_B)
        {
            stCom.stPrmPfcAdjCoeff.siVgInvZero_B = AD_BIAS_DC_CURR;          ///< Phase B inverter voltage AD bias calculation
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, VBINV_ADJ_ZERO_NUM);
        }
		
        l_ulAddrData = (Uint32)(&stCom.stPrmPfcAdjCoeff.ftVaInvK);
        l_ulDataEep  = *(Uint32*)l_ulAddrData;
        if(0xFFFFFFFFU == l_ulDataEep)
        {
            stCom.stPrmPfcAdjCoeff.ftVaInvK = 1.0f;                          ///< VaInv calibration coefficient
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, VAINV_ADJ_COFK_NUM);
        }
		
        l_ulAddrData = (Uint32)(&stCom.stPrmPfcAdjCoeff.ftVbInvK);
        l_ulDataEep  = *(Uint32*)l_ulAddrData;
        if(0xFFFFFFFFU == l_ulDataEep)
        {
            stCom.stPrmPfcAdjCoeff.ftVbInvK = 1.0f;                          ///< VbInv calibration coefficient
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, VBINV_ADJ_COFK_NUM);
        }
		
        if(0xFFFFU == stCom.uiStdGridSet)
        {
            stCom.uiStdGridSet = IEEE1547;                                   ///< Grid standard
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, GRID_STD_NUM);
        }
#elif(1U == GRID_PHASE_NUMBER)
        if(0xFFFFU == stCom.uiTypeGrid)
        {
            stCom.uiTypeGrid = TYPE_GRID_AN;                                 ///< Grid type
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, GRID_TYPE_NUM);
        }
#endif
    }
    else
    {
        IIC_WRITE_ENABLE;
        DELAY_US_APP(1000.0f);           ///< Delay 1ms
        v_Eep_RcvPrm_WrNonErasePrm();
    }
}

/******************************************************************************************************/
/**
* @brief: Writes non-erasable data to the EEPROM
* @param[in]
* @param[out]
* @return
*/
static void v_Eep_RcvPrm_WrNonErasePrm(void)
{
    Uint16 i = 0U;
    Uint16 l_uiIdxPrmTbl = 0U;
    Uint16 l_uiAddrData  = 0U;
    Uint16 l_uiFlgWrRead = 0U;

    l_uiIdxPrmTbl = MasterNonEraseEEPromIndex[MASTER_NONERASE_SAVE_NUM-1U];       ///< Table index
    l_uiAddrData = sFuncCode[l_uiIdxPrmTbl].MasterSaveAddr;                       ///< Master save address

    if(l_uiAddrData> (PARA_SAVE_END_NONERASE_ADDR - 4U))
    {
        stEepLoc.stPrmExt.stEepErr.bit.uiErrAddrOver = 1U;
    }

    for(i = 0U; i < MASTER_NONERASE_SAVE_NUM; i++)
    {
        l_uiIdxPrmTbl = MasterNonEraseEEPromIndex[i];

        v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, l_uiIdxPrmTbl);      ///< Write data by index

        if(stEepLoc.stPrmExt.stEepErr.all != 0U)
        {
            break;
        }
    }

    if(stEepLoc.stPrmExt.stEepErr.all == 0U)
    {
        stEepLoc.stI2cPrm.uiAddrMem = PARA_NONERASE_ADDR;            ///< Memory address
        stEepLoc.stI2cPrm.uiBufMsgWr[0] = NONERASED_SAVED;
        stEepLoc.stI2cPrm.uiNumOfWords = 1U;                         ///< Number of word
        l_uiFlgWrRead = 0U;

        if(I2C_RETURN_WRITE_SUCESS == ui_EepDrv_WrWait(&stEepLoc.stI2cPrm))    ///< Write parameter
        {
            l_uiFlgWrRead = ui_EepDrv_RdWait(&stEepLoc.stI2cPrm);    ///< Read parameter
        }

        if(l_uiFlgWrRead != I2C_RETURN_READ_SUCESS)
        {
            (void)ui_EepDrv_WrWordData(&stEepLoc.stI2cPrm, 0U);
        }

        if(stEepLoc.stI2cPrm.uiBufMsgWr[0] != stEepLoc.stI2cPrm.uiBufMsgRead[0])
        {
            stEepLoc.stPrmExt.stEepErr.bit.uiErrEep = 1U;
        }
    }
    else
    {
        stEepLoc.stI2cPrm.uiAddrMem = PARA_NONERASE_ADDR;
        stEepLoc.stI2cPrm.uiBufMsgWr[0] = 0x1001U;
        stEepLoc.stI2cPrm.uiNumOfWords = 1U;
        (void)ui_EepDrv_WrWait(&stEepLoc.stI2cPrm);    ///< Write error word to PARA_NONERASE_ADDR
    }
}

/**
 * @brief   EEprom erasable parameter read or recovery
 * @param [in]  NULL
 * @param [out] NULL
 * @return
 */
static void v_Eep_RcvPrm_ErasePrm(void)
{
    Uint16 i = 0U;
    Uint16 j = 0U;
    Uint16 l_uiPrmVer   = 0U;
    Uint16 l_uiSwVer    = 0U;    ///< Software version
    Uint16 l_uiTypeData = 0U;    ///<  The type of data that you want to save
    Uint16 l_uiFlgRead  = 0U;
    Uint16 l_uiDataTmp1 = 0U;
    Uint16 l_uiDataTmp2 = 0U;
    Uint16 l_uiDataTmp3 = 0U;
    Uint16 l_uiAddrDataInit = 0U;
    Uint16 l_uiIdxDataTbl = 0U;

    stEepLoc.stI2cPrm.uiAddrMem = PARA_VER_ADDR;     ///< Memory address
    stEepLoc.stI2cPrm.uiNumOfWords = 1U;
    if(I2C_RETURN_READ_SUCESS == ui_EepDrv_RdWait(&stEepLoc.stI2cPrm))   ///< Parameter read wait
    {
        l_uiPrmVer = stEepLoc.stI2cPrm.uiBufMsgRead[0];
    }

    stEepLoc.stI2cPrm.uiAddrMem = SOFT_VER_ADDR;     ///< Memory address
    stEepLoc.stI2cPrm.uiNumOfWords = 1U;
    if(I2C_RETURN_READ_SUCESS == ui_EepDrv_RdWait(&stEepLoc.stI2cPrm))  ///< Parameter read wait
    {
        l_uiSwVer = stEepLoc.stI2cPrm.uiBufMsgRead[0];
    }

#if 0U == FLG_SWUT_EN
    if((1U == stEepLoc.stI2cPrm.uiStoredOK) && (l_uiPrmVer == PARAM_VER) && (l_uiSwVer == DSP_SOFT_VERSON))        ///< The data has been written to the current version
#else
    if(1U == stEepLoc.stI2cPrm.uiStoredOK)
#endif
    {
        for(i = 0U; i < MASTER_SAVE_NUM; i++)
        {
            l_uiFlgRead = 0U;
            l_uiIdxDataTbl = MasterSaveEEPromIndex[i];
            l_uiTypeData = GET_DATA_TYPE(l_uiIdxDataTbl);
            l_uiAddrDataInit = GET_DATA_EEPROM_ADDR(l_uiIdxDataTbl);

            if((DATA_INT16 == l_uiTypeData) || (DATA_UINT16 == l_uiTypeData))   ///< 16 bit data type
            {
                stEepLoc.stI2cPrm.uiNumOfWords = 1U;
            }
            else if((DATA_INT32 == l_uiTypeData) || (DATA_UINT32 == l_uiTypeData) || (DATA_FLOAT32 == l_uiTypeData))   ///< 32 bit data type
            {
                stEepLoc.stI2cPrm.uiNumOfWords = 2U;
            }
            else if(DATA_STRING == l_uiTypeData)     ///< String data type
            {
                stEepLoc.stI2cPrm.uiNumOfWords = NUM_WORD_STRING;
            }
            else
            {
                ///< No code
            }

            for(j = 0U; j < stEepLoc.stI2cPrm.uiNumOfWords; j++)
            {
                /* Read the data for the first time */
                stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit;
                (void)ui_EepDrv_RdWordData(&stEepLoc.stI2cPrm, j);
                l_uiDataTmp1 = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                /* Read the data for the second time */
                stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit + I2C_EEPROM_ADDR1;
                (void)ui_EepDrv_RdWordData(&stEepLoc.stI2cPrm, j);
                l_uiDataTmp2 = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                /* Read the data for the third time */
                stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit + I2C_EEPROM_ADDR2;
                (void)ui_EepDrv_RdWordData(&stEepLoc.stI2cPrm, j);
                l_uiDataTmp3 = stEepLoc.stI2cPrm.uiBufMsgRead[j];

                /* The data is equal all three times */
                if((l_uiDataTmp1 == l_uiDataTmp2) && (l_uiDataTmp1 == l_uiDataTmp3))
                {
                    stEepLoc.stI2cPrm.uiBufMsgRead[j] = l_uiDataTmp1;
                }
#if 0U == FLG_SWUT_EN
                /* First == Second, but != third */
                else if((l_uiDataTmp1 == l_uiDataTmp2) && (l_uiDataTmp1 != l_uiDataTmp3))
                {
                    stEepLoc.stI2cPrm.uiBufMsgRead[j] = l_uiDataTmp1;
                    /* First == Second, but != third */
                    stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit + I2C_EEPROM_ADDR2;
                    stEepLoc.stI2cPrm.uiBufMsgWr[j] = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                    (void)ui_EepDrv_WrWordData(&stEepLoc.stI2cPrm, j);
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrThrdRead = 1U;
                }
                /* First == third, but != Second */
                else if((l_uiDataTmp1 != l_uiDataTmp2) && (l_uiDataTmp1 == l_uiDataTmp3))
                {
                    stEepLoc.stI2cPrm.uiBufMsgRead[j] = l_uiDataTmp1;
                    /* The data is re-written for the second time */
                    stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit + I2C_EEPROM_ADDR1;
                    stEepLoc.stI2cPrm.uiBufMsgWr[j] = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                    (void)ui_EepDrv_WrWordData(&stEepLoc.stI2cPrm, j);
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrSecRead = 1U;
                }
                /* Second == third, but != First */
                else if((l_uiDataTmp1 != l_uiDataTmp2) && (l_uiDataTmp2 == l_uiDataTmp3))
                {
                    stEepLoc.stI2cPrm.uiBufMsgRead[j] = l_uiDataTmp2;
                    /* The data is re-written for the First time */
                    stEepLoc.stI2cPrm.uiAddrMem = l_uiAddrDataInit;
                    stEepLoc.stI2cPrm.uiBufMsgWr[j] = stEepLoc.stI2cPrm.uiBufMsgRead[j];
                    (void)ui_EepDrv_WrWordData(&stEepLoc.stI2cPrm, j);
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrFirstRead = 1U;
                }
                /* Three times the data are not equal */
                else
                {
                    l_uiFlgRead = 1U;
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrRead = 1U;
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrInit = 1U;
                }
#endif
            }

            /* If there are no errors in the data read, the data is saved to the address */
            if(0U == l_uiFlgRead)
            {
                v_Eep_RcvPrm_DataToRAM(l_uiIdxDataTbl, l_uiTypeData, &stEepLoc.stI2cPrm);
            }
        }
    }
    else
    {
        IIC_WRITE_ENABLE;
        DELAY_US_APP(1000.0f);        ///< Delay 1ms
        v_Eep_RcvPrm_WrErasePrm();    ///<Write erasable EEPROM data
    }
}

/**
 * @brief   EEpromDataWriteByIndex
 * @param [in]  pI2C
 * @param [in]  uiIndex
 * @param [out] NULL
 * @return
 */
static void v_Eep_RcvPrm_WrByIdx(ST_I2C_handle pI2C, Uint16 uiIndex)
{
    Uint16 i = 0U;
    Uint16 l_uiTypeData = 0U;            ///<  The type of data that you want to save
    Uint16 l_uiNumWord  = 0U;             ///<  The number of data words to save data
    Uint16 l_uiDataTmp  = 0U;
    Uint16 l_uiDataTmp1 = 0U;
    Uint16 l_uiAddrDataInit = 0U;
    Uint16 l_uiFlgNonErased = 0U;

    l_uiTypeData = (sFuncCode[uiIndex].uiModifyAndDataType & 0x01C0U)>>6;   ///< Read data type
    l_uiAddrDataInit = sFuncCode[uiIndex].MasterSaveAddr;                 ///< The initial storage address of the current data
    l_uiFlgNonErased = (sFuncCode[uiIndex].uiModifyAndDataType & 0x0200U)>>9;

    if(l_uiFlgNonErased > 0U)        ///< Adjust address
    {
        pI2C->uiAddrSecBas  = I2C_EEPROM_NONERASE_ADDR1;
        pI2C->uiAddrThrdBas = I2C_EEPROM_NONERASE_ADDR2;
    }
    else
    {
        pI2C->uiAddrSecBas  = I2C_EEPROM_ADDR1;
        pI2C->uiAddrThrdBas = I2C_EEPROM_ADDR2;
    }

    if((TYPE_INT16 == l_uiTypeData) || (TYPE_UINT16 == l_uiTypeData))  ///< int16 or Uint16
    {
        l_uiNumWord = 1U;
        l_uiDataTmp = *(Uint16*) (sFuncCode[uiIndex].ParaAddr);
        pI2C->uiBufMsgWr[0] = l_uiDataTmp;
    }
    else if((TYPE_INT32 == l_uiTypeData) || (TYPE_UINT32 == l_uiTypeData) || (TYPE_FLOAT32 == l_uiTypeData))    ///< int32,Uint32 or float32
    {
        l_uiNumWord = 2U;

        l_uiDataTmp = *(Uint16*) (sFuncCode[uiIndex].ParaAddr);
        pI2C->uiBufMsgWr[0] = l_uiDataTmp;

        l_uiDataTmp = *(Uint16*) (sFuncCode[uiIndex].ParaAddr + 1);
        pI2C->uiBufMsgWr[1] = l_uiDataTmp;
    }
    else if(TYPE_STRING == l_uiTypeData)    ///< String
    {
        l_uiNumWord = NUM_WORD_STRING;
        for(i = 0U; i < NUM_WORD_STRING; i++)
        {
            l_uiDataTmp = *((Uint16*)sFuncCode[uiIndex].ParaAddr + 2U * i );            ///< High byte
            l_uiDataTmp1 = *((Uint16*)sFuncCode[uiIndex].ParaAddr + 2U * i + 1);        ///< Low byte
            pI2C->uiBufMsgWr[i] = (l_uiDataTmp << 8 | l_uiDataTmp1);
        }
    }
    else
    {
        ///< Do nothing
    }

    pI2C->uiStsWr  = RCV_FIRST_WRITE;
    pI2C->uiErrCnt = 0U;
    pI2C->uiWrOK   = 0U;

    /* The parameter is written for the first time*/
    while((pI2C->uiWrOK != 1U) && (pI2C->uiStsWr < RCV_END_WRITE))
    {
        /* Write EEprom data by index state machine */
        v_Eep_RcvPrm_WrByIdx_StMac(pI2C, l_uiAddrDataInit, l_uiNumWord);
    }
}

/**
 * @brief  Write EEprom data by index state machine
 * @param [in]  pI2C
 * @param [out] NULL
 * @return
 */
static void v_Eep_RcvPrm_WrByIdx_StMac(ST_I2C_handle pI2C, Uint16 uiAddrDataInit, Uint16 uiNumWord)
{
    switch (pI2C->uiStsWr)
    {
        case RCV_FIRST_WRITE:
            v_Eep_RcvPrm_WrByIdx_StMac_1st(pI2C, uiAddrDataInit, uiNumWord);
            break;

        case RCV_SECOND_WRITE:
            v_Eep_RcvPrm_WrByIdx_StMac_2nd(pI2C, uiAddrDataInit, uiNumWord);
            break;

        case RCV_THIRD_WRITE:
            v_Eep_RcvPrm_WrByIdx_StMac_3rd(pI2C, uiAddrDataInit, uiNumWord);
            break;

        default:
            ///< No code
            break;
    }
}

/**
 * @brief  Write EEprom data by index state machine first write task
 * @param [in]  pI2C
 * @param [out] NULL
 * @return
 */
static void v_Eep_RcvPrm_WrByIdx_StMac_1st(ST_I2C_handle pI2C, Uint16 uiAddrDataInit, Uint16 uiNumWord)
{
    Uint16 i = 0U;

    pI2C->uiAddrMem = uiAddrDataInit;        ///< Write first
    pI2C->uiNumOfWords = uiNumWord;               ///<  Number of word
    if(I2C_RETURN_WRITE_SUCESS == ui_EepDrv_WrWait(pI2C))
    {
        pI2C->uiAddrMem = uiAddrDataInit;    ///< Read first time
        pI2C->uiNumOfWords = uiNumWord;
        if(I2C_RETURN_READ_SUCESS == ui_EepDrv_RdWait(pI2C))
        {
            ///< No code
        }

        for(i = 0U; i < uiNumWord; i++)
        {
            if(pI2C->uiBufMsgWr[i] != pI2C->uiBufMsgRead[i])
            {
                stEepLoc.stPrmExt.stEepErr.bit.uiErrFirstRead = 1U;

                if(pI2C->uiErrCnt++ > 6U)
                {
                    pI2C->uiErrCnt = 0U;
                    break;
                }
            }
            else
            {
                pI2C->uiStsWr  = RCV_SECOND_WRITE;
                pI2C->uiErrCnt = 0U;
                stEepLoc.stPrmExt.stEepErr.bit.uiErrFirstRead = 0U;
            }
        }
    }
    else
    {
        stEepLoc.stPrmExt.stEepErr.bit.uiErrIniFirstWr = 1U;
    }
}

/**
 * @brief  Write EEprom data by index state machine second write task
 * @param [in]  pI2C
 * @param [out] NULL
 * @return
 */
static void v_Eep_RcvPrm_WrByIdx_StMac_2nd(ST_I2C_handle pI2C, Uint16 uiAddrDataInit, Uint16 uiNumWord)
{
    Uint16 i = 0U;

    pI2C->uiAddrMem = uiAddrDataInit + pI2C->uiAddrSecBas;       ///<  write second time
    pI2C->uiNumOfWords = uiNumWord;                              ///<  Number of word
    if(I2C_RETURN_WRITE_SUCESS == ui_EepDrv_WrWait(pI2C))
    {
        pI2C->uiAddrMem = uiAddrDataInit + pI2C->uiAddrSecBas;   ///<  read second time
        pI2C->uiNumOfWords = uiNumWord;
        if(I2C_RETURN_READ_SUCESS == ui_EepDrv_RdWait(pI2C))
        {
            ///< No code
        }

        for(i = 0U; i < uiNumWord; i++)
        {
            if(pI2C->uiBufMsgWr[i] != pI2C->uiBufMsgRead[i])
            {
                stEepLoc.stPrmExt.stEepErr.bit.uiErrSecRead = 1U;
                if(pI2C->uiErrCnt++ > 6U)
                {
                    pI2C->uiErrCnt = 0U;
                    break;
                }
            }
            else
            {
                pI2C->uiStsWr  = RCV_THIRD_WRITE;
                pI2C->uiErrCnt = 0U;
                stEepLoc.stPrmExt.stEepErr.bit.uiErrSecRead = 0U;
            }
        }
    }
    else
    {
        stEepLoc.stPrmExt.stEepErr.bit.uiErrIniSecWr = 1U;
    }
}

/**
 * @brief  Write EEprom data by index state machine third write task
 * @param [in]  pI2C
 * @param [out] NULL
 * @return
 */
static void v_Eep_RcvPrm_WrByIdx_StMac_3rd(ST_I2C_handle pI2C, Uint16 uiAddrDataInit, Uint16 uiNumWord)
{
    Uint16 i = 0U;

    pI2C->uiAddrMem = uiAddrDataInit + pI2C->uiAddrThrdBas;       ///<  write third time
    pI2C->uiNumOfWords = uiNumWord;                               ///<  Number of word
    if(I2C_RETURN_WRITE_SUCESS == ui_EepDrv_WrWait(pI2C))
    {
        pI2C->uiAddrMem = uiAddrDataInit + pI2C->uiAddrThrdBas;   ///<  read third time
        pI2C->uiNumOfWords = uiNumWord;

        if(I2C_RETURN_READ_SUCESS == ui_EepDrv_RdWait(pI2C))
        {
            ///< Do nothing
        }

        for(i = 0U; i < uiNumWord; i++)
        {
            if(pI2C->uiBufMsgWr[i] != pI2C->uiBufMsgRead[i])
            {
                stEepLoc.stPrmExt.stEepErr.bit.uiErrThrdRead = 1U;
                if(pI2C->uiErrCnt++ > 6U)
                {
                    pI2C->uiErrCnt = 0U;
                    break;
                }
            }
            else
            {
                 pI2C->uiWrOK   = 1U;
                 pI2C->uiErrCnt = 0U;
                 pI2C->uiStsWr  = RCV_END_WRITE;
                 stEepLoc.stPrmExt.stEepErr.bit.uiErrThrdRead = 0U;
            }
        }
    }
    else
    {
        stEepLoc.stPrmExt.stEepErr.bit.uiErrIniThrdWr = 1U;
    }
}

/******************************************************************************************************/
/**
 * @brief: Write erasable EEPROM data
 * @param [in]  ST_I2C_handle p
 * @param [out]
 * @return
 */
static void v_Eep_RcvPrm_WrErasePrm(void)
{
    Uint16 i = 0U;
    Uint16 l_uiIdxPrmTbl = 0U;
    Uint16 l_uiAddrData = 0U;
    Uint16 l_uiFlgWrRead = 0U;
    Uint16 l_uiFlgNonErased  = 0U;

    stEepLoc.stPrmExt.stEepErr.all = 0U;

    /* After the parameter table is updated, the default parameters of the current country are restored */
    v_Eep_Cmn_RldDftCtry();

    l_uiIdxPrmTbl = MasterSaveEEPromIndex[MASTER_SAVE_NUM-1U];          ///< Table index
    l_uiAddrData = sFuncCode[l_uiIdxPrmTbl].MasterSaveAddr;             ///< Master save address

    if(l_uiAddrData > (I2C_EEPROM_ADDR1 - 4U))
    {
        stEepLoc.stPrmExt.stEepErr.bit.uiErrAddrOver = 1U;
    }

    for(i = 0U; i < MASTER_SAVE_NUM; i++)
    {     
        l_uiIdxPrmTbl = MasterSaveEEPromIndex[i];
        l_uiFlgWrRead = (sFuncCode[l_uiIdxPrmTbl].uiModifyAndDataType & 0x0002U) >> 1;
        l_uiFlgNonErased = (sFuncCode[l_uiIdxPrmTbl].uiModifyAndDataType & 0x0200U) >> 9;

        if((1U == l_uiFlgWrRead) && (0U == l_uiFlgNonErased))
        {  
            v_Eep_RcvPrm_WrByIdx(&stEepLoc.stI2cPrm, l_uiIdxPrmTbl);    ///< Write data by index
        }

        if(stEepLoc.stPrmExt.stEepErr.all != 0U)
        {
            break;
        }
    }

    if(stEepLoc.stPrmExt.stEepErr.all == 0U)
    {
        IIC_WRITE_ENABLE;   ///< I2C write enable

        stEepLoc.stI2cPrm.uiAddrMem = PARA_VER_ADDR;     ///< Memory address
        stEepLoc.stI2cPrm.uiBufMsgWr[0] = PARAM_VER;
        stEepLoc.stI2cPrm.uiNumOfWords = 1U;                ///< Number of word
        l_uiFlgWrRead = 0U;

        if(I2C_RETURN_WRITE_SUCESS == ui_EepDrv_WrWait(&stEepLoc.stI2cPrm))     ///< Write parameter
        {
            l_uiFlgWrRead = ui_EepDrv_RdWait(&stEepLoc.stI2cPrm);
        }
        /* After the data is written, the data is read */
        if(l_uiFlgWrRead != I2C_RETURN_READ_SUCESS)
        {
            (void)ui_EepDrv_RdWordData(&stEepLoc.stI2cPrm,0U);
        }

        if(stEepLoc.stI2cPrm.uiBufMsgWr[0] != stEepLoc.stI2cPrm.uiBufMsgRead[0])
        {
            stEepLoc.stPrmExt.stEepErr.bit.uiErrEep = 1U;             ///<  The write and read data are inconsistent, indicating a fault
        }
        else
        {
            stEepLoc.stI2cPrm.uiAddrMem = PARA_SAVED_ADDR;       ///< Memory address
            stEepLoc.stI2cPrm.uiBufMsgWr[0] = EEPROM_SAVED;
            stEepLoc.stI2cPrm.uiNumOfWords = 1U;                     ///< Number of word

            l_uiFlgWrRead = 0U;
            if(I2C_RETURN_WRITE_SUCESS == ui_EepDrv_WrWait(&stEepLoc.stI2cPrm))
            {
                l_uiFlgWrRead = ui_EepDrv_RdWait(&stEepLoc.stI2cPrm);
            }
            /* After the data is written, the data is read */
            if(l_uiFlgWrRead != I2C_RETURN_READ_SUCESS)
            {
                (void)ui_EepDrv_RdWordData(&stEepLoc.stI2cPrm, 0U);
            }
            if(stEepLoc.stI2cPrm.uiBufMsgWr[0] != stEepLoc.stI2cPrm.uiBufMsgRead[0])
            {
                stEepLoc.stPrmExt.stEepErr.bit.uiErrEep = 1U;
            }
#if 0U == FLG_SWUT_EN
            else
            {
                stEepLoc.stI2cPrm.uiAddrMem     = SOFT_VER_ADDR;
                stEepLoc.stI2cPrm.uiBufMsgWr[0] = DSP_SOFT_VERSON;
                stEepLoc.stI2cPrm.uiNumOfWords = 1U;
                (void)ui_EepDrv_WrWordData(&stEepLoc.stI2cPrm, 0U);

                l_uiFlgWrRead = 0U;
                if(I2C_RETURN_WRITE_SUCESS == ui_EepDrv_WrWait(&stEepLoc.stI2cPrm))
                {
                    l_uiFlgWrRead = ui_EepDrv_RdWait(&stEepLoc.stI2cPrm);
                }

                if(l_uiFlgWrRead != I2C_RETURN_READ_SUCESS)
                {
                    (void)ui_EepDrv_RdWordData(&stEepLoc.stI2cPrm, 0U);
                }

                if(stEepLoc.stI2cPrm.uiBufMsgWr[0] != stEepLoc.stI2cPrm.uiBufMsgRead[0])
                {
                    stEepLoc.stPrmExt.stEepErr.bit.uiErrEep = 1U;
                }
            }
#endif
        }
    }
    else
    {
        stEepLoc.stPrmExt.stEepErr.bit.uiErrInit = 1U;
        IIC_WRITE_ENABLE;
        stEepLoc.stI2cPrm.uiAddrMem = PARA_SAVED_ADDR;
        stEepLoc.stI2cPrm.uiBufMsgWr[0] = 0x1111U;
        stEepLoc.stI2cPrm.uiNumOfWords = 1U;
        (void)ui_EepDrv_WrWait(&stEepLoc.stI2cPrm);

        stEepLoc.stI2cPrm.uiAddrMem = PARA_VER_ADDR;
        stEepLoc.stI2cPrm.uiBufMsgWr[0] = 0xBBBBU;
        stEepLoc.stI2cPrm.uiNumOfWords = 1U;
        (void)ui_EepDrv_WrWait(&stEepLoc.stI2cPrm);

        stEepLoc.stI2cPrm.uiAddrMem = SOFT_VER_ADDR;
        stEepLoc.stI2cPrm.uiBufMsgWr[0] = 0xCCCCU;
        stEepLoc.stI2cPrm.uiNumOfWords = 1U;
        (void)ui_EepDrv_WrWait(&stEepLoc.stI2cPrm);
    }
}

/******************************************************************************************************/
/**
 * @brief:Store the data to the specified address
 * @param [in]
 * @param [out]
 * @return
 */
static void v_Eep_RcvPrm_DataToRAM(Uint16 uiNum, Uint16 uiDataType, ST_I2C_handle p)
{
    static Uint16 i = 0U;

    switch(uiDataType)
    {
        case DATA_INT16 :
        case DATA_UINT16:
            *(sFuncCode[uiNum].ParaAddr) = p->uiBufMsgRead[0];      ///< int16 or Uint16
            break;

        case DATA_INT32  :
        case DATA_UINT32 :
        case DATA_FLOAT32:
            *(sFuncCode[uiNum].ParaAddr)     = p->uiBufMsgRead[0];   ///< int32,Uint32 or float32
            *(sFuncCode[uiNum].ParaAddr + 1) = p->uiBufMsgRead[1];
            break;

        case DATA_STRING :
            for(i = 0U; i < NUM_WORD_STRING; i++)
            {
                *(Uint16 *)(sFuncCode[uiNum].ParaAddr + 2U * i)     = (p->uiBufMsgRead[i] >> 8) & 0xFFU;           ///< String data stores are also 16 bits
                *(Uint16 *)(sFuncCode[uiNum].ParaAddr + 2U * i + 1) = p->uiBufMsgRead[i] & 0xFFU;
            }
            break;

        default:
            i = 0U;
            break;
    }
}

/******************************************************************************************************/
/**
 * @brief   Eep 1ms task
 * @param [in]  EepromAddr
 * @param [in]  DataLen
 * @param [in]  puiDataAddr
 * @param [out] I2C_RETURN_READ_SUCESS
 * @return
 */
/******************************************************************************************************/
void v_Eep_1ms(void)
{
    if(STOP_CMD == stComIf.uiCmdRun)    ///< Stop command
    {
        switch(stEep.stCmdPrm.uiCmd)
        {
            case SAVE_ERASABLE_PARA:      ///< Save erasable parameter
                stEepLoc.stPrmExt.stCmdPrm.uiCmd = SAVE_ERASABLE_PARA;

                if(stEepLoc.stPrmExt.stCmdPrm.uiNumSaved < MASTER_SAVE_NUM)
                {
                    stEepLoc.uiIdxAry[0] = MasterSaveEEPromIndex[stEepLoc.stPrmExt.stCmdPrm.uiNumSaved];
                    if(1U == ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stEepLoc.uiIdxAry[0], 1U))
                    {
                        stEepLoc.stPrmExt.stCmdPrm.uiNumSaved++;
                    }
                }
                else
                {
                    if(0U == stEep.stQuePrmChg.uiDataLength)
                    {
                        stEepLoc.stPrmExt.stCmdPrm.uiNumSaved = 0U;
                        stEepLoc.stPrmExt.stCmdPrm.uiCmd      = WAIT_CMD;
                    }
                }
                break;

            case SAVE_NONERASE_PARA:     ///< Save non-erasable parameter
                stEepLoc.stPrmExt.stCmdPrm.uiCmd = SAVE_NONERASE_PARA;

                if(stEepLoc.stPrmExt.stCmdPrm.uiNumSaved < MASTER_NONERASE_SAVE_NUM)
                {
                    stEepLoc.uiIdxAry[0] = MasterNonEraseEEPromIndex[stEepLoc.stPrmExt.stCmdPrm.uiNumSaved];
                    if (1U == ui_Eep_DataEnQue(&stEep.stQuePrmChg, &stEepLoc.uiIdxAry[0], 1U))
                    {
                        stEepLoc.stPrmExt.stCmdPrm.uiNumSaved++;
                    }
                }
                else
                {
                    if(0U == stEep.stQuePrmChg.uiDataLength)
                    {
                        stEepLoc.stPrmExt.stCmdPrm.uiNumSaved = 0U;
                        stEepLoc.stPrmExt.stCmdPrm.uiCmd = WAIT_CMD;
                    }
                }
                break;

            case RELOAD_ERASABLE_PARA:    ///< Initialize erasable parameter
                v_AppInit_ASW_Modl();        ///< ASW module initialization
                v_Com_Rx_Tsk_EepPrmUpd();    ///< EEPROM related parameter update
                /* Switch to SAVE_ERASABLE_PARA state */
                stEepLoc.stPrmExt.stCmdPrm.uiCmd      = SAVE_ERASABLE_PARA;
                stEepLoc.stPrmExt.stCmdPrm.uiNumSaved = 0U;
                break;

            case RELOAD_NONERASE_PARA:    ///< Initialize AD parameter
                v_Com_NonEraPrm_Init();      ///< Non-erasable Parameter initialization
                v_Com_Rx_Tsk_EepPrmUpd();    ///< EEPROM related parameter update
                /* Switch to SAVE_NONERASE_PARA state */
                stEepLoc.stPrmExt.stCmdPrm.uiCmd      = SAVE_NONERASE_PARA;
                stEepLoc.stPrmExt.stCmdPrm.uiNumSaved = 0U;
                break;

            case RELOAD_V2G_PARA:         ///< Initialize V2G parameter
                v_Eep_Cmn_RldDftCtry();      ///< Grid connection parameters initialization
                v_Com_Rx_Tsk_EepPrmUpd();    ///< EEPROM related parameter update
                /* Switch to SAVE_ERASABLE_PARA state */
                stEepLoc.stPrmExt.stCmdPrm.uiCmd      = SAVE_ERASABLE_PARA;
                stEepLoc.stPrmExt.stCmdPrm.uiNumSaved = 0U;
                break;

            default:
                stEepLoc.stPrmExt.stCmdPrm.uiNumSaved = 0U;
                break;
        }
    }

    /* Eep parameter handle state machine task */
    v_Eep_PrmHndl_StMac_1ms();

    /* Output parameter */
#if (1U == EEP_DBG)
    stEep.stEepErr.all           = stEepDbg.stEepErr.all;
    stEep.stCmdPrm.uiCmd         = stEepDbg.stCmdPrm.uiCmd;
    stEep.stCmdPrm.uiIndexPrm[0] = stEepDbg.stCmdPrm.uiIndexPrm[0];
    stEep.stCmdPrm.uiNumSaved    = stEepDbg.stCmdPrm.uiNumSaved;
#else
    stEep.stEepErr.all           = stEepLoc.stPrmExt.stEepErr.all;
    stEep.stCmdPrm.uiCmd         = stEepLoc.stPrmExt.stCmdPrm.uiCmd;
    stEep.stCmdPrm.uiIndexPrm[0] = stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0];
    stEep.stCmdPrm.uiNumSaved    = stEepLoc.stPrmExt.stCmdPrm.uiNumSaved;
#endif

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn1ms)
    {
        printf("****SWIT DynamicTest: function v_Eep_1ms() is running****\r\n"); 
    }
#endif
}

/******************************************************************************************************/
/**
 * @brief   Eep parameter handle state machine task
 * @param [in]  null
 * @param [in]  null
 * @param [out] null
 * @return
 */
/******************************************************************************************************/
static void v_Eep_PrmHndl_StMac_1ms(void)
{
    switch(stEepLoc.stI2cSt.uiStsPrmHndl)
    {
        case WAIT_CHECK:
            if((stEep.stQuePrmChg.uiDataLength > 0U) && (I2C_BUS_FREE == stEepLoc.stI2cPrm.uiStsMsgBus))    ///< Need write parameter to EEPROM
            {
                v_Eep_PrmHndl_StMac_Chk_1ms();    ///< Eep parameter handle state machine check task
            }
            break;

        case WRITE_EEPROM:
            v_Eep_PrmHndl_StMac_Wr_1ms();        ///< Eep parameter handle state machine write task
            break;

        default:
            stEepLoc.stI2cSt.uiStsWr = WAIT_CHECK;
            break;
    }
}

/******************************************************************************************************/
/**
 * @brief   Eep parameter handle state machine check 1ms task
 * @param [in]  null
 * @param [in]  null
 * @param [out] null
 * @return
 */
/******************************************************************************************************/
static void v_Eep_PrmHndl_StMac_Chk_1ms(void)
{
    Uint16 i = 0U;
    Uint16 l_uiDataLow = 0U;
    Uint16 l_uiDataHi  = 0U;

    if(1U == ui_Eep_DataDeQue(&stEep.stQuePrmChg, &stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0], 1U))
    {
        stEepLoc.stI2cSt.uiTypPrm      = (sFuncCode[stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0]].uiModifyAndDataType & DATA_TYPE_MASK);
        stEepLoc.stI2cSt.uiFlgNonErase = (sFuncCode[stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0]].uiModifyAndDataType & DATA_NONERASE_FLAG);
        stEepLoc.stI2cSt.uiAddrPrmEep  = sFuncCode[stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0]].MasterSaveAddr;
        stEepLoc.stI2cSt.uiPrmLen      = uiTypPrmLen[(stEepLoc.stI2cSt.uiTypPrm>>6)];

        if(stEepLoc.stI2cSt.uiFlgNonErase > 0U)    ///< Non_erase parameter
        {
            stEepLoc.stI2cSt.uiAddrSecBas  = I2C_EEPROM_NONERASE_ADDR1;
            stEepLoc.stI2cSt.uiAddrThrdBas = I2C_EEPROM_NONERASE_ADDR2;
        }
        else    ///< Erasable parameter
        {
            stEepLoc.stI2cSt.uiAddrSecBas  = I2C_EEPROM_ADDR1;
            stEepLoc.stI2cSt.uiAddrThrdBas = I2C_EEPROM_ADDR2;
        }

        if((DATA_INT16 == stEepLoc.stI2cSt.uiTypPrm) || (DATA_UINT16 == stEepLoc.stI2cSt.uiTypPrm))    ///< 16 bit parameter
        {
            /* Stored as word in the parameter buffer */
            *(stEepLoc.stI2cPrm.uiBufMsgWr) = *(Uint16*)(sFuncCode[stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0]].ParaAddr);
        }
        else if((DATA_INT32 == stEepLoc.stI2cSt.uiTypPrm) || (DATA_UINT32 == stEepLoc.stI2cSt.uiTypPrm) || (DATA_FLOAT32 == stEepLoc.stI2cSt.uiTypPrm))    ///< 32 bit parameter
        {
            /* Stored as word in the parameter buffer */
            *(stEepLoc.stI2cPrm.uiBufMsgWr)      = *(Uint16*)(sFuncCode[stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0]].ParaAddr);
            *(stEepLoc.stI2cPrm.uiBufMsgWr + 1U) = *(Uint16*)(sFuncCode[stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0]].ParaAddr + 1);
        }
        else if(DATA_STRING == stEepLoc.stI2cSt.uiTypPrm)    ///< string parameter
        {
            /* String data is processed in word on the next computer */
            for(i = 0U; i < NUM_WORD_STRING; i++)
            {
                l_uiDataHi  = *((Uint16*)sFuncCode[stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0]].ParaAddr + 2U * i );    ///<The data in the address is assigned to the array for transmission
                l_uiDataLow = *((Uint16*)sFuncCode[stEepLoc.stPrmExt.stCmdPrm.uiIndexPrm[0]].ParaAddr + 2U * i + 1U);
                stEepLoc.stI2cPrm.uiBufMsgWr[i] = (l_uiDataHi << 8 | l_uiDataLow);
            }
        }
        else
        {
            ///< No code
        }

        /* Switch to WRITE_EEPROM state */
        stEepLoc.stI2cSt.uiStsPrmHndl  = WRITE_EEPROM;
        stEepLoc.stI2cSt.uiStsWr       = FIRST_WRITE;
        stEepLoc.stI2cPrm.uiStsMsgBus  = I2C_BUS_ON_PARA;
    }
}

/******************************************************************************************************/
/**
 * @brief   Eep parameter handle state machine write 1ms task
 * @param [in]  null
 * @param [in]  null
 * @param [out] null
 * @return
 */
/******************************************************************************************************/
static void v_Eep_PrmHndl_StMac_Wr_1ms(void)
{
    Uint16 i = 0U;

    switch(stEepLoc.stI2cSt.uiStsWr)
    {
        case FIRST_WRITE:       ///< First Write
            IIC_WRITE_ENABLE;

            stEepLoc.stI2cPrm.uiAddrMem    = stEepLoc.stI2cSt.uiAddrPrmEep;
            stEepLoc.stI2cPrm.uiNumOfWords = stEepLoc.stI2cSt.uiPrmLen;
            if(PARA_EEPROM_WRITE_SUCESS == ui_EepDrv_Wr(&stEepLoc.stI2cPrm))
            {
                stEepLoc.stI2cSt.uiStsWr = FIRST_READ;    ///< Switch to first read state
            }
            break;

        case FIRST_READ:        ///< First Read
            if(PARA_EEPROM_READ_SUCESS == ui_EepDrv_Rd(&stEepLoc.stI2cPrm))
            {
                /* Check whether the read and write data is equal */
                stEepLoc.stI2cSt.uiPrmOper = 0U;
                for(i = 0U; i < stEepLoc.stI2cPrm.uiNumOfWords; i++)
                {
                    if(stEepLoc.stI2cPrm.uiBufMsgWr[i] != stEepLoc.stI2cPrm.uiBufMsgRead[i])
                    {
                        stEepLoc.stI2cSt.uiPrmOper = 1U;
                        stEepLoc.stPrmExt.stEepErr.bit.uiErrMaiFirstRead = 1U;
                    }
                }
                if(0U == stEepLoc.stI2cSt.uiPrmOper)
                {
                    stEepLoc.stI2cSt.uiStsWr = SECOND_WRITE;    ///< Switch to second write state
                }
                else
                {
                    stEepLoc.stI2cSt.uiStsWr = FIRST_WRITE;    ///< Switch to first write state
                    stEepLoc.stI2cSt.uiPrmOper = 0U;
                }
            }
            break;

        case SECOND_WRITE:      ///< Second Write
	        IIC_WRITE_ENABLE;

            stEepLoc.stI2cPrm.uiAddrMem = stEepLoc.stI2cSt.uiAddrPrmEep + stEepLoc.stI2cSt.uiAddrSecBas;
            if(PARA_EEPROM_WRITE_SUCESS == ui_EepDrv_Wr(&stEepLoc.stI2cPrm))
            {
                stEepLoc.stI2cSt.uiStsWr = SECOND_READ;    ///< Switch to second read state
            }
            break;

        case SECOND_READ:       ///< Second Read
            if(I2C_RETURN_READ_SUCESS == ui_EepDrv_Rd(&stEepLoc.stI2cPrm))
            {
                /* Check whether the read and write data is equal */
                stEepLoc.stI2cSt.uiPrmOper = 0U;
                for(i = 0U; i < stEepLoc.stI2cPrm.uiNumOfWords; i++)
                {
                    if(stEepLoc.stI2cPrm.uiBufMsgWr[i] != stEepLoc.stI2cPrm.uiBufMsgRead[i])
                    {
                        stEepLoc.stI2cSt.uiPrmOper = 1U;
                        stEepLoc.stPrmExt.stEepErr.bit.uiErrMaiSecRead = 1U;
                    }
                }
                if(0U == stEepLoc.stI2cSt.uiPrmOper)
                {
                    stEepLoc.stI2cSt.uiStsWr = THIRD_WRITE;    ///< Switch to third read state
                }
                else
                {
                    stEepLoc.stI2cSt.uiStsWr = SECOND_WRITE;    ///< Switch to second write state
                    stEepLoc.stI2cSt.uiPrmOper = 0U;
                }
            }
            break;

        case THIRD_WRITE:       ///< Third Write
            IIC_WRITE_ENABLE;

            stEepLoc.stI2cPrm.uiAddrMem = stEepLoc.stI2cSt.uiAddrPrmEep + stEepLoc.stI2cSt.uiAddrThrdBas;
            if(PARA_EEPROM_WRITE_SUCESS == ui_EepDrv_Wr(&stEepLoc.stI2cPrm))
            {
                stEepLoc.stI2cSt.uiStsWr = THIRD_READ;    ///< Switch to third read state
            }
            break;

        case THIRD_READ:        ///< Third Read
            if(I2C_RETURN_READ_SUCESS == ui_EepDrv_Rd(&stEepLoc.stI2cPrm))
            {
                /* Check whether the read and write data is equal */
                stEepLoc.stI2cSt.uiPrmOper = 0U;
                for(i = 0U; i < stEepLoc.stI2cPrm.uiNumOfWords; i++)
                {
                    if (stEepLoc.stI2cPrm.uiBufMsgWr[i] != stEepLoc.stI2cPrm.uiBufMsgRead[i])
                    {
                        stEepLoc.stI2cSt.uiPrmOper = 1U;
                        stEepLoc.stPrmExt.stEepErr.bit.uiErrMaiThrdRead = 1U;
                    }
                }
                if(0U == stEepLoc.stI2cSt.uiPrmOper)
                {
                    stEepLoc.stI2cSt.uiStsPrmHndl = WAIT_CHECK;
                    stEepLoc.stI2cPrm.uiStsMsgBus = I2C_BUS_FREE;
                    stEepLoc.stI2cSt.uiStsWr      = FIRST_WRITE;
                }
                else
                {
                    stEepLoc.stI2cSt.uiStsWr = THIRD_WRITE;
                    stEepLoc.stI2cSt.uiPrmOper = 0U;
                }
            }
            break;

        default:
            stEepLoc.stI2cSt.uiStsWr = FIRST_WRITE;
            break;
    }
}

/******************************************************************************************************/
/**
* @defgroup DataqueueControl
* @brief    Data queue operation
* @{
* @ingroup ui_Eep_DataDeQue
* @fn  Uint16 ui_Eep_DataDeQue(ST_EEP_DATA_QUE *Que, Uint16 *puiAddrDest, Uint16 uiNum)
* @brief     Data queue out processing
* @details   get out the data in the SPI send data buffer.
* @param[in] *Que          : queue
* @param[in] *puiAddrDest  : The address of the data to be stored
* @param[in] uiNum         : The number of data fetched
* @return
* -# 1 -OK;
* -# 0 -Fail
*/
static Uint16 ui_Eep_DataDeQue(ST_EEP_DATA_QUE *Que, Uint16 *puiAddrDest, Uint16 uiNum)
{
     Uint16 l_uiRetn = 0U;
     int16  l_siNumTmp = 0;
     Uint16 *puiAddrSrcStrt;    ///< Source start address
     Uint16 *puiAddrSrcEnd;     ///< Source end address

    if((Que->uiDataLength >= uiNum) && (uiNum != 0U))
    {
        l_siNumTmp = (int16)Que->uiFront + (int16)uiNum - (int16)Que->QueMax;
        if(l_siNumTmp > 0)
        {
            /* Copy the data from the queue to puiAddrDest[] */
            puiAddrSrcStrt = Que->puiQueBuf  + Que->uiFront;
            puiAddrSrcEnd   = puiAddrSrcStrt + uiNum - (Uint16)l_siNumTmp;
            v_Eep_MemCopy(puiAddrSrcStrt, puiAddrSrcEnd, puiAddrDest);    ///< Copy parameter
            Que->uiFront = ((Que->uiFront + uiNum - (Uint16)l_siNumTmp) % Que->QueMax);
            /* Copy the data from the receiving queue to the puiAddrDest[] */
            puiAddrSrcStrt = Que->puiQueBuf;
            puiAddrSrcEnd = puiAddrSrcStrt + (Uint16)l_siNumTmp;
            v_Eep_MemCopy(puiAddrSrcStrt, puiAddrSrcEnd, puiAddrDest);    ///< Copy parameter
            Que->uiFront = ((Que->uiFront + (Uint16)l_siNumTmp) % Que->QueMax);
        }
        else
        {
            puiAddrSrcStrt = Que->puiQueBuf + Que->uiFront ;
            puiAddrSrcEnd = puiAddrSrcStrt + uiNum;
            v_Eep_MemCopy(puiAddrSrcStrt, puiAddrSrcEnd, puiAddrDest);    ///< Copy parameter
            Que->uiFront = ((Que->uiFront + uiNum) % Que->QueMax);
        }

        Que->uiDataLength = Que->uiDataLength - uiNum;

        l_uiRetn = 1U;     ///< Return Value
    }
    else
    {
        l_uiRetn = 0U;     ///< Return Value
    }
    return l_uiRetn;
}

/****************************************************************************************************/
/**
* @ingroup ui_Eep_DataEnQue
* @fn  Uint16 ui_Eep_DataEnQue(ST_EEP_DATA_QUE *Que,Uint16 *puiDataAddr,Uint16 uiDatalength)
* @brief     Queue processing
* @details   Store the data in the recive data buffer.
* @param[in] *Que          : queue
* @param[in] *puiDataAddr  : The address of the data to be stored
* @param[in] uiDatalength  : The number of data input
* @return  ±êÖ¾
* -# 1 -OK
* -# 0 -Fail
*/
Uint16 ui_Eep_DataEnQue(ST_EEP_DATA_QUE *Que, Uint16 *puiDataAddr, Uint16 uiDatalength)
{
    Uint16 *puiDestAddr;
    Uint16 *puiAddrSrcEnd;
    Uint16 l_uiRetn = 0U;
    int16  l_siNumTmp = 0;

    if((Que->QueMax >= (Que->uiDataLength + uiDatalength)) && (uiDatalength != 0U))
    {
        if(Que->uiRear == Que->QueMax)    ///< The queue reaches its maximum value
        {
            Que->uiRear = 0U;
        }

        l_siNumTmp = (int16)Que->uiRear + (int16)uiDatalength - (int16)Que->QueMax;
        if(l_siNumTmp > 0)    ///< The queue more than maximum value
        {
            puiDestAddr = Que->puiQueBuf + Que->uiRear;
            puiAddrSrcEnd = puiDataAddr + uiDatalength - (Uint16)l_siNumTmp;
            v_Eep_MemCopy(puiDataAddr, puiAddrSrcEnd, puiDestAddr);    ///< Copy parameter
            Que->uiRear = (Que->uiRear +  uiDatalength - (Uint16)l_siNumTmp) % Que->QueMax;

            puiDestAddr = (Que->puiQueBuf + Que->uiRear);
            puiAddrSrcEnd = puiDataAddr + uiDatalength;
            v_Eep_MemCopy((puiDataAddr + uiDatalength - (Uint16)l_siNumTmp), puiAddrSrcEnd, puiDestAddr);    ///< Copy parameter
            Que->uiRear = (Que->uiRear + (Uint16)l_siNumTmp) % Que->QueMax;
        }
        else    ///< The queue not more than its maximum value
        {
            puiDestAddr = Que->puiQueBuf + Que->uiRear;
            puiAddrSrcEnd = puiDataAddr + uiDatalength;
            v_Eep_MemCopy(puiDataAddr, puiAddrSrcEnd, puiDestAddr);    ///< Copy parameter
            Que->uiRear = (Que->uiRear + uiDatalength) % Que->QueMax;
        }
        Que->uiDataLength = Que->uiDataLength + uiDatalength;
        l_uiRetn = 1U;
    }
    else
    {
        l_uiRetn = 0U;
    }
    return l_uiRetn;
}

/******************************************************************************************************/
/**
 * @brief   Memory copy task
 * @param [in] null
 * @param [out] null
 * @return
 */
/******************************************************************************************************/
static void v_Eep_MemCopy(Uint16 *puiAddrSrcStrt, Uint16 *puiAddrSrcEnd, Uint16 *puiAddrDest)
{
    while((Uint32)puiAddrSrcStrt < (Uint32)puiAddrSrcEnd)
    {
        *puiAddrDest++ = *puiAddrSrcStrt++;    ///< Copy parameter to destination address
    }
}


/******************************************************************************************************/
/**
 * @brief   Eep 100ms task
 * @param [in] null
 * @param [out] null
 * @return
 */
/******************************************************************************************************/
void v_Eep_100ms(void)
{
    /* Update Grid standard */
    if(stPfcStMac.unPFCSts.bit.uiMacSt <= PFC_ST_MAC_STB)
    {
        if((stCom.uiStdGridSet != stEepLoc.stPrmExt.uiStdGridSel) && (WAIT_CMD == stEep.stCmdPrm.uiCmd))
        {
            stEepLoc.stPrmExt.uiStdGridSel   = stCom.uiStdGridSet;
            stEepLoc.stPrmExt.stCmdPrm.uiCmd = RELOAD_V2G_PARA;

            /* Output parameter */
#if (1U == EEP_DBG)
            stEep.uiStdGridSel   = stEepDbg.uiStdGridSel;
            stEep.stCmdPrm.uiCmd = stEepDbg.stCmdPrm.uiCmd;
#else
            stEep.uiStdGridSel   = stEepLoc.stPrmExt.uiStdGridSel;
            stEep.stCmdPrm.uiCmd = stEepLoc.stPrmExt.stCmdPrm.uiCmd;
#endif
        }
    }

#if(1U == FLG_SWIT_EN)
    if(FCN_ENABLE == stPerdTsk.uiFlgSWITDyn100ms)
    {
        printf("****SWIT DynamicTest: function v_Eep_100ms() is running****\r\n");
    }
#endif
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
