#include <iostream>
#include <stdio.h>
#include "../lib/table_functions.h"
#include "../lib/transm_functions.h"
#include <vector>

int main()
{
	int NDA = NDA_calculation(16,4);
	float lat = 0.0; 
	/* float lat = -14.7973; //Ilhéus em graus */
	float hora_local = 12.0;
	float J = 0.0;
	float rel_air_humid = 0.8; 
	float altitude = 70; 
	float d = 200; 
	float temp_Kelvin = 393.0;

	float J_0 = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
	std::cout <<"lat;J;ReflPercent" << std::endl;
	for (lat = 0.0; lat > -70; lat -= 1){
		J = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
		std::cout << lat << ";" << J  << ";" << 100*J/J_0 << std::endl;
	}

	return 0;
}
