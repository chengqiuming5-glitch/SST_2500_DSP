//==============================================================================================
//    File description
//==============================================================================================
/**@file         CDD_Drv.h
 * @brief
 * Header file of CDD drive.
 *
 * Module      :                       \n
 * CDD_Drv
 *
 * Module Task :                       \n
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

#ifndef CDD_DRV_H_
#define CDD_DRV_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "App.h"

//==============================================================================================
//    Macro Definition
//==============================================================================================


//==============================================================================================
//   Global Struct & Enum & Union Typedef
//==============================================================================================

//==============================================================================================
//    Global Function Declaration
//==============================================================================================
/* ADC drive */
extern void v_AdcDrv_Init(void);
extern void v_AdcDrv_Isr(void);
extern void v_AdcDrv_1ms(void);
#if(0U == COM_MODE)
/* SCI drive */
extern void v_SciDrv_Init(void);
extern void v_SciDrv_TxOkFlg(void);
extern void v_SciDrv_Rx(void);
#if(0U == FLG_SWUT_EN)
//extern __interrupt void v_SciDrv_Rx(void);
#else
extern void v_SciDrv_Rx(void);
#endif
extern void v_SciDrv_Tx(void);
extern void v_SciDrv_ErrRst(void);
extern void v_SciDrv_ProcessInMainLoop(void);
extern void v_SciDrv_1ms(void);
#else
/* Com drive */
extern void v_ComDrv_Init(void);
extern void v_ComDrv_TxOkFlg(void);
extern void v_ComDrv_Rx(void);
extern void v_ComDrv_Tx(void);
#endif
/* ECap drive */
extern void v_ECapDrv_Init(void);
extern void v_ECapDrv_1ms(void);
/* EEprom drive */
extern void v_EepDrv_Init(void);
extern Uint16 ui_EepDrv_Wr(ST_I2C_handle pI2Cdata);
extern Uint16 ui_EepDrv_Rd(ST_I2C_handle pI2Cdata);
extern Uint16 ui_EepDrv_WrWait(ST_I2C_handle pI2Cdata);
extern Uint16 ui_EepDrv_RdWait(ST_I2C_handle pI2Cdata);
extern Uint16 ui_EepDrv_WrWordData(ST_I2C_handle p, Uint16 uiNUM);
extern Uint16 ui_EepDrv_RdWordData(ST_I2C_handle p,Uint16 uiNUM);
/* EPwm drive */
extern void v_EPwmDrv_Init(void);
extern void v_EPwmDrv_Isr(void);
extern void v_EPwmDrv_1ms(void);
extern void v_EPwmDrv_Pfc_TurnOff(void);
#if(3U == GRID_PHASE_NUMBER)
extern void v_EPwmDrv_Pfc_ClrTzFlg(void);
#endif
extern void v_EPwmDrv_D2d_TurnOff(void);
extern void v_EPwmDrv_D2d_ClrTzFlg(void);
/* PerphDrv */
extern void v_PerphDrv_Init(void);
#if(2U == GRID_PHASE_NUMBER)
extern void v_PerphDrv_Isr(void);
#endif
extern void v_PerphDrv_1ms(void);
extern void v_PerphDrv_10ms(void);
extern void v_PerphDrv_100ms(void);
/* SpiDrv */
extern void v_SpiDrv_Init(void);
extern void v_SpiDrv_ReadBuf(Uint16* pBuf, Uint32 ulAddrRead, Uint32 ulNumByte, volatile struct SPI_REGS *pstSpiXReg);
extern void v_SpiDrv_WrBuf(Uint16* pBuf, Uint32 ulAddrWr, Uint16 uiNumByte, volatile struct SPI_REGS *pstSpiXReg);
extern void v_SpiDrv_Cmn_EraseSector(Uint32 ulAddrSector, volatile struct SPI_REGS *pstSpiXReg);
extern void v_SpiDrv_Cmn_EraseBlock(Uint32 uiAddrBlock, volatile struct SPI_REGS *pstSpiXReg);
extern void v_SpiDrv_Cmn_EraseChip(volatile struct SPI_REGS *pstSpiXReg);
#if FLG_SPI_RDID_EN
extern Uint16 ui_SpiDrv_Cmn_ReadId(volatile struct SPI_REGS *pstSpiXReg);
#endif

#endif /* CDD_DRV_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
