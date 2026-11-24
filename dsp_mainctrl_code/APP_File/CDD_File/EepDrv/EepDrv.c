//==============================================================================================
//    File description
//==============================================================================================
/**@file         EepDrv.c
 * @brief
 * Source file of Eep drive.
 *
 * Module      :                       \n
 * EepDrv
 *
 * Module Task :                       \n
 * v_EepDrv_Init()                     \n
 * ui_EepDrv_Wr()                      \n
 * ui_EepDrv_Rd()                      \n
 * ui_EepDrv_WrWait()                  \n
 * ui_EepDrv_RdWait()                  \n
 * ui_EepDrv_WrWordData()              \n
 * ui_EepDrv_RdWordData()              \n
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
#include "EepDrv.h"
#include "F2837xD_Examples.h"

//=====================================================
//    Variable Definition
//=====================================================
static ST_EEPDRV_LOC stEepDrvLoc;
#if(1U == FLG_SWUT_EN)
struct I2C_REGS I2caRegsUnitTest;
#endif

//=====================================================
//    Function definition
//=====================================================
/******************************************************************************************************/
/**
 * @brief   v_EepDrv_Init
 * @param [in]
 * @param [in]
 * @param [in]
 * @param [out]
 * @return
 */
/******************************************************************************************************/
void v_EepDrv_Init(void)
{
    stEepDrvLoc.uiReadDataDrvSts = I2C_SEND_ADDR;  ///< Initialize to 0U
    stEepDrvLoc.uiFlgWrFirstIn   = 0U;             ///< Initialize to 0U
    stEepDrvLoc.uiCntrStpWait    = 0U;             ///< Initialize to 0U
    stEepDrvLoc.uiCntrArdyWait   = 0U;             ///< Initialize to 0U
    stEepDrvLoc.uiCntrScdWait    = 0U;             ///< Initialize to 0U
    stEepDrvLoc.uiTmrWrWait      = 0U;             ///< Initialize to 0U
	
#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_EepDrv_Init() is running****\r\n");
#endif
}

/*
 **************************************************************************
 * name         :EepromDataReadWait
 * Description : eeprom data read function
 * Argument    : .
; 1) Input argument : Uint16 uiEepromAddr read the eeprom address of data
                      UIN16 uiDataLen length of data reading
                      Uint16 *puiDataAdrr,Eeprom Read data override address
; 2) Modify argument  $Modify_argument_and_Description$
; 3) Output argument :$Output_argument_and_Description$
 * Return      : $Return_argument_and_Description$
 * Notes       : $Notes$
 **************************************************************************
 */
Uint16 ui_EepDrv_RdWait(ST_I2C_handle pI2Cdata)
{
    Uint16 l_uiReturnValue = PARA_EEPROM_READING;
    static Uint16 sl_uiPageRvsByteNum  = 0U;              ///< The number of bytes remaining on the current page
    static Uint16 sl_uiCurrReadByteNum = 0U;              ///< Number of bytes written this time
    static Uint16 sl_uiDataByteNum     = 0U;              ///< The total number of bytes for the parameter
    static Uint16 sl_uiNewAddr         = 0U;              ///< EEPROM deposit address
    static Uint16 *pDataBuff           = NULL_POINTER;    ///< Data source pointer

    /* Avoid cross-page operation */
    sl_uiDataByteNum    = pI2Cdata->uiNumOfWords * 2U;
    sl_uiPageRvsByteNum = PAGE_SIZE - (pI2Cdata->uiAddrMem % PAGE_SIZE);
    if(sl_uiPageRvsByteNum >= sl_uiDataByteNum)
    {
        sl_uiCurrReadByteNum = sl_uiDataByteNum;
    }
    else
    {
        sl_uiCurrReadByteNum = sl_uiPageRvsByteNum;
    }
    pI2Cdata->uiLimtReadNum = 0U;
    pI2Cdata->uiNumMarkReadByt = 0U;
    sl_uiNewAddr = pI2Cdata->uiAddrMem;
    pDataBuff = pI2Cdata->uiBufMsgRead;

    if(I2C_RETURN_READ_SUCESS == ui_EepDrv_RdWait_DataRd(sl_uiNewAddr, sl_uiCurrReadByteNum>>1, pDataBuff))
    {
        pI2Cdata->uiNumMarkReadByt = pI2Cdata->uiNumMarkReadByt + sl_uiCurrReadByteNum;
    }

    while(pI2Cdata->uiNumMarkReadByt < (pI2Cdata->uiNumOfWords *2U))
    {
        sl_uiNewAddr        = (pI2Cdata->uiAddrMem + pI2Cdata->uiNumMarkReadByt);
        pDataBuff           = (pI2Cdata->uiBufMsgRead + (pI2Cdata->uiNumMarkReadByt>>1));
        /* Avoid cross-page operation */
        sl_uiPageRvsByteNum =  PAGE_SIZE - (sl_uiNewAddr % PAGE_SIZE);
        sl_uiDataByteNum    = (pI2Cdata->uiNumOfWords*2U) - pI2Cdata->uiNumMarkReadByt;
        if(sl_uiPageRvsByteNum >= sl_uiDataByteNum)
        {
            sl_uiCurrReadByteNum = sl_uiDataByteNum;
        }
        else
        {
            sl_uiCurrReadByteNum = sl_uiPageRvsByteNum;
        }

        if(I2C_RETURN_READ_SUCESS == ui_EepDrv_RdWait_DataRd(sl_uiNewAddr, sl_uiCurrReadByteNum>>1, pDataBuff))
        {
            pI2Cdata->uiNumMarkReadByt = pI2Cdata->uiNumMarkReadByt + sl_uiCurrReadByteNum;
        }
        else
        {
            pI2Cdata->uiLimtReadNum++;
            if(pI2Cdata->uiLimtReadNum > NUM_I2C_RAED_FAIL)    ///< More than NUM_I2C_RAED_FAIL
            {
                l_uiReturnValue = PARA_EEPROM_READ_FAIL;       ///< Return PARA_EEPROM_READ_FAIL
                pI2Cdata->uiLimtReadNum = 0U;
#if(1U == FLG_SWUT_EN)
                return l_uiReturnValue;
#endif
            }
        }
    }

    if(PARA_EEPROM_READ_FAIL != l_uiReturnValue)
    {
        l_uiReturnValue = PARA_EEPROM_READ_SUCESS;
    }

    return l_uiReturnValue;
}

