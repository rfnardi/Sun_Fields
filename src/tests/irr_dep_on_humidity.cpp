#include "../lib/transm_functions.cpp"

int main() {
	
	float J = 0.0;
	float d = 200;
	float rel_air_humid = 0.0;
	float temp_Kelvin = 393.0;
	float lat = 18;
	float altitude = 0.0;
	float NDA = NDA_calculation(1, 0);
	float hora_local = 12.00;

	std::cout << " Parâmetros de entrada: " << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "rel_air_humid = " << rel_air_humid << std::endl;
	std::cout << "temp_Kelvin = " << temp_Kelvin << std::endl;
	std::cout << "lat = " << lat << std::endl;
	std::cout << "altitude = " << altitude << std::endl;
	std::cout << "NDA = " << NDA << std::endl;
	std::cout << "hora_local = " << hora_local << std::endl;
	std::cout << "--------------------------" << std::endl;

	for (rel_air_humid = 0.0; rel_air_humid < 1 ; rel_air_humid += 0.01) {

		J = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
		std::cout << "Umidade relativa do ar: " << rel_air_humid << " ; J: "<< J << std::endl;
	}


	return 0;
}
