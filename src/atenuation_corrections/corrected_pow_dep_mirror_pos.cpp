#include <iostream>
#include <stdio.h>
#include "../lib/transm_functions.h"
#include <vector>

int main()
{
	int NDA = NDA_calculation(25,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	float power = 0.0;
	float hora_local = 12.0;
	vetor_3d mirror_place(0,0,0);
	float south_distance = 10.0;
	float x_pos = -100.0;
	vetor_3d s(0,0,0);

	s = get_sun_position(NDA, lat, hora_local,s);
	float rel_air_humid = 0.8;
	float altitude = 70.0;
	float d = 100;
	float temp_Kelvin = 293.0;
	float mirror_area = 1.0;


	float J = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);
	std::cout << "x_pos" << ";" << "power" << ";" << "Refl_Percent"<< std::endl;
	while (x_pos < 100.1) {
		mirror_place.reset_coord(x_pos,-south_distance,0.0);
		power = one_mirror_corrected_power(s, mirror_place, J, mirror_area);
		std::cout << x_pos << ";" << power << ";" << (100*power)/J << std::endl;
		x_pos += 0.1;
	}


	return 0;
}
