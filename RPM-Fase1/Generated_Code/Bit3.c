/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Bit3.c
**     Project     : RPM-Fase1
**     Processor   : MCF51QE128CLK
**     Component   : BitIO
**     Version     : Component 02.086, Driver 03.14, CPU db: 3.00.078
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-05-15, 09:46, # CodeGen: 4
**     Abstract    :
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This component is set to work in Output direction only.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings    :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       7             |  PTE7_RGPIO7_TPM3CLK
**             ----------------------------------------------------
**
**         Port name                   : PTE
**
**         Bit number (in port)        : 7
**         Bit mask of the port        : 0x0080
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTED      [0xFFFF8008]
**         Port control register       : PTEDD     [0xFFFF8009]
**
**         Optimization for            : speed
**     Contents    :
**         GetVal - bool Bit3_GetVal(void);
**         PutVal - void Bit3_PutVal(bool Val);
**         ClrVal - void Bit3_ClrVal(void);
**         SetVal - void Bit3_SetVal(void);
**         NegVal - void Bit3_NegVal(void);
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
** @file Bit3.c
** @version 03.14
** @brief
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This component is set to work in Output direction only.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
*/         
/*!
**  @addtogroup Bit3_module Bit3 module documentation
**  @{
*/         

/* MODULE Bit3. */

#include "Bit3.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  Bit3_GetVal (component BitIO)
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
/*
bool Bit3_GetVal(void)

**  This method is implemented as a macro. See Bit3.h file.  **
*/

/*
** ===================================================================
**     Method      :  Bit3_PutVal (component BitIO)
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
void Bit3_PutVal(bool Val)
{
  if (Val) {
    setReg8(PTESET, 0x80U);            /* PTESET7=0x01U */
  } else { /* !Val */
    setReg8(PTECLR, 0x80U);            /* PTECLR7=0x01U */
  } /* !Val */
}

/*
** ===================================================================
**     Method      :  Bit3_ClrVal (component BitIO)
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Bit3_ClrVal(void)

**  This method is implemented as a macro. See Bit3.h file.  **
*/

/*
** ===================================================================
**     Method      :  Bit3_SetVal (component BitIO)
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Bit3_SetVal(void)

**  This method is implemented as a macro. See Bit3.h file.  **
*/

/*
** ===================================================================
**     Method      :  Bit3_NegVal (component BitIO)
**     Description :
**         This method negates (inverts) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Bit3_NegVal(void)

**  This method is implemented as a macro. See Bit3.h file.  **
*/


/* END Bit3. */
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
