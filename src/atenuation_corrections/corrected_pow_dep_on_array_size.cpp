#include <iostream>
#include <stdio.h>
#include "../lib/transm_functions.h"
#include <vector>

int main()
{
	int NDA = NDA_calculation(15,4);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	float power = 0.0;
	float hora_local = 12.0;


	std::vector<vetor_3d> malha;
	vetor_3d mirror_place(0,0,0);

	//setting malha:
	//all mirrors in one single row
	float south_distance = 10.0;
	int half_size = 50;
	for (int i = 0; i < half_size; i++) {
		mirror_place.reset_coord(i+0.5,-south_distance,0.0);
		malha.push_back(mirror_place);
		if(i!=0){
			mirror_place.reset_coord(-i-0.5,-south_distance,0.0);
			malha.push_back(mirror_place);
		}
	}

	/* std::cout << "tamanho da malha: "<< malha.size() << " ; half_size: " << half_size <<std::endl; */

	vetor_3d s(0,0,0);

	s = get_sun_position(NDA, lat, hora_local,s);
	float rel_air_humid = 0.8;
	float altitude = 70;
	float temp_Kelvin = 393.0;
	float mirror_area = 1.0;
	float d = 100;
	float J = corrected_irradiance(NDA, lat, hora_local, rel_air_humid, altitude, d, temp_Kelvin);

	float delta = 0.0;
	power = one_mirror_corrected_power(s, malha[0], J, mirror_area);
	std::cout << "arraySize" << ";" << "power" << ";" << "delta" << std::endl;
	for(int i = 2; i < (int) malha.size(); i+=2){
		delta = 0.0;
		delta = one_mirror_corrected_power(s, malha[i], J, mirror_area) + one_mirror_corrected_power(s, malha[i-1], J, mirror_area);
		power += delta;
		std::cout << 1 + i << ";" << power << ";" << delta << std::endl;
	}

	return 0;
}
