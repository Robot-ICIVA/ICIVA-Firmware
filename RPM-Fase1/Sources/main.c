/* ###################################################################
**     Filename    : main.c
**     Project     : pruebas pwm
**     Processor   : MCF51QE128CLK
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-04-30, 14:22, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PWM1.h"
#include "PWM2.h"
#include "Bit1.h"
#include "Bit2.h"
#include "AD1.h"
#include "FC161.h"
#include "AS1.h"
#include "Bit3.h"
#include "Bit4.h"
#include "Bit5.h"
#include "PWM1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
int i=0;
int false = 0;
int true= 1;
unsigned short ADC16=0;

unsigned char estado = ESPERAR;

// Variables COMM
unsigned char CodError;
bool primero = FALSE;
unsigned char anuncio;
unsigned char anuncio2;
unsigned char found_band;
unsigned char n_canales;
unsigned char command; // Comando enviado desde pc para cambiar estado del sistema



// Variables COMM
unsigned int error;
unsigned short Velup,Vellow;
unsigned short Vel;
unsigned short Motor, Dir;
unsigned short Lectura_Buffer=4;
unsigned char Buffer[8];


void delay_ms (unsigned int time_delay);
void Motores( unsigned short Motor, unsigned short Direccion, unsigned short Velocidad);

void main(void){
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
	 for(;;) {
		 switch (estado){
				
				case ESPERAR:
					break;
					
				case MOTORES:
					
					Lectura_Buffer = 4;
					CodError = AS1_RecvBlock(Buffer, 4, &Lectura_Buffer);
					Motor = (unsigned short)Buffer[0];
					Dir = (unsigned short)Buffer[1];
					Velup =  (unsigned short)Buffer[2];
					Vellow =  (unsigned short)Buffer[3];
					Vel = (Velup<<8)+Vellow;
					PWM1_SetRatio16(5000);
					PWM2_SetRatio16(Vel);
					AS1_ClearRxBuf();
					//Motores(Motor, Dir, Vel);
					Bit3_NegVal();
					estado = ESPERAR;
					break;
				
				default:
					break;
		 }
	 }


  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

void Motores( unsigned short Motor, unsigned short Direccion, unsigned short Velocidad){
	if (Motor == 1) {
		if(Direccion==1){								//Direccion 1 esta asociada a forward
			PWM2_SetRatio16(Velocidad);
			Bit2_PutVal(FALSE);	
		}
		else {							//Direccion 0 esta asociada a backwards
		    Velocidad=65535-Velocidad;				//Inverso del DutyCycle
			PWM2_SetRatio16(Velocidad);
			Bit2_PutVal(TRUE);
	     }
	}
	
	else {
		if(Direccion==1){								//Direccion 1 esta asociada a forward
			PWM1_SetRatio16(Velocidad);
			Bit1_PutVal(FALSE);	
		}
		else {						//Direccion 0 esta asociada a backwards
			Velocidad=65535-Velocidad;				//Inverso del DutyCycle
			PWM1_SetRatio16(Velocidad);
			Bit1_PutVal(TRUE);
		 }

	}

	
}

/* END main */
void delay_ms (unsigned int time_delay){
	
	unsigned short time;
	CodError = FC161_Reset(); // Resetear contador
	CodError = FC161_GetTimeMS(&time);
	while(time_delay> time){
		CodError = FC161_GetTimeMS(&time);
	}
	
	
}
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
