//==============================================================================================
//    File description
//==============================================================================================
/**@file         ComDrv.c
 * @brief
 * Source file of Com drive.
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
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//=====================================================
//    Include Header Files
//=====================================================
#include "ComDrv.h"

//=====================================================
//    Variable Definition
//=====================================================
#if(1U == COM_MODE)
ST_COM_DRV stComDrv;                  ///< Communication drive global struct

#if(1U == FLG_SWUT_EN)
struct CAN_REGS CanRegsUnitTest;
#endif
#if (1U == COM_DRV_DBG)
ST_EPWM_DRV stComDrvDbg;              ///< Communication drive debug global struct
#endif

static ST_COM_DRV_LOC stComDrvLoc;    ///< Communication drive local global struct

//=====================================================
//    Function definition
//=====================================================
/********************************************Begin*********************************************/
/**
 * @brief        Com drive initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_ComDrv_Init(void)
{
    Uint16 i = 0U;

    stComDrvLoc.stPrmExt.uiFlgRxOk      = 0U;           ///< Initialize to 0U
    stComDrvLoc.stPrmExt.uiFlgTxOk      = 0U;           ///< Initialize to 0U
    stComDrvLoc.stPrmExt.unIDMaskRx.all = CAN_RX_ID;    ///< Initialize to 0x175A00FFUL

    /* Global Signal*/
#if (1U == COM_DRV_DBG)
    stComDrvDbg.uiFlgRxOk       = stComDrvLoc.stPrmExt.uiFlgRxOk;
    stComDrvDbg.uiFlgTxOk       = stComDrvLoc.stPrmExt.uiFlgTxOk;
    stComDrvDbg.unIDMaskRx.all  = stComDrvLoc.stPrmExt.unIDMaskRx.all;

    stComDrv.uiFlgRxOk          = stComDrvDbg.uiFlgTxOk;
    stComDrv.uiFlgTxOk          = stComDrvDbg.uiFlgRxOk;
    stComDrv.unIDMaskRx.all     = stComDrvDbg.unIDMaskRx.all;
#else
    stComDrv.uiFlgRxOk          = stComDrvLoc.stPrmExt.uiFlgRxOk;
    stComDrv.uiFlgTxOk          = stComDrvLoc.stPrmExt.uiFlgTxOk;
    stComDrv.unIDMaskRx.all     = stComDrvLoc.stPrmExt.unIDMaskRx.all;
#endif
    for(i = 0U; i < 8U; i++)
    {
        stComDrvLoc.stPrmExt.uiByteRx[i] = 0U;   ///< Initialize Can RX Byte to 0U
        stComDrv.uiByteRx[i]             = 0U;   ///< Initialize Can RX Byte to 0U
    }

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_ComDrv_Init() is running****\r\n");
#endif
}

