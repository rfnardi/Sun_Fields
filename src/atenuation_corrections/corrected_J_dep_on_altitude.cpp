#include <iostream>
#include "../lib/transm_functions.h"

int main()
{
	int NDA = NDA_calculation(16,4);
	float lat = -18.90; 
	float hora_local = 12.0;
	float J = 0.0;
	float rel_air_humid = 80.0; 
	float altitude = 0.0; 
	float d = 200.0; 
	float temp_Kelvin = 393.0;
	float J0 = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);

	std::cout <<"altitude;J;Percent_transm" << std::endl;
	for (altitude = 0.0; altitude <= 1000; altitude += 1.0){
		J = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
		std::cout << altitude << ";" << J  << ";" << (100*J)/(J0) << std::endl;
	}

	return 0;
}
