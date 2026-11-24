//==============================================================================================
//    File description
//==============================================================================================
/**@file         Emif.h
 * @brief
 * The header file of Emif is designed to realize Emif communication.
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
 * <tr><td>2025/11/27  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */
#ifndef EMIF_H_
#define EMIF_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "EmifExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define ENA_EMIF_RD_CNTR            0x1U

#define FPGA_NO_ERR_CODE            0x0U
#define FPGA_HEAD_ERR_CODE          0x1U
#define FPGA_CHECK_ERR_CODE         0x2U

#define FPGA_WR_CHECK_POSN          (FPGA_WR_WORD_NUM - 1U)             ///< FPGA write check code position
#define FPGA_RD_CHECK_POSN          (FPGA_RD_WORD_NUM - 1U)             ///< FPGA read check code position

#define FPGA_WR_ADDR_SHIFT_1        DMA_FPGA_SRC_BURST_STEP             ///< FPGA write 1st word address shift
#define FPGA_WR_ADDR_SHIFT_2        (DMA_FPGA_SRC_BURST_STEP * 2U)
#define FPGA_WR_ADDR_SHIFT_3        (DMA_FPGA_SRC_BURST_STEP * 3U)
#define FPGA_WR_ADDR_SHIFT_4        (DMA_FPGA_SRC_BURST_STEP * 4U)
#define FPGA_WR_ADDR_SHIFT_5        (DMA_FPGA_SRC_BURST_STEP * 5U)
#define FPGA_WR_ADDR_SHIFT_6        (DMA_FPGA_SRC_BURST_STEP * 6U)
#define FPGA_WR_ADDR_SHIFT_7        (DMA_FPGA_SRC_BURST_STEP * 7U)
#define FPGA_WR_ADDR_SHIFT_8        (DMA_FPGA_SRC_BURST_STEP * 8U)
#define FPGA_WR_ADDR_SHIFT_9        (DMA_FPGA_SRC_BURST_STEP * 9U)
#define FPGA_WR_ADDR_SHIFT_10       (DMA_FPGA_SRC_BURST_STEP * 10U)
#define FPGA_WR_ADDR_SHIFT_11       (DMA_FPGA_SRC_BURST_STEP * 11U)
#define FPGA_WR_ADDR_SHIFT_12       (DMA_FPGA_SRC_BURST_STEP * 12U)
#define FPGA_WR_ADDR_SHIFT_13       (DMA_FPGA_SRC_BURST_STEP * 13U)
#define FPGA_WR_ADDR_SHIFT_14       (DMA_FPGA_SRC_BURST_STEP * 14U)
#define FPGA_WR_ADDR_SHIFT_15       (DMA_FPGA_SRC_BURST_STEP * 15U)
#define FPGA_WR_ADDR_SHIFT_16       (DMA_FPGA_SRC_BURST_STEP * 16U)
#define FPGA_WR_ADDR_SHIFT_17       (DMA_FPGA_SRC_BURST_STEP * 17U)
#define FPGA_WR_ADDR_SHIFT_18       (DMA_FPGA_SRC_BURST_STEP * 18U)
#define FPGA_WR_ADDR_SHIFT_19       (DMA_FPGA_SRC_BURST_STEP * 19U)
#define FPGA_WR_ADDR_SHIFT_20       (DMA_FPGA_SRC_BURST_STEP * 20U)
#define FPGA_WR_ADDR_SHIFT_21       (DMA_FPGA_SRC_BURST_STEP * 21U)
#define FPGA_WR_ADDR_SHIFT_22       (DMA_FPGA_SRC_BURST_STEP * 22U)
#define FPGA_WR_ADDR_SHIFT_23       (DMA_FPGA_SRC_BURST_STEP * 23U)
#define FPGA_WR_ADDR_SHIFT_24       (DMA_FPGA_SRC_BURST_STEP * 24U)
#define FPGA_WR_ADDR_SHIFT_25       (DMA_FPGA_SRC_BURST_STEP * 25U)
#define FPGA_WR_ADDR_SHIFT_26       (DMA_FPGA_SRC_BURST_STEP * 26U)
#define FPGA_WR_ADDR_SHIFT_27       (DMA_FPGA_SRC_BURST_STEP * 27U)
#define FPGA_WR_ADDR_SHIFT_28       (DMA_FPGA_SRC_BURST_STEP * 28U)
#define FPGA_WR_ADDR_SHIFT_29       (DMA_FPGA_SRC_BURST_STEP * 29U)
#define FPGA_WR_ADDR_SHIFT_30       (DMA_FPGA_SRC_BURST_STEP * 30U)
#define FPGA_WR_ADDR_SHIFT_31       (DMA_FPGA_SRC_BURST_STEP * 31U)
#define FPGA_WR_ADDR_SHIFT_32       (DMA_FPGA_SRC_BURST_STEP * 32U)
#define FPGA_WR_ADDR_SHIFT_33       (DMA_FPGA_SRC_BURST_STEP * 33U)
#define FPGA_WR_ADDR_SHIFT_34       (DMA_FPGA_SRC_BURST_STEP * 34U)
#define FPGA_WR_ADDR_SHIFT_35       (DMA_FPGA_SRC_BURST_STEP * 35U)
#define FPGA_WR_ADDR_SHIFT_36       (DMA_FPGA_SRC_BURST_STEP * 36U)
#define FPGA_WR_ADDR_SHIFT_37       (DMA_FPGA_SRC_BURST_STEP * 37U)
#define FPGA_WR_ADDR_SHIFT_38       (DMA_FPGA_SRC_BURST_STEP * 38U)
#define FPGA_WR_ADDR_SHIFT_39       (DMA_FPGA_SRC_BURST_STEP * 39U)
#define FPGA_WR_ADDR_SHIFT_40       (DMA_FPGA_SRC_BURST_STEP * 40U)
#define FPGA_WR_ADDR_SHIFT_41       (DMA_FPGA_SRC_BURST_STEP * 41U)
#define FPGA_WR_ADDR_SHIFT_42       (DMA_FPGA_SRC_BURST_STEP * 42U)
#define FPGA_WR_ADDR_SHIFT_43       (DMA_FPGA_SRC_BURST_STEP * 43U)
#define FPGA_WR_ADDR_SHIFT_44       (DMA_FPGA_SRC_BURST_STEP * 44U)
#define FPGA_WR_ADDR_SHIFT_45       (DMA_FPGA_SRC_BURST_STEP * 45U)
#define FPGA_WR_ADDR_SHIFT_46       (DMA_FPGA_SRC_BURST_STEP * 46U)
#define FPGA_WR_ADDR_SHIFT_47       (DMA_FPGA_SRC_BURST_STEP * 47U)
#define FPGA_WR_ADDR_SHIFT_48       (DMA_FPGA_SRC_BURST_STEP * 48U)
#define FPGA_WR_ADDR_SHIFT_49       (DMA_FPGA_SRC_BURST_STEP * 49U)
#define FPGA_WR_ADDR_SHIFT_50       (DMA_FPGA_SRC_BURST_STEP * 50U)
#define FPGA_WR_ADDR_SHIFT_51       (DMA_FPGA_SRC_BURST_STEP * 51U)
#define FPGA_WR_ADDR_SHIFT_52       (DMA_FPGA_SRC_BURST_STEP * 52U)
#define FPGA_WR_ADDR_SHIFT_53       (DMA_FPGA_SRC_BURST_STEP * 53U)
#define FPGA_WR_ADDR_SHIFT_54       (DMA_FPGA_SRC_BURST_STEP * 54U)
#define FPGA_WR_ADDR_SHIFT_55       (DMA_FPGA_SRC_BURST_STEP * 55U)
#define FPGA_WR_ADDR_SHIFT_56       (DMA_FPGA_SRC_BURST_STEP * 56U)
#define FPGA_WR_ADDR_SHIFT_57       (DMA_FPGA_SRC_BURST_STEP * 57U)
#define FPGA_WR_ADDR_SHIFT_58       (DMA_FPGA_SRC_BURST_STEP * 58U)
#define FPGA_WR_ADDR_SHIFT_59       (DMA_FPGA_SRC_BURST_STEP * 59U)

