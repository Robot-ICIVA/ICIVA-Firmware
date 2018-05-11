#include <stdio.h>

void decode( int *Buffer);

void main ()
{
	int Buffer[20] = {};
	char str[] =" ";
 // Variables COMM CMUcam1
		// Decodificacion de paquetes
    char *Data[20] = {};
    int i;
   	char * pch;
		// Deteccion de camara
   	char packet_type = ' ';
   	int x1, y1, x2, y2; // rectangulo detectado
   	int pixeles, confidence; // Calidad de la deteccion



	decode(Buffer);
	i = 0;
	printf("Codigo ascii:%d\n", Buffer[3]);
	/*
    while(Buffer[i]!=NULL){
    	printf("Codigo ascii:%s\n", Buffer[i]);
    	i++;
    }*/
  
}

void decode( int *Buffer){
	// Reconstruir string
	int i;
	i = 0;
	Buffer[3] = 1;
	printf("Codigo ascii:%d\n", Buffer[1]);
	/*
	printf("Codigo ascii:%d\n", Buffer[i]);
    while(Buffer[i] != NULL){
    	printf("Codigo ascii:%d\n", Buffer[i]);
    	i++;
    }
    
	pch = strtok (str," .");
	i = 0;
	while (pch != NULL)
	    {	
	    	
	    	printf ("%s\n",pch);
	    	Data[i] = pch;
	    	pch = strtok (NULL, " ");
	    	i++;
	  	}
	  	*/
}

