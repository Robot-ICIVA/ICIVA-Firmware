#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const char ADC_vector_len = 5;
float ADC_vector[5] = {0.2, 0.5, 1, 3.4, 4};
float ADC();
float Lowest();
float Filtro();


int main ()
{
	float voltage;
	voltage = 0.5;
	printf("%f", Lowest());
	return 0;
	
}

float ADC(){
    return 3.5;
}

float Lowest(){
    int i;
    float Lowest = 3.1; // Valor máximo del ADC
    for (i = 0; i < ADC_vector_len; i++){
       
        if(ADC_vector[i]< Lower){
            Lower = ADC_vector[i];
        }
    }
    
    return Lower;
}

float Filtro(){

}

