#include <iostream>
#include "../lib/transm_functions.h"
#include "../lib/table_functions.h"
#include <cmath>

int main() {

	/* std::cout << " Parâmetros de entrada: " << std::endl; */
	/* std::cout << "d = " << d << std::endl; */
	/* std::cout << "rel_air_humid = " << rel_air_humid << std::endl; */
	/* std::cout << "temp_Kelvin = " << temp_Kelvin << std::endl; */
	/* std::cout << "lat = " << lat << std::endl; */
	/* std::cout << "altitude = " << altitude << std::endl; */
	/* std::cout << "NDA = " << NDA << std::endl; */
	/* std::cout << "hora_local = " << hora_local << std::endl; */
	/* std::cout << "--------------------------" << std::endl; */

	double d = 200;
	double rel_air_humid = 0.0;
	double temp_Kelvin = 393.0;
	double lat = 18;
	double altitude = 0.0;
	double NDA = NDA_calculation(1, 0);
	double hora_local = 12.00;

	double I_lambda = 0.00;
	double tau = 0.0;

	double w = preciptable_water(rel_air_humid, temp_Kelvin);
	double sin_Alt = sin_Alt_calculation(NDA, lat, hora_local);
	double theta_z = acos(sin_Alt);

	std::cout << " lambda;Ibare;Icorr" << std::endl;

	double delta = 0.01;
	double lambda = 0.250;
	while(lambda < 2.0){
		
		tau = total_transmitance(lambda, theta_z, w, d, altitude);
		I_lambda = table_given_irradiance(lambda);
		std::cout << lambda << ";" << I_lambda << ";"<< I_lambda*tau << std::endl;

		lambda += delta;
	}	

	return 0;
}
