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

	vetor_3d R(0,-10,0); 

	float sin_Alt, sin_Azim ;

	float power = 0.0;
	float hora_local = 12.0;
	float mirror_area = 1.0;
	float rel_air_humid = 0.8;
	float altitude = 70.0;
	float d = 100;
	float temp_Kelvin = 393.0;
	float J =0.0;

	vetor_3d s(0,0,0);

	float theta_z = 0.0;
	std::cout << "NDA" << ";" << "J" << ";" << "POWER" << ";" << "Refl_percent" << ";" << "ZEN" << ";" << "S_z" << std::endl;

	for (NDA = 1; NDA<=365; NDA++){
		sin_Alt = sin_Alt_calculation(NDA, lat, hora_local);
		sin_Azim = sin_Azim_calculation(NDA, lat, hora_local);
		theta_z = acos(s.coord[2]);
		s =	sun_pos_in_cartesian_coord(sin_Alt, sin_Azim, s); 
		J = corrected_irradiance(NDA, lat, hora_local, rel_air_humid, altitude, d, temp_Kelvin);
		power = one_mirror_corrected_power(s, R, J, mirror_area);

		std::cout << NDA << ";" << J << ";" << power << ";" << 100*power/J << ";"<< theta_z << ";" <<  s.coord[2] << std::endl;
	}

	return 0;
}
