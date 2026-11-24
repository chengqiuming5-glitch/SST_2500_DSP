//==============================================================================================
//    File description
//==============================================================================================
/**@file         SciCfg.c
* TITLE         : SCI configuration Source File
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2025.10.25
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
#include "SciCfg.h"

//=====================================================
//    Variable Definition
//=====================================================
#if(0U == COM_MODE)

//=====================================================
//    Function definition
//=====================================================

/***********************************************************************************************
* @Type         : Module function
* @brief        : SCI Initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_SciCfg_Init(void)
{
    EALLOW;
    /* FIFO Initialization */
    SCI_REG.SCIFFTX.all = 0xE040U;          ///< 0xC040     0xE040U //0xE050U
    SCI_REG.SCIFFRX.all = 0x604FU;          ///< 0x2040U: Disable Rx Interrupt   0x2044U: Enable Rx Interrupt
    SCI_REG.SCIFFCT.all = 0x0U;
    SCI_REG.SCICCR.all  = 0x0007U;          ///< 8 char bits, idle-line mode protocol,
    SCI_REG.SCICTL1.all = 0x0003U;          ///< 0x0003: Enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    SCI_REG.SCICTL2.all = 0x0U;             ///< Disable RX and Tx Interrupt
    v_SciCfg_BaudRate_Init(SCIB_BAUD_RATE);  ///< Set up baud rate
    SCI_REG.SCIPRI.all = 0x10;              ///< Complete current receive/transmit sequence before stopping
    SCI_REG.SCICTL1.all = 0x0023U;          ///< Relinquish SCI from Reset
    EDIS;
}

/***********************************************************************************************
* @Type         : Module function
* @brief        : SCI Baud Rate Set
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
static void v_SciCfg_BaudRate_Init(Uint32 ulBaudRate)
{
    Uint16 l_uiBRR;

    ///<SCI Asynchronous Baud = LSPCLK / ((BRR + 1) *8)
    ///<BRR = LSPCLK / (SCI Asynchronous Baud * 8) - 1 = SYS_CLK_FRQ/4
    l_uiBRR                    = (Uint16)((SYS_CLK_FRQ >> 5U) / (ulBaudRate)) - 1U;
    SCI_REG.SCIHBAUD.bit.BAUD = (l_uiBRR & 0xFF00U) >> 8U;
    SCI_REG.SCILBAUD.bit.BAUD = (l_uiBRR & 0x00FFU);
}

#endif     // (0U == COM_MODE)

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)

//===========================================================================
// End of file.
//===========================================================================
