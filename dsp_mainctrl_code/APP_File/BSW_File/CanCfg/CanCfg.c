//==============================================================================================
//    File description
//==============================================================================================
/**@file         CanCfg.c
* TITLE         : Can configuration Source File
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
#include "CanCfg.h"

//=====================================================
//    Variable Definition
//=====================================================

//=====================================================
//    Function definition
//=====================================================

/***********************************************************************************************
* @Type         : Module function
* @brief        : CAN Initialization function
* @Signal [in]  : null
* @Signal [out] : null
* @return       : null
***********************************************************************************************/
void v_CanCfg_Init(void)
{
    /* Initializes the CAN controller Module */
    v_CanCfg_InitMod();

    /* Set CAN Clock Frequency */
    v_CanCfg_SetBitTiming(SYS_CLK_FRQ, CAN_CLK_FRQ, 20U);    // Sets the CAN Bit Timing

    /* Set Mailbox 15 as Receiver Object*/
    v_CanCfg_SetupMsgObj(CAN_RX_BOX, CAN_RX_ID, CAN_MSG_FRAME_EXT, \
                            CAN_MSG_OBJ_TYPE_RX, 0x1F000000UL, CAN_MSG_OBJ_FLAGS, \
                            MSG_DATA_LENGTH);
    /* Set Mailbox 1 as Transmitter Object*/
    v_CanCfg_SetupMsgObj(CAN_TX_BOX, CAN_TX_ID, CAN_MSG_FRAME_EXT, \
                                CAN_MSG_OBJ_TYPE_TX, 0UL, CAN_MSG_OBJ_NO_FLAGS, \
                                MSG_DATA_LENGTH);

    /* Starts the CAN Module's Operations */
    v_CanCfg_StartMod();
}


/**
* @brief   Initializes the CAN controller module
*          This function initializes the message RAM, which also clears all the
*          message objects, and places the CAN controller in an initial state.
*          Write access to the configuration registers is available as a result,
*          allowing the bit timing and message objects to be setup.
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_CanCfg_InitMod(void)
{
    // Place CAN controller in initial state, regardless of previous state. This
    // will put controller in idle, and allow the message object RAM to be
    // programmed.

    /* Set Initialization Mode; Disable Parity function; Disable Interrupt */
    CANX_REGS.CAN_CTL.all = 0x1401U;

    /* Initialize the message RAM before using it */
    CANX_REGS.CAN_RAM_INIT.all = 0x1AU;

    while(!(0x25U == (CANX_REGS.CAN_RAM_INIT.all & 0x003FU)))
    {
        // Wait until RAM Initialization is complete
    }

    /* Force module to reset state */
    CANX_REGS.CAN_CTL.all |=  0x8000U;
#if 0U == FLG_SWUT_EN
    DELAY_US(1.0f);    // Delay 1us
#endif
    /* Configuration Change Enable */
    CANX_REGS.CAN_CTL.all |= 0x0040U;
}

