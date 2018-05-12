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
unsigned short Lectura_Buffer=2;
unsigned char Buffer[4];


void delay_ms (unsigned int time_delay);
void Motor(int Direccion, unsigned short Velocidad, int Derecha, int Izquierda, short Mantener);

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
					
					Lectura_Buffer = 2;
					CodError = AS1_RecvBlock(Buffer, 2, &Lectura_Buffer);
					Velup =  (unsigned short)Buffer[0];
					Vellow =  (unsigned short)Buffer[1];
					Vel = (Velup<<8)+Vellow;
					PWM1_SetRatio16(Vel);
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

void Motor(int Direccion, unsigned short Velocidad, int Derecha, int Izquierda, short Mantener){
	unsigned short PrimVelocidad;
	unsigned short PostVelocidad;
	
	if(Mantener==0){
		
		if(Direccion==1){								//Direccion 1 esta asociada a forward
			
			PrimVelocidad=Velocidad*6;					//Velocidad = 0-10 (parar-Maxima) (0% - 60%)
			//PrimVelocidad=Velocidad*10;					//Velocidad = 0-10 (parar-Maxima) (0% - 100%)
			PostVelocidad=(PrimVelocidad*65535)/100;	//Porcentaje de DutyCycle traducido
			Bit1_PutVal(FALSE);							//Referente a Forward
			Bit2_PutVal(FALSE);							//Referente a Forward
			
			if(PostVelocidad<39322 && PostVelocidad>0){
				
				if(Derecha==0 && Izquierda==0){			//No hay cruce a izquierda o derecha
					PWM1_SetRatio16(PostVelocidad); 	//Aplica misma velocidad rueda 1
					PWM2_SetRatio16(PostVelocidad);		//Aplica misma velocidad rueda 2				
				}
				
				else if((Derecha>0 && Derecha<=90) && (Izquierda>0 && Izquierda<=90)){
					
				}
				else{/*printf("Error");*/}
				
			}
			else if(PostVelocidad>39322 || PostVelocidad<0){
				//printf("Error");
			}
			else{
				PWM1_SetRatio16(PostVelocidad); 	//PrimVel=0 por lo tanto 0% DutyCycle
				PWM2_SetRatio16(PostVelocidad);		//Esto implica siempre en Low (Motor1 y 2 Stop)
			}
				
			//printf("esto vale postvelocidad %d", PostVelocidad);
		}
		else if(Direccion==0){							//Direccion 0 esta asociada a backwards
			
			PrimVelocidad= 100 - Velocidad*6;			//El area efectiva es la inversa, se toma el negado del %
			PostVelocidad=(PrimVelocidad*65535)/100;	//Porcentaje de DutyCycle (100%-40%)
			Bit1_PutVal(TRUE);							//Referente a Forward
			Bit2_PutVal(TRUE);							//Referente a Forward
					
			if(PostVelocidad>39322 && PostVelocidad<65535){
						
				if(Derecha==0 && Izquierda==0){			//No hay cruce a izquierda o derecha
					PWM1_SetRatio16(PostVelocidad); 	//Aplica misma velocidad rueda 1
					PWM2_SetRatio16(PostVelocidad);		//Aplica misma velocidad rueda 2				
				}
						
				else if((Derecha>0 && Derecha<=90) && (Izquierda>0 && Izquierda<=90)){
							
				}
				else{/*printf("Error");*/}
						
			}
			else if(PostVelocidad>65536 || PostVelocidad<39322){
				//printf("Error");
			}
			else if(PostVelocidad==65535){
				PWM1_SetRatio16(PostVelocidad); 	//PrimVel=100 por lo tanto 100% DutyCycle
				PWM2_SetRatio16(PostVelocidad);		//Esto implica siempre en High (Motor1 y 2 Stop)
			}
			else{/*printf("Error");*/}
						
			//printf("esto vale postvelocidad%d", PostVelocidad);
		}
		
		else{
			//printf("\nError\n");
		}
	}
	
	else{//Se mantiene la velocidad
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
