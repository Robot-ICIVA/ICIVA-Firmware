#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const char ADC_vector_len = 5;
float ADC_vector[5] = {0.2, 0.22, 0.25, 3.4, 4};
float ADC();
float Lowest();
float Filtro(float percent);


int main ()
{
	float voltage;
	voltage = 0.5;
	printf("%f", Lowest());
    printf("%f", Filtro(0.16));
	return 0;
	
}

float ADC(){
    return 3.5;
}

float Lowest(){
    int i;
    float Lowest = 3.1; // Valor máximo del ADC
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
    j = 0;
      for (i = 0; i < ADC_vector_len; i++){
       if(ADC_vector[i]< threshold){
            ADC_filter[j] = ADC_vector[i] ;
            j++;
            printf("%f",  ADC_vector[i]);
        }
    }
    float sum= 0;
    for (i = 0; i < j; i++){
        sum = sum + ADC_vector[i];
    }
    return sum/(j);
}

