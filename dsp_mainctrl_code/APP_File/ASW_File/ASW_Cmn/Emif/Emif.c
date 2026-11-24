//==============================================================================================
//    File description
//==============================================================================================
/**@file         Emif.c
 * @brief
 * The source file of Emif is designed to realize SPI communication.
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
 * 2025/11/27
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

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "Emif.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
#pragma DATA_SECTION(stEmifDma1, "CMADataRam")
#pragma DATA_SECTION(stEmifDma1Raw, "CMADataRam")
//#pragma DATA_SECTION(stEmifDmaPollData, "CMADataRam")
//#pragma DATA_SECTION(stEmifDma2, "CMADataRam")

/* Emif global struct */
ST_EMIF_DMA stEmifDma1;
ST_EMIF_DMA stEmifDma1Raw;
ST_EMIF_DMA_DATA stEmifDmaPollData;
//ST_EMIF_DMA stEmifDma2;
ST_EMIF stEmif;

#if(1U == EMIF_DBG)
ST_EMIF stEmifDbg;
#endif

/* Emif local struct */
static ST_EMIF_LOC stEmifLoc;

//==============================================================================================
//    Function definition
//==============================================================================================
/***********************************************************************************************
* @Type         : Module function
* @brief        : EMIF initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
extern void v_Emif_Init(void)
{
    Uint16 i;

    for(i = 0U; i < DMA_FPGA_WORD_NUM; i++)
    {
        ((int16 *)&stEmifDma1)[i] = 0;
        ((int16 *)&stEmifDma1Raw)[i] = 0;
    }
    stEmifLoc.uiCodeChkFastRd     = 0U;
    stEmifLoc.uiCntrFastRdHeadErr = 0U;
    stEmifLoc.uiCntrFastRdChkErr  = 0U;
    stEmifLoc.uiCntrFastRdRx      = 0U;
    stEmifLoc.uiCodeChkCellRd     = 0U;
    stEmifLoc.uiCntrCellRdHeadErr = 0U;
    stEmifLoc.uiCntrCellRdChkErr  = 0U;
    stEmifLoc.uiCntrCellRdRx      = 0U;

    stEmifLoc.ulAddrCellRd[0] = FPGA_RD_CHB_FLT_BASE_ADDR;        ///< Initialize to FPGA_RD_CHB_FLT_BASE_ADDR
    stEmifLoc.ulAddrCellRd[1] = FPGA_RD_CHB_VOLT_BASE_ADDR;
    stEmifLoc.ulAddrCellRd[2] = FPGA_RD_DAB_CURR_BASE_ADDR;
    stEmifLoc.ulAddrCellRd[3] = FPGA_RD_FPGA_VER_BASE_ADDR;

    stEmifLoc.uiFlgCellRd = 0U;
    for(i = 0U; i < FPGA_RD_WORD_NUM; i++)
    {
        stEmifLoc.siPrmCellRd[i] = 0;
    }
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : EMIF read ISR function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
extern void v_Emif_Rd_Isr(void)
{
    /* Read DMA parameter */
#if 1U == ENA_EMIF_DSP_DMA_RD

    stEmifLoc.uiCodeChkFastRd = ui_Emif_Fpga_Fast_Chk((int16 *)&stEmifDma1Raw); //2.59us

    if(FPGA_NO_ERR_CODE == stEmifLoc.uiCodeChkFastRd)
    {
        memcpy((void *)&stEmifDma1, (const void *)&stEmifDma1Raw, DMA_FPGA_WORD_NUM * sizeof(int16));
    }
    #if 1U == ENA_DMA2_FPGA
    stEmifLoc.uiCodeChkFastRd = ui_Emif_Fpga_Fast_Chk((int16 *)&stEmifDma2.siPrmFromFpga);
    #endif
#endif
    /* Parse polling data */
    v_Emif_Fpga_Polldata_Rd();
    /* Read cell parameter */
#if 1U == ENA_EMIF_DSP_RD_CELL
    v_Emif_Fpga_Cell_Prm_Rd(); //4.49us
#endif
}

