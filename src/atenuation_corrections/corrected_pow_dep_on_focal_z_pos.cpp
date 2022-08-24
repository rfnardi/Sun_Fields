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
	float local_time = 12.0;
	vetor_3d mirror_place(0,0,0);
	vetor_3d s(0,0,0);

	float rel_air_humid = 0.001; 
	float altitude = 70; 
	float d = 100; 
	float temp_Kelvin = 393.0;
	float mirror_area = 1.0;
	float z_pos = 0.0;
	float south_distance = 10.0;

	float J = corrected_irradiance(NDA, lat, local_time,  rel_air_humid, altitude, d, temp_Kelvin);
	s = get_sun_position(NDA, lat, local_time,s);
	std::cout << "zpos" << ";" << "power" <<  std::endl;
	while (z_pos > -20.1) {
		mirror_place.reset_coord(0.0,-south_distance,z_pos);
		power = one_mirror_corrected_power(s, mirror_place, J, mirror_area);
		std::cout << -z_pos << ";" << power << std::endl;
		z_pos -= 0.1;
	}

	return 0;
}
