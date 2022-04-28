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

	float sin_Alt, sin_Azim;
	float power = 0.0;
	float hora_local = 6.0;

	/* log_entrada(NDA, lat, hora_local); */

	std::cout << "HORA_LOCAL" << ";" << "POWER" << ";" << "ZEN" << ";" << "AZIM" << ";" << "S_z" << std::endl;
	vetor_3d s(0,0,0);
	for (hora_local = 6.0; hora_local < 18; hora_local += 0.08){

		sin_Alt = sin_Alt_calculation(NDA, lat, hora_local);
		sin_Azim = sin_Azim_calculation(NDA, lat, hora_local);
		s = sun_pos_in_cartesian_coord(sin_Alt, sin_Azim, s);
		power = one_mirror_power(s, R, NDA);

		if (sin_Alt > 0.0){
			std::cout << hora_local << ";" 
			<<	power << ";" 
			<< acos(sin_Alt) << ";" 
			<< asin(sin_Azim) << ";" 
			<< sin_Alt << std::endl;
		}

	}

	return 0;
}