/*
 **************************************************************************
 * name         :I2C Data read dead wait function
 * Description : Data is read from EEprom via I2C
 * Argument    :
 * Return      : 1-Success£¬2-Fail
 * Notes       : 1.Used to read parameter values before entering the main loop, note that this
 *                 function does not distinguish paging, paging is handled by the calling function
                 2.The I2C address identification is known during EEPROM
                 3.puiDataBufAddr must be an integer multiple of 2
 **************************************************************************
 */
static Uint16 ui_EepDrv_RdWait_DataRd(Uint16 uiEepromAddr, Uint16 uiDataLen, Uint16 *puiDataBufAddr)
{
    Uint16  l_uiRetVal = I2C_RETURN_READ_FAIL;

#ifndef _SIMULATION_NO_DSP_
    if(I2C_RETURN_READ_FAIL != ui_EepDrv_RdWait_DataRd_STP())
    {
        /* Write eeprom address, read order */
        I2CX_REG.I2CSAR.bit.SAR = EEPROM_I2C_ADDR_READ;

        if(I2C_RETURN_READ_FAIL != ui_EepDrv_RdWait_DataRd_BB())
        {
            /* Send the reading data's head address in Eeprom */
            I2CX_REG.I2CCNT = 2U;
            I2CX_REG.I2CDXR.bit.DATA = (uiEepromAddr >> 8U) & 0xFFU;    ///< High byte
            I2CX_REG.I2CDXR.bit.DATA = uiEepromAddr & 0xFFU;            ///< Low byte
            I2CX_REG.I2CMDR.all = 0x6620U;                              ///< Send data to setup EEPROM address
            I2CX_REG.I2CSTR.bit.SCD = 1U;

            if(I2C_RETURN_READ_FAIL != ui_EepDrv_RdWait_DataRd_ARDY())
            {
                I2CX_REG.I2CCNT         = (uiDataLen * 2U);    ///< Setup how many bytes to expect
                I2CX_REG.I2CMDR.all     = 0x6C20U;             ///< Send restart as master receiver
                I2CX_REG.I2CSTR.bit.SCD = 1U;

                if(I2C_RETURN_READ_FAIL != ui_EepDrv_RdWait_DataRd_SCD())
                {
                    v_EepDrv_RdWait_DataRd_Rx(uiDataLen, puiDataBufAddr);    ///< Read data
                    DELAY_US_APP(1000.0f);                                   ///< Delay 1ms
                    l_uiRetVal = I2C_RETURN_READ_SUCESS;
                }
            }
        }
    }
#endif
    return l_uiRetVal;
}

/*
 **************************************************************************
 * name        :I2CRead Data Wait STP Check function
 * Description :
 * Argument    :
 * Return      :1-Success£¬2-Fail
 * Notes       :
 **************************************************************************
 */
static Uint16 ui_EepDrv_RdWait_DataRd_STP(void)
{
    Uint16 l_uiRetVal = I2C_RETURN_READING;
    Uint16 l_uiWaitTime = 0U;

    while(0U != I2CX_REG.I2CMDR.bit.STP)
    {
        l_uiWaitTime++;
        if(l_uiWaitTime > NUM_I2C_WHILE_OT)       ///< Number of cycles is more than NUM_I2C_WHILE_OT
        {
            l_uiRetVal = I2C_RETURN_READ_FAIL;    ///< Return I2C_RETURN_READ_FAIL
            break;
        }
    }

    return l_uiRetVal;
}

/*
 **************************************************************************
 * name        :I2CRead Data Wait BBC Check function
 * Description :
 * Argument    :
 * Return      :1-Success£¬2-Fail
 * Notes       :
 **************************************************************************
 */
static Uint16 ui_EepDrv_RdWait_DataRd_BB(void)
{
    Uint16  l_uiRetVal   = I2C_RETURN_READING;
    Uint16  l_uiWaitTime = 0U;

    /* I2C Bus busy judgment */
    while(0U != I2CX_REG.I2CSTR.bit.BB)
    {
        l_uiWaitTime++;
        if(l_uiWaitTime > NUM_I2C_WHILE_OT)       ///< Number of cycles is more than NUM_I2C_WHILE_OT
        {
            RESET_I2C();
            l_uiRetVal = I2C_RETURN_READ_FAIL;    ///< Return I2C_RETURN_READ_FAIL
            break;
        }
    }

    return l_uiRetVal;
}

/*
 **************************************************************************
 * name        :I2CRead Data Wait ARDY Check function
 * Description :
 * Argument    :
 * Return      :1-Success£¬2-Fail
 * Notes       :
 **************************************************************************
 */
static Uint16 ui_EepDrv_RdWait_DataRd_ARDY(void)
{
    Uint16 l_uiRetVal   = I2C_RETURN_READING;
    Uint16 l_uiWaitTime = 0U;

    while(1U != I2CX_REG.I2CSTR.bit.ARDY)
    {
        l_uiWaitTime++;
        if(l_uiWaitTime > NUM_I2C_WHILE_OT)       ///< Number of cycles is more than NUM_I2C_WHILE_OT
        {
            l_uiRetVal = I2C_RETURN_READ_FAIL;    ///< Return I2C_RETURN_READ_FAIL
            break;
        }
    }

    return l_uiRetVal;
}