#define FPGA_WR_WORD(addr, word)    (*(int16 *)(addr) = (word))
#define FPGA_RD_WORD(word, addr)    ((word) = *(int16 *)(addr))

#define SUM_19_BUF(sum, buf)        sum = buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7] + buf[8] + buf[9] \
                                        + buf[10] + buf[11] + buf[12] + buf[13] + buf[14] + buf[15] + buf[16] + buf[17] + buf[18];

#define SUM_31_BUF(sum, buf)        sum = buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7] + buf[8] + buf[9] \
                                        + buf[10] + buf[11] + buf[12] + buf[13] + buf[14] + buf[15] + buf[16] + buf[17] + buf[18] + buf[19] \
                                        + buf[20] + buf[21] + buf[22] + buf[23] + buf[24] + buf[25] + buf[26] + buf[27] + buf[28] + buf[29] \
                                        + buf[30];

#define SUM_37_BUF(sum, buf)        sum = buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7] + buf[8] + buf[9] \
                                        + buf[10] + buf[11] + buf[12] + buf[13] + buf[14] + buf[15] + buf[16] + buf[17] + buf[18] + buf[19] \
                                        + buf[20] + buf[21] + buf[22] + buf[23] + buf[24] + buf[25] + buf[26] + buf[27] + buf[28] + buf[29] \
                                        + buf[30] + buf[31] + buf[32] + buf[33] + buf[34] + buf[35] + buf[36];

