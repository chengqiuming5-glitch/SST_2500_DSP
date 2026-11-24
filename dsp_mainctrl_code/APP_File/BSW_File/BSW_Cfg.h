//==============================================================================================
//    File description
//==============================================================================================
/**@file         BSWCfg.h
* TITLE         : BSW configuration Header File
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
#ifndef BSW_CFG_H_
#define BSW_CFG_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "App.h"
#include "F2837xD_Examples.h"

//==============================================================================================
//    Macro Definition
//==============================================================================================


//==============================================================================================
//   Global Struct & Enum & Union Typedef
//==============================================================================================
/* CAN Enum typedef */
typedef enum
{
    CAN_MSG_FRAME_STD,    ///< Set the message ID frame to standard.
    CAN_MSG_FRAME_EXT     ///< Set the message ID frame to extended.
}EN_CAN_MsgFrameType;

typedef enum
{
    CAN_MSG_OBJ_TYPE_TX,            ///< Transmit message object
    CAN_MSG_OBJ_TYPE_TX_REMOTE,     ///< Transmit remote request message object
    CAN_MSG_OBJ_TYPE_RX,            ///< Receive message object.
    CAN_MSG_OBJ_TYPE_RXTX_REMOTE    ///< Remote frame receive remote, with auto-transmit message object
}EN_CAN_MsgObjType;

//==============================================================================================
//    Global Function Declaration
//==============================================================================================
/* ADC configuration */
extern void v_AdcCfg_Init(void);
/* CLA configuration */
extern void v_ClaCfg_Init(void);
/* CMPSS configuration */
extern void v_CmpssCfg_Init(void);
extern void v_CmpssCfg_D2d_FctPwm(void);
extern void v_CmpssCfg_Pfc_FctPwm(void);
extern void v_CmpssCfg_PrmUpd_Eep(void);
/* ECAP configuration */
extern void v_ECapCfg_Init(void);
/* EPWM configuration */
extern void v_EPwmCfg_Init(void);
extern void v_EPwmCfg_D2d_FctPwm(void);
extern void v_EPwmCfg_Pfc_FctPwm(void);
#if(1U == GRID_PHASE_NUMBER)
extern void v_EPwmCfg_Pfc_Slow_CBC_Cfg(void);
#endif
/* GPIO configuration */
extern void v_GpioCfg_Init(void);
/* I2C configuration */
extern void v_I2cCfg_Init(void);
/* PIE configuration */
extern void v_PieCfg_Init(void);
extern void v_PieCfg_Cmn_FctPwm(void);
/* SYS configuration */
extern void v_SysCfg_Init(void);
extern void v_SysCfg_EnableDog(void);
/* TMR configuration */
extern void v_TmrCfg_Init(void);
/* XBR configuration */
extern void v_XBarCfg_Init(void);
#if(0U == COM_MODE)
/* SCI configuration */
extern void v_SciCfg_Init(void);
#else
/* Can configuration */
extern void v_CanCfg_SetupMsgObj(Uint16 uiObjID, Uint32 ulMsgID, EN_CAN_MsgFrameType enFrame, \
                                    EN_CAN_MsgObjType enMsgType, Uint32 ulMsgIDMask, Uint32 ulFlags, \
                                    Uint16 uiMsgLen);
extern void v_CanCfg_Init(void);
#endif /* (0U == COM_MODE) */
/* SPI configuration */
extern void v_SpiCfg_Init(void);
/* DMA configuration */
extern void v_DmaCfg_Init(void);
/* EMIF configuration */
extern void v_EmifCfg_Init(void);
#endif /* BSW_CFG_H_ */
//===========================================================================
// End of file.
//===========================================================================
