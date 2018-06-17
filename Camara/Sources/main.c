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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* User includes (#include below this line is not maintained by Processor Expert) */
int i=0;
int false = 0;
int true= 1;
unsigned short ADC16=0;

unsigned char estado = ESPERAR;
unsigned char last_estado = ESPERAR ;
unsigned char estado_camara = ESPERAR;

// Variables Motores
unsigned short PWM_rd;
unsigned short PWM_ri;
float k_rd=3000;
float k_ri=3000;
unsigned int dir1;  // Rueda izquierda
unsigned int dir2;  // Rueda derecha


// Variables ADC
unsigned short ADC16;
float voltage;


// Variables COMM

// Banderas
bool serial_start;
unsigned char serial_end;
unsigned char CodError;
bool primero = FALSE;
unsigned char command; // Comando enviado desde pc para cambiar estado del sistema
unsigned short Enviados = 0;
unsigned short Recibidos = 0;



// Variables camara
unsigned char mx, my;


// Variables COMM
int  Data[20] = {}; // Data del paquete M
unsigned int error;
unsigned short Velup1,Vellow1, Velup2, Vellow2;
unsigned short Vel1, Vel2;
unsigned short Dir1, Dir2;
unsigned short Lectura_Buffer=4;
unsigned char packet_size;
unsigned char Buffer[100];
unsigned char Trama_PC[4]={0xff, 0x02, 0x00, 0x00}; // Esta es una primera trama, sinc+packet_size+data
unsigned char Trama_ACK[2]={0xff, 0x00};
char TC_command[] = "TC 110 150 10 30 10 30\r";
unsigned char Trama_Camara[100];

const char ADC_vector_len = 20;
float ADC_vector[20];

// Parametros de la camara
const unsigned char cx = 40; // 80
const unsigned char cy = 71; // 143
const unsigned char tx = 5; // threshold en x


void force_idle();
void send_TC();
bool Ack();
void delay_ms (unsigned int time_delay);
void Motor( unsigned short Motor, unsigned short Direccion, unsigned short Velocidad);
void Motores( unsigned short Dir1, unsigned short Vel1, unsigned short Dir2, unsigned short Vel2);
float distancia;
float ADC();
float poly(float voltage);
float Lowest();
float Filtro(float percent);
float measure(); // Muestrea 20 veces el canal ADC, filtra y  regresa el promedio de la medida
void clean_data();
void decode( );
void clean_buffer();
int string_is_number(char *str);
unsigned char ACK_cam[4];




void main(void){
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  
  /*** End of Processor Expert internal initialization.                    ***/
  TI1_Disable();
  /* Write your code here */
  estado_camara = ACK;
  			    	
	force_idle();
	//AS1_SendChar('I');
	
	
	delay_ms(20); //Delay magico que arregla todo
	clean_buffer();
	clean_data();
	estado_camara = TC;
	serial_end = 'N';
	send_TC();
	 for(;;) {
		 switch (estado){
		 	 	case RESET:
					//Send_ACK(); // Enviar ack de comando
					Motores(1, 0, 1, 0); //Apagar motores
					estado = ESPERAR;
					break;
		 	 		
				case ESPERAR:
					estado= CAMARA;
					break;
					
				case MOTORES:
					
					Motores(dir1, PWM_ri, dir2, PWM_rd);
					TI1_Enable();
					estado = ESPERAR;
					break;
					
				case MOTORES_APAGAR:
					TI1_Disable(); // Deshabilitar timer
					Motores(1, 0, 1, 0);
					
					estado = ESPERAR;
					break;
					
			    case CAMARA:
			    	
			    	//Force idle
			    	
			    	serial_end = 'N';
			    	while(serial_end == 'N'){
						delay_ms(10);
					
			    	}
			    	
			    	decode();
			    	
			    	Enviados = packet_size;
			    	//CodError = AS1_SendBlock(Buffer, Enviados,&Enviados);
			    	
			    	mx = (unsigned char)Data[0];
			    	my = (unsigned char)Data[1];
			    	
			    	AS1_SendChar(mx);
			    	//AS2_ClearRxBuf();
			    	/*
			    	clean_buffer();
			    	clean_data();
			    	// Confirmar que la camara esta en idle
			    	estado_camara = ACK;
			    	
			    	AS2_SendChar(13);
					
					estado_camara = ACK;
					serial_end = 'N';
					while(serial_end == 'N'){
						delay_ms(10);
						AS2_SendChar(13);
						//send_TC();
					}
					
					AS1_SendChar('I');
			    	AS2_ClearRxBuf();
					// Enviar comando de camara
			    	
			    	 //ConfirmarACK
			    	//serial_end = FALSE;
			    	delay_ms(1000);
			    	//while(serial_end == FALSE){
			    		//delay_ms(10);
			    		//send_TC();
			    	//}
			    	//AS1_SendChar('A');
			    	
			    	
			    	// Decodificar paquete TC
			    	//serial_end = FALSE;
			    	//estado_camara = TC;
			    	//delay_ms(200);
			    	
			    	/*while(serial_end == FALSE){
							//delay_ms(50);
							//send_TC();
					}
			    	
			    	serial_end = FALSE;
			    	
			    	 AS1_SendChar('F');
			   
			    	 //serial_end = FALSE;
			    	 /*while(serial_end!= TRUE){
			    		 send_TC();
			    		 delay_ms(10);
			    	 }
			    	 */
			    	 //estado_camara = TC;
			    	 //while(serial_end!= TRUE){
			    		 
			    	// }
			    	 
					 // Cambiar el estado a recibir TC
			    	
			    	//while(serial_end == 0){}
			    	//delay_ms(100);
			    	//serial_end = 0; // Bajar bandera
			    	//estado_camara = DCARE;
			    	
			    	//AS2_SendChar(13);
			    	
			    	
			    	
			    	/*
			    	AS1_SendChar(mx);
			    	
			    	if (mx > cx +tx)  // Mover rueda derecha, ir  a la izquierda
			    	{
			    		Dir2 = 1;
			    		PWM_rd = 30000;
			    		Dir1= 1;
			    		PWM_ri = 0;
			    		estado= MOTORES;
			    		
			    	}
			    	else if ( (mx <cx -tx) & mx >0){
			    		Dir2 = 1;
			    		PWM_rd = 0;
			    		Dir1= 1;
			    		PWM_ri = 30000;
			    		estado= MOTORES;
			    	}
			    	else {
			    		Dir2 = 1;
						PWM_rd = 0;
						Dir1= 1;
						PWM_ri = 0;
			    		estado = MOTORES;
			    		// Objeto no centrados
			    	}*/
			    	clean_data();
					//found_band2= 0;
					 
			    	
			    	estado = ESPERAR;
					break;
			    case INFRARROJO:

			    	break;
				
				default:
					break;
		 }
	 }


  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/





/* END main */

void force_idle(){
	serial_end = 'N';
	AS2_SendChar(13);
	while(serial_end == 'N'){
			delay_ms(20);
			AS2_ClearRxBuf();
			AS2_SendChar(13);
			//send_TC();
		}
}
void send_TC(){
	
	unsigned short i;
	unsigned short length = (unsigned short) strlen(TC_command);
	for (i = 0; i < length; i++){
		Trama_Camara[i]= (unsigned char)TC_command[i];
	}
	Enviados = length ;
	CodError = AS2_SendBlock(Trama_Camara, Enviados,&Enviados);
	
} 
void delay_ms (unsigned int time_delay){
	
	unsigned short time;
	CodError = FC161_Reset(); // Resetear contador
	CodError = FC161_GetTimeMS(&time);
	while(time_delay> time){
		CodError = FC161_GetTimeMS(&time);
	}
	
}



bool Ack(){
	Recibidos = 4;
	
	//AS2_RecvBlock(ACK_cam, 4, Recibidos);
	if (ACK_cam[0]== 'A' & ACK_cam[1]== 'C' ){}
}
void decode(){
  // Reconstruir string
	int i, j;
	char str[100];
	char * pch;
	i = 0;
	while (Buffer[i] != 0){
		str[i] = (char)Buffer[i];
		//printf("%c, Codigo ascii:%d\n", str[i], Buffer[i]);
		i++;
	}
	//str[i]='\r';
	//printf("String Reconstruida:\n%s\n", str);
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

void clean_buffer(){
	int i;
	for (i = 0; i < 100; i++){
		Buffer[i] = 0;
	}
}

void clean_data(){
	int i;
	for (i = 0; i < 20; i++){
		Data[i] = 0;
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


float ADC(){ // Devuelve el voltaje medido
			float voltage;
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


float Lowest(){
    int i;
    float Lowest = 3.1; // Valor m�ximo del ADC
    for (i = 0; i < ADC_vector_len; i++){
       
        if(ADC_vector[i]< Lowest){
            Lowest = ADC_vector[i];
        }
    }
    
    return Lowest;
}

float Filtro(float percent){ // Porcentaje de 0  a 1
    int i, j;
    float ADC_filter[20]; //Vector de 0
    float lowest=Lowest(); 
    float threshold = lowest*(1+percent);
    float sum ;
    
    sum = 0;
    j = 0;
      for (i = 0; i < ADC_vector_len; i++){
       if(ADC_vector[i]< threshold){
            ADC_filter[j] = ADC_vector[i] ;
            j++;
        }
    }
    
    
    for (i = 0; i < j; i++){
        sum = sum + ADC_vector[i];
    }
    return sum/(j);
}

float measure(){
	int i;
	for (i = 0; i < 20; i++){
	        ADC_vector[i]= ADC();
	        delay_ms(3); // @20 muestras, 60 ms
	    }
	return Filtro(0.17); // Regresar las muestras filtradas, 10 % de filtraje del valor mas bajo
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
