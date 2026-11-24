
/*
*********************************************************************************************************
*                                Application head files
*                            macro definition of Base module 
*
*
*            (c) Copyright 2010-2040, WANBANG Digital Energy Co. LTD
*                                 All Rights Reserved
*

*
* Name       : Data_type_definition.h
* Version    : v100
* Author     : xcc
*
* Aim        : TMS320F28335
* Mode       : LARG_MODEL
* Environment: CCS v7.4

;**--------------------------------------------------------------------------
----------------------------
;** Created by:      xcc
;** Created date:    2019-09-20
** Version:          v100
;** Descriptions:
;**
;**--------------------------------------------------------------------------
----------------------------
;** Modified by:
;** Modified date:
;** Version:
;** Descriptions:
;**
*******************************************************************************
**************************
*/

/**
* @file         Data_type_definition.h
* @brief	    Data type definition and Common Module definitions
* @details      xxxx
* @author	    xcc
* @date 	    2019-9-20
* @version	    V1.0
* @copyright	(c) Copyright 2010-2040, WANBANG Digital Energy Co. LTD
*                                All Rights Reserved
*******************************************************************************
***
* @attention
* CPU        :    DSP28335 \n
* Environment:    CCS v7.4
* @par upgrade log :
* <table>
* <tr><th>Date		    <th>Version                 <th>Author	    <th>Description
* <tr><td>2019/09/19    <td>1.0	                    <td>xcc         <td>initial
* </table>
*
*******************************************************************************
***
*/

#ifndef  DATA_TYPE_H_
#define  DATA_TYPE_H_

//#include <string.h>
/**
*******************************************************************************
**************************
*                                           Global macro Defines (#define)
*******************************************************************************
**************************
*/
/**************** Data type definition **************************************/
#ifdef _SIMULATION_NO_DSP_ 
    typedef int8_T           UCHAR8;
    typedef int16_T          INT16;
    typedef unsigned int     UINT16;
    typedef int32_T          INT32;
    typedef uint32_T         UINT32;
    typedef real_T           FLOAT32;
    
    typedef uint32_T         UINT64;
    typedef int32_T          INT64; 
    typedef real_T           FLOAT64;
    //typedef bool             _Bool;
    typedef  UINT16          WORD;
    typedef  UINT32          DWORD;
    typedef  UINT16          BYTE;
#else
    typedef unsigned char      UCHAR8;
    typedef signed   short     INT16;
    typedef unsigned short     UINT16;
    typedef signed     long    INT32;
    typedef unsigned long      UINT32;
    typedef unsigned long long   UINT64;
    typedef long long            INT64;   
    typedef          float       FLOAT32;
    typedef          double      FLOAT64;
    typedef          UINT16      WORD;
    typedef          UINT32      DWORD;
    typedef          UINT16      BYTE;
#endif

#ifndef TRUE

#define         FALSE       0U
#define         TRUE        1U
#endif

#ifndef POSITIVE
#define         POSITIVE    0U
#endif

#ifndef NEGATIVE
#define         NEGATIVE    1U
#endif 

#ifndef INACTIVE
#define         INACTIVE    0U
#define         OFF_CMD     0U
#endif 

#ifndef ACTIVE
#define         ACTIVE      1U
#define         ON_CMD      1U
#endif

#define         ENABLE_OK      1U
#define         DIS_ENABLE     0U

#define         STS_OK         1U
#define         STS_NO         0U

/** ifndef BOOL */
#ifndef  BOOL
#define  BOOL UINT16
#endif 

#define CON_ZERO 0U

#define ILLEGAL_FUNCTION_CODE_INDEX     FUNC_CODE_NUM + 1U

#define CONST		const

#if defined(MAIN_LOOP_TIME_IS_2MS)
#define MAIN_LOOP_TIME   2000
#define MAIN_CYCLE_TS    0.002
#define BaseTime(x)    (((x) + 1)>>1)
#define LPFILTER(filter_num,filter_var,unlong_store)     (((((long)(filter_var)<<16) - (unlong_store))>>((((filter_num) + 1)>>1) + 1)) + (unlong_store))
//#define LPFILTERMS(filter_ms,filter_var,unlong_store)    (((((long)(filter_var)<<16) - (unlong_store)) / (((filter_ms + 1)>>1) + 1)) + (unlong_store))
#else
#define MAIN_LOOP_TIME 1000
#define MAIN_CYCLE_TS  0.001
#define BaseTime(x)   (x)
#define LPFILTER_ISR(filter_num,filter_var,unlong_store)     (((((long)(filter_var)<<16) - (unlong_store))>>((filter_num) + 1)) + (unlong_store))
#define LPFILTER(filter_num,filter_var,unlong_store)     (((((long)(filter_var)<<16) - (unlong_store))>>((filter_num) + 1)) + (unlong_store))
//#define LPFILTERMS(filter_ms,filter_var,unlong_store)    (((((long)(filter_var)<<16) - (unlong_store)) / (filter_ms + 1)) + (unlong_store))
#endif

#define LPFILTER_PWMINTISR(filter_num,filter_var,unlong_store)  (((((long)(filter_var)<<16) - (unlong_store))>>((filter_num) + 1)) + (unlong_store))

/**************** Swap high and low bytes of word **************************************/
#define SWAP_WORD_BYTE(w)        (((((WORD)(w))>>8) & (WORD)0x00ff) + ((((WORD)(w))<<8) & (WORD)0xff00) )