/**
* @brief   CAN Read data
* @param [in]  param piData is a pointer to the message object's data
*              param uiSize is the number of bytes of data in the message object (0-8)
* @param [out] null
* @return null
*/
static void v_ComDrv_Rx_Msg_Data(Uint16 *piData, Uint16 uiSize)
{
    switch(uiSize)
    {
        /* 1 byte data */
        case 0x01U:
            piData[0] = CANX_REGS.CAN_IF2DATA.bit.Data_0;
            break;
        /* 2 byte data */
        case 0x02U:
            piData[0] = CANX_REGS.CAN_IF2DATA.bit.Data_0;
            piData[1] = CANX_REGS.CAN_IF2DATA.bit.Data_1;
            break;
        /* 3 byte data */
        case 0x03U:
            piData[0] = CANX_REGS.CAN_IF2DATA.bit.Data_0;
            piData[1] = CANX_REGS.CAN_IF2DATA.bit.Data_1;
            piData[2] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_2;
            break;
        /* 4 byte data */
        case 0x04U:
            piData[0] = CANX_REGS.CAN_IF2DATA.bit.Data_0;
            piData[1] = CANX_REGS.CAN_IF2DATA.bit.Data_1;
            piData[2] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_2;
            piData[3] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_3;
            break;
        /* 5 byte data */
        case 0x05U:
            piData[0] = CANX_REGS.CAN_IF2DATA.bit.Data_0;
            piData[1] = CANX_REGS.CAN_IF2DATA.bit.Data_1;
            piData[2] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_2;
            piData[3] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_3;
            piData[4] = CANX_REGS.CAN_IF2DATB.bit.Data_4;
            break;
        /* 6 byte data */
        case 0x06U:
            piData[0] = CANX_REGS.CAN_IF2DATA.bit.Data_0;
            piData[1] = CANX_REGS.CAN_IF2DATA.bit.Data_1;
            piData[2] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_2;
            piData[3] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_3;
            piData[4] = CANX_REGS.CAN_IF2DATB.bit.Data_4;
            piData[5] = CANX_REGS.CAN_IF2DATB.bit.Data_5;
            break;
        /* 7 byte data */
        case 0x07U:
            piData[0] = CANX_REGS.CAN_IF2DATA.bit.Data_0;
            piData[1] = CANX_REGS.CAN_IF2DATA.bit.Data_1;
            piData[2] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_2;
            piData[3] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_3;
            piData[4] = CANX_REGS.CAN_IF2DATB.bit.Data_4;
            piData[5] = CANX_REGS.CAN_IF2DATB.bit.Data_5;
            piData[6] = (Uint16)CANX_REGS.CAN_IF2DATB.bit.Data_6;
            break;
        /* 8 byte data */
        case 0x08U:
            piData[0] = CANX_REGS.CAN_IF2DATA.bit.Data_0;
            piData[1] = CANX_REGS.CAN_IF2DATA.bit.Data_1;
            piData[2] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_2;
            piData[3] = (Uint16)CANX_REGS.CAN_IF2DATA.bit.Data_3;
            piData[4] = CANX_REGS.CAN_IF2DATB.bit.Data_4;
            piData[5] = CANX_REGS.CAN_IF2DATB.bit.Data_5;
            piData[6] = (Uint16)CANX_REGS.CAN_IF2DATB.bit.Data_6;
            piData[7] = (Uint16)CANX_REGS.CAN_IF2DATB.bit.Data_7;
            break;

        default:
            ///< No code
            break;
    }
}

/**
* @brief   Write CAN Data
* @param [in]  param piData is a pointer to the message object's data
*              param uiSize is the number of bytes of data in the message object (0-8)
* @param [out] null
* @return null
*/
static void v_ComDrv_Tx_Msg_Data(Uint16 *piData, Uint16 uiSize)
{
    switch(uiSize)
    {
        /* 1 byte data */
        case 0x01:
            CANX_REGS.CAN_IF1DATA.bit.Data_0 = piData[0];
            break;
        /* 2 byte data */
        case 0x02:
            CANX_REGS.CAN_IF1DATA.bit.Data_0 = piData[0];
            CANX_REGS.CAN_IF1DATA.bit.Data_1 = piData[1];
            break;
        /* 3 byte data */
        case 0x03:
            CANX_REGS.CAN_IF1DATA.bit.Data_0 = piData[0];
            CANX_REGS.CAN_IF1DATA.bit.Data_1 = piData[1];
            CANX_REGS.CAN_IF1DATA.bit.Data_2 = piData[2];
            break;
        /* 4 byte data */
        case 0x04:
            CANX_REGS.CAN_IF1DATA.bit.Data_0 = piData[0];
            CANX_REGS.CAN_IF1DATA.bit.Data_1 = piData[1];
            CANX_REGS.CAN_IF1DATA.bit.Data_2 = piData[2];
            CANX_REGS.CAN_IF1DATA.bit.Data_3 = piData[3];
            break;
        /* 5 byte data */
        case 0x05:
            CANX_REGS.CAN_IF1DATA.bit.Data_0 = piData[0];
            CANX_REGS.CAN_IF1DATA.bit.Data_1 = piData[1];
            CANX_REGS.CAN_IF1DATA.bit.Data_2 = piData[2];
            CANX_REGS.CAN_IF1DATA.bit.Data_3 = piData[3];
            CANX_REGS.CAN_IF1DATB.bit.Data_4 = piData[4];
            break;
        /* 6 byte data */
        case 0x06:
            CANX_REGS.CAN_IF1DATA.bit.Data_0 = piData[0];
            CANX_REGS.CAN_IF1DATA.bit.Data_1 = piData[1];
            CANX_REGS.CAN_IF1DATA.bit.Data_2 = piData[2];
            CANX_REGS.CAN_IF1DATA.bit.Data_3 = piData[3];
            CANX_REGS.CAN_IF1DATB.bit.Data_4 = piData[4];
            CANX_REGS.CAN_IF1DATB.bit.Data_5 = piData[5];
            break;
        /* 7 byte data */
        case 0x07:
            CANX_REGS.CAN_IF1DATA.bit.Data_0 = piData[0];
            CANX_REGS.CAN_IF1DATA.bit.Data_1 = piData[1];
            CANX_REGS.CAN_IF1DATA.bit.Data_2 = piData[2];
            CANX_REGS.CAN_IF1DATA.bit.Data_3 = piData[3];
            CANX_REGS.CAN_IF1DATB.bit.Data_4 = piData[4];
            CANX_REGS.CAN_IF1DATB.bit.Data_5 = piData[5];
            CANX_REGS.CAN_IF1DATB.bit.Data_6 = piData[6];
            break;
        /* 8 byte data */
        case 0x08:
            CANX_REGS.CAN_IF1DATA.bit.Data_0 = piData[0];
            CANX_REGS.CAN_IF1DATA.bit.Data_1 = piData[1];
            CANX_REGS.CAN_IF1DATA.bit.Data_2 = piData[2];
            CANX_REGS.CAN_IF1DATA.bit.Data_3 = piData[3];
            CANX_REGS.CAN_IF1DATB.bit.Data_4 = piData[4];
            CANX_REGS.CAN_IF1DATB.bit.Data_5 = piData[5];
            CANX_REGS.CAN_IF1DATB.bit.Data_6 = piData[6];
            CANX_REGS.CAN_IF1DATB.bit.Data_7 = piData[7];
            break;

        default:
            ///< No code
            break;
    }
}

