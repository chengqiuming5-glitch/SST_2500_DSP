//==============================================================================================
//    File description
//==============================================================================================
/**@file         EmifCfg.c
* TITLE         : EMIF configuration function
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2025.11.25
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
#include "EmifCfg.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================
/***********************************************************************************************
* @Type         : Module function
* @brief        : EMIF Initial function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_EmifCfg_Init(void)
{
    EALLOW;

#if 0
    Emif1Regs.ASYNC_CS3_CR.bit.SS       = 0U;       ///< Select Strobe mode: Disable(Normal mode)
    Emif1Regs.ASYNC_CS3_CR.bit.EW       = 0U;       ///< Extend Wait mode: Disable
    Emif1Regs.ASYNC_CS3_CR.bit.R_HOLD   = 0U;       ///< Read Hold cycles: 1 EMIF Clock
    Emif1Regs.ASYNC_CS3_CR.bit.R_STROBE = 0x4U;     ///< Read Strobe cycles: 5 EMIF Clock
    Emif1Regs.ASYNC_CS3_CR.bit.R_SETUP  = 0x0U;     ///< Read Setup cycles: 1 EMIF Clock
    Emif1Regs.ASYNC_CS3_CR.bit.W_HOLD   = 0x0U;     ///< Write Hold cycles: 1 EMIF Clock
    Emif1Regs.ASYNC_CS3_CR.bit.W_STROBE = 0x1U;     ///< Write Strobe cycles: 2 EMIF Clock
    Emif1Regs.ASYNC_CS3_CR.bit.W_SETUP  = 0x0U;     ///< Write Setup cycles: 1 EMIF Clock
    Emif1Regs.ASYNC_CS3_CR.bit.TA       = 0x1U;     ///< Turn Around cycles: 2 EMIF Clock
    Emif1Regs.ASYNC_CS3_CR.bit.ASIZE    = 0x1U;     ///< Asynchronous Memory Size: 16Bit Memory Interface
#else
    Emif1Regs.ASYNC_CS3_CR.all =  ( EMIF_ASYNC_ASIZE_16    |  // 16Bit Memory Interface
                                    EMIF_ASYNC_TA_2        |  // Turn Around time of 2 Emif Clock
                                    EMIF_ASYNC_RHOLD_1     |  // Read Hold time of 1 Emif Clock
                                    EMIF_ASYNC_RSTROBE_6   |  // Read Strobe time of 5 Emif Clock
                                    EMIF_ASYNC_RSETUP_1    |  // Read Setup time of 1 Emif Clock
                                    EMIF_ASYNC_WHOLD_1     |  // Write Hold time of 1 Emif Clock
                                    EMIF_ASYNC_WSTROBE_2   |  // Write Strobe time of 2 Emif Clock
                                    EMIF_ASYNC_WSETUP_1    |  // Write Setup time of 1 Emif Clock
                                    EMIF_ASYNC_EW_DISABLE  |  // Extended Wait Disable.
                                    EMIF_ASYNC_SS_DISABLE     // Strobe Select Mode Disable.
                                  );
#endif

    Emif1ConfigRegs.EMIF1MSEL.all                = 0x93A5CE71UL;    ///< CPU1 is master
    Emif1ConfigRegs.EMIF1ACCPROT0.all            = 0x0UL;           ///< CPU write & fetch are allowed
    Emif1ConfigRegs.EMIF1COMMIT.bit.COMMIT_EMIF1 = 0x1U;            ///< Write to ACCPROT and Mselect fields are permanently blocked
    Emif1ConfigRegs.EMIF1LOCK.bit.LOCK_EMIF1     = 0x1U;            ///< Write to ACCPROT and Mselect fields are blocked

    EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
