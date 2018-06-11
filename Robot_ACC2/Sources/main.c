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
Este codigo se emplea para controlar la velocidad de los motores, establecer comunicacion con la camara y medir por el canal aDC
la salida del sensor infrarrojo
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
#include "AS2.h"
#include "TI1.h"
#include "PWM1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "math.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
int i=0;
int false = 0;
int true= 1;
//unsigned short ADC16=0;

unsigned char estado = INFRARROJO;

// Variables COMM
unsigned char CodError;
bool primero = FALSE;
unsigned char anuncio;
unsigned char anuncio2;
unsigned char found_band;
unsigned char n_bytes;
unsigned char command; // Comando enviado desde pc para cambiar estado del sistema
unsigned short Enviados = 4;	

// Variables Motores
unsigned short PWM_rd;
unsigned short PWM_ri;
float k_rd=3000;
float k_ri=3000;
unsigned int dir1;
unsigned int dir2;
unsigned short ADC16;
float voltage;
// Variables COMM
unsigned int error;
unsigned short Velup,Vellow;
unsigned short Vel;
unsigned short Dir;
unsigned short Lectura_Buffer=4;
unsigned char Buffer[40];
unsigned char Trama_PC[4]={0xff, 0x02, 0x00, 0x00}; // Esta es una primera trama
float errorDist;

void delay_ms (unsigned int time_delay);
void Motor( unsigned short Motor, unsigned short Direccion, unsigned short Velocidad);
void Motores( unsigned short Dir1, unsigned short Vel1, unsigned short Dir2, unsigned short Vel2);
float distancia;
float ADC();
float poly(float voltage);
float abs(float numero);

void main(void){
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  
  /*** End of Processor Expert internal initialization.                    ***/
  TI1_Disable();
  /* Write your code here */
	 for(;;) {
		 switch (estado){
				
				case ESPERAR:
					break;
					
				case MOTORES:
					Motores(dir1, PWM_ri, dir2, PWM_rd);
					TI1_Enable();
					estado = INFRARROJO;
					break;
					
				case MOTORES_APAGAR:
					
					TI1_Disable();
					Motores(1,0,1,0);
					estado = ESPERAR;
					break;
					
			    case CAMARA:
			    	
					Lectura_Buffer = n_bytes;
					CodError = AS1_RecvBlock(Buffer, n_bytes, &Lectura_Buffer);
					AS2_SendBlock(Buffer, n_bytes, &Lectura_Buffer);
					estado = ESPERAR;
					break;
			    case INFRARROJO:
			    	Bit4_NegVal();	

			    	distancia = poly(ADC());
			    		
			    	errorDist = distancia - 15;
			    	if(distancia<15.0)
						Bit5_ClrVal();
					else
						Bit5_SetVal();
		
			    	delay_ms(10);
			    	estado = CONTROL;
			    	break;
			    case CONTROL :
			    if (errorDist <0.0){
			    	errorDist = -errorDist; // Positivo
			    	dir1 = 1;
			    	dir2 = 1;
				    PWM_rd= roundf(k_rd*errorDist);
				    PWM_ri= roundf(k_ri*errorDist);
			    }	
			    else{
			    	dir1 = 0;
			    	dir2 = 0;
			    	PWM_rd= roundf(k_rd*errorDist);
					PWM_ri= roundf(k_ri*errorDist);
			    	
			    }
			    if(PWM_rd > 65000)
			    	PWM_rd = 30000;
			    if(PWM_ri > 65000)
			    	PWM_ri = 65000;
			    delay_ms(10);
			    estado = MOTORES;
			    	break;
				default:
					break;
		 }
	 }


  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

void Motor( unsigned short Motor, unsigned short Direccion, unsigned short Velocidad){
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

void Motores( unsigned short Dir1, unsigned short Vel1, unsigned short Dir2, unsigned short Vel2){
	Motor(1, Dir1, Vel1); // Motor1
	Motor(2, Dir2, Vel2); // Motor2 = Motor derecha desde arriba-atras
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

float ADC(){ // Devuelve el voltaje medido

			CodError = AD1_Enable();
			// Otras mediciones
			ADC16 = 0;
			//MADC16 = 0; // Promedio de mediciones
			CodError = AD1_Measure(TRUE);
			CodError = AD1_GetValue16(&ADC16);
			/*for (i = 0; i<16; i++){
							CodError = AD1_Measure(TRUE);
							CodError = AD1_GetValue16(&ADC16);
							MADC16= MADC16+(ADC16>>4);
							delay_ms(4);
			}*/
		
			ADC16 = (ADC16>>4) ;  //  5 bit mas significativo 
			CodError = AD1_Disable();
			voltage = (float)3.1/(pow(2,12)-1)*ADC16;
			
			return voltage; 
}

float poly(float voltage){
	float poly_a = 0;
	poly_a = 152.7-422.1*voltage+491.5*pow(voltage, 2)-258.6*pow(voltage, 3)+50.47*pow(voltage, 4);
	/*poly_a = (float)(
			-5.0018e+04*(pow(voltage,12))+
			6.009e+05*pow(voltage,11)-
			3.25e+06*pow(voltage,10)+
			1.042e+07*pow(voltage,9)-
			2.215e+07*pow(voltage,8)+
			3.276e+07*pow(voltage,7)-
			3.456e+07*pow(voltage,6)+
			2.6177e+07*pow(voltage,5)-
			1.412e+07*pow(voltage,4)+
			5.278e+06*pow(voltage,3)-
			1.297e+06*pow(voltage,2)+
			1.8723e+05*pow(voltage,1)-
			1.190e+04);
			*/

return poly_a;
}
float abs(float numero){
	return numero;
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
