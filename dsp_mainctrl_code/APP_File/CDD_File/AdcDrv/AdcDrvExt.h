//==============================================================================================
//    File description
//==============================================================================================
/**@file         AdcDrvExt.h
 * @brief
 * Header file of ADC drive extern.
 *
 * Module      :                       \n
 * AdcDrvExt
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

#ifndef ADCDRVEXT_H_
#define ADCDRVEXT_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "CDD_Drv.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define ADC_DRV_DBG    0U    ///< Debug for SWUT,SWIT,Function debug,etc

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef struct
{
    Uint16 uiADVgA;      ///< VgA AD
    Uint16 uiADVgB;      ///< VgB AD
    Uint16 uiADVgC;      ///< VgC AD
    Uint16 uiADVgN;      ///< VgN AD

    Uint16 uiADVgInvA;   ///< VgA AD
    Uint16 uiADVgInvB;   ///< VgB AD

    Uint16 uiADIgA;      ///< IgA AD
    Uint16 uiADIgB;      ///< IgB AD
    Uint16 uiADIgC;      ///< IgC AD
//    Uint16 uiADIgN;      ///< IgN AD

//    Uint16 uiADVbus;     ///< Bus voltage AD
//    Uint16 uiADVbusPos;  ///< Bus voltage AD
//    Uint16 uiADVbusNeg;  ///< Bus voltage AD

    Uint16 uiADVgDcA;    ///< VgA DC AD
    Uint16 uiADVgDcB;    ///< VgB DC AD
    Uint16 uiADVgDcC;    ///< VgC DC AD

    Uint16 uiADIgDcA;    ///< IgA DC AD
    Uint16 uiADIgDcB;    ///< IgB DC AD
    Uint16 uiADIgDcC;    ///< IgC DC AD

//    Uint16 uiADDspBdTemp;      ///<DSP board temperature
//    Uint16 uiADDspCoreTemp;    ///<DSP core temperature
//    Uint16 uiADAux12V;         ///<Aux 12V temperature
    Uint16 uiADAux1V5;         ///<Aux 1.5V temperature
    Uint16 uiADPt1Temp;        ///<PT1 temperature
    Uint16 uiADPt2Temp;        ///<PT2 temperature
}ST_ADC_DRV;

//==============================================================================================
//    Global Variable Declaration
//==============================================================================================
extern ST_ADC_DRV stAdcDrv;

#if (1U == ADC_DRV_DBG)
extern ST_ADC_DRV stAdcDrvDbg;
#endif

#endif /* ADCDRVEXT_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
