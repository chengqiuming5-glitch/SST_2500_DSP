/**
*******************************************************
* @copyright 2010-2040, WANBANG Digital Energy Co. LTD
* @file      FaultData.h
* @author    xcc
* @date      2026/7/02 11:17:47
* @version   V0.1
**********************************************************
*/

#ifndef FAULT_DATA_H_
#define FAULT_DATA_H_

#ifdef FAULT_DATA_C
#define FAULT_DATA_EXT
#else
#define FAULT_DATA_EXT extern
#endif

//==============================================================================================
//    Include Header Files
//==============================================================================================


//==============================================================================================
//    Macro Definition
//==============================================================================================
#define FAULTNUM          23U
#define SAFETY_FAULT_NUM  19U

//==============================================================================================
//    Variable Definition
//==============================================================================================
typedef struct
{
    Uint16 FaultType;
    Uint16 DetectType;
    Uint16 LimtHysteresis;
    Uint16 ConfirmTime;
    Uint16 DisappearTime;
    int16  *Actual_valueAddr;
    int16  *ThresholdsAddr;
    Uint16 *FaultWordAddr;
    Uint16 *FaultMaskWordAddr;
    Uint16 *FaultStsWordAddr;
    Uint16 Mode_Dis[4];
    Uint16 ResvdWord;
}FaultDataType;

FAULT_DATA_EXT const FaultDataType BaseFaultDataTable[FAULTNUM];
FAULT_DATA_EXT const FaultDataType CQC_Table[19];
FAULT_DATA_EXT Uint16 wBaseFaultOccurTime[FAULTNUM];
FAULT_DATA_EXT Uint16 wSafetyFaultOccurTime[SAFETY_FAULT_NUM];

#endif /* FAULT_DATA_H_ */

//==============================================================================================
// End of file.
//==============================================================================================

