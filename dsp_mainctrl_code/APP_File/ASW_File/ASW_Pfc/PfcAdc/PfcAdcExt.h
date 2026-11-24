//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcAdcExt.h
* TITLE         : Header file of common ADC global parameter and function
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

#ifndef PFCADCEXT_H_
#define PFCADCEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Pfc.h"

//==============================================================================================
//    Global Macro Definition
//==============================================================================================
#define PFC_ADC_DBG    0U    // Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//    Global Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    float32  ftVal_A;              ///< Phase A value
    float32  ftVal_B;              ///< Phase B value
    float32  ftVal_C;              ///< Phase C value
    float32  ftVal_N;              ///< Phase N value

    float32  ftValLpf10kHz_A;      ///< Phase A 10kHz LPF value
    float32  ftValLpf10kHz_B;      ///< Phase B 10kHz LPF value
    float32  ftValLpf10kHz_C;      ///< Phase C 10kHz LPF value
    float32  ftValLpf10kHz_N;      ///< Phase N 10kHz LPF value
}ST_THREE_PHASE_PARM;

typedef struct
{
    float32  ftVal_A;              ///< Value

    float32  ftValLpf10kHz_A;      ///< 10kHz LPF value
}ST_ONE_PHASE_PARM;

typedef struct
{
    ST_THREE_PHASE_PARM stVg;       ///< Grid voltage parameter
//    ST_THREE_PHASE_PARM stVgInv;    ///< Inverter voltage parameter
    ST_THREE_PHASE_PARM stVgLine;   ///< Line voltage parameter
    ST_THREE_PHASE_PARM stIg;       ///< Grid current parameter
    ST_THREE_PHASE_PARM stVgDc;     ///< Grid voltage DC parameter
    ST_THREE_PHASE_PARM stIgDc;     ///< Grid current DC parameter

    ST_ONE_PHASE_PARM stVbus;       ///< Bus voltage parameter
    ST_ONE_PHASE_PARM stVbusPos;    ///< Bus voltage parameter
    ST_ONE_PHASE_PARM stVbusNeg;    ///< Bus voltage parameter
    float32 ftVbusPosCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];    ///< Power Cell Bus voltage parameter
    float32 ftVbusNegCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];    ///< Power Cell Bus voltage parameter
    float32 ftVbusCell[NUM_PHA_GRID][NUM_EMIF_POW_CELL];       ///< Power Cell Bus voltage parameter
    float32 ftVbusCellAvg;                                    ///< Power Cell Bus voltage parameter

    //ST_ONE_PHASE_PARM stVbusPosCell[NUM_PHA_GRID][NUM_PHA_POW_CELL];    ///< Power Cell Bus voltage parameter
    //ST_ONE_PHASE_PARM stVbusNegCell[NUM_PHA_GRID][NUM_PHA_POW_CELL];    ///< Power Cell Bus voltage parameter
    //ST_ONE_PHASE_PARM stVbusCell[NUM_PHA_GRID][NUM_PHA_POW_CELL];       ///< Power Cell Bus voltage parameter
}ST_PFC_ADC;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_PFC_ADC stPfcAdc;

#if (1U == PFC_ADC_DBG)
extern ST_PFC_ADC stPfcAdcDbg;
#endif

#endif /* PFCADCEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
