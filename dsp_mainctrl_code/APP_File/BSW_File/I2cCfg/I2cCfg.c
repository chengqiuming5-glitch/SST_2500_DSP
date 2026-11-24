//==============================================================================================
//    File description
//==============================================================================================
/**@file         I2cCfg.c
* TITLE         : I2C configuration Source File
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
#include "I2cCfg.h"

//=====================================================
//    Variable Definition
//=====================================================


//=====================================================
//    Function definition
//=====================================================
/**
* @brief   I2C initialization function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_I2cCfg_Init(void)
{
    // Initialize I2C-A:
    //I2caRegs.I2CMDR.bit.IRS = 0;
    I2caRegs.I2CIER.all = 0x0000U;// Disable All interrupts
    I2caRegs.I2CSTR.all = 0xFFFFU;// Write 1 to Clear all Bits
    I2caRegs.I2CSAR.bit.SAR = 0x50U;        ///< Slave address - EEPROM control code

#if (CPU_FRQ_200MHZ)                 // Default - For 150MHz SYSCLKOUT
    I2caRegs.I2CPSC.all = 19U;        ///< 19  Prescaler - need 7-12 Mhz on module clk (200/20 = 10MHz)
#endif
#if (CPU_FRQ_150MHZ)                 // Default - For 150MHz SYSCLKOUT
    I2caRegs.I2CPSC.all = 14U;        ///< 14  Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz)
#endif
#if (CPU_FRQ_100MHZ)                 // For 100 MHz SYSCLKOUT
    I2caRegs.I2CPSC.all = 9U;         ///< Prescaler - need 7-12 Mhz on module clk (100/10 = 10MHz)
#endif

    I2caRegs.I2CCLKL = 10U;           ///< NOTE: must be non zero
    I2caRegs.I2CCLKH = 10U;           ///< NOTE: must be non zero
    I2caRegs.I2CMDR.all = 0x0000U;   // Reset I2C

    I2caRegs.I2CFFTX.bit.TXFFRST = 0U;
    I2caRegs.I2CFFTX.bit.TXFFRST = 1U;

    I2caRegs.I2CMDR.all  = 0x0020U;    // Take I2C out of reset
                              // Stop I2C when suspended
    I2caRegs.I2CFFTX.all = 0x6000U;   ///< Enable FIFO mode and TXFIFO
    I2caRegs.I2CFFRX.all = 0x2040U;   ///< Enable RXFIFO, clear RXFFINT,

    I2caRegs.I2CCNT      = 0x0000U;
    I2caRegs.I2CSTR.all  = 0xFFFFU;

    //tbd...
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
