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


	/* mirror_place.log_coords(); */
	/* malha.push_back(mirror_place); */
	/* mirror_place.reset_coord(3,4,7); */
	/* mirror_place.log_coords(); */
	/* malha.push_back(mirror_place); */
	
	/* std::cout << "na malha: "<< std::endl; */
	/* malha[0].log_coords(); */
	/* malha[1].log_coords(); */


	//setting malha:
	for (float i = -10; i < 12; i +=1.5) {
		mirror_place.reset_coord(i,-12.0,0.0);
		malha.push_back(mirror_place);
	}

	std::cout << "tamanho da malha: "<< malha.size()<<std::endl;

	/* for (int i = 0; i < malha.size(); ++i) { */
	/* 	malha[i].log_coords(); */
	/* } */

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

	/* log_entrada(NDA, lat, hora_local); */
	/* log_angulos(sin_Alt_sin_Azim_Array); */
	/* log_sun_position(s); */


	return 0;
}
