//==============================================================================================
//    File description
//==============================================================================================
/**@file         SpiExt.h
 * @brief
 * The header file of SpiExt is designed to realize SPI communication.
 *
 * Module      :                       \n
 *
 *
 * Module Task :                       \n
 *                                     \n
 *                                     \n
 *                                     \n
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
#ifndef SPIExt_H_
#define SPIExt_H_

//==============================================================================================
//    Include Header Files
//==============================================================================================
#include "ASW_Cmn.h"
#include "FltDataRecExt.h"

//==============================================================================================
//    Local Macro Definition
//==============================================================================================
#define SPI_DBG                 0U              ///< Debug for SWUT,SWIT,Function debug,etc

/* SPI state */
#define SPI_STATE_IDLE          0U              ///< Idle state
#define SPI_STATE_WRITE         1U              ///< Write state
#define SPI_STATE_READ          2U              ///< Read state
//==============================================================================================
//   Local Struct & Enum & Union Typedef
//==============================================================================================
typedef union
{
    Uint16 all;
    struct
    {
        Uint16 uiErrTime        :1;    ///< bit0 - Time error
        Uint16 uiErrPrmPow      :1;    ///< bit1 - Power parameter error
        Uint16 uiErrTemp        :1;    ///< bit2 - Temperature error
        Uint16 uiErrWordFlt     :1;    ///< bit3 - Fault word error
        Uint16 uiErrRead        :1;    ///< bit4 - Read timeout error
        Uint16 uiRsvd           :11;   ///< Reserve
    }bit;
}UN_SPI_ERR;

typedef struct
{
	Uint16      uiFlgReadCmpl;        ///< Read complete flag
    Uint16 		uiStSpi;              ///< SPI state
    UN_SPI_ERR  stErrSpi;        	  ///< SPI error flag
    ST_FLT_DATA stFltDataRead;        ///< Fault data read structure
}ST_SPI;

//==============================================================================================
//    Local Function Declaration
//==============================================================================================
extern ST_SPI stSpi;

#endif /* SPIExt_H_ */
//==============================================================================================
// End of file.
//==============================================================================================
