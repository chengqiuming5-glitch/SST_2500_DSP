//==============================================================================================
//    File description
//==============================================================================================
/**@file         SpiCfg.c
* TITLE         : Spi configuration Source File
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2023.11.10
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
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//=====================================================
//    Include Header Files
//=====================================================
#include "SpiCfg.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================
/***********************************************************************************************
* @Type         : Module function
* @brief        :
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_SpiCfg_Init(void)
{
    // Initialize SPI FIFO registers
    SPIX_REG.SPICCR.bit.SPISWRESET   = 0U;         ///< Soft reset SPI
    SPIX_REG.SPICCR.bit.SPICHAR      = 0x7U;       ///< Data length:8-bit
    SPIX_REG.SPICCR.bit.SPILBK       = 0U;         ///< Loop-back disable
    SPIX_REG.SPICCR.bit.CLKPOLARITY  = 0U;
    SPIX_REG.SPICTL.bit.SPIINTENA    = 0U;         ///< Disable interrupt
    SPIX_REG.SPICTL.bit.TALK         = 1U;         ///< Transmit Enable
    SPIX_REG.SPICTL.bit.MASTER_SLAVE = 1U;         ///< Master Mode
    SPIX_REG.SPICTL.bit.CLK_PHASE    = 1U;
    SPIX_REG.SPIBRR.all              = 0x0031U;    ///< SPI Baud Rate:(50M/50) = 1MHz bit/s 0x0031
    SPIX_REG.SPIFFTX.bit.TXFFIENA    = 0U;
    SPIX_REG.SPIFFTX.bit.TXFFINTCLR  = 1U;
    SPIX_REG.SPIFFTX.bit.TXFIFO      = 0U;
    SPIX_REG.SPIFFTX.bit.SPIFFENA    = 1U;         ///< Enable FIFO
    SPIX_REG.SPIFFTX.bit.SPIRST      = 1U;
    SPIX_REG.SPIFFRX.bit.RXFFIENA    = 0U;
    SPIX_REG.SPIFFRX.bit.RXFFINTCLR  = 1U;
    SPIX_REG.SPIFFRX.bit.RXFIFORESET = 0U;
    SPIX_REG.SPIFFRX.bit.RXFFINTCLR  = 1U;
    SPIX_REG.SPISTS.all              = 0x0000U;
    SPIX_REG.SPIFFCT.all             = 0x00U;
    SPIX_REG.SPIFFCT.bit.TXDLY       = 0U;

    SPIX_REG.SPIPRI.bit.FREE         = 1U;
    SPIX_REG.SPIFFTX.bit.TXFIFO      = 1U;
    SPIX_REG.SPIFFRX.bit.RXFIFORESET = 1U;

    SPIX_REG.SPICCR.bit.SPISWRESET   = 1U;         ///< Reset SPI
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
