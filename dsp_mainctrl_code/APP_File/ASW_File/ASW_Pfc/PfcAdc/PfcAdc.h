//==============================================================================================
//    File description
//==============================================================================================
/**@file         PfcAdc.h
* TITLE         : Header file of PFC ADC
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
* Module        : PfcAdc
* 1st Unit      :
* 2nd Unit      :
* 3rd Unit      :
*
* Module Task   : v_PfcAdc_Init()

*
* 1st Unit Task :
*
* 2nd Unit Task :
*
* 3rd Unit Task :
*
************************************************************************************************
*/
#ifndef PFCADC_H_
#define PFCADC_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "PfcAdcExt.h"
#include "ComExt.h"
#include "ComIfExt.h"
#include "AdcDrvExt.h"
#include "PfcGridCtrlExt.h"
#include "PfcDataCalcExt.h"
#include "PfcStMacExt.h"
#include "EmifExt.h"
//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define LPF_10KHZ_ISR_COEFF    (1.0f / (1.0f + PI_2_CONST * 10000.0f * PERD_PFC_CTRL))    ///< Cof1:1/(1+wT)

#if(1U == GRID_PHASE_NUMBER)
#define COEFF_AD_VG        ((908.7f*4.3f*3.0f)/(4.7f*2.2f*4095.0f))          ///< Vg AD coefficient
#define COEFF_AD_IG        (80.0f*(4.7f*10.0f*3.0f)/(10.0f*6.8f*4095.0f))    ///< Ig AD coefficient
#define COEFF_AD_VBUS      ((923.6f*3.0f)/(5.6f*4095.0f))                    ///< Vbus AD coefficient
#define COEFF_AD_IGDC      ((80.0f*3.0f)/(60.4f*4095.0f))                    ///< Ig_dc AD coefficient
#define COEFF_AD_VGDC      ((908.7f*3.0)/(4.7f*100.0f*4095.0f))              ///< Vg_dc AD coefficient
#elif(2U == GRID_PHASE_NUMBER)
#define  COEFF_AD_VG       0.12045724f
#define  COEFF_AD_VGINV    0.158203125f
#define  COEFF_AD_VGDC     0.00118966f
#define  COEFF_AD_IG       0.08519175f
#define  COEFF_AD_IGN      0.0227178f
#define  COEFF_AD_IGDC     0.00194793f
#define  COEFF_AD_VBUSNEG  0.08891601f
#define  COEFF_AD_VBUSPOS  0.08891601f
#elif(3U == GRID_PHASE_NUMBER)
#define  COEFF_AD_VG       14.5429425f//3.732693f//1.45429425f//14.5429425f
#define  COEFF_AD_VGDC     0.0f
#define  COEFF_AD_IG       0.043094f//0.06464124f
#define  COEFF_AD_IGDC     0.0f//0.00219780f
//#define  COEFF_AD_VBUS     0.370798204f
//#define  COEFF_AD_VBUSPOS  0.370798204f
//#define  COEFF_AD_VBUSNEG  0.370798204f
//#define  COEFF_AD_VBUS_RECPER  (1/COEFF_AD_VBUS)
#endif

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
	ST_PFC_ADC stPrmExt;    // Parameter to extern
}ST_PFC_ADC_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================


#endif /* PFCADC_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
