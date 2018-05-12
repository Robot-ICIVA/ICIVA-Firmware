/* ###################################################################
**     Filename    : main.c
**     Project     : Camara-Fase1
**     Processor   : MCF51QE128CLK
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-05-10, 02:22, # CodeGen: 0
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
#include "AS1.h"
#include "AS2.h"
#include "Bit1.h"
#include "FC161.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Variables
// Estado
unsigned char estado = ESPERAR ;
// Variables COMM
unsigned char CodError;
unsigned short Enviados = 13;		// Esta variable no aporta nada más sino el número de elementos del arreglo a enviar.
unsigned short error;
unsigned char Buffer[4] = {0x00, 0x00, 0x00, 0x00};
unsigned short Lectura_Buffer= 2;
unsigned short Velup, Vellow;
bool primero = FALSE;
unsigned char anuncio;
unsigned char anuncio2;
unsigned char found_band;
unsigned char n_canales;
unsigned char command; // Comando enviado desde pc para cambiar estado del sistema
char paquete;


// Variables COMM CMUcam1
		// Decodificacion de paquetes

int Data[20] = {};
int i;

	// Deteccion de camara
char packet_type = ' ';
int x1, y1, x2, y2; // rectangulo detectado
int pixeles, confidence; // Calidad de la deteccion


void decode( int *Buffer);
void clean_buffer(int* Buffer, int length);
int string_is_number(char *str);
void delay_ms (unsigned int time_delay  );

void main(void){
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
	 for(;;) {
		 switch (estado){
				
				case ESPERAR:
					if (paquete  == 's'){
						estado = MOTORES;
						paquete =' ';
					}
					break;
					
				case MOTORES:
					Bit1_NegVal();
						estado = ESPERAR;
					break;
				
				default:
					break;
		 }
	 }


  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
	 for(;;) {}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* Implementacion de funciones */
void decode( int *Buffer){
  // Reconstruir string
	int i,j;
	char str[20];
	char * pch;
	i = 0;
	while (Buffer[i] != 0){
		str[i] =(char) Buffer[i];
		printf("%c, Codigo ascii:%d\n", str[i], Buffer[i]);
		i++;
	}
	//str[i]='\r';
   printf("String Reconstruida:\n%s\n", str);
  // Extraccion de numeros   
	pch = strtok (str," ");
	i = 0;
	j = 0;
	while (pch != NULL)
	    {	
	    	//printf("%s\n", pch);
	    	if(string_is_number(pch)){
	    		Data[j] = atoi(pch);
	    		j++;
	    	}
	    	
	    	pch = strtok (NULL, " ");
	    	i++;
	  	}
	  	
}

void clean_buffer(int* Buffer, int length){
	int i;
	for (i = 0; i < length; i++){
		Buffer[i] = 0;
	}
}
int string_is_number(char *str){ // Verifica si todos los elementos  del string son numeros
	int i;
	int length = (int) strlen(str);
	for (i = 0; i < length; i++){
		if (!isdigit(str[i])) {
			return 0;
		}
	}
	return 1;
}

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
