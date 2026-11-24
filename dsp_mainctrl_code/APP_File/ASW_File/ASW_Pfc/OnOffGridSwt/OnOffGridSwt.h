//==============================================================================================
//    File description
//==============================================================================================
/**@file         OnOffGridSwt.h
 * @brief
 * The header file of On&Off grid switch module.
 *
 * Module      :                           \n
 * OnOffGridSwt
 *
 * Unit        :                           \n
 *                                         \n
 *
 *
 * Module Task :                           \n
 * v_OnOffGridSwt_Init()                   \n
 * v_OnOffGridSwt_1ms()                    \n
 * v_OnOffGridSwt_Isr()
 *
 * Unit Task   :                           \n
 *                                         \n
 *
 * Sub Unit Task   :                       \n
 *
 *
 ***********************************************************************************************
 * @author
 *
 * @date
 * 2025/05/15
 * @version
 * V1.0
 * @copyright
 * (c) Copyright 2000-2050, Wanbang New Energy Investment Co.,LTD..    \n
 *                            All Rights Reserved
 * @attention
 * MCU           : TMS320F2837xD           \n
 * Environment   : CCSv10.4.0
 * @note
 * <table>
 * <tr><th>Date        <th>Version         <th>Author       <th>Description
 * <tr><td>2025/05/15  <td>1.0             <td>             <td>First edition
 * </table>
 *
 ***********************************************************************************************
 */

#ifndef ONOFFGRIDSWT_H_
#define ONOFFGRIDSWT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "OnOffGridSwtExt.h"

#include "ComExt.h"
#include "ComIfExt.h"
#include "PfcAdcExt.h"
#include "PfcDiagExt.h"
#include "PfcStMacExt.h"
#include <errno.h>

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define NUM_HALF_GRID_ISR      ((float32)FRQ_PFC_CTRL / (RATED_AC_FRQ * 2.0f * (float32)GRID_PHASE_NUMBER))
#define VOLT_RAT_JDG_HV_LMT    0.615f
#define VOLT_RAT_JDG_LV_LMT    0.307f
#define VOLT_JDG_HV_LMT        (VOLT_RAT_JDG_HV_LMT * RATED_AC_VOLT_AMP)
#define VOLT_JDG_LV_LMT        (VOLT_RAT_JDG_LV_LMT * RATED_AC_VOLT_AMP)

#if 1U == GRID_PHASE_NUMBER
#define TI_VOLT_INS_PRT        6U
#define HV_CNTR_UP_LIM         322U
#define HV_CNTR_DN_LIM         0U
#define LV_CNTR_UP_LIM         228U
#define LV_CNTR_DN_LIM         74U
#elif 2U == GRID_PHASE_NUMBER
#define TI_VOLT_INS_PRT        3U
#define HV_CNTR_UP_LIM         80U
#define HV_CNTR_DN_LIM         0U
#define LV_CNTR_UP_LIM         57U
#define LV_CNTR_DN_LIM         18U
#else
#define TI_VOLT_INS_PRT        2U
#define HV_CNTR_UP_LIM         53U
#define HV_CNTR_DN_LIM         0U
#define LV_CNTR_UP_LIM         38U
#define LV_CNTR_DN_LIM         12U
#endif

