//==============================================================================================
//    File description
//==============================================================================================
/**@file         AdcDrv.h
 * @brief
 * Header file of ADC drive.
 *
 * Module      :                       \n
 * AdcDrv
 *
 * Module Task :                       \n
 * v_EPwmDrv_Init()                    \n
 * v_EPwmDrv_Isr()                     \n
 * v_EPwmDrv_1ms()                     \n
 * v_EPwmDrv_Pfc_TurnOff()             \n
 * v_EPwmDrv_Pfc_ClrTzFlg()            \n
 * v_EPwmDrv_D2d_TurnOff()             \n
 * v_EPwmDrv_D2d_ClrTzFlg()            \n
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

#ifndef EEPDRV_H_
#define EEPDRV_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "CDD_Drv.h"
#include "EepExt.h"

//=====================================================
//    Macro Definition
//=====================================================
#define PAGE_SIZE                   8U      ///< 2408:16;2464:32;24128:64; 64U/N, No more than 16U

/**Write status*/
#define I2C_DATA_SEND               0U
#define I2C_WAIT_WRITE              1U

/**Read status*/
#define I2C_SEND_ADDR               0U
#define I2C_WAIT_RECEIVE            1U
#define I2C_DATA_RECEIVE            2U

/**Wait time for read and write*/
#define I2C_WRITEWORD_WAITTIME      5U
#define I2C_READ_WAITTIME           3U

/**I2C Data read return flag*/
#define EEPROM_I2C_ADDR_WRITE       0x50U
#define EEPROM_I2C_ADDR_READ        0x50U

#define I2C_BUFFERMAX               12U
#define I2C_RESET_DELAY             1000U
#define NUM_I2C_RAED_FAIL           5U        ///< I2C read fail number
#define NUM_I2C_WR_FAIL             5U        ///< I2C write fail number
#define NUM_I2C_WHILE_OT            25000U    ///< I2C while Over-time number

/**Function define */
#define RESET_I2C()                   I2caRegs.I2CMDR.all = 0x0000;\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    I2caRegs.I2CMDR.all  = 0x0020;\
    I2caRegs.I2CFFTX.all = 0x6000;\
    I2caRegs.I2CFFRX.all = 0x2040


#define RESET_I2C_FFTX()            I2caRegs.I2CFFTX.bit.TXFFRST = 0;\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    I2caRegs.I2CFFTX.bit.TXFFRST = 1

#define RESET_I2C_FFRX()            I2caRegs.I2CFFRX.bit.RXFFRST = 0;\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    asm("    NOP");\
    I2caRegs.I2CFFRX.bit.RXFFRST = 1

//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================
typedef struct
{
    Uint16 uiReadDataDrvSts;    ///< Read Data Drive Status
    Uint16 uiFlgWrFirstIn;      ///< Write First In Flag
    Uint16 uiCntrStpWait;       ///< STP   Wait Counter
    Uint16 uiCntrArdyWait;      ///< ARDY  Wait Counter
    Uint16 uiCntrScdWait;       ///< SCD   Wait Counter
    Uint16 uiTmrWrWait;         ///< Write Wait Timer
}ST_EEPDRV_LOC;

//=====================================================
//    Variable Declaration
//=====================================================


//=====================================================
//    Function Declaration
//=====================================================
static Uint16 ui_EepDrv_RdWait_DataRd_STP(void);
static Uint16 ui_EepDrv_RdWait_DataRd_BB(void);
static Uint16 ui_EepDrv_RdWait_DataRd_ARDY(void);
static Uint16 ui_EepDrv_RdWait_DataRd_SCD(void);
static void v_EepDrv_RdWait_DataRd_Rx(Uint16 uiDataLen, Uint16 *puiDataBufAddr);
static Uint16 ui_EepDrv_WrWait_DataWr_STP(void);
static Uint16 ui_EepDrv_WrWait_DataWr_BB(void);
static Uint16 ui_EepDrv_Rd_DataRd_SndAddr(Uint16 uiEepromAddr);
static Uint16 ui_EepDrv_Rd_DataRd_WaitRx(Uint16 uiDataLength);
static Uint16 ui_EepDrv_Rd_DataRd_Rx(Uint16 *pDataBuff, Uint16 uiDataLength);
static Uint16 ui_EepDrv_RdWait_DataRd(Uint16 uiEepromAddr, Uint16 uiDataLen, Uint16 *puiDataBufAddr);
static Uint16 ui_EepDrv_WrWait_DataWr(Uint16 uiEepromAddr, Uint16 uiDataLen, Uint16 *puiDatabuf);
static Uint16 ui_EepDrv_Rd_DataRd(Uint16 uiEepromAddr,Uint16 uiDataLength,Uint16 *pDataBuff);
static Uint16 ui_EepDrv_Wr_DataWr(Uint16 uiEepromAddr,Uint16 uiDataLength,Uint16 *pDataBuff);

#endif /* EEPDRV_H_ */
//===========================================================================
// End of file.
//===========================================================================
