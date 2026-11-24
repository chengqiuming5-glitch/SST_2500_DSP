//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcStMacExt.h
* TITLE         : Header file of PFC state machine external parameter and function
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2024.03.19
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

#ifndef PFCSTMACEXT_H_
#define PFCSTMACEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Pfc.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define PFC_ST_MAC_FLG_DBG    0U  ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef union
{
    Uint16 all;
    struct
    {
/*bit00*/   Uint16 uiRdy        :1;  ///< no use
/*bit01*/   Uint16 uiRunOk      :1;  ///< PFC run OK bit
/*bit02*/   Uint16 uiRelayA_Sts :1;  ///< Pre-charger Relay A status
/*bit03*/   Uint16 uiFlt        :1;  ///< PFC fault bit
/*bit04~06*/Uint16 uiResvd0     :3;  ///< Reserved
/*bit07*/   Uint16 uiWarn       :1;  ///< PFC warning bit
/*bit08*/   Uint16 uiResvd1     :1;  ///< Reserved
/*bit09*/   Uint16 uiRemote     :1;  ///< no use
/*bit10*/   Uint16 uiOnOffSts   :1;  ///< no use
/*bit11*/   Uint16 uiExtFlt     :1;  ///< no use
/*bit12*/   Uint16 uiRelayB_Sts :1;  ///< Pre-charger Relay B status
/*bit13*/   Uint16 uiRelayC_Sts :1;  ///< Pre-charger Relay C status
/*bit14*/   Uint16 uiRelayN_Sts :1;  ///< Relay N status
/*bit15*/   Uint16 uiHeartBeat  :1;  ///< no use
    }bit;
}UN_PFC_STSTOARM_WORD;

typedef union
{
    Uint16 all;

    struct
    {
        /*00~02*/ Uint16 uiMacSt           :3;   ///< PFC state
        /*03*/    Uint16 uiFlgPreChrgOk    :1;   ///< Bus pre-charge ok flag
        /*04*/    Uint16 uiFlgBusVoltOk    :1;   ///< Bus voltage ok for PFC running flag
        /*05*/    Uint16 uiFlgRunOk        :1;   ///< PFC run OK flag
        /*06*/    Uint16 uiFault           :1;   ///< 0:  NO Fault,  1: system fault
        /*07~15*/ Uint16 uiResvd           :9;   ///< reserved
     }bit;
}UN_PFC_STS_WORD;

typedef union
{
    Uint16 all;

    struct
    {
        /*00*/    Uint16 uiCmdRun       :1;   ///< PFC control running command
        /*01~03*/ Uint16 uiMode         :3;   ///< PFC control mode
        /*04~05*/ Uint16 uiPwmMode      :2;   ///< PFC PWM mode
        /*06~15*/ Uint16 uiResvd        :10;   ///< reserved
     }bit;
}UN_PFC_CTRL_WORD;

typedef struct
{
    UN_PFC_STS_WORD      unPFCSts;             ///< PFC status
#ifdef _SIMULATION_NO_DSP_
    UN_PFC_STS_WORD      unPFCStsOld;
    UN_PFC_CTRL_WORD     unCtrlCmdOld;
#endif
    UN_PFC_GPIO_CMD      unGPIOCmd;            ///< PFC control GPIO command
    UN_PFC_CTRL_WORD     unCtrlCmd;            ///< PFC control command
    UN_PFC_STSTOARM_WORD unStsToArm;           ///< PFC status to ARM

    float32 ftVoltPreChrgLmt;                  ///< Bus pre-charge voltage limit
}ST_PFC_ST_MAC;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PFC_ST_MAC stPfcStMac;

#if (1U == PFC_ST_MAC_FLG_DBG)
extern ST_PFC_ST_MAC stPfcStMacDbg;
#endif
#endif /* PFCSTMACEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
