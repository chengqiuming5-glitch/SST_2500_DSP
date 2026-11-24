//==============================================================================================
//    File description
//==============================================================================================
/**@file         SwVers.h
 * @brief
 * The header file of module software version is designed to realize software version display and management.
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

#ifndef SWVERS_H_
#define SWVERS_H_

/*
*********************************************************************************************************
*                                           Include files
*********************************************************************************************************
*/
#include "SwVersExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#if(IEC_GRID_STD == GRID_STD_ID)
#define  CHAR_GRID_STD    "IEC"
#elif(GB_GRID_STD == GRID_STD_ID)
#define  CHAR_GRID_STD    "GB"
#elif(UL_GRID_STD == GRID_STD_ID)
#define  CHAR_GRID_STD    "UL"
#endif

#if(1U == GRID_PHASE_NUMBER)
#define  CHAR_PWR_TYPE    "7.4"
#elif(2U == GRID_PHASE_NUMBER)
#define  CHAR_PWR_TYPE    "19.2"
#elif(3U == GRID_PHASE_NUMBER)
#define  CHAR_PWR_TYPE    "1.25MW"
#endif

#if(BMW_CUSTUMER == CUSTUMER_ID)
#define  CHAR_CUSTOMER    "SC"
#elif(STD_CUSTUMER == CUSTUMER_ID)
#define  CHAR_CUSTOMER    "STD"
#endif

#define  CHAR_SW_VERS    "DSP_v1.0.0_20260715"

#define  DSP_VERSON      (CHAR_GRID_STD "-" CHAR_PWR_TYPE "-"  CHAR_CUSTOMER "_" CHAR_SW_VERS)
#define  MAKER           "WANBANG Digital Energy Co. LTD"
#define  COMPLIE_ENV     "TI CCS Ver 10.4.0"
#define  CHAR_SIZE       sizeof(char)

#define  COMPILE_DATE    __DATE__
#define  COMPILE_TIME    __TIME__

#if !defined(PROJECT_TYPE)
#define PROJECT_TYPE " "
#endif

#define  DSP_VERSON_NUM    (sizeof(DSP_VERSON)/CHAR_SIZE)
#define  PROJECT_TYPE_NUM  (sizeof(PROJECT_TYPE)/CHAR_SIZE)
#define  MAKER_NUM         (sizeof(MAKER)/CHAR_SIZE)
#define  COMPILE_DATE_NUM  (sizeof(COMPILE_DATE)/CHAR_SIZE)
#define  COMPILE_TIME_NUM  (sizeof(COMPILE_TIME)/CHAR_SIZE)
#define  COMPLIE_ENV_NUM   (sizeof(COMPLIE_ENV)/CHAR_SIZE)

#if 0
// Retrieve year info
11 #define OS_YEAR     ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 \
12                                     + (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0'))
13 
14 // Retrieve month info
15 #define OS_MONTH    (__DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) \
16                                 : __DATE__ [2] == 'b' ? 2 \
17                                 : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
18                                 : __DATE__ [2] == 'y' ? 5 \
19                                 : __DATE__ [2] == 'l' ? 7 \
20                                 : __DATE__ [2] == 'g' ? 8 \
21                                 : __DATE__ [2] == 'p' ? 9 \
22                                 : __DATE__ [2] == 't' ? 10 \
23                                 : __DATE__ [2] == 'v' ? 11 : 12)
24 
25 // Retrieve day info
26 #define OS_DAY      ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 \
27                                 + (__DATE__ [5] - '0'))
28 
29 // Retrieve hour info
30 #define OS_HOUR     ((__TIME__ [0] - '0') * 10 + (__TIME__ [1] - '0'))
31 
32 // Retrieve minute info
33 #define OS_MINUTE   ((__TIME__ [3] - '0') * 10 + (__TIME__ [4] - '0'))
34 
35 // Retrieve second info
36 #define OS_SECOND   ((__TIME__ [6] - '0') * 10 + (__TIME__ [7] - '0'))
37 
38 static char time_str[32]; //= "YYYYMMDDHHMMSSres";

#endif

//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================


//==============================================================================================
//    Local Function Declaration
//==============================================================================================


#endif
//==============================================================================================
// End of file.
//==============================================================================================