/*
 **************************************************************************
 * name        :I2CRead Data Wait SCD Check function
 * Description :
 * Argument    :
 * Return      :1-Success£¬2-Fail
 * Notes       :
 **************************************************************************
 */
static Uint16 ui_EepDrv_RdWait_DataRd_SCD(void)
{
    Uint16 l_uiRetVal = I2C_RETURN_READING;
    Uint16  l_uiWaitTime = 0U;

    while(1U != I2CX_REG.I2CSTR.bit.SCD)
    {
        l_uiWaitTime++;
        if(l_uiWaitTime > NUM_I2C_WHILE_OT)       ///< Number of cycles is more than NUM_I2C_WHILE_OT
        {
            l_uiRetVal = I2C_RETURN_READ_FAIL;    ///< Return I2C_RETURN_READ_FAIL
            break;
        }
    }

    return l_uiRetVal;
}

/*
 **************************************************************************
 * name        :I2CRead Data Wait Receive data function
 * Description :
 * Argument    :
 * Return      : null
 * Notes       : Receive data in I2CRead Data Wait function
 **************************************************************************
 */
static void v_EepDrv_RdWait_DataRd_Rx(Uint16 uiDataLen, Uint16 *puiDataBufAddr)
{
    Uint16  i = 0U;
    Uint16  l_uiRecivebuff[2] = {0U, 0U};

    for(i = 0U; i < uiDataLen; i++)
    {
        l_uiRecivebuff[0]  = I2CX_REG.I2CDRR.bit.DATA;    ///< High byte
        l_uiRecivebuff[1]  = I2CX_REG.I2CDRR.bit.DATA;    ///< Low byte

        *(puiDataBufAddr+i) = (l_uiRecivebuff[0]<<8)+ l_uiRecivebuff[1];
    }
}

/******************************************************************************************************/
/**
 * @brief   ui_EepDrv_WrWait
 * @param [in]  I2c structure
 * @param [out] 1-SUCESS,2-FAIL
 * @return
 */
/******************************************************************************************************/
Uint16 ui_EepDrv_WrWait(ST_I2C_handle pI2Cdata)
{
    Uint16 l_uiReturnValue = PARA_EEPROM_WRITTING;
    static Uint16 sl_uiPageRvsByteNum   = 0U;              ///< The number of bytes remaining on the current page
    static Uint16 sl_uiCurrWriteByteNum = 0U;              ///< Number of bytes written this time
    static Uint16 sl_uiDataByteNum      = 0U;              ///< The total number of bytes for the parameter
    static Uint16 sl_uiNewAddr          = 0U;              ///< EEPROM deposit address
    static Uint16 *pDataBuff            = NULL_POINTER;    ///< Data source pointer

    /* Avoid cross-page operation */
    sl_uiDataByteNum    = pI2Cdata->uiNumOfWords * 2U;
    sl_uiPageRvsByteNum = PAGE_SIZE - (pI2Cdata->uiAddrMem % PAGE_SIZE);
    if(sl_uiPageRvsByteNum >= sl_uiDataByteNum)
    {
        sl_uiCurrWriteByteNum = sl_uiDataByteNum;
    }
    else
    {
        sl_uiCurrWriteByteNum = sl_uiPageRvsByteNum;
    }
    pI2Cdata->uiLimtWrNum = 0U;
    pI2Cdata->uiNumWrByt = 0U;
    sl_uiNewAddr = pI2Cdata->uiAddrMem;
    pDataBuff = pI2Cdata->uiBufMsgWr;

    if(I2C_RETURN_WRITE_SUCESS == ui_EepDrv_WrWait_DataWr(sl_uiNewAddr, sl_uiCurrWriteByteNum>>1, pDataBuff))
    {
        pI2Cdata->uiNumWrByt = pI2Cdata->uiNumWrByt + sl_uiCurrWriteByteNum;
    }

    while(pI2Cdata->uiNumWrByt < (pI2Cdata->uiNumOfWords * 2U))
    {
        sl_uiNewAddr        = (pI2Cdata->uiAddrMem + pI2Cdata->uiNumWrByt);
        pDataBuff           = (pI2Cdata->uiBufMsgWr + (pI2Cdata->uiNumWrByt>>1));
        /* Avoid cross-page operation */
        sl_uiPageRvsByteNum = PAGE_SIZE - (sl_uiNewAddr % PAGE_SIZE);
        sl_uiDataByteNum    = (pI2Cdata->uiNumOfWords*2U) - pI2Cdata->uiNumWrByt;
        if(sl_uiPageRvsByteNum >= sl_uiDataByteNum)
        {
            sl_uiCurrWriteByteNum = sl_uiDataByteNum;
        }
        else
        {
            sl_uiCurrWriteByteNum = sl_uiPageRvsByteNum;
        }

        if(I2C_RETURN_WRITE_SUCESS == ui_EepDrv_WrWait_DataWr(sl_uiNewAddr, sl_uiCurrWriteByteNum>>1, pDataBuff))
        {
            pI2Cdata->uiNumWrByt = pI2Cdata->uiNumWrByt + sl_uiCurrWriteByteNum;
        }
        else
        {
            pI2Cdata->uiLimtWrNum++;
            if(pI2Cdata->uiLimtWrNum > NUM_I2C_WR_FAIL)      ///< More than NUM_I2C_RAED_FAIL
            {
                l_uiReturnValue = PARA_EEPROM_WRITE_FAIL;    ///< Return PARA_EEPROM_WRITE_FAIL
                pI2Cdata->uiLimtWrNum = 0U;
#if(1U == FLG_SWUT_EN)
                return l_uiReturnValue;
#endif
            }
        }
    }

    if(PARA_EEPROM_WRITE_FAIL != l_uiReturnValue)
    {
        l_uiReturnValue = PARA_EEPROM_WRITE_SUCESS;
    }

    return l_uiReturnValue;
}
/*
 **************************************************************************
 * name         :I2CWriteData
 * Description : I2C write data to eeprom
 * Argument    :
 * Return      : 2-Fail,1-Success,0-Wait
 * Notes       : uiDataLen No more than 14
 **************************************************************************
 */