/**
* @brief   Sets the CAN Bit Timing based on requested Bit Rate
* @param [in]  param ulClock is the CAN module clock frequency before the bit rate prescaler (Hertz);
*              param ulBitRate is the desired bit rate (bits/sec);
*              param uiBitTime is the number of time quanta per bit required for desired
               bit time (Tq) and must be in the range from 8 to 25.
* @param [out] null
* @return null
*/
static void v_CanCfg_SetBitTiming(Uint32 ulClock, Uint32 ulBitRate, Uint16 uiBitTime)
{
    Uint16 l_uiBrp = 1U;
    Uint16 l_uiTPhase = 1U;
    Uint16 l_uiPhaseSeg = 1U;
    Uint16 l_uiTSync = 1U;
    Uint16 l_uiTProp = 2U;
    Uint16 l_uiTSeg1 = 0U;
    Uint16 l_uiTSeg2 = 0U;
    Uint16 l_uiSjw = 1U;
    Uint16 l_uiPrescaler = 1U;
    Uint16 l_uiPrescalerExtension = 1U;
    Uint32 l_ulBitReg = 1U;

    /* Calculate bit timing values */
    l_uiBrp = (Uint16)(ulClock / (ulBitRate * uiBitTime));
    l_uiTPhase = uiBitTime - (l_uiTSync + l_uiTProp);
    if((l_uiTPhase / 2U) <= 8U)
    {
        l_uiPhaseSeg = l_uiTPhase / 2U;
    }
    else
    {
        l_uiPhaseSeg = 8U;
    }
    l_uiTSeg1 = ((l_uiTPhase - l_uiPhaseSeg) + l_uiTProp) - 1U;
    l_uiTSeg2 = l_uiPhaseSeg - 1U;
    if(l_uiPhaseSeg > 4U)
    {
        l_uiSjw = 3U;
    }
    else
    {
        l_uiSjw = l_uiTSeg2;
    }
    l_uiPrescalerExtension = ((l_uiBrp - 1U) / 64U);
    l_uiPrescaler = ((l_uiBrp - 1U) % 64U);

    //
    // To set the bit timing register, the controller must be placed in init
    // mode (if not already), and also configuration change bit enabled.
    // State of the init bit should be saved so it can be restored at the end.
    //
    CANX_REGS.CAN_CTL.bit.Init = 1U;    // Initialization Mode
    CANX_REGS.CAN_CTL.bit.CCE = 1U;     // Configuration Change Enable

    /* Set the bit fields of the bit timing register */
    l_ulBitReg = (Uint32)((Uint32)l_uiPrescaler & 0x3FU);
    l_ulBitReg |= (Uint32)(((Uint32)l_uiSjw << 6U) & 0xC0U);
    l_ulBitReg |= (Uint32)(((Uint32)l_uiTSeg1 << 8U) & 0xF00U);
    l_ulBitReg |= (Uint32)(((Uint32)l_uiTSeg2 << 12U) & 0x7000U);
    l_ulBitReg |= (Uint32)(((Uint32)l_uiPrescalerExtension << 16U) & 0xF0000U);
    CANX_REGS.CAN_BTR.all = l_ulBitReg;

    CANX_REGS.CAN_CTL.bit.CCE = 0U;     // The CPU has no write access to the configuration registers
    CANX_REGS.CAN_CTL.bit.Init = 0U;    // CAN module processes messages normally

}

