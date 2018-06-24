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


unsigned char c1, c2;
unsigned char estado_temp ; 
unsigned char  wait_r = 0;
unsigned char counter = 0;
unsigned char click = 0;
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
	Bit5_NegVal();// PTC2
	CodError = AS1_RecvChar( &c1) ;
	// //Se debe leer el byte  o no sale de la interrupcion
	switch (estado_camara){
	
				case TC:
					
					if (serial_end == 'N'){
						if (c1  == 'M' ) { // Paquete tipo M
							// // PTE6
						
							packet_size = 1;
							counter = 0;
							wait_r = 1;
							Buffer[counter]= c1;
						}
						
						else if(wait_r == 1){
							if (c1 == 13){
								Bit4_NegVal(); // PTE6
								serial_end = 'M';
								wait_r = 0;
							}
						
						 else {
								 counter ++;
								 Buffer[counter]= c1;
								 packet_size = packet_size+1;} // se lee el siguiente byte
							
						}
					}
				  break;
				case ACK:
					//AS1_SendChar(c1);
					
						if (c1  == 'A' ) { // Paquete tipo M
							Bit4_NegVal(); // PTE6
							
							serial_end = 'A';
							//serial_end = 1;
						}
						if (c1  == 'N' ) { // Paquete tipo M
							Bit5_NegVal(); // PTE6
							serial_end = 'N';
							//serial_end = 1;
						}
						
					break;
					
					case DCARE:
						break;
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
	Bit5_NegVal();// PTC2
	CodError = AS2_RecvChar( &c1) ;
	// //Se debe leer el byte  o no sale de la interrupcion
	switch (estado_camara){
	
				case TC:
					
					if (serial_end == 'N'){
						if (c1  == 'M' ) { // Paquete tipo M
							// // PTE6
						
							packet_size = 1;
							counter = 0;
							wait_r = 1;
							Buffer[counter]= c1;
						}
						
						else if(wait_r == 1){
							if (c1 == 13){
								Bit4_NegVal(); // PTE6
								serial_end = 'M';
								wait_r = 0;
							}
						
						 else {
								 counter ++;
								 Buffer[counter]= c1;
								 packet_size = packet_size+1;} // se lee el siguiente byte
							
						}
					}
				  break;
				case ACK:
					//AS1_SendChar(c1);
					
						if (c1  == 'A' ) { // Paquete tipo M
							//Bit4_NegVal(); // PTE6
							
							wait_r = 1;
							//serial_end = 1;
						}
						if (c1  == 'N' ) { // Paquete tipo M
							//Bit5_NegVal(); // PTE6
							serial_end = 'N';
							//serial_end = 1;
						}
						if(wait_r == 1){
							if (c1 == 13){
								serial_end = 'A';
								wait_r = 0;
							}
							
						}
					
					
				break;
				
				case DCARE:
					break;
	}
	

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

/*
** ===================================================================
**     Event       :  EInt1_OnInterrupt (module Events)
**
**     Component   :  EInt1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EInt1_OnInterrupt(void)
{
  /* place your EInt1 interrupt procedure body here*/
	unsigned short time;
	
	CodError = FC162_Reset(); // Resetear contador
	CodError = FC162_GetTimeMS(&time);
	while(35> time){
		CodError = FC162_GetTimeMS(&time);
	}
	
	if (click == 0){
		if (!EInt1_GetVal()){
				Bit6_NegVal();
				send_TW();
				estado = CAMARA;
				click++;
			}
	}
	else{
		if (!EInt1_GetVal()){
						Bit6_NegVal();
						estado = RESET;
						click= 0;
					}
		
	}
	
	
	
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
