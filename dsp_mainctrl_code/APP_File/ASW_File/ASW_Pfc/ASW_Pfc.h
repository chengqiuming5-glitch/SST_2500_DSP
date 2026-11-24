//==============================================================================================
//    File description
//==============================================================================================
/**@file         ASW_Pfc.h
* TITLE         : Header file of ASW PFC common
* Version       : V1.0
* Author        :
*
* MCU           : TMS320F2837xD
* Environment   : CCSv10.4.0
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
* Created by    :
* Created date  : 2023.11.09
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

#ifndef ASW_PFC_H_
#define ASW_PFC_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "App.h"

//==============================================================================================
//    Macro Definition
//==============================================================================================


//==============================================================================================
//   Global Struct & Enum & Union Typedef
//==============================================================================================


//==============================================================================================
//    Global Function Declaration
//==============================================================================================
/* PfcAdc */
extern void v_PfcAdc_Init(void);
extern void v_PfcAdc_Isr(void);
extern void v_PfcAdc_1ms(void);
/* PfcDataCalc */
extern void v_PfcDataCalc_Init(void);
extern void v_PfcDataCalc_1ms(void);
extern void v_PfcDataCalc_10ms(void);
extern void v_PfcDataCalc_Isr(void);
extern void v_PfcDataCalc_PrmUpd_Eep(void);
/* PfcDiag */
extern void v_PfcDiag_Init(void);
extern void v_PfcDiag_Isr(void);
#if(1U == GRID_PHASE_NUMBER)
extern interrupt void v_PfcDiag_ePwm_TZ_ISR(void);
extern interrupt void v_PfcDiag_eCap_ISR(void);
extern interrupt void v_PfcDiag_XInt1_ISR(void);
extern interrupt void v_PfcDiag_XInt3_ISR(void);
#elif(2U == GRID_PHASE_NUMBER)
extern interrupt void v_PfcDiag_eCap_ISR(void);
extern interrupt void v_PfcDiag_XInt1_ISR(void);
extern interrupt void v_PfcDiag_XInt3_ISR(void);
#elif(3U == GRID_PHASE_NUMBER)
extern interrupt void v_PfcDiag_ePwm_TZ_ISR(void);
#endif
extern void v_PfcDiag_1ms(void);
extern void v_PfcDiag_10ms(void);
extern void v_PfcDiag_100ms(void);
/* PfcGridCtrl */
extern void v_PfcGridCtrl_Init(void);
extern void v_PfcGridCtrl_1ms(void);
extern void v_PfcGridCtrl_10ms(void);
extern void v_PfcGridCtrl_PrmUpd_Eep(void);
/* PfcPowPreCtrl */
extern void v_PfcPowPreCtrl_Init(void);
extern void v_PfcPowPreCtrl_1ms(void);
extern void v_PfcPowPreCtrl_10ms(void);
/* PfcStMac */
extern void v_PfcStMac_Init(void);
extern void v_PfcStMac_1ms(void);
/* PfcPowCtrl */
extern void v_PfcPowCtrl_Init(void);
extern void v_PfcPowCtrl_Isr(void);
extern void v_PfcPowCtrl_1ms(void);
extern void v_PfcPowCtrl_Frq_PrmUpd(float32 ftTs, float32 ftWn);
extern void v_PfcPowCtrl_Frq_PrmCopy_Isr(void);
extern void v_PfcPowCtrl_PrmUpd_Eep(void);
/* OnOffGridSwt */
extern void v_OnOffGridSwt_Init(void);
extern void v_OnOffGridSwt_1ms(void);
extern void v_OnOffGridSwt_Isr(void);
extern void v_OnOffGridSwt_PrmUpd_Eep(void);
#endif /* ASW_PFC_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
