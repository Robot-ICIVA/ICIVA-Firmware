/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PE_Types.h
**     Project     : RPM-Fase1
**     Processor   : MCF51QE128CLK
**     Component   : PE_Types
**     Version     : Driver 01.01
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-05-20, 16:29, # CodeGen: 14
**     Abstract    :
**         PE_Types.h - contains definitions of basic types,
**         register access macros and hardware specific macros
**         which can be used in user application.
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
** @file PE_Types.h
** @version 01.01
** @brief
**         PE_Types.h - contains definitions of basic types,
**         register access macros and hardware specific macros
**         which can be used in user application.
*/         
/*!
**  @addtogroup PE_Types_module PE_Types module documentation
**  @{
*/         

#ifndef __PE_Types_H
#define __PE_Types_H

#include <stdint.h>
#include <ewl_misra_types.h>

#ifndef FALSE
  #define  FALSE  0                    /* Boolean value FALSE. FALSE is defined always as a zero value. */
#endif
#ifndef TRUE
  #define  TRUE   1                    /* Boolean value TRUE. TRUE is defined always as a non zero value. */
#endif

/*Types definition*/
#ifndef __cplusplus
typedef unsigned char bool;
#endif
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef unsigned long dlong[2];
typedef void (*tIntFunc)(void);
typedef unsigned char TPE_ErrCode;
#ifndef TPE_Float
typedef float TPE_Float;
#endif

/* Freescale types */
typedef unsigned char       VUINT8;
typedef signed char         VINT8;
typedef unsigned short int  VUINT16;
typedef signed short int    VINT16;
typedef unsigned long int   VUINT32;

/*lint -save  -esym(960,19.12) -esym(961,19.13) Disable MISRA rule (19.12,19.13) checking. */
/**************************************************/
/* PE register access macros                      */
/**************************************************/
#define setRegBit(reg, bit)                                     (reg |= reg##_##bit##_##MASK)
#define clrRegBit(reg, bit)                                     (reg &= ~reg##_##bit##_##MASK)
#define getRegBit(reg, bit)                                     (reg & reg##_##bit##_##MASK)
#define setReg(reg, val)                                        (reg = (byte)(val))
#define getReg(reg)                                             (reg)
#define setRegBits(reg, mask)                                   (reg |= (byte)(mask))
#define getRegBits(reg, mask)                                   (reg & (byte)(mask))
#define clrRegBits(reg, mask)                                   (reg &= (byte)(~(mask)))
#define setRegBitGroup(reg, bits, val)                          (reg = (byte)((reg & ~reg##_##bits##_##MASK) | ((val) << reg##_##bits##_##BITNUM)))
#define getRegBitGroup(reg, bits)                               ((reg & reg##_##bits##_##MASK) >> reg##_##bits##_##BITNUM)
#define setRegMask(reg, maskAnd, maskOr)                        (reg = (byte)((getReg(reg) & ~(maskAnd)) | (maskOr)))
#define setRegBitVal(reg, bit, val)                             ((val) == 0 ? (reg &= ~reg##_##bit##_##MASK) : (reg |= reg##_##bit##_##MASK))
#define changeRegBits(reg, mask)                                (reg ^= (mask))
#define changeRegBit(reg, bit)                                  (reg ^= reg##_##bit##_##MASK)

/******************************************************************/
/* Uniform multiplatform peripheral access macros - 32 bit access */
/******************************************************************/
#define setReg32Bit(RegName, BitName)                            (RegName |= RegName##_##BitName##_##MASK)
#define clrReg32Bit(RegName, BitName)                            (RegName &= ~RegName##_##BitName##_##MASK)
#define invertReg32Bit(RegName, BitName)                         (RegName ^= RegName##_##BitName##_##MASK)
#define testReg32Bit(RegName, BitName)                           (RegName & RegName##_##BitName##_##MASK)

