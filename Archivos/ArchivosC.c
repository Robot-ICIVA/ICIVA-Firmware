#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void decode( int *Buffer);
void clean_buffer(int* Buffer, int length);
int string_is_number(char *str);

 // Variables COMM CMUcam1
		// Decodificacion de paquetes
	
    int Data[20] = {};
    int i;
   	
		// Deteccion de camara
   	char packet_type = ' ';
   //	int x1, y1, x2, y2; // rectangulo detectado
   	int pixeles, confidence; // Calidad de la deteccion


void main ()
{
	int Buffer[20] = {};



   	clean_buffer(Buffer, 20);
   	clean_buffer(Data, 20);
   	Buffer[0] = (int)'S';
	Buffer[1] = (int)' ';
	Buffer[2] = (int)'1';
	Buffer[3] = (int)'2';
	Buffer[4] = (int)' ';
	Buffer[5] = (int)'h';
	decode(Buffer);
	i = 0;
	while (Data[i] != 0){
		printf("Data %d = %d ", i, Data[i]);
		i++;
	}



}

void decode( int *Buffer){
  // Reconstruir string
	int i,j;
	char str[20]={};
	char * pch;
	i = 0;
	while (Buffer[i] != 0){
		str[i] = (char)Buffer[i];
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