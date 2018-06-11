#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
float poly(float voltage);


int main ()
{
	float voltage;
	voltage = 0.5;
	//printf("Hola");
	printf("Data %f  ",  poly(voltage));
	return 0;
	
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