/**
* @brief   Read the data in a Message Object
* @param [in]  param uiMsgLen is the number of bytes of data in the message object (0-8)
*              param piMsgData is a pointer to the message object's data
* @param [out] null
* @return null
*/
static void v_ComDrv_Rx_Msg(Uint16 uiObjID, Uint16 uiMsgLen)
{
    Uint32 l_ulMsgCtrl = 0U;

    /* Check the arguments */
    if((0UL < uiObjID) && (uiObjID <= 32UL))
    {
        /* Set the Message Data A, Data B, and control values to be read
         * on request for data from the message object.
         * Transfer the message object to the message object IF register. */
        CANX_REGS.CAN_IF2CMD.all = (0x20000UL | 0x10000UL | 0x100000UL | (uiObjID & 0xFFUL) | 0x200000UL);

#if(0U == FLG_SWUT_EN)
        /* Wait for busy bit to clear */
        while((CANX_REGS.CAN_IF2CMD.all & 0x8000UL) == 0x8000UL)
        {
            ///< No code
        }
#endif
        /* Read out the IF control Register. */
        l_ulMsgCtrl = CANX_REGS.CAN_IF2MCTL.all;

        /* See if there is new data available. */
        if((l_ulMsgCtrl & 0x8000UL) == 0x8000UL)
        {
            /* Read out the data from the CAN registers. */
            v_ComDrv_Rx_Msg_Data(stComDrv.uiByteRx, uiMsgLen);

            /* Now clear out the new data flag */
            CANX_REGS.CAN_IF2CMD.all = (0x40000UL | (uiObjID & 0xFFUL));

#if(0U == FLG_SWUT_EN)
            /* Wait for busy bit to clear */
            while((CANX_REGS.CAN_IF2CMD.all & 0x8000UL) == 0x8000UL)
            {
                // No code
            }
#endif
            stComDrvLoc.stPrmExt.uiFlgRxOk    = 1U;                            ///< A Frame of Data is Received
            stComDrvLoc.stPrmExt.unIDMaskRx.all = CANX_REGS.CAN_IF2ARB.bit.ID;   ///< Record the received frame identifier
        }
        else
        {
            stComDrvLoc.stPrmExt.uiFlgRxOk    = 0U;
        }
    }

    /* Global Signal*/
#if (1U == COM_DRV_DBG)
    stComDrv.uiFlgRxOk       = stComDrvDbg.uiFlgRxOk;
    stComDrv.unIDMaskRx.all    = stComDrvDbg.unIDMaskRx.all;
#else
    stComDrv.uiFlgRxOk       = stComDrvLoc.stPrmExt.uiFlgRxOk;
    stComDrv.unIDMaskRx.all    = stComDrvLoc.stPrmExt.unIDMaskRx.all;
#endif
}