#define ASIN_UP_LIM            (PI_CONST * 0.5f)
#define ASIN_DN_LIM            0.0f
/* errno process especially for static scan */
#define ASINF(OUTP, INP, LIM) { \
                                  errno = 0; \
                                  (OUTP) = asinf(INP); \
                                  if(0 != errno) \
                                  { \
                                      (OUTP) = (LIM); \
                                  } \
                              }

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    ST_ON_OFF_GRID_SWT stPrmExt;   ///< Parameter to extern

    Uint16  uiOrdJdg;              ///< Judgement order
    Uint16  uiCntrVaOv;            ///< Va over voltage counter
    Uint16  uiCntrVbOv;            ///< Vb over voltage counter
    Uint16  uiCntrVcOv;            ///< Vc over voltage counter

    Uint16  uiCntrVabOv;           ///< Vab over voltage counter
    Uint16  uiCntrVbcOv;           ///< Vbc over voltage counter
    Uint16  uiCntrVcaOv;           ///< Vca over voltage counter

    Uint16  uiFlgVaOvIns;          ///< Va over voltage flag
    Uint16  uiFlgVbOvIns;          ///< Vb over voltage flag
    Uint16  uiFlgVcOvIns;          ///< Vc over voltage flag

    Uint16  uiFlgVabOvIns;         ///< Vab over voltage flag
    Uint16  uiFlgVbcOvIns;         ///< Vbc over voltage flag
    Uint16  uiFlgVcaOvIns;         ///< Vca over voltage flag

    Uint16  uiHvCntrLmtUp;         ///< High voltage counter up limit
    Uint16  uiHvCntrLmtDn;         ///< High voltage counter down limit
    Uint16  uiLvCntrLmtUp;         ///< Low voltage counter up limit
    Uint16  uiLvCntrLmtDn;         ///< Low voltage counter down limit

    Uint16  uiCntrVaHv;            ///< Va high voltage judgement counter
    Uint16  uiCntrVbHv;            ///< Vb high voltage judgement counter
    Uint16  uiCntrVcHv;            ///< Vc high voltage judgement counter

    Uint16  uiFlgVaHv;             ///< Va high voltage judgement succeed flag
    Uint16  uiFlgVbHv;             ///< Vb high voltage judgement succeed flag
    Uint16  uiFlgVcHv;             ///< Vc high voltage judgement succeed flag

    Uint16  uiVaHv1stJdg;          ///< Va high voltage first judgement flag
    Uint16  uiVbHv1stJdg;          ///< Vb high voltage first judgement flag
    Uint16  uiVcHv1stJdg;          ///< Vc high voltage first judgement flag

    Uint16  uiCntrVaLv;            ///< Va low voltage judgement counter
    Uint16  uiCntrVbLv;            ///< Vb low voltage judgement judgement counter
    Uint16  uiCntrVcLv;            ///< Vc low voltage judgement judgement counter

    Uint16  uiFlgVaLv;             ///< Va low voltage judgement judgement succeed flag
    Uint16  uiFlgVbLv;             ///< Vb low voltage judgement judgement succeed flag
    Uint16  uiFlgVcLv;             ///< Vc low voltage judgement judgement succeed flag

    Uint16  uiVaLv1stJdg;          ///< Va low voltage judgement first judgement flag
    Uint16  uiVbLv1stJdg;          ///< Vb low voltage judgement first judgement flag
    Uint16  uiVcLv1stJdg;          ///< Vc low voltage judgement first judgement flag

    float32 ftVaAbs;               ///< Va absolute value
    float32 ftVbAbs;               ///< Vb absolute value
    float32 ftVcAbs;               ///< Vc absolute value

    float32 ftVabAbs;              ///< Vab absolute value
    float32 ftVbcAbs;              ///< Vbc absolute value
    float32 ftVcaAbs;              ///< Vca absolute value

    float32 ftVoltLineInsPrt;      ///< Line voltage instant protect value
    float32 ftVoltHvJdgLim;        ///< High voltage judgement limit voltage
    float32 ftVoltLvJdgLim;        ///< Low voltage judgement limit voltage
}ST_ON_OFF_GRID_SWT_LOC;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
static void v_OnOffGridSwt_Inp_Isr(void);
static void v_OnOffGridSwt_Jdg_Isr(void);
static void v_OnOffGridSwt_Outp_Isr(void);
static Uint16 ui_OnOffGridSwt_VgInsDet_Isr(float32 ftVolt, float32 ftPrtVal, Uint16 *puiCntr);
static Uint16 ui_OnOffGridSwt_HvCntr_Isr(float32 ftVolt, Uint16 *puiCntr, Uint16 *pui1stJdg);
static Uint16 ui_OnOffGridSwt_LvCntr_Isr(float32 ftVolt, Uint16 *puiCntr, Uint16 *pui1stJdg);

#endif /* ONOFFGRIDSWT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
