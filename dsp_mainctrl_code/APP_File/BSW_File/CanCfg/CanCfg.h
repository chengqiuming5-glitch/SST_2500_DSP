//==============================================================================================
//    File description
//==============================================================================================
/**@file         CanCfg.h
* TITLE         : Can configuration Header File
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

#ifndef CANCFG_H_
#define CANCFG_H_

//=====================================================
//    Include Header Files
//=====================================================
#include "BSW_Cfg.h"

//=====================================================
//    Macro Definition
//=====================================================
#define CAN_CLK_FRQ                  250000UL            ///< CAN Clock Frequency

#define CAN_MSG_OBJ_TX_INT_ENABLE    CAN_IF1MCTL_TXIE    // This indicates that transmit interrupts should be enabled,
                                                         // or are enabled.
#define CAN_MSG_OBJ_RX_INT_ENABLE    CAN_IF1MCTL_RXIE    // This indicates that receive interrupts should be enabled,
                                                         // or are enabled.
#define CAN_MSG_OBJ_USE_ID_FILTER    (0x00000001UL)      // This indicates that a message object will use or is using filtering
                                                         // based on the object's message identifier.
#define CAN_MSG_OBJ_USE_DIR_FILTER   CAN_IF1MSK_MDIR     // This indicates that a message object will use or is using filtering
                                                         // based on the direction of the transfer.
#define CAN_MSG_OBJ_USE_EXT_FILTER   CAN_IF1MSK_MXTD     // This indicates that a message object will use or is using message
                                                         // identifier filtering based on the extended identifier.
#define CAN_MSG_OBJ_FIFO             (0x00000002UL)      // This indicates that this message object is part of a FIFO structure and
                                                         // not the final message object in a FIFO.
#define CAN_MSG_OBJ_FLAGS            (0x00000001UL)      // This indicates that a message object has A flags set.

//=====================================================
//    Struct & Enum & Union Typedef
//=====================================================

//=====================================================
//    Variable Declaration
//=====================================================

//=====================================================
//    Function Declaration
//=====================================================

static void v_CanCfg_InitMod(void);
static void v_CanCfg_SetBitTiming(Uint32 ulClock, Uint32 ulBitRate, Uint16 uiBitTime);
static void v_CanCfg_StartMod(void);

#endif /* CANCFG_H_ */
//===========================================================================
// End of file.
//===========================================================================
