#include <iostream>
#include <stdio.h>
#include <vector>
#include "../lib/transm_functions.h"
#include <cmath>

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
	float south_distance = 2.0;
	int half_size = 50; //quantidade total de heliostatos por linha dividido por 2
	for (int j = 0; j<100; j++) {
		for (int i = 0; i <= half_size; i++) {
			mirror_place.reset_coord(i*heliost_gap,-south_distance-j*heliost_gap,0);
			malha.push_back(mirror_place);
			if(i!=0){
				mirror_place.reset_coord(-i*heliost_gap,-south_distance-j*heliost_gap,0);
				malha.push_back(mirror_place);
			}
		}
	}


	vetor_3d s(0,0,0);
	s = get_sun_position(NDA, lat, hora_local,s);

	//condições atmosféricas:
	float rel_air_humid = 0.8;
	float altitude = 70;
	float temp_Kelvin = 393.0;
	float d = 100;
	float J = corrected_irradiance(NDA, lat, hora_local, rel_air_humid, altitude, d, temp_Kelvin);

	float mirror_area = 1.0;

	float delta = 0.0;
	float scalar_prod;
	float azimut_angle;
	vetor_3d heliost_pos(0,0,0);
	std::cout << "heliost_number,n.s,azimut_angle,x,y,power,net_power" << std::endl;
	vetor_3d normal_to_mirror(0,0,0);
	vetor_3d reflected(0,0,0);
	vetor_3d south_direction(0,-1,0);
	float x, y;
	for(int i = 0; i < (int) malha.size(); i++){
		normal_to_mirror = get_normal_vector(s, malha[i], focus_pos, normal_to_mirror);

		heliost_pos = malha[i];
		heliost_pos.get_unitary_vector();
		azimut_angle = heliost_pos.scalar_prod(south_direction);
		azimut_angle = std::acos(azimut_angle);//em radianos
		azimut_angle = rad_to_deg(azimut_angle); //em graus

		scalar_prod = normal_to_mirror.scalar_prod(s);
		x = malha[i].coord[0];
		y = malha[i].coord[1];

		if (!tower_shadow_cil_aprox(tower_radius, tower_height, malha[i], s)){

			delta = one_mirror_corrected_power(s,malha[i],focus_pos,J,mirror_area);
			power += delta;
			std::cout << i << "," << scalar_prod << ","<< azimut_angle << "," << x << "," << y << "," << delta << "," << power << std::endl;
		}
	}

	return 0;
}