/* Whole peripheral register access macros */
#define setReg32(RegName, val)                                   (RegName = (dword)(val))
#define getReg32(RegName)                                        RegName

/* Bits peripheral register access macros */
#define testReg32Bits(RegName, GetMask)                          (RegName & (GetMask))
#define clrReg32Bits(RegName, ClrMask)                           (RegName &= ~(dword)(ClrMask))
#define setReg32Bits(RegName, SetMask)                           (RegName |= (dword)(SetMask))
#define invertReg32Bits(RegName, InvMask)                        (RegName ^= (dword)(InvMask))
#define clrSetReg32Bits(RegName, ClrMask, SetMask)               (RegName = (RegName & (~(dword)(ClrMask))) | (dword)(SetMask))
#define seqClrSetReg32Bits(RegName, BitsMask, BitsVal)           (RegName &= ~(~(dword)(BitsVal) & (dword)(BitsMask)),\
                                                                 RegName |= (dword)(BitsVal) & (dword)(BitsMask) )
#define seqSetClrReg32Bits(RegName, BitsMask, BitsVal)           (RegName |= (dword)(BitsVal) & (dword)(BitsMask),\
                                                                 RegName &= ~(~(dword)(BitsVal) & (dword)(BitsMask)) )
#define seqResetSetReg32Bits(RegName, BitsMask, BitsVal)         (RegName &= ~(dword)(BitsMask),\
                                                                 RegName |= (dword)(BitsVal) & (dword)(BitsMask) )
#define clrReg32BitsByOne(RegName, ClrMask, BitsMask)            (RegName &= (dword)(ClrMask) & (dword)(BitsMask))

/* Bit group peripheral register access macros */
#define testReg32BitGroup(RegName, GroupName)                    (RegName & RegName##_##GroupName##_##MASK)
#define getReg32BitGroupVal(RegName, GroupName)                  ((RegName & RegName##_##GroupName##_##MASK) >> RegName##_##GroupName##_##BITNUM)
#define setReg32BitGroupVal(RegName, GroupName, GroupVal)        (RegName = (RegName & ~RegName##_##GroupName##_##MASK) | ((GroupVal) << RegName##_##GroupName##_##BITNUM))
#define seqClrSetReg32BitGroupVal(RegName,GroupName,GroupVal)    (RegName &= ~(~((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK),\
                                                                 RegName |= ((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK )
#define seqSetClrReg32BitGroupVal(RegName,GroupName,GroupVal)    (RegName |= ((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK,\
                                                                 RegName &= ~(~((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK) )
#define seqResetSetReg32BitGroupVal(RegName,GroupName,GroupVal)  (RegName &= ~RegName##_##GroupName##_##MASK,\
                                                                 RegName |= ((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK )

/******************************************************************/
/* Uniform multiplatform peripheral access macros - 16 bit access */
/******************************************************************/
#define setReg16Bit(RegName, BitName)                            (RegName |= RegName##_##BitName##_##MASK)
#define clrReg16Bit(RegName, BitName)                            (RegName &= ~RegName##_##BitName##_##MASK)
#define invertReg16Bit(RegName, BitName)                         (RegName ^= RegName##_##BitName##_##MASK)
#define testReg16Bit(RegName, BitName)                           (RegName & RegName##_##BitName##_##MASK)

/* Whole peripheral register access macros */
#define setReg16(RegName, val)                                   (RegName = (word)(val))
#define getReg16(RegName)                                        (RegName)

/* Bits peripheral register access macros */
#define testReg16Bits(RegName, GetMask)                          (RegName & (GetMask))
#define clrReg16Bits(RegName, ClrMask)                           (RegName &= ~(word)(ClrMask))
#define setReg16Bits(RegName, SetMask)                           (RegName |= (word)(SetMask))
#define invertReg16Bits(RegName, InvMask)                        (RegName ^= (word)(InvMask))
#define clrSetReg16Bits(RegName, ClrMask, SetMask)               (RegName = (word)((word)((word)RegName & (~(word)(ClrMask))) | (word)(SetMask)))
#define seqClrSetReg16Bits(RegName, BitsMask, BitsVal)           (RegName &= ~(~(word)(BitsVal) & (word)(BitsMask)),\
                                                                 RegName |= (word)(BitsVal) & (word)(BitsMask) )
#define seqSetClrReg16Bits(RegName, BitsMask, BitsVal)           (RegName |= (word)(BitsVal) & (word)(BitsMask),\
                                                                 RegName &= ~(~(word)(BitsVal) & (word)(BitsMask)) )
#define seqResetSetReg16Bits(RegName, BitsMask, BitsVal)         (RegName &= ~(word)(BitsMask),\
                                                                 RegName |= (word)(BitsVal) & (word)(BitsMask) )
