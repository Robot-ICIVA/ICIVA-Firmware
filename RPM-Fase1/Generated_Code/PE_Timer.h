/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PE_Timer.h
**     Project     : RPM-Fase1
**     Processor   : MCF51QE128CLK
**     Component   : PE_Timer
**     Version     : Driver 01.04
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-05-20, 16:29, # CodeGen: 14
**     Abstract    :
**         This module "PE_Timer" implements internal methods and definitions
**         used by components working with timers.
**     Settings    :
**     Contents    :
**         No public methods
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file PE_Timer.h
** @version 01.04
** @brief
**         This module "PE_Timer" implements internal methods and definitions
**         used by components working with timers.
*/         
/*!
**  @addtogroup PE_Timer_module PE_Timer module documentation
**  @{
*/         
#ifndef __PE_Timer
#define __PE_Timer
/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Const.h"

/* MODULE PE_Timer. */

void PE_Timer_LngMul(dword va1, dword va2, dlong *var);
/*
** ===================================================================
**     Method      :  PE_Timer_LngMul (component PE_Timer)
**
**     Description :
**         The method multiplies two 32 bit values and returns pointer to 
**         64 bit result.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

bool PE_Timer_LngHi1(dword High, dword Low, word *Out);
/*
** ===================================================================
**     Method      :  PE_Timer_LngHi1 (component PE_Timer)
**
**     Description :
**         The method transfers 64 bit result to 16 bit ratio value and 
**         returns overflow flag.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

bool PE_Timer_LngHi2(dword High, dword Low, word *Out);
/*
** ===================================================================
**     Method      :  PE_Timer_LngHi2 (component PE_Timer)
**
**     Description :
**         The method transfers 64 bit result to 16 bit ratio value and 
**         returns overflow flag.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

bool PE_Timer_LngHi3(dword High, dword Low, word *Out);
/*
** ===================================================================
**     Method      :  PE_Timer_LngHi3 (component PE_Timer)
**
**     Description :
**         The method transfers 64 bit result to 16 bit ratio value and 
**         returns overflow flag.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


#endif /* END PE_Timer. */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
