
//==============================================================================================
//    File description
//==============================================================================================
/**@file         SciDrv.c
 * @brief
 * The source file of Sci Drive is designed to realize SCI communication.
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
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "SciDrv.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
#if(0U == COM_MODE)

ST_COM_DRV stComDrv;                  ///< Communication drive global struct
#if (1U == SCI_DRV_DBG)
ST_COM_DRV stComDrvDbg;               ///< Communication drive debug global struct
#endif

static ST_COM_DRV_LOC stComDrvLoc;      ///< Sci drive local struct

static Uint16 uiCrcTbl[256] =           ///< CRC16 check table
{
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

//==============================================================================================
//    Function definition
//==============================================================================================
/**
 * @brief        Com drive initialization task
 * @param [in]   null
 * @param [out]  null
 * @return       null
 * @see          SWDD-xxxx
 */
void v_SciDrv_Init(void)
{
    Uint16 i = 0U;

    stComDrvLoc.uiCntrRx                = 0U;           ///< Initialize to 0U
    stComDrvLoc.uiFlgRxFrmOk            = 0U;           ///< Initialize to 0U
    stComDrvLoc.uiCntrRxEnd             = 0U;           ///< Initialize to 0U
    stComDrvLoc.uiFlgTxReq              = 0U;           ///< Initialize to 0U
    stComDrvLoc.uiCntrTx                = 0U;           ///< Initialize to 0U
    stComDrvLoc.stPrmExt.uiFlgRxOk      = 0U;           ///< Initialize to 0U
    stComDrvLoc.stPrmExt.uiFlgTxOk      = 0U;           ///< Initialize to 0U
    stComDrvLoc.stPrmExt.unIDMaskRx.all = CAN_RX_ID;    ///< Initialize to 0x175A00FFUL
    /* Global Signal*/
#if (1U == SCI_DRV_DBG)
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
    for(i = 0U; i < SCI_FRAME_LEN; i++)
    {
        stComDrvLoc.uiRxBuf[i]           = 0U;   ///< Initialize to 0U
        stComDrvLoc.uiTxBuf[i]           = 0U;   ///< Initialize to 0U
    }
#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_SciDrv_Init() is running****\r\n");
#endif
}

