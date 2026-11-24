//==============================================================================================
//    File description
//==============================================================================================
/**@file         ASW_D2d.h
 * @brief
 * Header file of ASW_D2d.
 *
 * Module      :                       \n
 * ASW_D2d
 *
 * Module Task :                       \n
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2023/11/22
 * @version
 * V1.0
 * @copyright
 * (c) Copyright 2000-2050, Wanbang New Energy Investment Co.,LTD..    \n
 *                            All Rights Reserved
 * @attention
 * MCU           : TMS320F2837xD     \n
 * Environment   : CCSv10.4.0
 * @note
 * <table>
 * <tr><th>Date        <th>Version         <th>Author       <th>Description
 * <tr><td>2023/11/22  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef ASW_D2D_H_
#define ASW_D2D_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "App.h"

//==============================================================================================
//    Macro Definition
//==============================================================================================

//==============================================================================================
//    Global Function Declaration
//==============================================================================================
/* Module: D2dAdc */
extern void v_D2dAdc_Init(void);
extern void v_D2dAdc_1ms(void);
/* Module: D2dDiag */
extern void v_D2dDiag_Init(void);
extern void v_D2dDiag_1ms(void);
extern void v_D2dDiag_10ms(void);
#if(0U == FLG_SWUT_EN)
extern __interrupt void v_D2dDiag_EpwmTz_Hw_Isr(void);
extern __interrupt void v_D2dDiag_XInt_PriUpOC_Isr(void);
#if((1U == GRID_PHASE_NUMBER) || (2U == GRID_PHASE_NUMBER))
extern __interrupt void v_D2dDiag_XInt_PriDwnOC_Isr(void);
#endif
#else
extern void v_D2dDiag_EpwmTz_Hw_Isr(void);
extern void v_D2dDiag_XInt_PriUpOC_Isr(void);
#if((1U == GRID_PHASE_NUMBER) || (2U == GRID_PHASE_NUMBER))
extern void v_D2dDiag_XInt_PriDwnOC_Isr(void);
#endif
#endif

/* D2dStMac */
extern void v_D2dStMac_Init(void);
extern void v_D2dStMac_1ms(void);
/* D2dPowPreCtrl */
extern void v_D2dPowPreCtrl_Init(void);
extern void v_D2dPowPreCtrl_1ms(void);
extern void v_D2dPowPreCtrl_ParlPrmUpd(void);
extern void v_D2dPowPreCtrl_SeriesPrmUpd(void);
#if(3U == GRID_PHASE_NUMBER)
extern void v_D2dPowPreCtrl_FrqJitPrmUpd(void);
#endif
/* D2dPowCtrl */
extern void v_D2dPowCtrl_Init(void);
extern void v_D2dPowCtrl_Isr(void);
extern void v_D2dPowCtrl_1ms(void);
#if 0U == FLG_SWUT_EN
extern __interrupt void vD2dPowCtrlClaTask1(void);
extern __interrupt void vD2dPowCtrlClaTask7(void);
#if 3U == GRID_PHASE_NUMBER
extern __interrupt void vD2dPowCtrlClaTask2(void);
#endif
#else
extern void vD2dPowCtrlClaTask1(void);
extern void vD2dPowCtrlClaTask7(void);
#if 3U == GRID_PHASE_NUMBER
extern void vD2dPowCtrlClaTask2(void);
#endif
#endif
extern void v_D2dPowCtrl_FctPwm(void);

#endif /* ASW_D2D_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
