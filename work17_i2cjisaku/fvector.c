/***********************************************************************/
/*                                                                     */
/*  FILE        :fvector.c                                             */
/*  DATE        :Mon, Jan 02, 2017                                     */
/*  DESCRIPTION :define the fixed vector table.                        */
/*  CPU GROUP   :35C                                                   */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.19).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/***********************************************************************/
/*********************************************************************
*
* Device     : R8C/3x
*
* File Name  : fvector.c
*
* Abstract   : Define the fixed vector table.
*
* History    : 1.20  (2009-03-18)
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2009 (2010) Renesas Electronics Corporation.
* and Renesas Solutions Corp.
*
*********************************************************************/

#include "cstartdef.h"

#pragma sectaddress     fvector,ROMDATA 0xffd8
                                                                                
//////////////////////////////////////////////////////////////////////////
                                                                                
_asm("	.addr 0FFFFFFH");       //reserved
_asm("	.byte 0FFH");           // OFS2
#pragma interrupt/v _dummy_int  //udi
#pragma interrupt/v _dummy_int  //over_flow
#pragma interrupt/v _dummy_int  //brki
#pragma interrupt/v _dummy_int  //address_match
#pragma interrupt/v _dummy_int  //single_step
#pragma interrupt/v _dummy_int  //wdt
#pragma interrupt/v _dummy_int  //reserved
#pragma interrupt/v _dummy_int  //reserved
#pragma interrupt/v start

#if __WATCH_DOG__ != 0
_asm("	.ofsreg 0FEH");
#else
_asm("	.ofsreg	0FFH");
#endif

_asm("	.id	""\"#FFFFFFFFFFFFFF\"");

#pragma interrupt _dummy_int()
void _dummy_int(void);
void _dummy_int(void){}
                                                                                


