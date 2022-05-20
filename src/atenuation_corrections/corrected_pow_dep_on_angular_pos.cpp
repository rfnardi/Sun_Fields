#include <iostream>
#include <stdio.h>
#include "../lib/transm_functions.h"
#include <vector>
#include <cmath>

int main()
{
	int NDA = NDA_calculation(25,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	float power = 0.0;
	float hora_local = 12.0;
	vetor_3d mirror_place(0,0,0);
	float r = 10.0;
	float theta = M_PI;
	vetor_3d s(0,0,0);

	float rel_air_humid = 0.001; 
	float altitude = 70; 
	float d = 100; 
	float temp_Kelvin = 393.0;
	float mirror_area = 1.0;

	float J = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
	s = get_sun_position(NDA, lat, hora_local,s);
	std::cout << "thetaDeg" << ";" << "power" << ";" << "ReflecPercent" << std::endl;
	while (theta < 2*M_PI) {
		mirror_place.transf_coord_from_spher_to_cart(r,theta,M_PI/2);
		power = one_mirror_corrected_power(s, mirror_place, J, mirror_area);
		std::cout << rad_to_deg(theta) - 3*90 << ";" << power << ";" << 100*power/J << std::endl;
		theta += 0.01;
	}


	return 0;
}