static Uint16 ui_EepDrv_WrWait_DataWr(Uint16 uiEepromAddr, Uint16 uiDataLen, Uint16 *puiDatabuf)
{
    Uint16 i;
    Uint16 l_uiRetVal = I2C_RETURN_WRITE_FAIL;
    Uint16 l_uiDataTemp = 0U;

#ifndef _SIMULATION_NO_DSP_
    /* If all the input parameters are 0, the command is considered to quit reading data */
    if((0U != uiDataLen) && (NULL_POINTER != puiDatabuf))
    {
        /** Wait until the STP bit is cleared from any previous master communication.
        Clearing of this bit by the module is delayed until after the SCD bit isset. If
        this bit is not checked prior to initiating a new message, the I2C could get confused.*/
        if(I2C_RETURN_WRITE_FAIL != ui_EepDrv_WrWait_DataWr_STP())
        {
            I2CX_REG.I2CSAR.bit.SAR = EEPROM_I2C_ADDR_WRITE;

            if(I2C_RETURN_WRITE_FAIL != ui_EepDrv_WrWait_DataWr_BB())
            {
                I2CX_REG.I2CCNT = (uiDataLen * 2U) + 2U;
                I2CX_REG.I2CDXR.bit.DATA = (uiEepromAddr >> 8U) & 0xFFU;    ///< High byte
                I2CX_REG.I2CDXR.bit.DATA = uiEepromAddr & 0xFFU;            ///< Low byte

                for(i = 0U; i < uiDataLen; i++)
                {
                    l_uiDataTemp = *(puiDatabuf + i);
//	                while(I2CX_REG.I2CFFTX.bit.TXFFST >= I2C_BUFFERMAX)
//	                {
//	                    // None Operation
//	                }
                    I2CX_REG.I2CDXR.bit.DATA = ((l_uiDataTemp>>8U) & 0x00FFU);
                    I2CX_REG.I2CDXR.bit.DATA = (l_uiDataTemp & 0x00FFU);
                }

                I2CX_REG.I2CMDR.all = 0x6E20U;           ///< Send start as master transmitter
                I2CX_REG.I2CSTR.bit.SCD = 1U;
                DELAY_US_APP(5500.0f);                   ///< Delay 5.5ms
                l_uiRetVal = I2C_RETURN_WRITE_SUCESS;
            }
        }
    }
    return l_uiRetVal;
#else
    return I2C_RETURN_WRITE_SUCESS;
#endif
}

/***************************************************************************
 * name         :I2C Write Data STP check
 * Description : I2C write data to eeprom
 * Argument    :
 * Return      : 2-Fail,1-Success,0-Wait
 * Notes       : uiDataLen No more than 14
 ***************************************************************************/
static Uint16 ui_EepDrv_WrWait_DataWr_STP(void)
{
    Uint16 l_uiRetVal = I2C_RETURN_WRITTING;
    Uint16 l_uiWaitTime = 0U;

    while(0U != I2CX_REG.I2CMDR.bit.STP)
    {
        l_uiWaitTime++;
        if(l_uiWaitTime > NUM_I2C_WHILE_OT)        ///< Number of cycles is more than NUM_I2C_WHILE_OT
        {
            l_uiRetVal = I2C_RETURN_WRITE_FAIL;    ///< Return I2C_RETURN_WRITE_FAIL
            break;
        }
    }

    return l_uiRetVal;
}

/***************************************************************************
 * name         :I2C Write Data BBC check
 * Description : I2C write data to eeprom
 * Argument    :
 * Return      : 2-Fail,1-Success,0-Wait
 * Notes       : uiDataLen No more than 14
 ***************************************************************************/
static Uint16 ui_EepDrv_WrWait_DataWr_BB(void)
{
    Uint16 l_uiRetVal   = I2C_RETURN_WRITTING;
    Uint16 l_uiWaitTime = 0U;

    while(0U != I2CX_REG.I2CSTR.bit.BB)
    {
        l_uiWaitTime++;
        if(l_uiWaitTime > NUM_I2C_WHILE_OT)        ///< Number of cycles is more than NUM_I2C_WHILE_OT
        {
            RESET_I2C_FFTX();                      ///< Reset I2C FFTX
            RESET_I2C();                           ///< Reset I2C
            l_uiRetVal = I2C_RETURN_WRITE_FAIL;    ///< Return I2C_RETURN_WRITE_FAIL
            break;
        }
    }
    return l_uiRetVal;
}

/******************************************************************************************************/
/**
 * @brief   ui_EepDrv_Read
 * @param [in]  NULL
 * @param [out] NULL
 * @return
 */
