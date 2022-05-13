#include "../lib/transm_functions.cpp"

int main()
{
	float NDA = 160; 
	float local_time = 12; 
	float lat = 14; 
	float rel_air_humid = 0.7; 
	float altitude = 70; 
	float d = 200; 
	float temp_Kelvin = 393;
	float w = preciptable_water(rel_air_humid, temp_Kelvin, altitude);

	float sin_Alt = sin_Alt_calculation(NDA, lat, local_time);
	float theta_z = acos(sin_Alt);

	float lambda = 0.250;//em micrôns
	while(lambda <= 25){

	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "lambda: " << lambda << std::endl;
	float ozone_transm = ozone_absorp_transm_lambda(lambda, theta_z, altitude, w);
	std::cout << "transmitância do ozônio: " << ozone_transm << std::endl;
	float wv_aborp_transm = water_vapor_absorp_transm_lambda(lambda, theta_z, altitude, w);
	std::cout << "transmitância do vapor de água: " << wv_aborp_transm << std::endl;
	float gas_mixt_transm = gas_mix_absorp_transm_lambda(lambda, theta_z, altitude);
	std::cout << "transmitância da mistura gasosa: " << gas_mixt_transm << std::endl;
	lambda += 0.01;
	}


	return 0;
}
