#include <iostream>
#include <random>
#include <cstring>
#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"
#include "/home/nardi/repos/Sun_Fields/src/lib/bare_functions.h"
#include "/home/nardi/repos/Sun_Fields/src/lib/transm_functions.h"
/* #include "/home/nardi/repos/Sun_Fields/src/lib/table_functions.h" */

int main(int argc, char *argv[]){

	//---------------cli-handler: 
	int grid_size = 0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-grid_size")==0){
			grid_size = std::atoi(argv[i+1]);
		}
	}

	if (grid_size == 0) {
		std::cout << "Tamanho do grid inválido." << std::endl;
		exit(EXIT_FAILURE);
	}

	float gap = 0.0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-gap")==0){
			gap = std::atof(argv[i+1]);
		}
	}

	if (gap == 0.0) {
		std::cout << "Tamanho do gap inválido." << std::endl;
		exit(EXIT_FAILURE);
	}
	//---------------END - cli-handler 

vetor_3d Focus(0, 20, 20);

float mirrors_side_leght = 1.0; //square mirrors
float vert_axis_height = 1.0;
int month_day = 22;
int month = 10;
int NDA = NDA_calculation(month_day, month);
float latitude = -14.7973; //ilhéus
float hora_local = 12.0;
vetor_3d Sun = get_sun_position(NDA, latitude, hora_local);

float rel_air_humid = 0.8; 
float altitude = 70; 
float d = 100; //índice de poeira
float temp_Kelvin = 393.0;
float mirror_area = mirrors_side_leght*mirrors_side_leght;
float J = corrected_irradiance(NDA, latitude, hora_local, rel_air_humid, altitude, d, temp_Kelvin);

/* float power = one_mirror_corrected_power(s, mirror_place, focus_pos, J, mirror_area); */

Heliostato *** Square_Grid = new Heliostato**[grid_size];
for (int i = 0; i < grid_size; i++){
	Square_Grid[i] = new Heliostato*[grid_size];
}

//popular o grid com objetos da classe heliostato
for (int i = 0; i < grid_size; i++) {
	for (int j = 0; j < grid_size; j++) {
		Square_Grid[i][j] = new Heliostato(j*(mirrors_side_leght + gap) - (gap + mirrors_side_leght)*((float) grid_size/2), i*(mirrors_side_leght + gap), 0.0, vert_axis_height, mirrors_side_leght, mirrors_side_leght);

	// setar normal, xi, eta
	Square_Grid[i][j]->set_normal(Sun, Focus);
	Square_Grid[i][j]->set_eta_vec();
	Square_Grid[i][j]->set_xi_vec();
	Square_Grid[i][j]->calculate_power(J, Sun, Focus);
	std::cout << "linha: "<< i << " ; coluna: " << j << " ; power: " << Square_Grid[i][j]->power << std::endl;
	}
}









//Liberação de memória:
for (int i = 0; i < grid_size; ++i) {
	for (int j = 0; j < grid_size; ++j) {
		delete Square_Grid[i][j]; // Libera cada objeto Heliostato
	}
	delete[] Square_Grid[i]; // Libera cada linha
}
delete[] Square_Grid; // Libera o array principal

	return 0;
}