/******************************************************************************************************/
Uint16 ui_EepDrv_Rd(ST_I2C_handle pI2Cdata)
{
    Uint16 l_uiTempSts = 0U;
    Uint16 l_uiReturnValue = PARA_EEPROM_READING;
    static Uint16 sl_uiFirstInFlag   = 0U;
    static Uint16 sl_uiPageRvsNum    = 0U;             ///< The number of bytes remaining on the current page
    static Uint16 sl_uiCurrReadNum   = 0U;             ///< Number of bytes written this time
    static Uint16 sl_uiDataNum       = 0U;             ///< The total number of bytes for the parameter
    static Uint16 sl_uiNewAddr       = 0U;             ///< EEPROM deposit address
    static Uint16 *pDataBuff         = NULL_POINTER;   ///< Data source pointer

    if(0U == sl_uiFirstInFlag)
    {
        sl_uiFirstInFlag = 1U;
        /* Avoid cross-page operation */
        sl_uiDataNum    = pI2Cdata->uiNumOfWords * 2U;
        sl_uiPageRvsNum = PAGE_SIZE - (pI2Cdata->uiAddrMem % PAGE_SIZE);
        if(sl_uiPageRvsNum >= sl_uiDataNum)
        {
            sl_uiCurrReadNum = sl_uiDataNum;
        }
        else
        {
            sl_uiCurrReadNum = sl_uiPageRvsNum;
        }

        pI2Cdata->uiNumMarkReadByt = 0U;
        sl_uiNewAddr = pI2Cdata->uiAddrMem;
        pDataBuff = pI2Cdata->uiBufMsgRead;
        pI2Cdata->uiLimtReadNum = 0U;
    }
    if(NULL_POINTER != pDataBuff)    ///< Avoid static scan errors: pDataBuff may be NULL
    {
        l_uiTempSts = ui_EepDrv_Rd_DataRd(sl_uiNewAddr, sl_uiCurrReadNum>>1, pDataBuff);
        if(I2C_RETURN_READ_SUCESS == l_uiTempSts)
        {
            pI2Cdata->uiNumMarkReadByt = pI2Cdata->uiNumMarkReadByt + sl_uiCurrReadNum;
            if(pI2Cdata->uiNumMarkReadByt < (pI2Cdata->uiNumOfWords *2U))
            {
                sl_uiNewAddr = pI2Cdata->uiAddrMem + pI2Cdata->uiNumMarkReadByt;
                pDataBuff    = pI2Cdata->uiBufMsgRead + (pI2Cdata->uiNumMarkReadByt>>1);
                /* Avoid cross-page operation */
                sl_uiPageRvsNum = PAGE_SIZE - (sl_uiNewAddr % PAGE_SIZE);
                sl_uiDataNum = (pI2Cdata->uiNumOfWords * 2U) - pI2Cdata->uiNumMarkReadByt;
                if(sl_uiPageRvsNum >= sl_uiDataNum)
                {
                    sl_uiCurrReadNum = sl_uiDataNum;
                }
                else
                {
                    sl_uiCurrReadNum = sl_uiPageRvsNum;
                }
            }
            else
            {
                l_uiReturnValue  = PARA_EEPROM_READ_SUCESS;
                sl_uiFirstInFlag = 0U;
            }
        }
        else
        {
            if(I2C_RETURN_READ_FAIL == l_uiTempSts)
            {
                pI2Cdata->uiLimtReadNum++;
                if(pI2Cdata->uiLimtReadNum > NUM_I2C_RAED_FAIL)    ///< More than NUM_I2C_RAED_FAIL
                {
                    sl_uiFirstInFlag = 0U;
                    l_uiReturnValue  = PARA_EEPROM_READ_FAIL;      ///< Return PARA_EEPROM_READ_FAIL
                }
            }
        }
    }
    return l_uiReturnValue;
}

/******************************************************************************************************/
/**
 * @brief   Uint16 ui_EepDrv_Read_DataRead(Uint16 EepromAddr,Uint16 DataLen,Uint16 *pDataAddr),I2C Read drive
 * @param [in]  EepromAddr p, Storage address in EEPROM
 * @param [in]  DataLen, data length
 * @param [in]  pDataAddr£¬Data source address
 * @param [out] I2C_RETURN_READ_SUCESS, Indicating read complete
 * @return
 */
/******************************************************************************************************/
static Uint16 ui_EepDrv_Rd_DataRd(Uint16 uiEepromAddr,Uint16 uiDataLength,Uint16 *pDataBuff)
{
    Uint16 l_uiReturnValue = I2C_RETURN_READING;

    /* Wait until the STP bit is cleared from any previous master communication.
    Clearing of this bit by the module is delayed until after the SCD bit is set. If
    this bit is not checked prior to initiating a new message, the I2C could get confused.*/
#ifndef _SIMULATION_NO_DSP_
    switch(stEepDrvLoc.uiReadDataDrvSts)
    {
        case I2C_SEND_ADDR:/*Send address*/
            l_uiReturnValue = ui_EepDrv_Rd_DataRd_SndAddr(uiEepromAddr);
            break;

        case I2C_WAIT_RECEIVE: /**< Awaiting acceptance*/
            l_uiReturnValue = ui_EepDrv_Rd_DataRd_WaitRx(uiDataLength);
            break;

        case I2C_DATA_RECEIVE:/**< receive data*/
            l_uiReturnValue = ui_EepDrv_Rd_DataRd_Rx(pDataBuff, uiDataLength);
            break;

        default:
            stEepDrvLoc.uiReadDataDrvSts =  I2C_SEND_ADDR;
            l_uiReturnValue = I2C_RETURN_READING;
            break;
    }
#endif
    return l_uiReturnValue;
}

/******************************************************************************************************/
/**
 * @brief   Uint16 ui_EepDrv_Read_DataRead_SndAddr(Uint16 EepromAddr),I2C Read drive
 * @param [in]  EepromAddr p, Storage address in EEPROM
 * @param [out] I2C_RETURN_READ_SUCESS, Indicating read complete
 * @return
 */
