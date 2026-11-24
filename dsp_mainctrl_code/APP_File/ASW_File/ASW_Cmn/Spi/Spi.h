//==============================================================================================
//    File description
//==============================================================================================
/**@file         Spi.h
 * @brief
 * The header file of Spi is designed to realize SPI communication.
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
#ifndef SPI_H_
#define SPI_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "FltDataRecExt.h"
#include "SpiExt.h"

#include "ASW_Cmn.h"
#include "CDD_Drv.h"
#include "ComExt.h"
#include "ComIf.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
/* W25Q32JV Definition of Memory Structure */
#define PAGE_SIZE_SPI           256U                                    ///< 256 bytes per page
#define SECTOR_SIZE_SPI         16U                                     ///< 16 pages per sector (4 KB)
#define BLOCK_SIZE_SPI          16U                                     ///< 16 sectors per block (64 KB)
#define TOTAL_BLOCKS_SPI        64U                                     ///< Total of 64 blocks (4 MB)
#define TOTAL_SECTORS_SPI       (TOTAL_BLOCKS_SPI * BLOCK_SIZE_SPI)     ///< Total of 1024 sectors
#define TOTAL_PAGES_SPI         (TOTAL_SECTORS_SPI * SECTOR_SIZE_SPI)   ///< Total of 16384 pages

/* Starting address for data storage (Sector 1 of Block0) */
#define DATA_START_ADDRESS      0x00001000UL

/* Current page value storage address (Sector0 of Block0) */
#define CURRENT_PAGE_ADDRESS    0x00000000UL

/* The number of pages occupied by each set of data */
#define PAGES_PER_GROUP_DATAS   8U

/* Maximum number of stored data groups */
#define MAX_GROUP_COUNT         (((SECTOR_SIZE_SPI * BLOCK_SIZE_SPI * TOTAL_BLOCKS_SPI) - SECTOR_SIZE_SPI) / PAGES_PER_GROUP_DATAS) ///< 2046U
#define MAX_PAGE_COUNT          (MAX_GROUP_COUNT * PAGES_PER_GROUP_DATAS)

#define TI_RETRY_WR_DATA        1U                              ///< Retry write data time
#define SPI_READ_TIMEOUT        100U                            ///< SPI read timeout count (100ms)
//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_SPI stPrmExt;
    Uint16 uiBufSpiWR[PAGES_PER_GROUP_DATAS * PAGE_SIZE_SPI];   ///< Write buffer
    Uint16 uiCntrRetryWr;        ///< Retry write data time
}ST_SPI_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_Spi_StMac_1ms(void);
static void v_Spi_FltRst_1ms(void);
static void v_Spi_StMac_FlgChk(void);
static void v_Spi_StMac_DataWr(void);
static void v_Spi_StMac_DataWr_Cnv(ST_FLT_DATA *pData);
static void v_Spi_StMac_DataWr_PageCurrUpd(Uint16 uiPagePrsnt);
static void v_Spi_StMac_DataVrfy(void);
static void v_Spi_StMac_ErrHndl(void);
static void v_Spi_StMac_DataRead(Uint16 uiPageReadReq);
static void v_Spi_StMac_DataRead_Cnv(ST_FLT_DATA *pData);
static Uint16 ui_Spi_Cmn_PageCurrRead(void);
static void v_Spi_StMac_AutoRead(UN_SYS_TIME *pstTiReq);
static void v_Spi_DataRec_Init(ST_FLT_DATA *pData);

#endif /* SPI_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
