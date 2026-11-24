//==============================================================================================
//    File description
//==============================================================================================
/**@file         Cla_Cfg.c
* TITLE         : Cla configuration Source File
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
#include "ClaCfg.h"

//=====================================================
//    Variable Definition
//=====================================================


//=====================================================
//    Function definition
//=====================================================
/**
* @brief   CLA Initial function
* @param [in]  null
* @param [out] null
* @return null
*/
void v_ClaCfg_Init(void)
{
    v_ClaCfg_Mem_Init();       ///< Configuration CLA Memory
    v_ClaCfg_Cpu1_Init();      ///< CLA1 task vectors Initialize
}

/**
* @brief   Configuration CLA Memory function
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_ClaCfg_Mem_Init(void)
{
    extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
    EALLOW;

#ifdef _FLASH
    //
    // Copy over code from FLASH to RAM
    //
    (void)memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
           (uint32_t)&Cla1funcsLoadSize);
#endif //_FLASH

    //
    // Initialize and wait for CLA1ToCPUMsgRAM
    //
    MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1U;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1U)
    {
        // No Code
    };

    //
    // Initialize and wait for CPUToCLA1MsgRAM
    //
    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1U;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1U)
    {
        // No Code
    };

    //
    // Select LS1RAM ~ LS5RAM to be the programming space for the CLA
    // First configure the CLA to be the master for LS2 ~ LS5 and then
    // set the space to be a program block
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 1U;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS2 = 1U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS2 = 1U;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS3 = 1U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS3 = 1U;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS4 = 1U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS4 = 1U;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 1U;

    //
    // Next configure LS0RAM as data spaces for the CLA
    // First configure the CLA to be the master for LS0(1) and then
    // set the spaces to be code blocks
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 0U;

    EDIS;
}

/**
* @brief   Initialize CLA1 task vectors
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_ClaCfg_Cpu1_Init(void)
{
    //
    // Compute all CLA task vectors
    // On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
    // opposed to offsets used on older Type-0 CLAs
    //
    EALLOW;
    //Cla1Regs.MVECT1 = (Uint16)(&vD2dPowCtrlClaTask1);
#if 3U == GRID_PHASE_NUMBER
    //Cla1Regs.MVECT2 = (Uint16)(&vD2dPowCtrlClaTask2);
#endif
    //Cla1Regs.MVECT7 = (Uint16)(&vD2dPowCtrlClaTask7);


    //set the triggers
    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK1 = CLA_TRIG_ADCAINT1;     // ADCA1_INT
    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK2 = CLA_TRIG_NOPERPH;     // Software_Trigger
    DmaClaSrcSelRegs.CLA1TASKSRCSEL2.bit.TASK7 = CLA_TRIG_NOPERPH;     // Software_Trigger

    // Enable software forcing (IACKE)
    Cla1Regs.MCTL.bit.IACKE = 1U;

    // Enable tasks (or a subset of tasks) by writing to their respective bits in the MIER register
    Cla1Regs.MIER.bit.INT1 = 1U;
    Cla1Regs.MIER.bit.INT2 = 1U;
    Cla1Regs.MIER.bit.INT7 = 1U;

    EDIS;
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