/******************************************************************************************************/
static Uint16 ui_EepDrv_Rd_DataRd_SndAddr(Uint16 uiEepromAddr)
{
    Uint16 l_uiReturnValue     = I2C_RETURN_READING;

    if(0U == I2CX_REG.I2CMDR.bit.STP)
    {
        I2CX_REG.I2CSAR.bit.SAR = EEPROM_I2C_ADDR_READ;    ///< Slave address

        if(0U == I2CX_REG.I2CSTR.bit.BB)
        {
            I2CX_REG.I2CCNT = 2U;
            I2CX_REG.I2CDXR.bit.DATA = (uiEepromAddr >> 8U) & 0XFFU;    ///< High byte
            I2CX_REG.I2CDXR.bit.DATA = uiEepromAddr & 0xFFU;            ///< Low byte
            /* Send data to setup EEPROM address */
            I2CX_REG.I2CMDR.all = 0x6620U;     ///< Send data to setup EEPROM address
            I2CX_REG.I2CSTR.bit.SCD = 1U;
            stEepDrvLoc.uiCntrStpWait = 0U;
            /* Switch to I2C_WAIT_RECEIVE state*/
            stEepDrvLoc.uiReadDataDrvSts = I2C_WAIT_RECEIVE;
        }
    }
    else
    {
        /* Overtime judgment */
        if(stEepDrvLoc.uiCntrStpWait++ > I2C_RESET_DELAY)    ///< Number of cycles is more than I2C_RESET_DELAY
        {
            stEepDrvLoc.uiCntrStpWait = 0U;
            stEepDrvLoc.uiReadDataDrvSts = I2C_SEND_ADDR;
            RESET_I2C();
            l_uiReturnValue = I2C_RETURN_READ_FAIL;     ///< Return I2C_RETURN_READ_FAIL
        }
    }

    return l_uiReturnValue;
}

/******************************************************************************************************/
/**
 * @brief   Uint16 ui_EepDrv_Read_DataRead_WaitRx(Uint16 DataLen),I2C Read drive
 * @param [in]  DataLen, data length
 * @param [out] I2C_RETURN_READ_SUCESS, Indicating read complete
 * @return
 */
/******************************************************************************************************/
static Uint16 ui_EepDrv_Rd_DataRd_WaitRx(Uint16 uiDataLength)
{
    Uint16 l_uiReturnValue     = I2C_RETURN_READING;

    if(1U == I2CX_REG.I2CSTR.bit.ARDY)
    {
        I2CX_REG.I2CCNT         = (uiDataLength*2U);       ///< Setup how many bytes to expect
        I2CX_REG.I2CMDR.all     = 0x6C20U;                 ///< Send restart as master receiver
        I2CX_REG.I2CSTR.bit.SCD = 1U;
        stEepDrvLoc.uiCntrArdyWait = 0U;
        /* Switch to I2C_DATA_RECEIVE state*/
        stEepDrvLoc.uiReadDataDrvSts = I2C_DATA_RECEIVE;
    }
    else
    {
        /* Overtime judgment */
        if(stEepDrvLoc.uiCntrArdyWait++ > I2C_RESET_DELAY)    ///< Number of cycles is more than I2C_RESET_DELAY
        {
            stEepDrvLoc.uiCntrArdyWait = 0U;
            stEepDrvLoc.uiReadDataDrvSts =  I2C_SEND_ADDR;
            RESET_I2C();
            l_uiReturnValue = I2C_RETURN_READ_FAIL;     ///< Return I2C_RETURN_READ_FAIL
        }
    }

    return l_uiReturnValue;
}

/******************************************************************************************************/
/**
 * @brief   Uint16 ui_EepDrv_Read_DataRead_Rx(Uint16 *pDataAddr,Uint16 DataLen),I2C Read drive
 * @param [in]  DataLen, data length
 * @param [in]  pDataAddr£¬Data source address
 * @param [out] I2C_RETURN_READ_SUCESS, Indicating read complete
 * @return
 */
/******************************************************************************************************/
static Uint16 ui_EepDrv_Rd_DataRd_Rx(Uint16 *pDataBuff, Uint16 uiDataLength)
{
    Uint16 i = 0U;
    Uint16 l_uiReturnValue   = I2C_RETURN_READING;
    Uint16 l_uiRecivebuff[2]  = {0U,0U};

    if(1U == I2CX_REG.I2CSTR.bit.SCD)
    {
        for(i = 0U; i < uiDataLength; i++)
        {
            l_uiRecivebuff[0] = I2CX_REG.I2CDRR.bit.DATA;    ///< High byte of data
            l_uiRecivebuff[1] = I2CX_REG.I2CDRR.bit.DATA;    ///< Low byte of Receive data
            *(pDataBuff+i) = (l_uiRecivebuff[0]<<8) + l_uiRecivebuff[1];
        }
        stEepDrvLoc.uiCntrScdWait = 0U;
        l_uiReturnValue = I2C_RETURN_READ_SUCESS;     ///< Return I2C_RETURN_READ_SUCESS
        /* Switch to I2C_SEND_ADDR state*/
        stEepDrvLoc.uiReadDataDrvSts = I2C_SEND_ADDR;
    }
    else
    {
        /* Overtime judgment */
        if(stEepDrvLoc.uiCntrScdWait++ > I2C_RESET_DELAY)   ///< Number of cycles is more than I2C_RESET_DELAY
        {
            stEepDrvLoc.uiCntrScdWait = 0U;
            stEepDrvLoc.uiReadDataDrvSts =  I2C_SEND_ADDR;
            RESET_I2C();
            l_uiReturnValue = I2C_RETURN_READ_FAIL;     ///< Return I2C_RETURN_READ_FAIL
        }
    }

    return l_uiReturnValue;
}

/******************************************************************************************************/
/**
 * @brief   ui_EepDrv_Wr
 * @param [in]  NULL
 * @param [out] NULL
 * @return
 */