#define SUM_59_BUF(sum, buf)        sum = buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7] + buf[8] + buf[9] \
                                        + buf[10] + buf[11] + buf[12] + buf[13] + buf[14] + buf[15] + buf[16] + buf[17] + buf[18] + buf[19] \
                                        + buf[20] + buf[21] + buf[22] + buf[23] + buf[24] + buf[25] + buf[26] + buf[27] + buf[28] + buf[29] \
                                        + buf[30] + buf[31] + buf[32] + buf[33] + buf[34] + buf[35] + buf[36] + buf[37] + buf[38] + buf[39] \
                                        + buf[40] + buf[41] + buf[42] + buf[43] + buf[44] + buf[45] + buf[46] + buf[47] + buf[48] + buf[49] \
                                        + buf[50] + buf[51] + buf[52] + buf[53] + buf[54] + buf[55] + buf[56] + buf[57] + buf[58];

#define SUM_63_BUF(sum, buf)        sum = buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7] + buf[8] + buf[9] \
                                        + buf[10] + buf[11] + buf[12] + buf[13] + buf[14] + buf[15] + buf[16] + buf[17] + buf[18] + buf[19] \
                                        + buf[20] + buf[21] + buf[22] + buf[23] + buf[24] + buf[25] + buf[26] + buf[27] + buf[28] + buf[29] \
                                        + buf[30] + buf[31] + buf[32] + buf[33] + buf[34] + buf[35] + buf[36] + buf[37] + buf[38] + buf[39] \
                                        + buf[40] + buf[41] + buf[42] + buf[43] + buf[44] + buf[45] + buf[46] + buf[47] + buf[48] + buf[49] \
                                        + buf[50] + buf[51] + buf[52] + buf[53] + buf[54] + buf[55] + buf[56] + buf[57] + buf[58] + buf[59] \
                                        + buf[60] + buf[61] + buf[62];

#define SUM_DMA_FPGA_BUF_POSN         (DMA_FPGA_WORD_NUM - 1U)
#if 1U == DMA_FPGA_TRANSFER_SIZE
#define SUM_DMA_FPGA_BUF(sum, buf)    SUM_31_BUF(sum, buf)
#elif 2U == DMA_FPGA_TRANSFER_SIZE
#define SUM_DMA_FPGA_BUF(sum, buf)    SUM_63_BUF(sum, buf)
#endif

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16 uiCodeChkFastRd;
    Uint16 uiCntrFastRdHeadErr;
    Uint16 uiCntrFastRdChkErr;
    Uint16 uiCntrFastRdRx;
    Uint16 uiCodeChkCellRd;
    Uint16 uiCntrCellRdHeadErr;
    Uint16 uiCntrCellRdChkErr;
    Uint16 uiCntrCellRdRx;
    int16  siPrmCellRd[FPGA_RD_WORD_NUM];
    Uint16 uiFlgCellRd;
    Uint32 ulAddrCellRd[4];
}ST_EMIF_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static Uint16 ui_Emif_Fpga_Rd(int16 *siBufRd, Uint32 ulAddrBase);
static void v_Emif_Fpga_Cell_Prm_Rd(void);
static void v_Emif_Fpga_Polldata_Rd(void);
#endif /* EMIF_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
