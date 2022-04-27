#include <stdio.h>
#include "./all_functions.cpp"

int main()
{
	int NDA = NDA_calculation(25,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	vetor_3d R(0,-10,0); //espelho localizado a 12 metros ao sul do ponto focal

	float * sin_Alt_sin_Azim_Array;
	float power;
	float hora_local = 6.0;
	vetor_3d s(0,0,0);
	while(hora_local<18){
		sin_Alt_sin_Azim_Array = sin_Alt_sin_Azim_calculation(NDA, lat, hora_local, sin_Alt_sin_Azim_Array);
		s = sun_pos_in_cartesian_coord(sin_Alt_sin_Azim_Array, s);
		power = one_mirror_power(s, R, NDA);
		std::cout << "Hora local: "<< hora_local ;
		std::cout << "\t ; Projeção vertical do sol: " << s.coord[2] ; 
		std::cout << "\t ; Potência: "<< power << std::endl;
		hora_local += 1;
	}

	/* log_entrada(NDA, lat, hora_local); */
	/* log_angulos(sin_Alt_sin_Azim_Array); */
	/* log_sun_position(s); */


	return 0;
}
