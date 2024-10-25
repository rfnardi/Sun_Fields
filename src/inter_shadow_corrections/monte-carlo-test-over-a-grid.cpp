#include <iostream>
#include <random>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"
#include "/home/nardi/repos/Sun_Fields/src/lib/bare_functions.h"
#include "/home/nardi/repos/Sun_Fields/src/lib/transm_functions.h"

int main(int argc, char *argv[]){

	//---------------cli-handler: 
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-flags")==0){
			std::cout << "Flags possíveis:" << std::endl;
			std::cout << "-grid-size: quantidade de espelhos por linha/coluna (malha quadrada)" << std::endl;
			std::cout << "-gap: distância entre espelhos (considerando-os na horizontal)" << std::endl;
			std::cout << "-hora_local: hora local (frações de hora são inseridas em decimais: 12.5 = 12h30min)" << std::endl;
			std::cout << "-mirror-side-lenght: tamanho do lado do espelho quadrado" << std::endl;
			return EXIT_SUCCESS;
		}
	}

	int grid_size = 0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-grid_size")==0){
			grid_size = std::atoi(argv[i+1]);
		}
	}
	if (grid_size == 0) {
		std::cout << "Tamanho do grid inválido." << std::endl;
		return EXIT_FAILURE;
	}


	float gap = 0.0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-gap")==0){
			gap = std::atof(argv[i+1]);
		}
	}
	if (gap == 0.0) {
		std::cout << "Tamanho do gap inválido." << std::endl;
		return EXIT_FAILURE;
	}


	float hora_local = 0.0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-hora_local")==0){
			hora_local = std::atof(argv[i+1]);
		}
	}
	if (hora_local == 0.0) {
		std::cout << "Hora local inválida." << std::endl;
		return EXIT_FAILURE;
	}


	float mirrors_side_leght = 0.0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-mirror-side-lenght")==0){
			mirrors_side_leght = std::atof(argv[i+1]);
		}
	}
	if (hora_local == 0.0) {
		std::cout << "Tamanho do espelho inválido." << std::endl;
		return EXIT_FAILURE;
	}
	

	//---------------END - cli-handler 

vetor_3d Focus(0, 20, 20);

/* float mirrors_side_leght = 1.0; //square mirrors */
float vert_axis_height = 1.0;
int month_day = 22;
int month = 10;
int NDA = NDA_calculation(month_day, month);
float latitude = -14.7973; //ilhéus
vetor_3d Sun = get_sun_position(NDA, latitude, hora_local);

float rel_air_humid = 0.8; 
float altitude = 70; 
float d = 100; //índice de poeira
float temp_Kelvin = 393.0;
float J = corrected_irradiance(NDA, latitude, hora_local, rel_air_humid, altitude, d, temp_Kelvin);


Heliostato *** Square_Grid = new Heliostato**[grid_size];
for (int i = 0; i < grid_size; i++){
	Square_Grid[i] = new Heliostato*[grid_size];
}

//popular o grid com objetos da classe heliostato
for (int i = 0; i < grid_size; i++) {
	for (int j = 0; j < grid_size; j++) {
		Square_Grid[i][j] = new Heliostato(j*(mirrors_side_leght + gap) - (gap + mirrors_side_leght)*((float) grid_size/2), -i*(mirrors_side_leght + gap), 0.0, vert_axis_height, mirrors_side_leght, mirrors_side_leght);

	// setar normal, xi, eta
	Square_Grid[i][j]->set_normal(Sun, Focus);
	Square_Grid[i][j]->set_eta_vec();
	Square_Grid[i][j]->set_xi_vec();
	Square_Grid[i][j]->calculate_D();
	Square_Grid[i][j]->calculate_power(J, Sun, Focus);
	/* std::cout << "linha: "<< i << " ; coluna: " << j << " ; power: " << Square_Grid[i][j]->power << std::endl; */
	}
}

std::random_device rd;  // Usado para obter um seed inicial
std::mt19937 gen(rd()); // Mersenne Twister engine
std::uniform_real_distribution<> distrib(0.0, 1.0);

double random_xi, random_eta;
int count_yes = 0;
int count_no = 0;
bool is_inside;

//nenhuma sombra na primeira fileira de heliostatos
for (int j = 0; j < grid_size; j++) {
	Square_Grid[0][j]->percent_brightness = 1.0;
	Square_Grid[0][j]->effective_power = Square_Grid[0][j]->power * Square_Grid[0][j]->percent_brightness;
}

vetor_3d P_shadow;
vetor_3d P_bright;
std::vector<vetor_3d> random_points;

//iteração do heliostato sombreado no grid todo (menos a primeira fileira):
for (int i = 1; i < grid_size; i++) {
	std::cout << " ------- Iterando linha " << i << " ------- \r" << std::flush;
	for (int j = 0; j < grid_size; j++) {

		//iteração na fileira da frente (àquela onde estamos calculando o sombreamento):
		count_yes = 0;
		count_no = 0;
		for (int k = 0; k < grid_size; k++){
			//monte-carlo loop:
			for (int n = 0; n < 100000; n++) {
				random_eta = distrib(gen);
				random_xi = distrib(gen);

				P_shadow = Square_Grid[i][j]->pick_point_inside_mirror_region(random_eta, random_xi);
				random_points.push_back(P_shadow);
				P_bright = Square_Grid[i-1][k]->intersec_plano_reta(P_shadow, Sun, Square_Grid[i-1][k]->normal, Square_Grid[i-1][k]->d);
				is_inside = Square_Grid[i-1][k]->check_if_picked_point_is_inside_mirror(P_bright, 0);

				if (is_inside) {count_yes++;} //yes means shadow
				else{ count_no++;}
			}
		}
		Square_Grid[i][j]->percent_brightness = (float) count_no/( (float) count_yes + (float) count_no);
		Square_Grid[i][j]->effective_power = Square_Grid[i][j]->power * Square_Grid[i][j]->percent_brightness;
	}
}

float total_grid_power = 0.0;

std::cout << std::endl;
for (int i = 0; i < grid_size; i++) {
	for (int j = 0; j < grid_size; j++) {
		/* std::cout << " ------------------------------------- " << std::endl; */
		/* std::cout << "linha: "<< i << " ; coluna: " << j  << std::endl; */
		/* Square_Grid[i][j]->base_pos.log_coords(); */
		std::cout << "l: "<< i << " ; c: " << j << " ; x= " << Square_Grid[i][j]->base_pos.coord[0] << " ; y= " << Square_Grid[i][j]->base_pos.coord[1] << "\npower: " << Square_Grid[i][j]->power << " ; \% brightness: " << Square_Grid[i][j]->percent_brightness << " ; Eff power: " << Square_Grid[i][j]->effective_power << std::endl;
		/* std::cout << "power: " << Square_Grid[i][j]->power << " ; Perc_brightness: " << Square_Grid[i][j]->percent_brightness << " ; Eff Power: " << Square_Grid[i][j]->effective_power << std::endl; */
		std::cout << " ------------------------------------- " << std::endl;
		total_grid_power += Square_Grid[i][j]->effective_power;
	}
}

FILE * data_file_ptr;

data_file_ptr = fopen("random_points.txt", "w+");

for (int i=0; i < (int) random_points.size(); i++){
	fprintf(data_file_ptr, "%2f %2f %2f\n", random_points[i].coord[0], random_points[i].coord[1], random_points[i].coord[2]);
}

fclose(data_file_ptr);

std::cout << "\nTotal Grid Power: "<< total_grid_power << " W\n" << std::endl;

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