#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_Emif_Fpga_Wr_Debug, ".TI.ramfunc");
#endif
extern void v_Emif_Fpga_Wr_Debug(int16 *siBufWr, Uint32 ulAddrBase)
{
    FPGA_WR_WORD(ulAddrBase, *siBufWr); ///< Head
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_1,  *(siBufWr + 1U));///< Data
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_2,  *(siBufWr + 2U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_3,  *(siBufWr + 3U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_4,  *(siBufWr + 4U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_5,  *(siBufWr + 5U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_6,  *(siBufWr + 6U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_7,  *(siBufWr + 7U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_8,  *(siBufWr + 8U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_9,  *(siBufWr + 9U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_10, *(siBufWr + 10U));
}
/***********************************************************************************************
* @Type         : Module function
* @brief        : EMIF FPGA write function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_Emif_Fpga_Wr, ".TI.ramfunc");
#endif
Uint16 test_time[60];
extern void v_Emif_Fpga_Wr(int16 *siBufWr, Uint32 ulAddrBase)
{

    FPGA_WR_WORD(ulAddrBase, *siBufWr); ///< Head
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_1,  *(siBufWr + 1U));///< Data
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_2,  *(siBufWr + 2U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_3,  *(siBufWr + 3U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_4,  *(siBufWr + 4U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_5,  *(siBufWr + 5U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_6,  *(siBufWr + 6U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_7,  *(siBufWr + 7U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_8,  *(siBufWr + 8U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_9,  *(siBufWr + 9U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_10, *(siBufWr + 10U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_11, *(siBufWr + 11U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_12, *(siBufWr + 12U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_13, *(siBufWr + 13U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_14, *(siBufWr + 14U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_15, *(siBufWr + 15U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_16, *(siBufWr + 16U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_17, *(siBufWr + 17U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_18, *(siBufWr + 18U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_19, *(siBufWr + 19U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_20, *(siBufWr + 20U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_21, *(siBufWr + 21U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_22, *(siBufWr + 22U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_23, *(siBufWr + 23U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_24, *(siBufWr + 24U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_25, *(siBufWr + 25U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_26, *(siBufWr + 26U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_27, *(siBufWr + 27U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_28, *(siBufWr + 28U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_29, *(siBufWr + 29U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_30, *(siBufWr + 30U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_31, *(siBufWr + 31U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_32, *(siBufWr + 32U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_33, *(siBufWr + 33U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_34, *(siBufWr + 34U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_35, *(siBufWr + 35U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_36, *(siBufWr + 36U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_37, *(siBufWr + 37U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_38, *(siBufWr + 38U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_39, *(siBufWr + 39U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_40, *(siBufWr + 40U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_41, *(siBufWr + 41U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_42, *(siBufWr + 42U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_43, *(siBufWr + 43U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_44, *(siBufWr + 44U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_45, *(siBufWr + 45U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_46, *(siBufWr + 46U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_47, *(siBufWr + 47U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_48, *(siBufWr + 48U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_49, *(siBufWr + 49U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_50, *(siBufWr + 50U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_51, *(siBufWr + 51U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_52, *(siBufWr + 52U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_53, *(siBufWr + 53U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_54, *(siBufWr + 54U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_55, *(siBufWr + 55U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_56, *(siBufWr + 56U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_57, *(siBufWr + 57U));
    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_58, *(siBufWr + 58U));


    SUM_59_BUF(*(siBufWr + 59U), siBufWr);//2us
//    test_time[59] = test_time[0] + test_time[1]+test_time[2]+test_time[3]+test_time[4]+test_time[5]+test_time[6]+test_time[7]+test_time[8] \
//     /*0.3us*/      + test_time[9]+test_time[10]+test_time[11]+test_time[12]+test_time[13]+test_time[14]+test_time[15] \
//                    + test_time[16]+test_time[17]+test_time[18]+test_time[19]+test_time[20]+test_time[21]+test_time[22] \
//                    + test_time[23]+test_time[24]+test_time[25]+test_time[26]+test_time[27]+test_time[28]+test_time[29] \
//                    + test_time[16]+test_time[17]+test_time[18]+test_time[19]+test_time[20]+test_time[21]+test_time[22] \
//                    + test_time[23]+test_time[24]+test_time[25]+test_time[26]+test_time[27]+test_time[28]+test_time[29] \
//                    + test_time[16]+test_time[17]+test_time[18]+test_time[19]+test_time[20]+test_time[21]+test_time[22] \
//                    + test_time[23]+test_time[24]+test_time[25]+test_time[26]+test_time[27]+test_time[28]+test_time[29];

    FPGA_WR_WORD(ulAddrBase + FPGA_WR_ADDR_SHIFT_59, *(siBufWr + 59U));
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : EMIF FPGA parameter read function
* @Signal [in]  : null
* @Signal [out] : Error code
* @return       : null
***********************************************************************************************/
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(ui_Emif_Fpga_Rd, ".TI.ramfunc");
#endif
static Uint16 ui_Emif_Fpga_Rd(int16 *siBufRd, Uint32 ulAddrBase)
{
    int16  l_siCodeChk    = 0;        ///< check code
    Uint16 l_uiCodeReturn = 0U;       ///< return code
    static Uint16 sl_uiCntrTmp = 0U;

    FPGA_RD_WORD(*siBufRd , ulAddrBase);
    if(FPGA_RD_HEAD == *siBufRd)
    {
        FPGA_RD_WORD(*(siBufRd + 1U),  ulAddrBase + FPGA_WR_ADDR_SHIFT_1);
        FPGA_RD_WORD(*(siBufRd + 2U),  ulAddrBase + FPGA_WR_ADDR_SHIFT_2);
        FPGA_RD_WORD(*(siBufRd + 3U),  ulAddrBase + FPGA_WR_ADDR_SHIFT_3);
        FPGA_RD_WORD(*(siBufRd + 4U),  ulAddrBase + FPGA_WR_ADDR_SHIFT_4);
        FPGA_RD_WORD(*(siBufRd + 5U),  ulAddrBase + FPGA_WR_ADDR_SHIFT_5);
        FPGA_RD_WORD(*(siBufRd + 6U),  ulAddrBase + FPGA_WR_ADDR_SHIFT_6);
        FPGA_RD_WORD(*(siBufRd + 7U),  ulAddrBase + FPGA_WR_ADDR_SHIFT_7);
        FPGA_RD_WORD(*(siBufRd + 8U),  ulAddrBase + FPGA_WR_ADDR_SHIFT_8);
        FPGA_RD_WORD(*(siBufRd + 9U),  ulAddrBase + FPGA_WR_ADDR_SHIFT_9);
        FPGA_RD_WORD(*(siBufRd + 10U), ulAddrBase + FPGA_WR_ADDR_SHIFT_10);
        FPGA_RD_WORD(*(siBufRd + 11U), ulAddrBase + FPGA_WR_ADDR_SHIFT_11);
        FPGA_RD_WORD(*(siBufRd + 12U), ulAddrBase + FPGA_WR_ADDR_SHIFT_12);
        FPGA_RD_WORD(*(siBufRd + 13U), ulAddrBase + FPGA_WR_ADDR_SHIFT_13);
        FPGA_RD_WORD(*(siBufRd + 14U), ulAddrBase + FPGA_WR_ADDR_SHIFT_14);
        FPGA_RD_WORD(*(siBufRd + 15U), ulAddrBase + FPGA_WR_ADDR_SHIFT_15);
        FPGA_RD_WORD(*(siBufRd + 16U), ulAddrBase + FPGA_WR_ADDR_SHIFT_16);
        FPGA_RD_WORD(*(siBufRd + 17U), ulAddrBase + FPGA_WR_ADDR_SHIFT_17);
        FPGA_RD_WORD(*(siBufRd + 18U), ulAddrBase + FPGA_WR_ADDR_SHIFT_18);
        FPGA_RD_WORD(*(siBufRd + 19U), ulAddrBase + FPGA_WR_ADDR_SHIFT_19);

        SUM_19_BUF(l_siCodeChk, siBufRd);
        if(l_siCodeChk != *(siBufRd + FPGA_RD_CHECK_POSN))
        {
            stEmifLoc.uiCntrCellRdChkErr++;
            l_uiCodeReturn = FPGA_CHECK_ERR_CODE;
        }
#if 1U == ENA_EMIF_RD_CNTR
        else
        {
            sl_uiCntrTmp++;
            if(sl_uiCntrTmp > 20000U)
            {
                sl_uiCntrTmp = 0U;
                stEmifLoc.uiCntrCellRdRx++;
            }
        }
#endif
    }
    else
    {
        stEmifLoc.uiCntrCellRdHeadErr++;
        l_uiCodeReturn = FPGA_HEAD_ERR_CODE;
    }

    return l_uiCodeReturn;
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : EMIF FPGA fast parameter check function
* @Signal [in]  : null
* @Signal [out] : Error code
* @return       : null
***********************************************************************************************/
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(ui_Emif_Fpga_Fast_Chk, ".TI.ramfunc");
#endif
extern Uint16 ui_Emif_Fpga_Fast_Chk(int16 *siBufDma)
{
    int16  l_siCodeChk    = 0;        ///< check code
    Uint16 l_uiCodeReturn = 0U;       ///< return code
    static Uint16 sl_uiCntrTmp = 0U;

    if(FPGA_RD_HEAD != *siBufDma)
    {
        stEmifLoc.uiCntrFastRdHeadErr++;
        l_uiCodeReturn = FPGA_HEAD_ERR_CODE;
    }
    else
    {
        SUM_DMA_FPGA_BUF(l_siCodeChk, siBufDma);

        if(l_siCodeChk != *(siBufDma + SUM_DMA_FPGA_BUF_POSN))
        {
            l_uiCodeReturn = FPGA_CHECK_ERR_CODE;
            stEmifLoc.uiCntrFastRdChkErr++;
        }
#if 1U == ENA_EMIF_RD_CNTR
        else
        {
            sl_uiCntrTmp++;
            if(sl_uiCntrTmp > 20000U)
            {
                sl_uiCntrTmp = 0U;
                stEmifLoc.uiCntrFastRdRx++;
            }
        }
#endif
    }

    return l_uiCodeReturn;
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : EMIF FPGA cell parameter read function
* @Signal [in]  : null
* @Signal [out] : Error code
* @return       : null
***********************************************************************************************/
#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_Emif_Fpga_Cell_Prm_Rd, ".TI.ramfunc");
#endif
static void v_Emif_Fpga_Cell_Prm_Rd(void)
{
    int16 *pPrmBuf;

    /* Read parameter */
    stEmifLoc.uiCodeChkCellRd = ui_Emif_Fpga_Rd(&stEmifLoc.siPrmCellRd[0], stEmifLoc.ulAddrCellRd[stEmifLoc.uiFlgCellRd]);

    /* Copy parameter to destination */
    if(FPGA_NO_ERR_CODE == stEmifLoc.uiCodeChkCellRd)
    {
        switch(stEmifLoc.ulAddrCellRd[stEmifLoc.uiFlgCellRd])
        {
            case FPGA_RD_CHB_FLT_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siFltChbCell;
                break;
            case FPGA_RD_CHB_VOLT_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siVoltChbCell;
                break;
            case FPGA_RD_DAB_CURR_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siCurrDabCell;
                break;
            case FPGA_RD_FPGA_VER_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siVerFpgaCell;
                break;
            case FPGA_RD_DAB_FLT_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siFltDabCell;
                break;
            case FPGA_RD_RES_CURR_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siResCurCell;
                break;
            case FPGA_RD_DAB_VOLT_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siVoltDabCell;
                break;
            case FPGA_RD_HV_TEMP1_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siTemp1HvCell;
                break;
            case FPGA_RD_HV_TEMP2_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siTemp2HvCell;
                break;
            case FPGA_RD_LV_TEMP1_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siTemp1LvCell;
                break;
            case FPGA_RD_LV_TEMP2_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siTemp2LvCell;
                break;
            case FPGA_RD_FIBER_ERR_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siErrFiberCell;
                break;
            case FPGA_RD_HV_UP_FERR_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siErrHvUpFiberCell;
                break;
            case FPGA_RD_HV_DOWN_FERR_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siErrHvDownFiberCell;
                break;
            case FPGA_RD_LV_FIBER_ERR_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siErrLvFiberCell;
                break;
            case FPGA_RD_FAN_STATE_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siStateFanCell;
                break;
            case FPGA_RD_HV_TEMP3_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siTemp3HvCell;
                break;
            case FPGA_RD_HV_TEMP4_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siTemp4HvCell;
                break;
            case FPGA_RD_HV_TEMP5_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siTemp5HvCell;
                break;
            case FPGA_RD_LV_TEMP3_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siTemp3LvCell;
                break;
            case FPGA_RD_LV_TEMP4_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siTemp4LvCell;
                break;
            case FPGA_RD_MO_RF_VAL_BASE_ADDR:
                pPrmBuf = (int16 *)stEmif.siRfValCell;
                break;

            default:
              //  pPrmBuf = (int16 *)stEmif.siVerFpgaCell;
                ///< Do nothing
                break;

        }
        memcpy(pPrmBuf, &stEmifLoc.siPrmCellRd[1], NUM_EMIF_SUM_POW_CELL);

        /* Cell parameter read address update */
        if(stEmifLoc.uiFlgCellRd >= 3U)
        {
            stEmifLoc.uiFlgCellRd = 0U;

            stEmifLoc.ulAddrCellRd[3] += FPGA_CELL_ADDR_DELTA;
            if(stEmifLoc.ulAddrCellRd[3] > FPGA_RD_MO_RF_VAL_BASE_ADDR)
            {
                stEmifLoc.ulAddrCellRd[3] = FPGA_RD_FPGA_VER_BASE_ADDR;
            }
        }
        else
        {
            stEmifLoc.uiFlgCellRd++;
        }
    }
}


#if(0U == FLG_SWUT_EN)
#pragma CODE_SECTION(v_Emif_Fpga_Polldata_Rd, ".TI.ramfunc");
#endif
static void v_Emif_Fpga_Polldata_Rd(void)
{
    switch(stEmifDma1.uiPollAddr)
    {
        case 1:
            stEmifDmaPollData.siFpgaVersion1 = stEmifDma1.siPollData;
            break;
        case 2:
            stEmifDmaPollData.siFpgaVersion2 = stEmifDma1.siPollData;
            break;
        case 3:
            stEmifDmaPollData.siFpgaVersion3 = stEmifDma1.siPollData;
            break;
        default:
            break;
    }
}
//==============================================================================================
// End of file.
//==============================================================================================
