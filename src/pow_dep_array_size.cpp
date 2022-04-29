#include <iostream>
#include <stdio.h>
#include "./all_functions.cpp"
#include <vector>

int main()
{
	int NDA = NDA_calculation(25,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	float sin_Alt = 0.0;
	float sin_Azim = 0.0;
	float power = 0.0;
	float hora_local = 12.0;


	std::vector<vetor_3d> malha;
	vetor_3d mirror_place(0,0,0);

	//setting malha:
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

	float delta = 0.0;
	power = one_mirror_power(s, malha[0], NDA);
	std::cout << "array_size" << ";" << "power" << ";" << "delta" << std::endl;
	/* std::cout << 1 << ";" << power << ";" << power << std::endl; */
	for(int i = 2; i < malha.size(); i+=2){
		delta = 0.0;
		delta = one_mirror_power(s, malha[i], NDA) + one_mirror_power(s, malha[i-1], NDA);
		power += delta;
		std::cout << 1 + i << ";" << power << ";" << delta << std::endl;
	}

	return 0;
}
