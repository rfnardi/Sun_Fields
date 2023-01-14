#include <iostream>
#include <stdio.h>
#include <vector>
#include "../lib/transm_functions.h"

int main()
{
	int NDA = NDA_calculation(15,4);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	float power = 0.0;
	float hora_local = 12.0;

	//setting tower parameters:
	vetor_3d focus_pos(0,0,20);
	float tower_radius = 3.0;
	float tower_height = focus_pos.coord[2];
	float heliost_gap = 1.5;


	std::vector<vetor_3d> malha;
	vetor_3d mirror_place(0,0,0);

	//setting malha:
	//all mirrors in one single row
	float south_distance = 2.0;
	int half_size = 50; //quantidade total de heliostatos por linha dividido por 2
	for (int j = 0; j<100; j++) {
		for (int i = 0; i < half_size; i++) {
			mirror_place.reset_coord(i*heliost_gap,-south_distance-j*heliost_gap,0);
			malha.push_back(mirror_place);
			if(i!=0){
				mirror_place.reset_coord(-i*heliost_gap,-south_distance-j*heliost_gap,0);
				malha.push_back(mirror_place);
			}
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
	std::cout << "heliost_number ; produto escalar com s ; heliost_x_position ; heliost_y_pos ; power ; delta" << std::endl;
	vetor_3d reflected(0,0,0);
	float scalar_prod;
	for(int i = 0; i < (int) malha.size(); i++){
		delta = 0.0;
		if (!tower_shadow_cil_aprox(tower_radius, tower_height, malha[i], s)){

			reflected = malha[i];
			reflected.invert_direction();
			reflected = reflected.vector_sum(focus_pos, reflected);
			reflected.get_unitary_vector();

			scalar_prod = reflected.scalar_prod(s);
			
			delta = one_mirror_corrected_power(s,malha[i],focus_pos,J,mirror_area) + one_mirror_corrected_power(s,malha[i-1], focus_pos,J, mirror_area);
			power += delta;
			std::cout << i << ";" << scalar_prod << ";" << malha[i].coord[0] << ";" << malha[i].coord[1] << ";" << power << ";" << delta << std::endl;
		}
	}

	return 0;
}
