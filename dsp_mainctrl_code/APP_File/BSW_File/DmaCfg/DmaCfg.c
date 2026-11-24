//==============================================================================================
//    File description
//==============================================================================================
/**@file         DmaCfg.c
* TITLE         : DMA configuration function
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2025.11.26
* Version       : V1.0
* Descriptions  :
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Modified by   :
* Modified date :
* Version       :
* Descriptions  :
************************************************************************************************
*/

/*
************************************************************************************************
* Module        :
* 1st Unit      :
* 2nd Unit      :
* 3rd Unit      :
*
* Module Task   :

*
* 1st Unit Task :
*
* 2nd Unit Task :
*
* 3rd Unit Task :
*
************************************************************************************************
*/

//=====================================================
//    Include Header Files
//=====================================================
#include "DmaCfg.h"
#include "EmifExt.h"

//=====================================================
//    Variable Definition
//=====================================================


//=====================================================
//    Function definition
//=====================================================
/***********************************************************************************************
* @Type         : Module function
* @brief        : DMA Initial function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_DmaCfg_Init(void)
{
    /* Initializes the DMA to a known state */
    DMAInitialize();

    /* DMA1 source and destination address configuration */
    DMACH1AddrConfig(DMA_FPGA_DST_ADDR, DMA_FPGA_SRC_ADDR);

    /* DMA Channel 1 Burst configuration */
    DMACH1BurstConfig(DMA_FPGA_BURST_SIZE - 1U, DMA_FPGA_SRC_BURST_STEP, DMA_FPGA_DST_BURST_STEP);

    /* DMA Channel 1 Transfer configuration */
    DMACH1TransferConfig(DMA_FPGA_TRANSFER_SIZE - 1U, DMA_FPGA_SRC_TRANSFER_STEP, DMA_FPGA_DST_TRANSFER_STEP);

    DMACH1WrapConfig(0xFFFF, 0, 0xFFFF, 0);

    /* DMA Channel 1 Mode configuration */
    // 0U              : No peripheral trigger source
    // PERINT_ENABLE   : Peripheral or software can start a DMA burst
    // ONESHOT_DISABLE : Only performs one burst per trigger
    // CONT_ENABLE     : The channel re-initializes when TRANSFER_COUNT is zero and waits for the next event trigger
    // OVRFLOW_DISABLE : Overflow interrupt disabled
    // SIXTEEN_BIT     : 16-bit data size transfers
    // CHINT_END       : Generate interrupt to CPU at end of transfer
    // CHINT_ENABLE    : Interrupt enabled
    DMACH1ModeConfig(0U, PERINT_ENABLE, ONESHOT_ENABLE, CONT_ENABLE, SYNC_DISABLE, SYNC_SRC, \
                     OVRFLOW_DISABLE, SIXTEEN_BIT, CHINT_END, CHINT_ENABLE);

    /* Start DMA Channel 1 */
    StartDMACH1();

#if 1U == ENA_DMA2_FPGA
    /* DMA2 source and destination address configuration */
    DMACH2AddrConfig(DMA2_FPGA_DST_ADDR, DMA2_FPGA_SRC_ADDR);

    /* DMA Channel 2 Burst configuration */
    DMACH2BurstConfig(DMA_FPGA_BURST_SIZE - 1U, DMA_FPGA_SRC_BURST_STEP, DMA_FPGA_DST_BURST_STEP);

    /* DMA Channel 2 Transfer configuration */
    DMACH2TransferConfig(DMA_FPGA_TRANSFER_SIZE -1U, DMA_FPGA_SRC_TRANSFER_STEP, DMA_FPGA_DST_TRANSFER_STEP);

    DMACH2WrapConfig(0xFFFF, 0, 0xFFFF, 0);
    /* DMA Channel 2 Mode configuration */
    // 0U              : No peripheral trigger source
    // PERINT_ENABLE   : Peripheral or software can start a DMA burst
    // ONESHOT_DISABLE : Only performs one burst per trigger
    // CONT_ENABLE     : The channel re-initializes when TRANSFER_COUNT is zero and waits for the next event trigger
    // OVRFLOW_DISABLE : Overflow interrupt disabled
    // SIXTEEN_BIT     : 16-bit data size transfers
    // CHINT_END       : Generate interrupt to CPU at end of transfer
    // CHINT_ENABLE    : Interrupt enabled
    DMACH2ModeConfig(0U, PERINT_ENABLE, ONESHOT_ENABLE, CONT_ENABLE, SYNC_DISABLE, SYNC_SRC, \
                     OVRFLOW_DISABLE, SIXTEEN_BIT, CHINT_END, CHINT_ENABLE);

    /* Start DMA Channel 2 */
    StartDMACH2();
#endif
}

//===========================================================================
// End of file.
//===========================================================================
