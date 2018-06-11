/* ###################################################################
**     Filename    : Events.c
**     Project     : pruebas pwm
**     Processor   : MCF51QE128CLK
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-04-30, 14:22, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
unsigned char c1;
unsigned char c2;
unsigned char estado_temp ; 
unsigned char packet_size;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AD1_OnEnd(void)
{
  /* Write your code here ... */
}


/*
** ===================================================================
**     Event       :  PWM1_OnError (module Events)
**
**     Component   :  PWM1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  PWM1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PWM1_OnRxChar (module Events)
**
**     Component   :  PWM1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


/*
** ===================================================================
**     Event       :  PWM1_OnTxChar (module Events)
**
**     Component   :  PWM1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  PWM1_OnTxChar(void){
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PWM1_OnFullRxBuf (module Events)
**
**     Component   :  PWM1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  PWM1_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PWM1_OnFreeTxBuf (module Events)
**
**     Component   :  PWM1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  PWM1_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnRxChar(void){
	Bit4_NegVal();
	if(found_band == 0){
		CodError = AS1_RecvChar( & anuncio ) ; // Header 0xff
			if (anuncio  == 0xff ) {
				found_band = 1;		 
			}
	}
	else if (found_band == 1){
		 CodError =  AS1_RecvChar( &n_bytes) ; // Header numero de bytes de data
		 found_band = found_band+1;
	}
	else if (found_band == 2){
		CodError =  AS1_RecvChar( & command ) ;
		if (command == 1){
			Bit4_NegVal();
			 found_band = found_band+1 ; // es un commando y se lee el siguiente byte
			 n_bytes = n_bytes-1; // bytes restantes por leer
			 estado_temp = MOTORES;
		}
		else if (command == 2){
			 found_band = found_band+1 ; 
			 estado_temp = CAMARA;
			 n_bytes = n_bytes-1; // bytes restantes por leer
		}
		else if (command == 3){
					 estado = INFRARROJO;
					 found_band = 0; // Se termino la lectura del Bloque, se reincia la lectura
					 command = 0;
					 anuncio = 0;
					 estado_temp = 0; // se reinicia
		}
		else if (command == 4){
						 estado = RESET;
						 found_band = 0; // Se termino la lectura del Bloque, se reincia la lectura
						 command = 0;
						 anuncio = 0;
						 estado_temp = 0; // se reinicia
			}
		else{
			found_band = 0; // No es un commando, se reinicia el proceso de lectura
			command = 0;
			anuncio = 0;
		}
	}
	else { // El estado del sistema se actualiza cuando se termina de leer el bloque
			 if (found_band == (n_bytes+2)){ // Se lee hasta que se alcance el numero de bytes de trama (+ los dos de headers)
				 found_band = 0; // Se termino la lectura del Bloque, se reincia la lectura
				 command = 0;
				 anuncio = 0;
				 estado = estado_temp; // Se actualiza el estado del sistema
				 estado_temp = 0; // se reinicia
			 }
			 else {found_band = found_band+1;} // se lee el siguiente byte
	
	
	}
}

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFullRxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFreeTxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS2_OnError (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS2_OnError(void)
{
	  /* Write your code here ... */
	
}

/*
** ===================================================================
**     Event       :  AS2_OnRxChar (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS2_OnRxChar(void)
{
	Bit3_NegVal();
	
	CodError = AS2_RecvChar(&c1);
	AS1_SendChar(c1);
}

/*
** ===================================================================
**     Event       :  AS2_OnTxChar (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS2_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS2_OnFullRxBuf (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS2_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS2_OnFreeTxBuf (module Events)
**
**     Component   :  AS2 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS2_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
  estado = MOTORES_APAGAR;

}

/* END Events */

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
