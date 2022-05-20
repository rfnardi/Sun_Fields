#include <iostream>
#include <stdio.h>
#include "../lib/table_functions.h"
#include "../lib/transm_functions.h"
#include <vector>

int main()
{
	int NDA = NDA_calculation(10,4);
	float lat = -18.9051; 
	/* float lat = -14.7973; //Ilhéus em graus */
	float hora_local = 12.0;
	float J = 0.0;
	float rel_air_humid = 0.8; 
	float altitude = 70; 
	float d = 0.0; 
	float temp_Kelvin = 393.0;

	float J_0 = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
	std::cout <<"d;J;ReflPercent" << std::endl;
	for (d = 0.0; d < 800; d += 1){
		J = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
		std::cout << d << ";" << J  << ";" << 100*J/J_0 << std::endl;
	}

	return 0;
}
