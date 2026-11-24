//==============================================================================================
//    File description
//==============================================================================================
/**@file         SwVers.c
 * @brief
 * The source file of module software version is designed to realize software version display and management.
 *
 * Module      :                       \n
 * SwVers
 *
 * Module Task :                       \n
 * v_SwVers_Init()                     \n
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
#if (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)    ///< No PFC_LIB and D2D_LIB project

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include  "SwVers.h"

//==============================================================================================
//    Variable Definition
//==============================================================================================
static const char chDspSoftwareVer[] = DSP_VERSON;
static const char chMachineNameVer[] = PROJECT_TYPE;
static const char chComplDateConst[] = COMPILE_DATE;
static const char chComplTimeConst[] = COMPILE_TIME;
static const char chComplieVer[]     = COMPLIE_ENV;
static const char chProducer[]       = MAKER;
static const char chSpace            = ',';
static const char chSemicolon        = ';';
static const char chDashoff          = '-';

Uint16 uiCodeCompileTime[STIRNGNUM];
Uint16 uiDspSwVer[STIRNGNUM];
static Uint16 uiManufacturer[STIRNGNUM];
static Uint16 uiMachineMode[STIRNGNUM];

/**
*******************************************************************************
**************************
*                                            Local Function definition
*******************************************************************************
**************************
*/

/****************************************************************************************************/
/**
* @brief    Software version initialization
* @details  Include software version, Code compile time, manufacturer
* @param[in] 
* @param[in]  
 */
void v_SwVers_Init(void)
{
    Uint16 i = 0U;              ///< Initialize to 0U;
    Uint16 l_uiArrayNum = 0U;   ///< Initialize to 0U;

    /* Initialize to ';' */
    for(i = 0U; i < STIRNGNUM; i++)
    { 
    	uiDspSwVer[i]        = (Uint16)chSemicolon;
        uiCodeCompileTime[i] = (Uint16)chSemicolon;
        uiManufacturer[i]    = (Uint16)chSemicolon;
        uiMachineMode[i]     = (Uint16)chSemicolon;
    }
    /* Software version initialization */
    l_uiArrayNum = (Uint16)MIN_TWO(DSP_VERSON_NUM, STIRNGNUM);
    for(i = 0U; i < l_uiArrayNum; i++)
    {
        uiDspSwVer[i] = (Uint16)chDspSoftwareVer[i];
    }
    /* Project type initialization */
    l_uiArrayNum = (Uint16)MIN_TWO(PROJECT_TYPE_NUM, STIRNGNUM);
    for(i = 0U; i < l_uiArrayNum; i++)
    {
        uiMachineMode[i] = (Uint16)chMachineNameVer[i];
    }
    /* Manufacturer initialization */
    l_uiArrayNum = (Uint16)MIN_TWO(MAKER_NUM, STIRNGNUM);
    for(i = 0U; i < l_uiArrayNum; i++)
    {
        uiManufacturer[i] = (Uint16)chProducer[i];
    }
    /* Code compile time initialization */
    l_uiArrayNum = (Uint16)MIN_TWO(COMPILE_DATE_NUM, STIRNGNUM);
    for(i = 0U; i < l_uiArrayNum; i++)
    {
        if(chComplDateConst[i]==' ')
        {
            uiCodeCompileTime[i] = (Uint16)chDashoff;
        }
        else
        {
            uiCodeCompileTime[i] = (Uint16)chComplDateConst[i];
        }
    }
    uiCodeCompileTime[i-1U] = (Uint16)chSpace;
    l_uiArrayNum = (Uint16)MIN_TWO(COMPILE_TIME_NUM, STIRNGNUM);
    for(i = 0U; i < l_uiArrayNum; i++)
    {
        uiCodeCompileTime[i+COMPILE_DATE_NUM] = (Uint16)chComplTimeConst[i];
    }

#if(1U == FLG_SWIT_EN)
    printf("****SWIT DynamicTest: function v_SwVers_Init() is running****\r\n");
#endif
}

#endif    // (!defined _PFC_LIB_PRJ_) && (!defined _D2D_LIB_PRJ_)
//===========================================================================
// End of file.
//===========================================================================