/**
* @brief   Transmission OK flag
* @param [in]  null
* @param [out] null
* @return null
*/
void v_SciDrv_TxOkFlg(void)
{
    if((0U == stComDrvLoc.uiFlgTxReq) &&(0U == SCI_REG.SCIFFTX.bit.TXFFST))
    {
        stComDrvLoc.stPrmExt.uiFlgTxOk = 1U;
    }
    else
    {
        stComDrvLoc.stPrmExt.uiFlgTxOk = 0U;
    }
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
void v_SciDrv_Rx(void)
{
    v_SciDrv_Rx_Msg(stComDrv.uiByteRx, MSG_DATA_LENGTH);
}

/**
* @brief   Transmission Message
* @param [in]  null
* @param [out] null
* @return null
*/
void v_SciDrv_Tx(void)
{
    Uint16 l_uiWaitTime = 0U;

    if((1U == stCom.uiFlgTxMsg) && (stComDrvLoc.uiFlgTxReq == 0U))
    {
       v_SciDrv_Tx_Msg(stCom.uiCmdCode, MSG_DATA_LENGTH, stCom.uiByteTx);
    }

    if(((1U == stCom.uiFlgTxMsg) && (stComDrvLoc.uiFlgTxReq == 0U)) || ((stCom.uiFlgTxMsg == 0)&&((stComDrvLoc.uiFlgTxReq == 1U))))
    {
         stComDrvLoc.uiFlgTxReq = 1U;
         while(0 != SCI_REG.SCIFFTX.bit.TXFFST)
         {
             l_uiWaitTime++;
             if(l_uiWaitTime > NUM_SCI_WHILE_OT)
             {
                 break;
             }
         }
         if(SCI_REG.SCICTL2.all & 0x80U)      ///< SCITXBUF is ready to send the next data
         {
             SCI_REG.SCITXBUF.all = stComDrvLoc.uiTxBuf[stComDrvLoc.uiCntrTx++];
         }
         if(stComDrvLoc.uiCntrTx >= SCI_FRAME_LEN)
         {
             stComDrvLoc.uiFlgTxReq = 0U;
             stComDrvLoc.uiCntrTx = 0U;
         }
         else
         {
             stComDrvLoc.uiFlgTxReq = 1U;
         }
    }
}

/**
* @brief   SCI software reset
* @param [in]  null
* @param [out] null
* @return null
*/
void v_SciDrv_ErrRst(void)
{
    /* If has been reset, normal run */
    if(0U == SCI_REG.SCICTL1.bit.SWRESET)
    {
        SCI_REG.SCICTL1.bit.SWRESET = 1U;        ///< End the reset (Normal run)
    }
    else
    /* If not reset and has run, reset SCI */
    {
        if(1U == SCI_REG.SCIRXST.bit.RXERROR)
        {
            SCI_REG.SCICTL1.bit.SWRESET = 0U;    ///< Trigger reset
        }
    }
}

/**
* @brief   SCI 1ms task
* @param [in]  null
* @param [out] null
* @return null
*/
void v_SciDrv_1ms(void)
{
    if(0U != stComDrvLoc.uiCntrRx)
    {
        stComDrvLoc.uiCntrRxEnd++;
        if(stComDrvLoc.uiCntrRxEnd > 5U)     ///< If the time between two data transmission bits is greater than 5ms, it will be regarded as the beginning of a new frame.
        {
            stComDrvLoc.uiCntrRx    = 0U;
            stComDrvLoc.uiCntrRxEnd = 0U;
        }
    }
}

/**
* @brief   Read the data in a Message Object
* @param [in]  param uiMsgLen is the number of bytes of data in the message object (0-8)
*              param puiData is a pointer to the message object's data
* @param [out] null
* @return null
*/
static void v_SciDrv_Rx_Msg(Uint16 *puiData, Uint16 uiMsgLen)
{
    Uint16 l_uiCrc  = 0U;
    Uint16 l_uiCrcRx  = 0U;
    Uint16 i = 0U;

    v_ComDrv_Sci_Rx_Data(stComDrvLoc.uiRxBuf, SCI_FRAME_LEN);    ///< Receive buffer
    if(1U == stComDrvLoc.uiFlgRxFrmOk)
    {
        stComDrvLoc.uiFlgRxFrmOk = 0U;
        if(0xFFU == stComDrvLoc.uiRxBuf[0] && 0xFEU == stComDrvLoc.uiRxBuf[1])  ///< The frame header is correct
        {
            l_uiCrc = ui_CRC16_Calc_Table(&stComDrvLoc.uiRxBuf[2], SCI_DATA_LEN);
            l_uiCrcRx = (stComDrvLoc.uiRxBuf[SCI_FRAME_LEN - 2U] << 8U) + stComDrvLoc.uiRxBuf[SCI_FRAME_LEN - 1U];
            if(l_uiCrc == l_uiCrcRx)    ///< Received CRC is correct
            {
                stComDrvLoc.stPrmExt.unIDMaskRx.bit.DATACMD = (stComDrvLoc.uiRxBuf[2] << 8U) + stComDrvLoc.uiRxBuf[3];      ///< Command code of SCI communication
                for(i = 0U; i < MSG_DATA_LENGTH; i++)
                {
                    if(i < uiMsgLen)
                    {
                        puiData[i] = stComDrvLoc.uiRxBuf[4U + i] & 0x00FFU;
                    }
                    else
                    {
                        puiData[i] = 0U;  ///< fill 0U
                    }
                }
                stComDrvLoc.stPrmExt.uiFlgRxOk    = 1U;
                stComDrvLoc.stPrmExt.uiFlgTxOk    = 0U;
            }
            else
            {
                stComDrvLoc.stPrmExt.uiFlgRxOk    = 0U;
            }
        }
        else
        {
            stComDrvLoc.stPrmExt.uiFlgRxOk    = 0U;
        }
    }
    else
    {
        stComDrvLoc.stPrmExt.uiFlgRxOk    = 0U;
    }
//    if(1U == SCIA_REG.SCIFFRX.bit.RXFFOVF)
//    {
//        stComDrvLoc.stPrmExt.uiFlgRxOk    = 0U;
//    }

    /* Global Signal*/
#if (1U == SCI_DRV_DBG)
    stComDrv.uiFlgRxOk       = stComDrvDbg.uiFlgRxOk;
    stComDrv.unIDMaskRx.all    = stComDrvDbg.unIDMaskRx.all;
#else
    stComDrv.uiFlgRxOk         = stComDrvLoc.stPrmExt.uiFlgRxOk;
    stComDrv.uiFlgTxOk         = stComDrvLoc.stPrmExt.uiFlgTxOk;
    stComDrv.unIDMaskRx.all    = stComDrvLoc.stPrmExt.unIDMaskRx.all;
#endif
}

/**
* @brief   Send a Message
* @param [in]  param uiObjID is the command code
*              param uiMsgLen is the number of bytes of data in the message object (0-8)
*              param puiMsgData is a pointer to the message object's data
* @param [out] null
* @return null
*/
static void v_SciDrv_Tx_Msg(Uint16 uiDataCmd, Uint16 uiMsgLen, Uint16 *puiMsgData)
{
    Uint16 i = 0U;
    Uint16 l_uiCrc  = 0U;

    /* Head code (2 byte) */
    stComDrvLoc.uiTxBuf[0] = 0xFFU;  ///< SF1 High Byte
    stComDrvLoc.uiTxBuf[1] = 0xFEU;  ///< SF1 Low Byte

    /* Command code (2 byte) */
    stComDrvLoc.uiTxBuf[2] = (uiDataCmd >> 8U) & 0xFFU;  ///< High Byte
    stComDrvLoc.uiTxBuf[3] = uiDataCmd & 0xFFU;          ///< Low Byte

    /* Data (8 byte) */
    for(i = 0U; i < MSG_DATA_LENGTH; i++)
    {
        if(i < uiMsgLen)
        {
            stComDrvLoc.uiTxBuf[4U + i] = puiMsgData[i];
        }
        else
        {
            stComDrvLoc.uiTxBuf[4U + i] = 0U;  ///< fill 0U
        }
    }

    /* Calculate CRC (2 byte) */
    l_uiCrc = ui_CRC16_Calc_Table(&stComDrvLoc.uiTxBuf[2], SCI_DATA_LEN);
    stComDrvLoc.uiTxBuf[12] = (l_uiCrc >> 8) & 0xFFU;  ///< CRC High Byte
    stComDrvLoc.uiTxBuf[13] = l_uiCrc & 0xFFU;         ///< CRC Low Byte
}


/**
* @brief   SCI Read data
* @param [in]  param puiData is a pointer to the message object's data
*              param uiSize is the number of bytes of data in the message object (0-8)
* @param [out] null
* @return null
*/
static void v_ComDrv_Sci_Rx_Data(Uint16 *puiData, Uint16 uiSize)
{
      if(SCI_REG.SCIFFRX.bit.RXFFST)
      {
          if(stComDrvLoc.uiCntrRx < SCI_FRAME_LEN)
          {
              stComDrvLoc.uiCntrRxEnd = 0U;
              puiData[stComDrvLoc.uiCntrRx++] = (SCI_REG.SCIRXBUF.all) & 0xFFU;

              if(SCI_FRAME_LEN == stComDrvLoc.uiCntrRx)
              {
                  stComDrvLoc.uiFlgRxFrmOk = 1U;
              }
          }
      }
}

static Uint16 ui_CRC16_Calc_Table(Uint16 *puiData, Uint16 uiLen)
{
    Uint16 l_uiCrc  = 0U;
    Uint16 l_uiCrc1 = 0U;
    Uint16 i;
    Uint16 usTemp;

    for(i = 0; i < uiLen; i++)
    {
        usTemp = puiData[i] & 0x00FFU;
        l_uiCrc1 = (l_uiCrc & 0x00FFU) << 8U;
        l_uiCrc = l_uiCrc1 ^ uiCrcTbl[((l_uiCrc >> 8U) ^ usTemp) & 0xFFU];
    }

    return l_uiCrc;
}


#endif     // (0U == COM_MODE)

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