#define clrReg16BitsByOne(RegName, ClrMask, BitsMask)            (RegName &= (word)(ClrMask) & (word)(BitsMask))

/* Bit group peripheral register access macros */
#define testReg16BitGroup(RegName, GroupName)                    (RegName & RegName##_##GroupName##_##MASK)
#define getReg16BitGroupVal(RegName, GroupName)                  ((RegName & RegName##_##GroupName##_##MASK) >> RegName##_##GroupName##_##BITNUM)
#define setReg16BitGroupVal(RegName, GroupName, GroupVal)        (RegName = (RegName & ~RegName##_##GroupName##_##MASK) | ((GroupVal) << RegName##_##GroupName##_##BITNUM))
#define seqClrSetReg16BitGroupVal(RegName,GroupName,GroupVal)    (RegName &= ~(~((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK),\
                                                                 RegName |= ((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK )
#define seqSetClrReg16BitGroupVal(RegName,GroupName,GroupVal)    (RegName |= ((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK,\
                                                                 RegName &= ~(~((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK) )
#define seqResetSetReg16BitGroupVal(RegName,GroupName,GroupVal)  (RegName &= ~RegName##_##GroupName##_##MASK,\
                                                                 RegName |= ((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK )

/*****************************************************************/
/* Uniform multiplatform peripheral access macros - 8 bit access */
/*****************************************************************/
#define setReg8Bit(RegName, BitName)                            (RegName |= RegName##_##BitName##_##MASK)
#define clrReg8Bit(RegName, BitName)                            (RegName &= ~RegName##_##BitName##_##MASK)
#define invertReg8Bit(RegName, BitName)                         (RegName ^= RegName##_##BitName##_##MASK)
#define testReg8Bit(RegName, BitName)                           (RegName & RegName##_##BitName##_##MASK)

/* Whole peripheral register access macros */
#define setReg8(RegName, val)                                    (RegName = (byte)(val))
#define getReg8(RegName)                                         (RegName)

/* Bits peripheral register access macros */
#define testReg8Bits(RegName, GetMask)                           (RegName & (GetMask))
#define clrReg8Bits(RegName, ClrMask)                            (RegName &= ~(byte)(ClrMask))
#define setReg8Bits(RegName, SetMask)                            (RegName |= (byte)(SetMask))
#define invertReg8Bits(RegName, InvMask)                         (RegName ^= (byte)(InvMask))
#define clrSetReg8Bits(RegName, ClrMask, SetMask)                (RegName = (byte)((byte)((byte)RegName & (~(byte)(ClrMask))) | (byte)(SetMask)))
#define seqClrSetReg8Bits(RegName, BitsMask, BitsVal)            (RegName &= ~(~(byte)(BitsVal) & (byte)(BitsMask)),\
                                                                 RegName |= (byte)(BitsVal) & (byte)(BitsMask) )
#define seqSetClrReg8Bits(RegName, BitsMask, BitsVal)            (RegName |= (byte)(BitsVal) & (byte)(BitsMask),\
                                                                 RegName &= ~(~(byte)(BitsVal) & (byte)(BitsMask)) )
#define seqResetSetReg8Bits(RegName, BitsMask, BitsVal)          (RegName &= ~(byte)(BitsMask),\
                                                                 RegName |= (byte)(BitsVal) & (byte)(BitsMask) )
