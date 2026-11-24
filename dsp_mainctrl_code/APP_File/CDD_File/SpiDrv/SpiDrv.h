//==============================================================================================
//    File description
//==============================================================================================
/**@file         SpiDrv.h
 * @brief
 * The header file of Spi Drive is designed to realize SPI communication.
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

#ifndef SPIDRV_H_
#define SPIDRV_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "CDD_Drv.h"
#include "string.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define AT25F1024_ID        0x1FU
#define SECTOR_SIZE         (4U * 1024U)
#define BLOCK_SIZE          (SECTOR_SIZE * 16U)
#define FLASH_SIZE          (BLOCK_SIZE * 64U)

#define SF_TOTAL_SIZE       (1024UL*1024UL)    ///< Total size
#define SF_PAGE_SIZE        (256U)           ///< Page size

//CMD
#define CMD_WREN            0x06U      ///< Write enable command
#define CMD_DISWR           0x04U      ///< Write disable command
#define CMD_RDSR            0x05U      ///< Read status register command
#define CMD_WRSR            0x01U      ///< Write status register command
#define CMD_READ            0x03U      ///< Read data area command
#define CMD_PRGM            0x02U      ///< Flash programming
#define CMD_SE              0x20U      ///< Erase sector command
#define CMD_BE              0xD8U      ///< Erase block command
#define CMD_CE              0x60U      ///< Erase chip command
#define CMD_RDID            0x90U      ///< Read device ID command
#define DUMMY_BYTE          0xA5U      ///< Dumb command, can take on any value, used for read operations
#define WIP_FLAG            0x01U      ///< Programming flag (RDY) in the status register

#define NUM_SPI_WHILE_OT    500000U    ///< SPI while Over-time number
//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16 uiBufSpi[SF_PAGE_SIZE];     ///< Used for writing functions, first read the entire page, modify the buffer, and then write back the entire page
    Uint16 uiFlgEraseChk;              ///< Erase check flag
    Uint16 uiFirstAddr;                ///< First address of sector
    Uint16 uiNumOfPage;                ///< Number of page
    Uint16 uiNumOfSingle;              ///< Number of Single
    Uint16 uiDataCnt;                  ///< Data counter
    Uint16 uiAddr;                     ///< Address
}ST_SPI_DRV_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_SpiDrv_Hw_Init(volatile struct SPI_REGS *pstSpiXReg);
static void v_SpiDrv_Prm_Init(void);
static void v_SpiDrv_Cmn_WrEna(volatile struct SPI_REGS *pstSpiXReg);
static void v_SpiDrv_Cmn_WrDi(volatile struct SPI_REGS *pstSpiXReg);
static void v_SpiDrv_Cmn_WrEndWait(volatile struct SPI_REGS *pstSpiXReg);
static Uint16 ui_SpiDrv_Cmn_SndByt(Uint16 uiValue, volatile struct SPI_REGS *pstSpiXReg);
static void v_SpiDrv_ReadBuf_DataRx(Uint16* pBuf, Uint32 ulNumByte, volatile struct SPI_REGS *pstSpiXReg);
static Uint16 ui_SpiDrv_Cmn_EraseChk(Uint16* uipOldBuf, Uint16* uipNewBuf, Uint16 uiLen, volatile struct SPI_REGS *pstSpiXReg);
static void v_SpiDrv_WrBuf_FirstAdr(Uint16* pBuf, Uint32 ulAddrWr, Uint16 uiNumByte, volatile struct SPI_REGS *pstSpiXReg);
static void v_SpiDrv_WrBuf_NonFirstAdr(Uint16* pBuf, Uint32 ulAddrWr, Uint16 uiNumByte, volatile struct SPI_REGS *pstSpiXReg);
static void v_SpiDrv_WrBuf_AutoWrPage_Wr(Uint16 * pBuf, Uint32 ulAddrWr, Uint16 uiSize, volatile struct SPI_REGS *pstSpiXReg);

#endif /* SPIDRV_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