/******************************************************************************************************/
Uint16 ui_EepDrv_Wr(ST_I2C_handle pI2Cdata)
{
    Uint16 l_uiTempSts;
    Uint16 l_uiReturnValue = PARA_EEPROM_WRITTING;
    static Uint16 sl_uiPageRvsNum    = 0U;             ///< The number of bytes remaining on the current page
    static Uint16 sl_uiCurrWriteNum  = 0U;             ///< Number of bytes written this time
    static Uint16 sl_uiDataNum       = 0U;             ///< The total number of bytes for the parameter
    static Uint16 sl_uiNewAddr       = 0U;             ///< EEPROM deposit address
    static Uint16 *pDataBuff         = NULL_POINTER;   ///< Data source pointer

    if(0U == stEepDrvLoc.uiFlgWrFirstIn)
    {
        stEepDrvLoc.uiFlgWrFirstIn = 1U;
        /* Avoid cross-page operation */
        sl_uiDataNum     = pI2Cdata->uiNumOfWords * 2U;
        sl_uiPageRvsNum  = PAGE_SIZE - (pI2Cdata->uiAddrMem % PAGE_SIZE);
        if(sl_uiPageRvsNum >= sl_uiDataNum)
        {
            sl_uiCurrWriteNum = sl_uiDataNum;
        }
        else
        {
            sl_uiCurrWriteNum = sl_uiPageRvsNum;
        }

        pI2Cdata->uiNumWrByt = 0U;
        sl_uiNewAddr = pI2Cdata->uiAddrMem;
        pDataBuff = pI2Cdata->uiBufMsgWr;
        pI2Cdata->uiLimtWrNum = 0U;
    }

    if(NULL_POINTER != pDataBuff)    ///< Avoid static scan errors: pDataBuff may be NULL
    {
        l_uiTempSts = ui_EepDrv_Wr_DataWr(sl_uiNewAddr, sl_uiCurrWriteNum>>1, pDataBuff);

        if(I2C_RETURN_WRITE_SUCESS == l_uiTempSts)
        {
            pI2Cdata->uiNumWrByt = pI2Cdata->uiNumWrByt + sl_uiCurrWriteNum;
            if(pI2Cdata->uiNumWrByt < (pI2Cdata->uiNumOfWords * 2U))
            {
                sl_uiNewAddr    = (pI2Cdata->uiAddrMem + pI2Cdata->uiNumWrByt);
                pDataBuff       = (pI2Cdata->uiBufMsgWr + (pI2Cdata->uiNumWrByt>>1));
                /* Avoid cross-page operation */
                sl_uiPageRvsNum = PAGE_SIZE - (sl_uiNewAddr % PAGE_SIZE);
                sl_uiDataNum    = (pI2Cdata->uiNumOfWords * 2U) - pI2Cdata->uiNumWrByt;
                if(sl_uiPageRvsNum >= sl_uiDataNum)
                {
                    sl_uiCurrWriteNum = sl_uiDataNum;
                }
                else
                {
                    sl_uiCurrWriteNum = sl_uiPageRvsNum;
                }
            }
            else
            {
                l_uiReturnValue  = PARA_EEPROM_WRITE_SUCESS;     ///< Return PARA_EEPROM_WRITE_SUCESS
                stEepDrvLoc.uiFlgWrFirstIn = 0U;
            }
        }
        else if((I2C_RETURN_WRITE_FAIL == l_uiTempSts))
        {
            pI2Cdata->uiLimtWrNum++;
            if(pI2Cdata->uiLimtWrNum > NUM_I2C_WR_FAIL)       ///< More than NUM_I2C_RAED_FAIL
            {
                stEepDrvLoc.uiFlgWrFirstIn = 0U;
                l_uiReturnValue  = PARA_EEPROM_WRITE_FAIL;    ///< Return PARA_EEPROM_WRITE_FAIL
            }
        }
        else
        {
            ///< No code
        }
    }
    return l_uiReturnValue;
}

/******************************************************************************************************/
/**
 * @brief   Uint16 ui_EepDrv_Wr_DataWr(Uint16 EepromAddr,Uint16 DataLen,Uint16 *pDataAddr)£¬I2C read drive
 * @param [in]  EepromAddr p, Storage address in EEPROM
 * @param [in]  DataLen, data length
 * @param [in]  pDataAddr, Data source address
 * @param [out] I2C_RETURN_READ_SUCESS, Indicating read complete
 * @return
 */
/******************************************************************************************************/
static Uint16 ui_EepDrv_Wr_DataWr(Uint16 uiEepromAddr, Uint16 uiDataLength, Uint16 *pDataBuff)
{
    Uint16 i;
    Uint16 l_uiReturnValue = I2C_RETURN_WRITTING;
    static Uint16 sl_uiStsWr = I2C_DATA_SEND;

    if(I2C_DATA_SEND == sl_uiStsWr)
    {
#ifndef _SIMULATION_NO_DSP_
        if(0U == I2CX_REG.I2CMDR.bit.STP)
        {
            I2CX_REG.I2CSAR.bit.SAR = EEPROM_I2C_ADDR_WRITE;

            if(0U == I2CX_REG.I2CSTR.bit.BB)
            {
                I2CX_REG.I2CCNT = (uiDataLength * 2U) + 2U;
                I2CX_REG.I2CDXR.bit.DATA = (uiEepromAddr >> 8U) & 0xFFU;    ///< High byte of address
                I2CX_REG.I2CDXR.bit.DATA = uiEepromAddr & 0xFFU;            ///< Low byte of address

                for(i = 0U; i < uiDataLength; i++)
                {
                    I2CX_REG.I2CDXR.bit.DATA = ((*(pDataBuff + i))>>8U) & 0x00FFU;    ///< High byte of data
                    I2CX_REG.I2CDXR.bit.DATA = (*(pDataBuff + i)) & 0x00FFU;          ///< Low byte of data
                }
                I2CX_REG.I2CMDR.all = 0x6E20U;             ///< Send restart as master receiver
                I2CX_REG.I2CSTR.bit.SCD = 1U;

                stEepDrvLoc.uiTmrWrWait  = 0U;
                sl_uiStsWr      = I2C_WAIT_WRITE;
            }
        }

        if(stEepDrvLoc.uiTmrWrWait++ > I2C_RESET_DELAY)            ///< Number of cycles is more than I2C_RESET_DELAY
        {
            RESET_I2C();
            stEepDrvLoc.uiTmrWrWait  = 0U;
            sl_uiStsWr      = I2C_DATA_SEND;
            l_uiReturnValue = I2C_RETURN_WRITE_FAIL;      ///< Return I2C_RETURN_WRITE_FAIL
        }
#endif
    }
    else
    {
        /* Wait a while before quitting */
        if(stEepDrvLoc.uiTmrWrWait++ > (I2C_WRITEWORD_WAITTIME * uiDataLength))
        {
            stEepDrvLoc.uiTmrWrWait  = 0U;
            sl_uiStsWr      = I2C_DATA_SEND;
            l_uiReturnValue = I2C_RETURN_WRITE_SUCESS;      ///< Return I2C_RETURN_WRITE_SUCESS
        }
    }
    return l_uiReturnValue;
}