#define clrReg8BitsByOne(RegName, ClrMask, BitsMask)             (RegName &= (byte)(ClrMask) & (byte)(BitsMask))

/* Bit group peripheral register access macros */
#define testReg8BitGroup(RegName, GroupName)                     (RegName & RegName##_##GroupName##_##MASK)
#define getReg8BitGroupVal(RegName, GroupName)                   ((RegName & RegName##_##GroupName##_##MASK) >> RegName##_##GroupName##_##BITNUM)
#define setReg8BitGroupVal(RegName, GroupName, GroupVal)         (RegName = (RegName & ~RegName##_##GroupName##_##MASK) | ((GroupVal) << RegName##_##GroupName##_##BITNUM))
#define seqClrSetReg8BitGroupVal(RegName,GroupName,GroupVal)     (RegName &= ~(~((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK),\
                                                                 RegName |= ((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK )
#define seqSetClrReg8BitGroupVal(RegName,GroupName,GroupVal)     (RegName |= ((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK,\
                                                                 RegName &= ~(~((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK) )
#define seqResetSetReg8BitGroupVal(RegName,GroupName,GroupVal)   (RegName &= ~RegName##_##GroupName##_##MASK,\
                                                                 RegName |= ((GroupVal) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK )
/*lint -restore  +esym(960,19.12) +esym(961,19.13) Enable MISRA rule (19.12,19.13) checking. */

#define SaveStatusReg() \
/*lint -save  -e950 -esym(960,14.3) Disable MISRA rule (1.1,14.3) checking. */\
 asm{\
   move.w SR,D0; \
   move.w D0,SR_reg; \
   ori.l #1792,D0;\
   move.w D0,SR;\
   }                                   /* This macro is used by Processor Expert. It saves CCR register and disable global interrupts. */
/*lint -restore  +esym(960,14.3) Enable MISRA rule (1.1,14.3) checking. */
#define RestoreStatusReg() \
/*lint -save  -e950 -esym(960,14.3) Disable MISRA rule (1.1,14.3) checking. */\
 asm{ \
   move.w SR_reg,D0; \
   move.w D0,SR; \
 }                                     /* This macro is used by Processor Expert. It restores CCR register saved in SaveStatusReg(). */ \
/*lint -restore  +esym(960,14.3) Enable MISRA rule (1.1,14.3) checking. */
/* Save status register and disable interrupts */
#define EnterCritical()     {\
                              /*lint -save  -e950 -esym(960,14.3) Disable MISRA rule (1.1,14.3) checking. */\
                              if (++SR_lock == 1) SaveStatusReg();\
                              /*lint -restore  +esym(960,14.3) Enable MISRA rule (1.1,14.3) checking. */\
                            }

/* Restore status register  */
#define ExitCritical()      {\
                              /*lint -save  -e950 -esym(960,14.3) Disable MISRA rule (1.1,14.3) checking. */\
                              if (--SR_lock == 0) RestoreStatusReg();\
                              /*lint -restore  +esym(960,14.3) Enable MISRA rule (1.1,14.3) checking. */\
                            }

#define ISR(x) __interrupt void x(void)

typedef struct {          /* Black&White Image  */
  word width;             /* Image width  */
  word height;            /* Image height */
  const byte * pixmap;           /* Image pixel bitmap */
  word size;              /* Image size   */
  const char_t * name;  /* Image name   */
} TIMAGE;
typedef TIMAGE* PIMAGE ; /* Pointer to image */

/* 16-bit register (big endian) */
typedef union {
   word w;
   struct {
     byte high,low;
   } b;
} TWREG;

#endif /* __PE_Types_H */
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
