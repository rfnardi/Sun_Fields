#include <iostream>
#include <stdio.h>
#include "./all_functions.cpp"
#include <vector>

int main()
{
	int NDA = NDA_calculation(25,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	vetor_3d R(0,-10,0); //espelho localizado a 12 metros ao sul do ponto focal

	float * sin_Alt_sin_Azim_Array;
	float power = 0.0;
	float hora_local = 6.0;


	std::vector<vetor_3d> malha;
	vetor_3d mirror_place(0,0,0);

	//setting malha:
	for (float i = -10; i < 12; i +=1.5) {
		mirror_place.reset_coord(i,-12.0,0.0);
		malha.push_back(mirror_place);
	}

	std::cout << "tamanho da malha: "<< malha.size()<<std::endl;
	log_entrada(NDA, lat, hora_local);

	vetor_3d s(0,0,0);
	while(hora_local<=18){
		power = 0.0;
		sin_Alt_sin_Azim_Array = sin_Alt_sin_Azim_calculation(NDA, lat, hora_local, sin_Alt_sin_Azim_Array);
		s = sun_pos_in_cartesian_coord(sin_Alt_sin_Azim_Array, s);
		for(int i = 0; i < malha.size(); i++){
			power += one_mirror_power(s, malha[i], NDA);
			/* malha[i].log_coords(); */
		}
		std::cout << "Hora local: "<< hora_local ;
		std::cout << " ; Projeção vertical do sol: " << s.coord[2] ; 
		std::cout << " ; Potência: "<< power << std::endl;
		hora_local += 1;
	}

	/* log_angulos(sin_Alt_sin_Azim_Array); */
	/* log_sun_position(s); */

	return 0;
}