/**
* @brief   Sends a Message
* @param [in]  param uiObjID is the object number to configure (1-32).
*              param ulMsgID is the CAN message identifier used for the 11 or 29 bit identifiers;
*              param uiMsgLen is the number of bytes of data in the message object (0-8)
*              param piMsgData is a pointer to the message object's data
* @param [out] null
* @return null
*/
static void v_ComDrv_Tx_Msg(Uint16 uiObjID, Uint32 ulMsgID, Uint16 uiMsgLen, Uint16 *piMsgData)
{
    Uint32 l_ulmsgCtrl = 0U;
    Uint16 l_uiFlg = 0U;

#ifndef _SIMULATION_NO_DSP_
    v_CanCfg_SetupMsgObj(CAN_TX_BOX, ulMsgID, CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX, 0UL, CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);
#endif

    // Check the arguments.
    if((uiObjID <= 0UL) || (uiObjID > 32UL) || (uiMsgLen > 8U))
    {
        l_uiFlg = 1U;
    }

    if(0U == l_uiFlg)
    {
        /* Set IF command to read message object control value
         * Set up the request for data from the message object.
         * Transfer the message object to the IF register. */
        CANX_REGS.CAN_IF1CMD.all = (0x100000UL | (uiObjID & 0xFFUL));

#if(0U == FLG_SWUT_EN)
        /* Wait for busy bit to clear */
        while((CANX_REGS.CAN_IF1CMD.all & 0x8000UL) == 0x8000UL)
        {
        }
#endif
        /* Read IF message control */
//        l_ulmsgCtrl = CANX_REGS.CAN_IF1MCTL.all;
        /* Check provided DLC size with actual Message DLC size */
        if(CANX_REGS.CAN_IF1MCTL.bit.DLC == uiMsgLen)
        {
            v_ComDrv_Tx_Msg_Data(piMsgData, uiMsgLen);
        }

        /* Set Data to be transferred from IF */
        if(uiMsgLen > 0U)
        {
            l_ulmsgCtrl = 0x10000UL | 0x20000UL;
        }
        else
        {
            l_ulmsgCtrl = 0UL;
        }
        /* Set Direction to write.
         * Set Tx Request Bit.
         * Transfer the message object to the message object specified by uiObjID. */
        CANX_REGS.CAN_IF1CMD.all = (l_ulmsgCtrl | 0x800000UL | 0x40000UL | (uiObjID & 0xFFUL));
    }
}

/**
* @brief   Transmission OK flag
* @param [in]  null
* @param [out] null
* @return null
*/
void v_ComDrv_TxOkFlg(void)
{
    stComDrvLoc.stPrmExt.uiFlgTxOk = CANX_REGS.CAN_ES.bit.TxOk;

    /* Global Signal*/
#if (1U == COM_DRV_DBG)
    stComDrv.uiFlgTxOk = stComDrvDbg.uiFlgTxOk;
#else
    stComDrv.uiFlgTxOk = stComDrvLoc.stPrmExt.uiFlgTxOk;
#endif
}

/**
* @brief   Receive Message
* @param [in]  null
* @param [out] null
* @return null
*/
void v_ComDrv_Rx(void)
{
    /* Configure Receive email */
    v_ComDrv_Rx_Msg(CAN_RX_BOX, MSG_DATA_LENGTH);
}

/**
* @brief   Transmission Message
* @param [in]  null
* @param [out] null
* @return null
*/
void v_ComDrv_Tx(void)
{
    if(1U == stCom.uiFlgTxMsg)
    {
        /* Configure Transmit email */
        v_ComDrv_Tx_Msg(CAN_TX_BOX, stCom.unIDMaskTx.all, MSG_DATA_LENGTH, stCom.uiByteTx);    ///< Transmit Data
    }
}

#endif
#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
