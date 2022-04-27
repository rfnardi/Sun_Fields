#include <iostream>
#include <stdio.h>
#include "./all_functions.cpp"
#include <vector>

int main()
{
	int NDA = NDA_calculation(25,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	vetor_3d R(0,-10,0); 

	float * sin_Alt_sin_Azim_Array;
	float power = 0.0;
	float hora_local = 12.0;

	vetor_3d s(0,0,0);

	std::cout << "NDA" << ";" << "POWER" << std::endl;

	for (NDA = 1; NDA<=365; NDA++){
		sin_Alt_sin_Azim_Array = sin_Alt_sin_Azim_calculation(NDA, lat, hora_local, sin_Alt_sin_Azim_Array);
		s = sun_pos_in_cartesian_coord(sin_Alt_sin_Azim_Array, s);
		power = one_mirror_power(s, R, NDA);

		std::cout << NDA << ";" << power << std::endl;
	}

	/* log_angulos(sin_Alt_sin_Azim_Array); */
	/* log_sun_position(s); */

	return 0;
}