/**
* @brief   Setup a Message Object
* @param [in]  param uiObjID is the message object number to configure (1-32);
*              param ulMsgID is the CAN message identifier used for the 11 or 29 bit identifiers;
*              param enFrame is the CAN ID frame type;
*              param enMsgType is the message object type;
*              param ulMsgIDMask is the CAN message identifier mask used when identifier filtering is enabled;
*              param ulFlags is the various flags and settings to be set for the message object;
*              param uiMsgLen is the number of bytes of data in the message object (0-8).
* @param [out] null
* @return null
*/
void v_CanCfg_SetupMsgObj(Uint16 uiObjID, Uint32 ulMsgID, EN_CAN_MsgFrameType enFrame, \
                                    EN_CAN_MsgObjType enMsgType, Uint32 ulMsgIDMask, Uint32 ulFlags, \
                                    Uint16 uiMsgLen)
{
    Uint32 l_ulCmdMaskReg = 0U;
    Uint32 l_ulMaskReg = 0U;
    Uint32 l_ulArbReg = 0U;
    Uint32 l_ulMsgCtrl = 0U;

    /* Wait for busy bit to clear */
    while(1U == CANX_REGS.CAN_IF1CMD.bit.Busy)
    {
    }

    switch(enMsgType)
    {
        /* Transmit message object */
        case CAN_MSG_OBJ_TYPE_TX:
            l_ulArbReg = 0x20000000UL;             // Set message direction to transmit.
            break;

        /* Remote frame receive remote, with auto-transmit message object */
        case CAN_MSG_OBJ_TYPE_RXTX_REMOTE:
            l_ulArbReg = 0x20000000UL;             // Set message direction to Tx for remote receivers.
            l_ulMsgCtrl = (0x200UL | 0x1000UL);    // Set this object to auto answer if a matching identifier is seen.
            break;

        /* Transmit remote request message object (CAN_MSG_OBJ_TYPE_TX_REMOTE)
         * or Receive message object (CAN_MSG_OBJ_TYPE_RX) */
        default:
            l_ulArbReg = 0UL;    // Set message direction to read.
            break;
    }

    /* Set values based on Extended Frame or Standard Frame */
    if(CAN_MSG_FRAME_EXT == enFrame)
    {
        /* Configure the Mask Registers for 29 bit Identifier mask */
        if((ulFlags & 0x00000001UL) == 0x00000001UL)
        {
            l_ulMaskReg = ulMsgIDMask & 0x1FFFFFFFUL;
        }

        /* Set the 29 bit version of the Identifier for this message
         * object. Mark the message as valid and set the extended ID bit */
        l_ulArbReg |= (ulMsgID & 0x1FFFFFFFUL) | 0x80000000UL | 0x40000000UL;
    }
    else
    {
        /* Configure the Mask Registers for 11 bit Identifier mask */
        if((ulFlags & 0x00000001UL) == 0x00000001UL)
        {
            l_ulMaskReg = ((ulMsgIDMask << 18U) & 0x1FFC0000UL);
        }

        /* Set the 11 bit version of the Identifier for this message object.
         * The lower 18 bits are set to zero. Mark the message as valid */
        l_ulArbReg |= ((ulMsgID << 18U) & 0x1FFC0000UL) | 0x80000000UL;
    }

    /* If the caller wants to filter on the extended ID bit then set it */
    l_ulMaskReg |= (ulFlags & 0x80000000UL);

    /* The caller wants to filter on the message direction field */
    l_ulMaskReg |= (ulFlags & 0x40000000UL);

    /* If any filtering is requested, set the UMASK bit to use mask register */
    if(0U != ((ulFlags & 0x00000001UL) | (ulFlags & 0x40000000UL) | (ulFlags & 0x80000000UL)))
    {
        l_ulMsgCtrl |= 0x1000UL;
    }

    /* Set the data length for the transfers; This is applicable for Tx mailboxes. */
    if((CAN_MSG_OBJ_TYPE_TX == enMsgType) || (CAN_MSG_OBJ_TYPE_RXTX_REMOTE == enMsgType))
    {
        l_ulMsgCtrl |= ((Uint32)uiMsgLen & 0x0FUL);
    }

    /* If this is a single transfer or the last mailbox of a FIFO, set EOB bit.
     * If this is not the last entry in a FIFO, leave the EOB bit as 0 */
    if(0UL == (ulFlags & 0x00000002UL))
    {
        l_ulMsgCtrl |= 0x80UL;
    }

    /* Enable transmit interrupts if they should be enabled */
    l_ulMsgCtrl |= (ulFlags & 0x800UL);

    /* Enable receive interrupts if they should be enabled */
    l_ulMsgCtrl |= (ulFlags & 0x400UL);

    /* Set the Control, Arb, and Mask bit so that they get transferred to the Message object */
    l_ulCmdMaskReg |= 0x200000UL;
    l_ulCmdMaskReg |= 0x100000UL;
    l_ulCmdMaskReg |= 0x400000UL;
    l_ulCmdMaskReg |= 0x800000UL;

    /* Write out the registers to program the message object */
    CANX_REGS.CAN_IF1MSK.all = l_ulMaskReg;
    CANX_REGS.CAN_IF1ARB.all = l_ulArbReg;
    CANX_REGS.CAN_IF1MCTL.all = l_ulMsgCtrl;
#if 0U == FLG_SWUT_EN
    DELAY_US(50L);    // Delay for 50us
#endif
    /* Transfer data to message object RAM */
    CANX_REGS.CAN_IF1CMD.all = l_ulCmdMaskReg | (uiObjID & 0xFFUL);
}

/**
* @brief   Starts the CAN Module's Operations
*          This function starts the CAN module's operations after initialization,
*          which includes the CAN protocol controller state machine of the CAN core
*          and the message handler state machine to begin controlling the CAN's
*          internal data flow.
* @param [in]  null
* @param [out] null
* @return null
*/
static void v_CanCfg_StartMod(void)
{
    /* Clear Init and CCE bits */
    CANX_REGS.CAN_CTL.bit.Init = 0;    // CAN module processes messages normally
    CANX_REGS.CAN_CTL.bit.CCE = 0;     // The CPU has no write access to the configuration registers
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