/**************** Swap high and low bytes of Dword **************************************/
#define SWAP_DWORD_BYTE(dw)      (((((DWORD)(dw))>>24) & (DWORD)0x000000ff) + ((((DWORD)(dw))<<24) & (DWORD)0xff000000) + ((((DWORD)(dw))>>8) & (DWORD)0x0000ff00) + ((((DWORD)(dw))<<8) & (DWORD)0x00ff0000) )

/**************** Combine high and low bytes into word **************************************/
#define MK_WORD(Lo, Hi)          (((WORD)(((BYTE)((DWORD)(Lo)     & 0xff)) | (((WORD)((BYTE)((DWORD)(Hi)   & 0xff)))   << 8))))

/**************** Combine high and low bytes into Dword **************************************/
#define MK_DWORD(Lo, Hi)         (((DWORD)(((WORD)((DWORD)(Lo) & 0xffff)) | (((DWORD)((WORD)((DWORD)(Hi) & 0xffff))) << 16))))

/**************** Gets the high and low word of the Dword **************************************/
#define LO_WORD(l)               ((WORD)((DWORD)(l)  & 0xffff))
#define HI_WORD(l)               ((WORD)((DWORD)(l)>>16) & 0xffff)

/**************** Gets the high and low bytes of the Dword **************************************/
#define LO_BYTE(w)               ((BYTE)((DWORD)(w)  & 0xff))
#define HI_BYTE(w)               ((BYTE)((DWORD)(w) >> 8) & 0xff)

#ifdef _SIMULATION_NO_DSP_
    typedef union
    {
        int32_T dword;
        struct
        {
            uint16_T  lword;
            int16_T   hword;
        }half;
    }UNLONG;
#else
    typedef union
    {
        INT32 dword;
        struct
        {
            UINT16    lword;
            INT16     hword;
        }half;
    }UNLONG;
#endif

/**************** Limit **************************************/
#define  UpLimit16(iValue,UpValue)                       {(iValue) = ((iValue) >= (UpValue))?(UpValue):(iValue);}
#define  UpDownLimit16_ISR(iValue,UpValue,DownValue)     {(iValue) = ((iValue) >= (UpValue))?(UpValue):(iValue);    (iValue) = ((iValue) <= (DownValue))?(DownValue):(iValue);}
#define  UpDownLimit16(iValue,UpValue,DownValue)            {(iValue) = ((iValue) >= (UpValue))?(UpValue):(iValue);    (iValue) = ((iValue) <= (DownValue))?(DownValue):(iValue);}
#define  UpDownLimit32(iValue,UpValue,DownValue)            {(iValue) = ((iValue) >= (UpValue))?(UpValue):(iValue);    (iValue) = ((iValue) <= (DownValue))?(DownValue):(iValue);}
#define  UpDownLimitft(iValue,UpValue,DownValue)            {(iValue) = ((iValue) > (UpValue))?(UpValue):(iValue);    (iValue) = ((iValue) < (DownValue))?(DownValue):(iValue);}
#define  UpDownLimit32_ISR(iValue,UpValue,DownValue)     {(iValue) = ((iValue) >= (UpValue))?(UpValue):(iValue);    (iValue) = ((iValue) <= (DownValue))?(DownValue):(iValue);}

/**************** LPF **************************************/
#define  LPFILTER32(filter_num,filter_var,unlong_store)  (((((long)(filter_var)) - (unlong_store))>>((filter_num) + 1)) + (unlong_store))
#define  LPFILTERMS(filter_ms,filter_var,unlong_store)   (((((long)(filter_var)<<16) - (unlong_store)) / ((filter_ms) + 1)) + (unlong_store))

/*************** Calculate the maximum and minimum ******************/
#define  MAX(x,y)             ((x) > (y)?(x):(y))
#define  MAX3(x,y,z)          (MAX(MAX((x),(y)),(z)))
#define  MIN(x,y)             ((x) < (y)?(x):(y))
#define  MIN3(x,y,z)          (MIN(MIN((x),(y)),(z)))
#define  MAX_ISR(x,y)         ((x) > (y)?(x):(y))
#define  MAX3_ISR(x,y,z)      (MAX_ISR(MAX_ISR((x),(y)),(z)))
#define  MIN_ISR(x,y)         ((x) < (y)?(x):(y))
#define  MIN3_ISR(x,y,z)      (MIN_ISR(MIN_ISR((x),(y)),(z)))

/**************** Fetch symbol *************************************/
#define  SIGN(x)              (((x) <= 0)?0:1)
#define  SIGN_ISR(x)          (((x) <= 0)?0:1)

/**************** Shift division ************************************/
#define  DIV_2(x)          ((x)>>1)
#define  DIV_16(x)         ((x)>>4)
#define  DIV_256(x)        ((x)>>8)
#define  DIV_10000(x)      ((((long)(x))* 13)>>17)

/**************** Complementary method of divisor ********************/
#define  REMAINDER_16(x)      ((x) & 0x0F ) ///< REMAIN_64 =% 64
#define  REMAINDER_64(x)      ((x) & 0x3F ) ///< REMAIN_64 =% 64
#define  REMAINDER_256(x)     ((x) & 0xFF ) ///< REMAIN_256 =% 256

/**************** Bit operation **************************************/
#define  CLS_BIT(x,n)      ((x) &= (~(1U<<(n))))
#define  SET_BIT(x,n)      ((x) |= ((1U<<(n))))
#define  GET_BIT(x,n)      ((((x) & (1U<<(n))) > 0)?1:0)

/**************** Null pointer **************************************/
#define  NULL_POINTER      ((void*)0)

#endif        /* APP_H_ */
//===========================================================================
// End of file.
//===========================================================================
