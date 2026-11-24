//==============================================================================================
//    File description
//==============================================================================================
/**@file         Spi.c
 * @brief
 * The source file of Spi is designed to realize SPI communication.
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
#include "Spi.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
ST_SPI stSpi;                    ///< Spi global struct

#if(1U == SPI_DBG)
ST_SPI stSpiDbg;                 ///< Communication interface debug global struct
#endif

static ST_SPI_LOC stSpiLoc;      ///< Spi drive local struct

//==============================================================================================
//    Function definition
//==============================================================================================
/***********************************************************************************************
* @Type         : Module function
* @brief        : Initialize
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_Spi_Init(void)
{
    Uint16 i = 0U;

    /* Local Signal */
    stSpiLoc.uiCntrRetryWr          = 0U;               ///< Initialize retry write counter
    for(i = 0U; i < (PAGES_PER_GROUP_DATAS * PAGE_SIZE_SPI); i++)
    {
        stSpiLoc.uiBufSpiWR[i]      = 0U;               ///< Initialize write buffer
    }   
    v_Spi_DataRec_Init(&stSpi.stFltDataRead);           ///< Initialize fault data read

    /* Global Signal */
    stSpiLoc.stPrmExt.stErrSpi.all    = 0U;             ///< Initialize error flag
    stSpiLoc.stPrmExt.uiStSpi         = SPI_STATE_IDLE; ///< Initialize SPI state
	stSpiLoc.stPrmExt.uiFlgReadCmpl   = 0U;             ///< Initialize read complete flag

#if(1U == SPI_DBG)
    stSpiDbg.stErrSpi.all      = stSpiLoc.stPrmExt.stErrSpi.all;
    stSpiDbg.uiStSpi           = stSpiLoc.stPrmExt.uiStSpi;
    stSpiDbg.uiFlgReadCmpl     = stSpiLoc.stPrmExt.uiFlgReadCmpl;

    stSpi.stErrSpi.all         = stSpiDbg.stErrSpi.all;
    stSpi.uiStSpi              = stSpiDbg.uiStSpi;
	stSpi.uiFlgReadCmpl        = stSpiDbg.uiFlgReadCmpl;
