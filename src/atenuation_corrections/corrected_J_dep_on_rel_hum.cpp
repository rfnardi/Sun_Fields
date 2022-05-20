#include <iostream>
#include "../lib/transm_functions.h"

int main()
{
	int NDA = NDA_calculation(16,4);
	float lat = -18.90; 
	float hora_local = 12.0;
	float J = 0.0;
	float rel_air_humid = 0.01; 
	float altitude = 700.0; 
	float d = 200.0; 
	float temp_Kelvin = 393.0;
	float J0 = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);

	std::cout <<"relAirHumid;J;PercentTransm" << std::endl;
	for (rel_air_humid = 0.01; rel_air_humid <= 1; rel_air_humid += 0.01){
		J = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
		std::cout << rel_air_humid << ";" << J  << ";" << (100*J)/(J0) << std::endl;
	}

	return 0;
}
