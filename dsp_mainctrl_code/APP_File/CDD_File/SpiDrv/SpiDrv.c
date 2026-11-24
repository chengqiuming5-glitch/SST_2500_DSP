//==============================================================================================
//    File description
//==============================================================================================
/**@file         SpiDrv.c
 * @brief
 * The source file of Spi Drive is designed to realize SPI communication.
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
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "SpiDrv.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
static ST_SPI_DRV_LOC stSpiDrvLoc;      ///< Spi drive local struct

//==============================================================================================
//    Function definition
//==============================================================================================
/***********************************************************************************************
* @Type         : Module function
* @brief        :
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_SpiDrv_Init(void)
{
    v_SpiDrv_Prm_Init();             ///< Parameter Initialization
    v_SpiDrv_Hw_Init(&SPIX_REG);     ///< Flash SPI Hardware Initialization
#if 2U == GRID_PHASE_NUMBER
    v_SpiDrv_Hw_Init(&SPIC_REG);     ///< CPLD SPI Hardware Initialization
#endif

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_SpiDrv_Init() is running****\r\n");
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        :
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_SpiDrv_Prm_Init(void)
{
    Uint16 i = 0U;

    for(i = 0U; i < SF_PAGE_SIZE; i++)
    {
        stSpiDrvLoc.uiBufSpi[i] = 0U;       ///< Initialize to 0U
    }
    stSpiDrvLoc.uiFlgEraseChk   = 0U;       ///< Erase check flag
    stSpiDrvLoc.uiFirstAddr     = 0U;       ///< First address of sector
    stSpiDrvLoc.uiNumOfPage     = 0U;       ///< Number of page
    stSpiDrvLoc.uiNumOfSingle   = 0U;       ///< Number of Single
    stSpiDrvLoc.uiDataCnt       = 0U;       ///< Data counter
    stSpiDrvLoc.uiAddr          = 0U;       ///< Address
}

#if FLG_SPI_RDID_EN
Uint16 ui_SpiDrv_Cmn_ReadId(volatile struct SPI_REGS *pstSpiXReg)
{
    Uint16 l_uiMfrId = 0U;      ///< Manufacturer ID
    Uint16 l_uiDevId = 0U;      ///< Device ID
    Uint16 l_uiId    = 0U;      ///< Return ID

    SF_CS_LOW();                                      ///< Select serial Flash
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_LOW();                                 ///< Select CPLD Flash
#endif
    DELAY_US_APP(1.0f);
    (void)ui_SpiDrv_Cmn_SndByt(CMD_RDID, pstSpiXReg); ///< Send read ID command
    (void)ui_SpiDrv_Cmn_SndByt(0x00, pstSpiXReg);
    (void)ui_SpiDrv_Cmn_SndByt(0x00, pstSpiXReg);
    (void)ui_SpiDrv_Cmn_SndByt(0x00, pstSpiXReg);
    l_uiMfrId = ui_SpiDrv_Cmn_SndByt(0x00, pstSpiXReg);
    l_uiDevId = ui_SpiDrv_Cmn_SndByt(0x00, pstSpiXReg);

    SF_CS_HIGH();                                     ///< Deselect serial Flash
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_HIGH();                                ///< Deselect CPLD Flash
#endif

    l_uiId = ((l_uiMfrId & 0xFFU) << 8U) | (l_uiDevId & 0xFFU);

    return l_uiId;
}
#endif
/***********************************************************************************************
* @Type         : Module function
* @brief        :
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_SpiDrv_Hw_Init(volatile struct SPI_REGS *pstSpiXReg)
{
    SF_CS_LOW();                                               ///< Software enabled serial Flash chip selection
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_LOW();                              			   ///< Software enabled serial Flash chip selection
#endif
//    DELAY_US_APP(1.0f);
    (void)ui_SpiDrv_Cmn_SndByt(CMD_DISWR, pstSpiXReg);         ///< Disable write

    SF_CS_HIGH();                                              ///< Software enabled serial Flash chip selection
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_HIGH();                                         ///< Software enabled serial Flash chip selection
#endif
    v_SpiDrv_Cmn_WrEndWait(pstSpiXReg);                        ///< Waiting for serial Flash internal operations to complete
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Send a byte to the device while sampling the data returned by the device from the MISO port line
* @Signal [in]  : _ucByte : The byte value sent
* @Signal [out] : null
* @return       : Data returned from MISO port line sampling device
***********************************************************************************************/
static Uint16 ui_SpiDrv_Cmn_SndByt(Uint16 uiValue, volatile struct SPI_REGS *pstSpiXReg)
{
    Uint16 l_uiDataRx    = 0U;
    Uint16 l_uiStFf      = 0U;    ///< FIFO status
    Uint32 l_ulTiWait    = 0UL;   ///< Wait time

    /* Loop while send FIFO is not empty */
    l_uiStFf = pstSpiXReg->SPIFFTX.bit.TXFFST;
    while((1U == pstSpiXReg->SPISTS.bit.BUFFULL_FLAG) || (l_uiStFf > 0U))
    {
        /* Jumping out after timeout */
        if(l_ulTiWait++ >= NUM_SPI_WHILE_OT)
        {
            break;
        }
    }

    /* Send byte */
    pstSpiXReg->SPITXBUF = (uiValue << 8U);         ///< Data must be fewer than 16 bits and left-justified

    /* Loop while receive FIFO is empty */
    l_ulTiWait = 0UL;        ///< Clear wait time
    l_uiStFf = pstSpiXReg->SPIFFTX.bit.TXFFST;
    while((0U == pstSpiXReg->SPIFFRX.bit.RXFFST) || (l_uiStFf > 0U))
    {
        /* Jumping out after timeout */
        if(l_ulTiWait++ >= NUM_SPI_WHILE_OT)
        {
            break;
        }
    }

    /* Receive the data */
    l_ulTiWait = 0UL;        ///< Clear wait time
    while(pstSpiXReg->SPIFFRX.bit.RXFFST > 0U)
    {
        l_uiDataRx = (pstSpiXReg->SPIRXBUF) & 0xFFU;

        /* Jumping out after timeout */
        if(l_ulTiWait++ >= NUM_SPI_WHILE_OT)
        {
            break;
        }
    }

    return(l_uiDataRx);
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Send write enable command to the device
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_SpiDrv_Cmn_WrEna(volatile struct SPI_REGS *pstSpiXReg)
{
    SF_CS_LOW();                                         ///< Software enabled serial Flash chip selection
//    DELAY_US_APP(1.0f);
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_LOW();                                    ///< Software enabled serial Flash chip selection
#endif
    (void)ui_SpiDrv_Cmn_SndByt(CMD_WREN, pstSpiXReg);    ///< Send Write Enable command
    SF_CS_HIGH();                                        ///< Software enabled serial Flash chip selection
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_HIGH();                                   ///< Software enabled serial Flash chip selection
#endif
}

#if 0U
/***********************************************************************************************
* @Type         : Module function
* @brief        : Send write disable command to the device
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_SpiDrv_Cmn_WrDi(void)
{
    SF_CS_LOW();                                          ///< Enable CS
    (void)ui_SpiDrv_Cmn_SndByt(CMD_DISWR, pstSpiXReg);    ///< Send Write disable command
    SF_CS_HIGH();                                         ///< Disable CS
}
#endif

/***********************************************************************************************
* @Type         : Module function
* @brief        : Using a loop query method to wait for the completion of internal write operations in the device
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_SpiDrv_Cmn_WrEndWait(volatile struct SPI_REGS *pstSpiXReg)
{
    Uint16 l_uiStFlash = 0U;    ///< Flash status
    Uint32 l_ulTiWait  = 0UL;   ///< Wait time

    /* Select the flash: chip select low */
    SF_CS_LOW();                                   ///< Software enabled serial Flash chip selection
//    DELAY_US_APP(1.0f);
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_LOW();                              ///< Software enabled CPLD Flash selection
#endif

    /* Send "read status register" instruction */
    (void)ui_SpiDrv_Cmn_SndByt(CMD_RDSR, pstSpiXReg);
    do
    {
        /* Send a dummy byte to generate the clock needed by the flash
        and put the value of the status register in flash_status variable */
        l_uiStFlash = ui_SpiDrv_Cmn_SndByt(DUMMY_BYTE, pstSpiXReg);

        /* Jumping out after timeout */
        if(l_ulTiWait++ >= NUM_SPI_WHILE_OT)
        {
            break;
        }
    }while((l_uiStFlash & WIP_FLAG) == WIP_FLAG);

    /* Deselect the flash: chip select high */
    SF_CS_HIGH();                                              ///< Software enabled serial Flash chip selection
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_HIGH();                                         ///< Software enabled CPLD Flash selection
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Erase the specified sector
* @Signal [in]  : ulAddrSector: sector address
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_SpiDrv_Cmn_EraseSector(Uint32 ulAddrSector, volatile struct SPI_REGS *pstSpiXReg)
{
    /* Send write enable instruction */
    v_SpiDrv_Cmn_WrEna(pstSpiXReg);                                                      ///< Send write enable command

    /* Select the flash: chip select low */
    SF_CS_LOW();                                   ///< Software enabled serial Flash chip selection
//    DELAY_US_APP(1.0f);
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_LOW();                              ///< Software enabled CPLD Flash selection
#endif

    /* Send sector erase instruction  */
    (void)ui_SpiDrv_Cmn_SndByt(CMD_SE, pstSpiXReg);                                        ///< Send Erase command
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)((ulAddrSector & 0xFF0000U) >> 16U), pstSpiXReg);   ///< Send the high 8 bits of the sector address
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)((ulAddrSector & 0xFF00U) >> 8U), pstSpiXReg);      ///< Send the middle 8 bits of the sector address
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)(ulAddrSector & 0xFFU), pstSpiXReg);                ///< Send the low 8 bits of the sector address

    /* Deselect the flash: chip select high */
    SF_CS_HIGH();                                              ///< Software enabled serial Flash chip selection
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_HIGH();                                         ///< Software enabled CPLD Flash selection
#endif

    /* Wait the end of flash writing */
    v_SpiDrv_Cmn_WrEndWait(pstSpiXReg);                        ///< Waiting for serial Flash internal operations to complete
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Erase the block sector
* @Signal [in]  : uiAddrBlock: block address
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_SpiDrv_Cmn_EraseBlock(Uint32 uiAddrBlock, volatile struct SPI_REGS *pstSpiXReg)
{
    /* Send write enable instruction */
    v_SpiDrv_Cmn_WrEna(pstSpiXReg);

    /* Select the flash: chip select low */
    SF_CS_LOW();                                   ///< Software enabled serial Flash chip selection
//    DELAY_US_APP(1.0f);
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_LOW();                              ///< Software enabled CPLD Flash selection
#endif

    /* Send bulk erase instruction  */
    (void)ui_SpiDrv_Cmn_SndByt(CMD_BE, pstSpiXReg);                                        ///< Send Erase command
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)((uiAddrBlock & 0xFF0000U) >> 16U), pstSpiXReg);    ///< Send the high 8 bits of the sector address
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)((uiAddrBlock & 0xFF00U) >> 8U), pstSpiXReg);       ///< Send the middle 8 bits of the sector address
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)(uiAddrBlock & 0xFFU), pstSpiXReg);                 ///< Send the low 8 bits of the sector address

    /* Deselect the flash: chip select high */
    SF_CS_HIGH();                                              ///< Software enabled serial Flash chip selection
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_HIGH();                                         ///< Software enabled CPLD Flash selection
#endif
    /* Wait the end of flash writing */
    v_SpiDrv_Cmn_WrEndWait(pstSpiXReg);
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Erase whole chip
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_SpiDrv_Cmn_EraseChip(volatile struct SPI_REGS *pstSpiXReg)
{
    /* Send write enable instruction */
    v_SpiDrv_Cmn_WrEna(pstSpiXReg);

    /* Select the flash: chip select low */
    SF_CS_LOW();                                   ///< Software enabled serial Flash chip selection
//    DELAY_US_APP(1.0f);
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_LOW();                              ///< Software enabled serial CPLD selection
#endif

    /* Send Erase command */
    (void)ui_SpiDrv_Cmn_SndByt(CMD_CE, pstSpiXReg);

    /* Deselect the flash: chip select high */
    SF_CS_HIGH();                                              ///< Software enabled serial Flash chip selection
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_HIGH();                                         ///< Software enabled CPLD Flash selection
#endif

    /* Wait the end of flash writing */
    v_SpiDrv_Cmn_WrEndWait(pstSpiXReg);
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Read several bytes continuously. The number of bytes cannot exceed the chip capacity
* @Signal [in]  : pBuf : Data source buffer;
* @Signal [in]  : ulAddrRead : Read Data buffer address;
* @Signal [in]  : ulNumByte : Byte number
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_SpiDrv_ReadBuf(Uint16* pBuf, Uint32 ulAddrRead, Uint32 ulNumByte, volatile struct SPI_REGS *pstSpiXReg)
{
    SF_CS_LOW();                                   ///< Software enabled serial Flash chip selection
//    DELAY_US_APP(1.0f);
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_LOW();                              ///< Software enabled CPLD Flash selection
#endif
    (void)ui_SpiDrv_Cmn_SndByt(CMD_READ, pstSpiXReg);                                    ///< Send read command
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)((ulAddrRead & 0xFF0000U) >> 16U), pstSpiXReg);   ///< Send the high 8 bits of the sector address
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)((ulAddrRead & 0xFF00U) >> 8U), pstSpiXReg);      ///< Send the middle 8 bits of the sector address
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)((ulAddrRead & 0xFFU)), pstSpiXReg);              ///< Send the low 8 bits of the sector address
    v_SpiDrv_ReadBuf_DataRx(pBuf, ulNumByte, pstSpiXReg);                                ///< Receive Data from flash
    SF_CS_HIGH();                                              ///< Software enabled serial Flash chip selection
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_HIGH();                                         ///< Software enabled CPLD Flash selection
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Read several bytes continuously. The number of bytes cannot exceed the chip capacity
* @Signal [in]  : pBuf : Data source buffer;
* @Signal [in]  : ulAddrRead : Read Data buffer address;
* @Signal [in]  : ulNumByte : Byte number
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_SpiDrv_ReadBuf_DataRx(Uint16* pBuf, Uint32 ulNumByte, volatile struct SPI_REGS *pstSpiXReg)
{
    while((ulNumByte--) != 0UL)
    {   /* Read a byte from the flash */
        *pBuf = ui_SpiDrv_Cmn_SndByt(DUMMY_BYTE, pstSpiXReg);
        /* Point to the next location where the byte read will be saved */
        pBuf++;
    }
}
/***********************************************************************************************
* @Type         : Module function
* @brief        : Write one sector and verify. If it is incorrect, rewrite it twice. This function automatically completes the erase operation
* @Signal [in]  : pBuf : Data source buffer;
* @Signal [in]  : ulAddrWr : Write Data buffer address;
* @Signal [in]  : uiNumByte : Write Data size cannot over page;
* @Signal [out] : null
* @return       : 1 : Success  0 : Fail
***********************************************************************************************/
void v_SpiDrv_WrBuf(Uint16* pBuf, Uint32 ulAddrWr, Uint16 uiNumByte, volatile struct SPI_REGS *pstSpiXReg)
{
    stSpiDrvLoc.uiAddr = (Uint16)(ulAddrWr % SF_PAGE_SIZE);           ///< Address
    stSpiDrvLoc.uiDataCnt = SF_PAGE_SIZE - stSpiDrvLoc.uiAddr;        ///< Data Counter
    stSpiDrvLoc.uiNumOfPage =  uiNumByte / SF_PAGE_SIZE;              ///< Number of page
    stSpiDrvLoc.uiNumOfSingle = uiNumByte % SF_PAGE_SIZE;             ///< Number of single

    if (stSpiDrvLoc.uiAddr == 0U) ///< The starting address is the first address of the page
    {
        v_SpiDrv_WrBuf_FirstAdr(pBuf, ulAddrWr, uiNumByte, pstSpiXReg);
    }
    else  ///< The starting address is not the first address of the page
    {
        v_SpiDrv_WrBuf_NonFirstAdr(pBuf, ulAddrWr, uiNumByte, pstSpiXReg);
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Write one sector and verify. If it is incorrect, rewrite it twice. This function automatically completes the erase operation
* @Signal [in]  : pBuf : Data source buffer;
* @Signal [in]  : ulAddrWr : Write Data buffer address;
* @Signal [in]  : uiNumByte : Write Data size cannot over page;
* @Signal [out] : null
* @return       : 1 : Success  0 : Fail
***********************************************************************************************/
static void v_SpiDrv_WrBuf_FirstAdr(Uint16* pBuf, Uint32 ulAddrWr, Uint16 uiNumByte, volatile struct SPI_REGS *pstSpiXReg)
{
    if(0U == stSpiDrvLoc.uiNumOfPage) ///< The data length is less than the page size
    {
        v_SpiDrv_WrBuf_AutoWrPage_Wr(pBuf, ulAddrWr, uiNumByte, pstSpiXReg);
    }
    else    ///< Data length greater than or equal to page size
    {
        while((stSpiDrvLoc.uiNumOfPage--) != 0U)
        {
            v_SpiDrv_WrBuf_AutoWrPage_Wr(pBuf, ulAddrWr, SF_PAGE_SIZE, pstSpiXReg);
            ulAddrWr +=  SF_PAGE_SIZE;      ///< Add write address
            pBuf += SF_PAGE_SIZE;           ///< Add buffer point
        }
        v_SpiDrv_WrBuf_AutoWrPage_Wr(pBuf, ulAddrWr, stSpiDrvLoc.uiNumOfSingle, pstSpiXReg);
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Write one sector and verify. If it is incorrect, rewrite it twice. This function automatically completes the erase operation
* @Signal [in]  : pBuf : Data source buffer;
* @Signal [in]  : ulAddrWr : Write Data buffer address;
* @Signal [in]  : uiNumByte : Write Data size cannot over page;
* @Signal [out] : null
* @return       : 1 : Success  0 : Fail
***********************************************************************************************/
static void v_SpiDrv_WrBuf_NonFirstAdr(Uint16* pBuf, Uint32 ulAddrWr, Uint16 uiNumByte, volatile struct SPI_REGS *pstSpiXReg)
{
    Uint16 l_uiLenWrTemp   = 0U;   ///< Write length temporary

    if (0U == stSpiDrvLoc.uiNumOfPage) ///< The data length is less than the page size
    {
        if(stSpiDrvLoc.uiNumOfSingle > stSpiDrvLoc.uiDataCnt)  ///< (uiNumByte + ulAddrWr) > SPI_FLASH_PAGESIZE
        {
            l_uiLenWrTemp = stSpiDrvLoc.uiNumOfSingle - stSpiDrvLoc.uiDataCnt;
            v_SpiDrv_WrBuf_AutoWrPage_Wr(pBuf, ulAddrWr, stSpiDrvLoc.uiDataCnt, pstSpiXReg);
            ulAddrWr +=  stSpiDrvLoc.uiDataCnt;     ///< Add write address
            pBuf += stSpiDrvLoc.uiDataCnt;          ///< Add buffer point
            v_SpiDrv_WrBuf_AutoWrPage_Wr(pBuf, ulAddrWr, l_uiLenWrTemp, pstSpiXReg);
        }
        else
        {
            v_SpiDrv_WrBuf_AutoWrPage_Wr(pBuf, ulAddrWr, uiNumByte, pstSpiXReg);
        }
    }
    else    ///< Data length greater than or equal to page size
    {
        uiNumByte -= stSpiDrvLoc.uiDataCnt;
        stSpiDrvLoc.uiNumOfPage =  uiNumByte / SF_PAGE_SIZE;
        stSpiDrvLoc.uiNumOfSingle = uiNumByte % SF_PAGE_SIZE;

        v_SpiDrv_WrBuf_AutoWrPage_Wr(pBuf, ulAddrWr, stSpiDrvLoc.uiDataCnt, pstSpiXReg);
        ulAddrWr +=  stSpiDrvLoc.uiDataCnt;     ///< Add write address     
        pBuf += stSpiDrvLoc.uiDataCnt;          ///< Add buffer point

        while((stSpiDrvLoc.uiNumOfPage--) != 0U)
        {
            v_SpiDrv_WrBuf_AutoWrPage_Wr(pBuf, ulAddrWr, SF_PAGE_SIZE, pstSpiXReg);
            ulAddrWr +=  SF_PAGE_SIZE;      ///< Add write address
            pBuf += SF_PAGE_SIZE;           ///< Add buffer point            
        }

        if(0U != stSpiDrvLoc.uiNumOfSingle)
        {
            v_SpiDrv_WrBuf_AutoWrPage_Wr(pBuf, ulAddrWr, stSpiDrvLoc.uiNumOfSingle, pstSpiXReg);
        }
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Write several bytes into a page. The number of bytes cannot exceed the page size (256)
* @Signal [in]  : pBuf : Data source buffer;
* @Signal [in]  : ulAddrWr : Write Data buffer address;
* @Signal [in]  : uiSize : Write Data size cannot over page;
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_SpiDrv_WrBuf_AutoWrPage_Wr(Uint16 * pBuf, Uint32 ulAddrWr, Uint16 uiSize, volatile struct SPI_REGS *pstSpiXReg)
{
    /* Enable the write access to the flash */
    v_SpiDrv_Cmn_WrEna(pstSpiXReg);

    /* Select the flash: chip select low */
    SF_CS_LOW();                                   ///< Software enabled serial Flash chip selection
//    DELAY_US_APP(1.0f);
#if 2U == GRID_PHASE_NUMBER
    SF_CS_CPLD_LOW();                              ///< Software enabled CPLD Flash selection
#endif
    /* Send "write to memory" instruction */
    (void)ui_SpiDrv_Cmn_SndByt(CMD_PRGM, pstSpiXReg);

    (void)ui_SpiDrv_Cmn_SndByt((Uint16)((ulAddrWr & 0xFF0000U) >> 16U), pstSpiXReg);       ///< Send the high 8 bits of the sector address
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)((ulAddrWr & 0xFF00U) >> 8U), pstSpiXReg);          ///< Send the middle 8 bits of the sector address
    (void)ui_SpiDrv_Cmn_SndByt((Uint16)(ulAddrWr & 0xFFU), pstSpiXReg);                    ///< Send the low 8 bits of the sector addres

    while((uiSize--) != 0U)
    {
        /* Send the current byte */
        (void)ui_SpiDrv_Cmn_SndByt(*pBuf, pstSpiXReg);             ///< Send data
        /* Point on the next byte to be written */
        pBuf++;
    }

    /* Deselect the flash: chip select high */
     SF_CS_HIGH();                                              ///< Software enabled serial Flash chip selection
#if 2U == GRID_PHASE_NUMBER
     SF_CS_CPLD_HIGH();                                         ///< Software enabled CPLD Flash selection
#endif
    /* Wait the end of flash writing */
    v_SpiDrv_Cmn_WrEndWait(pstSpiXReg);
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