#else
    stSpi.stErrSpi.all         = stSpiLoc.stPrmExt.stErrSpi.all; 
    stSpi.uiStSpi              = stSpiLoc.stPrmExt.uiStSpi;
	stSpi.uiFlgReadCmpl        = stSpiLoc.stPrmExt.uiFlgReadCmpl;
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Initialize data record structure
* @Signal [in]  : pData: Pointer to fault data structure
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Spi_DataRec_Init(ST_FLT_DATA *pData)
{
    Uint16 i = 0U,j = 0U;   ///< Initialize to 0U 

    /* Initialize time */
    pData->ullTime.all = 0UL;

    /* Initialize power parameters */
    for(i = 0U; i < SIZE_POW_PRM_TYP_FLT_REC; i++)
    {
        for(j = 0U; j < SIZE_POW_PRM_NUM_FLT_REC; j++)
        {
            pData->uiPrmPow[i][j] = 0U;
        }
    }

    /* Initialize temperature data */
    for(i = 0U; i < SIZE_TEMP_DATA_FLT_REC; i++)
    {
        pData->siTemp[i] = 0;
    }

    /* Initialize fault words */
    for(i = 0U; i < SIZE_FAULT_WORD_FLT_REC; i++)
    {   
        pData->uiWordFlt[i] = 0U;
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : 1ms task
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_Spi_1ms(void)
{
    v_Spi_FltRst_1ms();     ///< Spi fault reset
    v_Spi_StMac_1ms();      ///< State machine
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Check fault flag
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Spi_FltRst_1ms(void)
{
    /* SPI fault reset */
    if((FCN_ENABLE == stComIf.uiFlgFltRst) && (0U != stSpiLoc.stPrmExt.stErrSpi.all))
    {
        stSpiLoc.stPrmExt.stErrSpi.all = 0U;    ///< Clear error flag
    }

    /* Output Signal*/
#if(1U == SPI_DBG)
    stSpi.stErrSpi.all      = stSpiDbg.stErrSpi.all;
#else
    stSpi.stErrSpi.all      = stSpiLoc.stPrmExt.stErrSpi.all;
#endif
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : State machine
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Spi_StMac_1ms(void)
{
    switch(stSpiLoc.stPrmExt.uiStSpi)
    {
        case SPI_STATE_IDLE:
            v_Spi_StMac_FlgChk();                    ///< State machine flag check
            break;

        case SPI_STATE_WRITE:
            v_Spi_StMac_DataWr();                    ///< Write data to flash
            v_Spi_StMac_DataRead(0U);                ///< Read data
            v_Spi_StMac_DataVrfy();                  ///< Verify data
            v_Spi_StMac_ErrHndl();                   ///< Error handle
            break;

        case SPI_STATE_READ:
            v_Spi_StMac_AutoRead(&stCom.unTiReq);             ///< Time from com
            stSpiLoc.stPrmExt.uiStSpi = SPI_STATE_IDLE;       ///< Set idle state
            stSpiLoc.stPrmExt.uiFlgReadCmpl = 1U;  			  ///< Set read write complete flag
            break;

        default:
            stSpiLoc.stPrmExt.uiStSpi       = SPI_STATE_IDLE;       ///< Set idle state
            stSpiLoc.stPrmExt.uiFlgReadCmpl = 0U;             ///< clear read write complete flag
            break;
    }

    /* Global Signal*/
#if(1U == SPI_DBG)
    stSpi.stErrSpi.all      = stSpiDbg.stErrSpi.all;
    stSpi.uiStSpi           = stSpiDbg.uiStSpi;
	stSpi.uiFlgReadCmpl     = stSpiDbg.uiFlgReadCmpl;
#else
    stSpi.stErrSpi.all      = stSpiLoc.stPrmExt.stErrSpi.all; 
    stSpi.uiStSpi           = stSpiLoc.stPrmExt.uiStSpi;
    stSpi.uiFlgReadCmpl     = stSpiLoc.stPrmExt.uiFlgReadCmpl;
#endif  
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Check the flag
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Spi_StMac_FlgChk(void) 
{
    if(1U == stFltDataRec.uiFlgFltDataRec)
    {
        stSpiLoc.stPrmExt.uiStSpi    = SPI_STATE_WRITE;             ///< Set write state
        stFltDataRec.uiFlgFltDataRec = 0U;
    }
    else if((1U == stCom.uiFlgReadReq) && (0U == stSpiLoc.stPrmExt.uiFlgReadCmpl))         
    {
        stSpiLoc.stPrmExt.uiStSpi = SPI_STATE_READ;                 ///< Set read state
    }
    else if(0U == stCom.uiFlgReadReq)
    {
        stSpiLoc.stPrmExt.uiFlgReadCmpl = 0U;
    }
    else
    {
        ///< No code
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Store data     
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Spi_StMac_DataWr(void)
{
    Uint16 l_uiPagePrsnt  = 0U;      ///< Initialize to 0U
    Uint32 l_ulAddr       = 0UL;     ///< Initialize to 0UL

    /* Read the current page value */
    l_uiPagePrsnt = ui_Spi_Cmn_PageCurrRead();

    /* Calculate storage address */
    l_ulAddr = DATA_START_ADDRESS + ((Uint32)l_uiPagePrsnt * (Uint32)PAGE_SIZE_SPI);

    /* Determine whether to erase the next sector */
    if(1U == ((l_uiPagePrsnt + 1U) % SECTOR_SIZE_SPI))
    {
        v_SpiDrv_Cmn_EraseSector(l_ulAddr, &SPIX_REG);         ///< Erase Sector
    }

    /* Write data */
    v_Spi_StMac_DataWr_Cnv(&stFltDataRec.stFltData); ///< Convert data
    v_SpiDrv_WrBuf(stSpiLoc.uiBufSpiWR, l_ulAddr, PAGES_PER_GROUP_DATAS * PAGE_SIZE_SPI, &SPIX_REG);  ///< Write data

    /* Update page value */
    l_uiPagePrsnt += PAGES_PER_GROUP_DATAS;          ///< Add the current page value
    if(l_uiPagePrsnt >= MAX_PAGE_COUNT)              ///< Page exceeds the limit
    {
        l_uiPagePrsnt = 0U;                          ///< Reset the current page value
    }
    v_Spi_StMac_DataWr_PageCurrUpd(l_uiPagePrsnt);   ///< Update the current page value
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Initialize the current page value
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static Uint16 ui_Spi_Cmn_PageCurrRead(void)
{
    Uint16 l_uiBuf[2];
    Uint16 l_uiPagePrsnt = 0U;       ///< Initialize to 0U
    
    v_SpiDrv_ReadBuf(l_uiBuf, CURRENT_PAGE_ADDRESS, 2U, &SPIX_REG);        ///< Read the current page value from Sector 0 of Block0
    l_uiPagePrsnt = (l_uiBuf[0] << 8U) | l_uiBuf[1];            ///< Convert to Uint16
    if(l_uiPagePrsnt == 0xFFFFU)                                ///< If not initialized (assuming all 0xFF indicate uninitialized), initialize to 0
    {
        l_uiPagePrsnt = 0U;
        l_uiBuf[0] = (l_uiPagePrsnt >> 8U) & 0xFFU;
        l_uiBuf[1] = l_uiPagePrsnt & 0xFFU;
        v_SpiDrv_WrBuf(l_uiBuf, CURRENT_PAGE_ADDRESS, 2U, &SPIX_REG);
    }
    else if(l_uiPagePrsnt >= MAX_PAGE_COUNT)    ///< Page exceeds the limit
    {
        l_uiPagePrsnt = 0U;     ///< Reset the current page value
    }
    else
    {
        ///< No code
    }

    return l_uiPagePrsnt;       ///< Return the current page value
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Update current page index storage
* @Signal [in]  : uiPagePrsnt:Current page index to update
* @Signal [out] : None
* @return       : None
***********************************************************************************************/
static void v_Spi_StMac_DataWr_PageCurrUpd(Uint16 uiPagePrsnt)        
{
    Uint16 l_uiBuf[2];  ///< Temporary buffer for page index storage

    l_uiBuf[0] = (uiPagePrsnt >> 8U) & 0xFFU;  ///< Store high byte of page index
    l_uiBuf[1] = uiPagePrsnt & 0xFFU;          ///< Store low byte of page index
    
    v_SpiDrv_Cmn_EraseSector(CURRENT_PAGE_ADDRESS, &SPIX_REG);     ///< Erase target sector before write
    v_SpiDrv_WrBuf(l_uiBuf, CURRENT_PAGE_ADDRESS, 2U, &SPIX_REG);  ///< Write new page index to flash
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Convert data structure to byte stream
* @Signal [in]  : pData: Pointer to fault data structure
* @Signal [out] : None
* @return       : None
***********************************************************************************************/
static void v_Spi_StMac_DataWr_Cnv(ST_FLT_DATA *pData)
{
    Uint16 i = 0U,j = 0U;
    Uint16 l_uiIndex = 0U;  ///< Buffer write position index

    /* Serialize 64-bit times */
    for(i = 0U; i < SIZE_TI_SYS_FLT_REC; i++)
    {
        stSpiLoc.uiBufSpiWR[l_uiIndex++] = (Uint16)((pData->ullTime.all >> (8U * (7U - i))) & 0xFFU);
    }

    /* Convert power parameters to bytes */
    for(i = 0U; i < SIZE_POW_PRM_TYP_FLT_REC; i++)
    {
        for(j = stFltDataRec.uiPtrArrRec; j < (SIZE_POW_PRM_NUM_FLT_REC + stFltDataRec.uiPtrArrRec); j++)
        {
            stSpiLoc.uiBufSpiWR[l_uiIndex++] = (pData->uiPrmPow[i][j % SIZE_POW_PRM_NUM_FLT_REC] >> 8U) & 0xFFU;  ///< Store high byte
            stSpiLoc.uiBufSpiWR[l_uiIndex++] = pData->uiPrmPow[i][j % SIZE_POW_PRM_NUM_FLT_REC] & 0xFFU;         ///< Store low byte
        }
    }

    /* Write temperature data */
    for(i = 0U; i < SIZE_TEMP_DATA_FLT_REC; i++)
    {
        stSpiLoc.uiBufSpiWR[l_uiIndex++] = ((Uint16)pData->siTemp[i] >> 8U) & 0xFFU;  ///< High byte
        stSpiLoc.uiBufSpiWR[l_uiIndex++] = ((Uint16)pData->siTemp[i] & 0xFFU);        ///< Low byte
    }

    /* Write fault words */
    for(i = 0U; i < SIZE_FAULT_WORD_FLT_REC; i++)
    {
        stSpiLoc.uiBufSpiWR[l_uiIndex++] = (pData->uiWordFlt[i] >> 8U) & 0xFFU; ///< High byte
        stSpiLoc.uiBufSpiWR[l_uiIndex++] = pData->uiWordFlt[i] & 0xFFU;         ///< Low byte
    }

    /* Fill remaining page space with default value */
    while(l_uiIndex < PAGES_PER_GROUP_DATAS * PAGE_SIZE_SPI)
    {
        stSpiLoc.uiBufSpiWR[l_uiIndex++] = 0xFFU;  ///< Initialize unused bytes to erased state
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Data verify
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Spi_StMac_DataVrfy(void)
{
    Uint16 i = 0U, j = 0U;
    
    /* Verify times */
    if(stFltDataRec.stFltData.ullTime.all != stSpi.stFltDataRead.ullTime.all)
    {
        stSpiLoc.stPrmExt.stErrSpi.bit.uiErrTime = 1U;
    }
    
    /* Verify power parameters */
    for(i = 0U; i < SIZE_POW_PRM_TYP_FLT_REC; i++)
    {
        for(j = 0U; j < SIZE_POW_PRM_NUM_FLT_REC; j++)
        {
            if(stFltDataRec.stFltData.uiPrmPow[i][(j + stFltDataRec.uiPtrArrRec) % SIZE_POW_PRM_NUM_FLT_REC] != stSpi.stFltDataRead.uiPrmPow[i][j])
            {
                stSpiLoc.stPrmExt.stErrSpi.bit.uiErrPrmPow = 1U;
            }
        }
    }
    
    /* Verify temperature data */
    for(i = 0U; i < SIZE_TEMP_DATA_FLT_REC; i++)
    {
        if(stFltDataRec.stFltData.siTemp[i] != stSpi.stFltDataRead.siTemp[i])
        {
            stSpiLoc.stPrmExt.stErrSpi.bit.uiErrTemp = 1U;  
        }
    }
    
    /* Verify fault words */
    for(i = 0U; i < SIZE_FAULT_WORD_FLT_REC; i++)
    {
        if(stFltDataRec.stFltData.uiWordFlt[i] != stSpi.stFltDataRead.uiWordFlt[i])
        {
            stSpiLoc.stPrmExt.stErrSpi.bit.uiErrWordFlt = 1U;   
        }
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Error handling
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Spi_StMac_ErrHndl(void)
{
    if(0U != stSpiLoc.stPrmExt.stErrSpi.all)
    {
        if(stSpiLoc.uiCntrRetryWr < TI_RETRY_WR_DATA)
        {
            stSpiLoc.stPrmExt.uiStSpi = SPI_STATE_WRITE;     ///< Set error state
            stSpiLoc.uiCntrRetryWr++;
        }
        else
        {
            stSpiLoc.stPrmExt.uiStSpi = SPI_STATE_IDLE;      ///< Set idle state
            stSpiLoc.uiCntrRetryWr = 0U;
        }
    }
    else
    {
        stSpiLoc.stPrmExt.uiStSpi = SPI_STATE_IDLE;      ///< Set idle state
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Read data (can choose whether to read the previous set of data)
* @Signal [in]  : uiPageReadReq:Page read request
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Spi_StMac_DataRead(Uint16 uiPageReadReq)
{
    static Uint16 sl_uiPageCurrRead = 0xFFFFU;  ///< Initialize to invalid value
    Uint16 l_uiPageLatestData       = 0U;       ///< Initialize to 0U
    Uint16 l_uiPageCurrWr           = 0U;       ///< Initialize to 0U
    Uint16 l_uiPageJump             = 0U;       ///< Initialize to 0U
    Uint32 l_ulAddr                 = 0UL;      ///< Initialize to 0UL

    l_uiPageCurrWr = ui_Spi_Cmn_PageCurrRead(); ///< Initialize the current page value
    if(0U == l_uiPageCurrWr)                    ///< Calculate the location of the latest data
    {
        l_uiPageLatestData = MAX_PAGE_COUNT - PAGES_PER_GROUP_DATAS;       ///< Storage is full, the latest data is at the end
    } 
    else 
    {
        l_uiPageLatestData = l_uiPageCurrWr - PAGES_PER_GROUP_DATAS;       ///< The latest data can be found in l_uiPageCurrWr - PAGE1_PERDATA
    }

    if((sl_uiPageCurrRead == 0xFFFFU) || (uiPageReadReq == 0U))     ///< Initialize read pointer (only on the first call)
    {
        sl_uiPageCurrRead = l_uiPageLatestData;          ///< Read latest data page
    } 
    else 
    {
        l_uiPageJump = uiPageReadReq * PAGES_PER_GROUP_DATAS;   ///< Calculate the jump page
        if(sl_uiPageCurrRead >= l_uiPageJump)
        {
            sl_uiPageCurrRead -= l_uiPageJump;           ///< Jump to the specified page
        }
        else
        {
            sl_uiPageCurrRead = MAX_PAGE_COUNT - (l_uiPageJump - sl_uiPageCurrRead);    ///< Jump to the specified page
        }
    }

    l_ulAddr = DATA_START_ADDRESS + ((Uint32)sl_uiPageCurrRead * (Uint32)PAGE_SIZE_SPI);          ///< Calculate the read address
    v_SpiDrv_ReadBuf(stSpiLoc.uiBufSpiWR, l_ulAddr, (Uint32)(PAGES_PER_GROUP_DATAS * PAGE_SIZE_SPI), &SPIX_REG);    ///< Read data
    v_Spi_StMac_DataRead_Cnv(&stSpi.stFltDataRead);                                            ///< Convert data
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Read data by searching for the closest time match
* @Signal [in]  : pstTiReq: Requested time to find in stored data
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_Spi_StMac_AutoRead(UN_SYS_TIME *pstTiReq)
{
    Uint16 i = 0U;
    Uint16 l_uiTiBuf[SIZE_TI_SYS_FLT_REC];                   ///< Buffer for time data
    Uint16 l_uiPageBest          = 0xFFFFU;                  ///< Initialize to invalid value
    Uint16 l_uiPagePrsnt         = 0U;                       ///< Current page pointer
    Uint16 l_uiPageStrt          = 0U;                       ///< Starting page for search
    Uint16 l_uiPageCntr          = 0U;                       ///< Page counter for search limit
    Uint16 l_uiPageSrch          = 0U;                       ///< Current search page
    Uint32 l_ulAddr              = 0UL;                      ///< SPI address
    Uint64 l_ullTiMinDelta       = 0xFFFFFFFFFFFFFFFFULL;    ///< Minimum time difference found
    Uint64 l_ullTiDelta          = 0ULL;                     ///< Current time difference
    UN_SYS_TIME l_ullTiPage;                                 ///< Time from current page

    /* Data page processing */
    l_uiPagePrsnt = ui_Spi_Cmn_PageCurrRead();      ///< Read the current page value
    if(0U == l_uiPagePrsnt)
    {
        l_uiPageStrt = MAX_PAGE_COUNT - PAGES_PER_GROUP_DATAS;  ///< Storage is full, the latest data is at the end
    }
    else
    {
        l_uiPageStrt = l_uiPagePrsnt - PAGES_PER_GROUP_DATAS;   
    }

    /* Search backward through stored data pages */
    l_uiPageSrch = l_uiPageStrt;
    while(l_uiPageCntr < MAX_GROUP_COUNT)
    {
        /* Read time from current page */
        l_ulAddr = DATA_START_ADDRESS + ((Uint32)l_uiPageSrch * (Uint32)PAGE_SIZE_SPI);
        v_SpiDrv_ReadBuf(l_uiTiBuf, l_ulAddr, (Uint32)SIZE_TI_SYS_FLT_REC, &SPIX_REG);
        
        /* Reconstruct 64-bit time */
        l_ullTiPage.all = 0ULL;
        for(i = 0U; i < SIZE_TI_SYS_FLT_REC; i++)
        {
            l_ullTiPage.all |= ((Uint64)l_uiTiBuf[i] << (8U * (7U - i)));
        }
    
        /* Process valid time only (not empty or erased) */
        if((l_ullTiPage.all != 0xFFFFFFFFFFFFFFFFULL) && (l_ullTiPage.all != 0ULL) && (l_ullTiPage.bit.ulYear != YEAR_SYS_TIME_DFT))
        {
            if(pstTiReq->all > l_ullTiPage.all)
            {
                l_ullTiDelta = pstTiReq->all - l_ullTiPage.all;        ///< Calculate time difference
            }
            else
            {
                l_ullTiDelta = l_ullTiPage.all - pstTiReq->all;        ///< Calculate time difference
            }

            /* Update best match if this is closer */
            if(l_ullTiDelta < l_ullTiMinDelta) 
            {
                l_ullTiMinDelta = l_ullTiDelta;
                l_uiPageBest = l_uiPageSrch;
            }
            /* Stop search if time difference starts increasing and we have a match */
            else if((l_ullTiDelta > l_ullTiMinDelta) && (l_uiPageBest != 0xFFFFU)) 
            {
                break;
            }
            else
            {
                ///< No code
            }
        }

        /* Check exit conditions */
        l_uiPageCntr++;
        if((l_uiPageSrch == l_uiPageStrt) && (l_uiPageCntr > 1U))
        {
            break; ///< Full circle search completed
        }
        
        /* Update search page with proper underflow handling */
        if(l_uiPageSrch < PAGES_PER_GROUP_DATAS)
        {
            /* Wrap around to the end when underflow would occur */
            l_uiPageSrch = MAX_PAGE_COUNT - PAGES_PER_GROUP_DATAS;
        }
        else
        {
            /* Normal decrement */
            l_uiPageSrch -= PAGES_PER_GROUP_DATAS;
        }
    }

    /* Process search results */
    if(l_uiPageBest != 0xFFFFU) 
    {
        /* Read the best matching data page */
        l_ulAddr = DATA_START_ADDRESS + ((Uint32)l_uiPageBest * (Uint32)PAGE_SIZE_SPI);
        v_SpiDrv_ReadBuf(stSpiLoc.uiBufSpiWR, l_ulAddr, (Uint32)(PAGES_PER_GROUP_DATAS * PAGE_SIZE_SPI), &SPIX_REG);
        v_Spi_StMac_DataRead_Cnv(&stSpi.stFltDataRead);
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : Convert byte stream to data structure
* @Signal [in]  : pData:Pointer to destination data structure
* @Signal [out] : None
* @return       : None
***********************************************************************************************/
static void v_Spi_StMac_DataRead_Cnv(ST_FLT_DATA *pData)
{
    Uint16 i = 0U,j = 0U;       
    Uint16 l_uiIndex = 0U;      ///< Buffer read position index
    Uint16 l_uiTempTmp = 0U;    ///< Temporary temperature data  

    /* Reconstruct 64-bit time from bytes */
    pData->ullTime.all = 0ULL;
    for(i = 0U; i < SIZE_TI_SYS_FLT_REC; i++)
    {
        pData->ullTime.all |= ((Uint64)stSpiLoc.uiBufSpiWR[l_uiIndex++] << (8U * (7U - i)));
    }

    /* Rebuild power parameter array from byte */
    for(i = 0U; i < SIZE_POW_PRM_TYP_FLT_REC; i++)
    {
        for (j = 0U; j < SIZE_POW_PRM_NUM_FLT_REC; j++)
        {
            pData->uiPrmPow[i][j] = (stSpiLoc.uiBufSpiWR[l_uiIndex] << 8U) | stSpiLoc.uiBufSpiWR[l_uiIndex + 1U];
            l_uiIndex += 2U;  ///< Advance buffer index by 2 bytes
        }
    }

    /* Read temperature data */
    for(i = 0U; i < SIZE_TEMP_DATA_FLT_REC; i++)
    {
        l_uiTempTmp = (stSpiLoc.uiBufSpiWR[l_uiIndex] << 8U) | stSpiLoc.uiBufSpiWR[l_uiIndex + 1U];  ///< Read temperature data
        pData->siTemp[i] = (int16)l_uiTempTmp;
        l_uiIndex += 2U;
    }

    /* Read fault words */
    for(i = 0U; i < SIZE_FAULT_WORD_FLT_REC; i++)
    {
        pData->uiWordFlt[i] = (stSpiLoc.uiBufSpiWR[l_uiIndex] << 8U) | stSpiLoc.uiBufSpiWR[l_uiIndex + 1U];   ///< Read fault words
        l_uiIndex += 2U;
    }
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//==============================================================================================
// End of file.
//==============================================================================================