/******************************************************************************************************/
/**
 * @brief: Store data to a specified address; Write only 2 bytes
 * @param [in]  ST_I2C_handle p,I2C Communication architecture
 * @param [in]  Uint16 NUM, The address of the current write data buff throughout the write data segment
 * @param [out] I2C_RETURN_WRITE_SUCESS
 * @return
 */
/******************************************************************************************************/
Uint16 ui_EepDrv_WrWordData(ST_I2C_handle p, Uint16 uiNUM)
{
    Uint16 l_uiRetVal = I2C_RETURN_WRITE_FAIL;

#ifndef _SIMULATION_NO_DSP_
    IIC_WRITE_ENABLE;

    if(I2C_RETURN_WRITE_FAIL != ui_EepDrv_WrWait_DataWr_STP())
    {
        /*  Setup slave address */
        I2CX_REG.I2CSAR.bit.SAR = p->uiAddrSlave;

        /* Check if bus busy */
        if(I2C_RETURN_WRITE_FAIL != ui_EepDrv_WrWait_DataWr_BB())
        {
            I2CX_REG.I2CCNT = 4U;
            // Setup data to send
            I2CX_REG.I2CDXR.bit.DATA = (p->uiAddrMem + 2U * uiNUM) >> 8;
            I2CX_REG.I2CDXR.bit.DATA = (p->uiAddrMem + 2U * uiNUM) & 0x00FFU;

            I2CX_REG.I2CDXR.bit.DATA = (p->uiBufMsgWr[uiNUM]>>8) & 0x00FFU;
            I2CX_REG.I2CDXR.bit.DATA = p->uiBufMsgWr[uiNUM] & 0x00FFU;

            // Send start as master transmitter
            I2CX_REG.I2CMDR.all = 0x6E20U;            ///< Send restart as master receiver
            I2CX_REG.I2CSTR.bit.SCD = 1U;
            DELAY_US_APP(5500.0f);                    ///< Delay 5.5ms
            l_uiRetVal = I2C_RETURN_WRITE_SUCESS;     ///< Return I2C_RETURN_WRITE_SUCESS
        }
    }
    return l_uiRetVal;
#else
    return I2C_RETURN_WRITE_SUCESS;
#endif
}

/******************************************************************************************************/
/**
 * @brief: The read data is stored to the specified buff bit
 * @param [in]  ST_I2C_handle p
 * @param [in]  Uint16 NUM
 * @param [out] PARA_EEPROM_READ_SUCESS
 * @return
 */
/******************************************************************************************************/
Uint16 ui_EepDrv_RdWordData(ST_I2C_handle p,Uint16 uiNUM)
{
    Uint16 l_uiTemp[2] = {0U,0U};
    Uint16 l_uiRetVal = I2C_RETURN_READ_FAIL;

#ifndef _SIMULATION_NO_DSP_
    if(I2C_RETURN_READ_FAIL != ui_EepDrv_RdWait_DataRd_STP())
    {
        I2CX_REG.I2CSAR.bit.SAR = p->uiAddrSlave;

        /* Check if bus busy */
        if(I2C_RETURN_READ_FAIL != ui_EepDrv_RdWait_DataRd_BB())
        {
            I2CX_REG.I2CCNT = 2U;
            I2CX_REG.I2CDXR.bit.DATA = (Uint16)((p->uiAddrMem + 2U * uiNUM) >> 8);
            I2CX_REG.I2CDXR.bit.DATA = (Uint16)((p->uiAddrMem + 2U * uiNUM) & 0x00FFU);
            I2CX_REG.I2CMDR.all = 0x6620U;           ///< Send data to setup EEPROM address
            I2CX_REG.I2CSTR.bit.SCD = 1U;

            if(I2C_RETURN_READ_FAIL != ui_EepDrv_RdWait_DataRd_ARDY())
            {
                I2CX_REG.I2CCNT         = 2U;
                I2CX_REG.I2CMDR.all     = 0x6C20U;           ///< Send restart as master receiver
                I2CX_REG.I2CSTR.bit.SCD = 1U;

                if(I2C_RETURN_READ_FAIL != ui_EepDrv_RdWait_DataRd_SCD())
                {
                    l_uiTemp[0] = I2CX_REG.I2CDRR.bit.DATA;
                    l_uiTemp[1] = I2CX_REG.I2CDRR.bit.DATA;
                    p->uiBufMsgRead[uiNUM] = (l_uiTemp[0] << 8) + l_uiTemp[1];

                    l_uiRetVal = I2C_RETURN_READ_SUCESS;
                }
            }
        }
    }
    return l_uiRetVal;
#else
    return PARA_EEPROM_READ_SUCESS;
#endif
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
