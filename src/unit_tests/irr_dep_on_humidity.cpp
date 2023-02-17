#include "../lib/transm_functions.h"
#include <cmath>
#include <iostream>

int main() {
	
	float J = 0.0;
	float d = 200;
	float rel_air_humid = 0.0;
	float temp_Kelvin = 393.0;
	float lat = -18.9051;
	float altitude = 0.0;
	float NDA = NDA_calculation(16, 4);
	float hora_local = 12.00;
	float J0 = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);

	std::cout << "rel_air_humid;J;Percent_transm" << std::endl;
	for (rel_air_humid = 0.0; rel_air_humid < 1 ; rel_air_humid += 0.01) {
		J = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
		std::cout << rel_air_humid << ";" << J << ";" << (100*J)/J0 << std::endl;
	}

	return 0;
}
