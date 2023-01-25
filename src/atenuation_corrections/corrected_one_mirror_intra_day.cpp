#include <iostream>
#include <stdio.h>
#include "../lib/table_functions.h"
#include "../lib/transm_functions.h"
#include <vector>
#include <cmath>

int main()
{
	int NDA = NDA_calculation(10,4);
	float lat = -18.9051; 
	/* float lat = -14.7973; //Ilhéus em graus */

	vetor_3d R(0,-10,0); 

	float sin_Alt, sin_Azim;
	float power = 0.0;
	float hora_local;
	float J = 0.0;

	float rel_air_humid = 0.001; 
	float altitude = 70; 
	float d = 100; 
	float temp_Kelvin = 393.0;
	float mirror_area = 1.0;

	/* log_entrada(NDA, lat, hora_local); */

	std::cout << "HORALOCAL" << ";" << "J" << ";"<< "POWER" << ";" << "ReflecPercent" << ";" << "ZEN" << ";" << "AZIM" << ";" << "Sz" << std::endl;
	vetor_3d s(0,0,0);
	vetor_3d focus_pos(0,0,20);
	for (hora_local = 6.0; hora_local < 18; hora_local += 0.08){

		sin_Alt = sin_Alt_calculation(NDA, lat, hora_local);
		sin_Azim = sin_Azim_calculation(NDA, lat, hora_local);
		s = sun_pos_in_cartesian_coord(sin_Alt, sin_Azim, s);
		J = corrected_irradiance(NDA, lat, hora_local,  rel_air_humid, altitude, d, temp_Kelvin);

		/* std::cout <<"Hora local: " << hora_local << " ; S_z: " << s.coord[2] << " ; J: " << J << std::endl; */

		power = one_mirror_corrected_power(s, R, focus_pos, J, mirror_area);

		if (sin_Alt > 0.0){
			std::cout 
			<< hora_local << ";" 
			<< J << ";" 
			<< power << ";" 
			<< (100*power)/J << ";" 
			<< acos(sin_Alt) << ";" 
			<< asin(sin_Azim) << ";" 
			<< s.coord[2] << std::endl;
		}
	}

	return 0;
}
