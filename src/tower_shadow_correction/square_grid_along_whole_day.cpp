#include <iostream>
#include <stdio.h>
#include <vector>
#include "../lib/transm_functions.h"
#include <cmath>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
#include <string.h>

int main()
{
	int NDA = NDA_calculation(15,4);
	int *NDA_ptr = &NDA;
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */
	float *lat_ptr = &lat;


	//setting tower parameters:
	vetor_3d focus_pos(0,0,20);
	vetor_3d *focus_pos_ptr = &focus_pos;
	float tower_radius = 3.0, *tower_radius_ptr = &tower_radius;
	float tower_height = focus_pos.coord[2], *tower_height_ptr = &tower_height;
	float heliost_gap = 1.5;

	int row_size = 100; //quantidade total de heliostatos por linha
	vetor_3d malha[row_size][row_size];
	vetor_3d mirror_place(0,0,0);

	//setting malha de heliostatos:
	float south_distance = 2.0;
	for (int j = 0; j<row_size; j++) {
		for (int i = 0; i < row_size; i++) {
			if (i % 2 == 0) {
				mirror_place.reset_coord(i*heliost_gap/2,-south_distance-j*heliost_gap,0);
				malha[i][j] = mirror_place;
			}
			else {
				mirror_place.reset_coord((-i-1)*heliost_gap/2,-south_distance-j*heliost_gap,0);
				malha[i][j] = mirror_place;
			}
		}
	}


	//condições atmosféricas:
	float rel_air_humid = 0.8, *rel_air_humid_ptr = &rel_air_humid;
	float altitude = 70, *altitude_ptr = &altitude;
	float temp_Kelvin = 393.0, *temp_Kelvin_ptr = &temp_Kelvin;
	float d = 100, *d_ptr = &d;
	float J, *J_ptr = &J;

	float mirror_area = 1.0, *mirror_area_ptr = &mirror_area;
	float hora_local, *hora_local_ptr = &hora_local;

	//-----------------------------------------------------------------------------
	//-------------------------- Paralelizando: -----------------------------------
	//-----------------------------------------------------------------------------

	int num_children = 8;
	int child_status;


	for (int child_number = 0; child_number < num_children; child_number++) {
		int pid = fork();
		if (pid == 0) {
			FILE *fptr;
			char filename[12];
			sprintf(filename, "child%i.dat", child_number);
			fptr = fopen(filename,"w");
			std::cout << "Criado processo " << child_number << std::endl;

			int iterator, *iterator_ptr = &iterator;
			float power, *power_ptr = &power;
			float delta, *delta_ptr = &delta;
			vetor_3d s(0,0,0);
			vetor_3d *s_ptr = &s;

			for(int j = child_number*row_size/num_children; j < (child_number + 1)*row_size/num_children; j++){
				for(int i = 0; i < row_size; i++){
					*iterator_ptr = 1;
					*power_ptr = 0.0;
					for (hora_local = 6; hora_local < 18.0; hora_local += 0.25) {
						*J_ptr = corrected_irradiance(*NDA_ptr, *lat_ptr, *hora_local_ptr, *rel_air_humid_ptr, *altitude_ptr, *d_ptr, *temp_Kelvin_ptr);
						*s_ptr = get_sun_position( *NDA_ptr,  *lat_ptr,  *hora_local_ptr, *s_ptr);

						//este if certifica de que já é dia
						if (s.coord[2]>0.0) {
							//este if certifica que o heliostato não está na sombra da torre
							if (!tower_shadow_cil_aprox(*tower_radius_ptr, *tower_height_ptr, malha[i][j], *s_ptr)){
								*delta_ptr = one_mirror_corrected_power(*s_ptr,malha[i][j],*focus_pos_ptr,*J_ptr,*mirror_area_ptr);
							}
							else { *delta_ptr = 0.0; 
							}
							*power_ptr += *delta_ptr;
							*iterator_ptr += 1;
						}
					}
					fprintf(fptr, "%i,%i,%.2f,%.2f,%.2f\n", i,j,malha[i][j].coord[0],malha[i][j].coord[1],*power_ptr/ *iterator_ptr);
					/* std::cout  << "Child_number: "<< child_number << "," << i << "," << j << ","<< malha[i][j].coord[0] << "," << malha[i][j].coord[1] << "," << *power_ptr / iterator << std::endl; */
				}
			}
			fclose(fptr);
			exit(0);
			std::cout << "Encerrado processo " << child_number << std::endl;
		}
	}

	while(wait(&child_status)>0);
	std::cout << "Todos Processos terminados." << std::endl;

	std::cout << "Coletando trabalhos." << std::endl;
	
	std::ofstream outfile("dados.dat");
	outfile  << "i,j,x,y,power" << std::endl;

	std::string child_file_names[num_children];
	std::ifstream infiles[num_children];

	for (int i = 0; i < num_children; i++) {
		child_file_names[i] = "child" + std::__cxx11::to_string(i) + ".dat";
		infiles[i].open(child_file_names[i]);
		outfile  << infiles[i].rdbuf();
		infiles[i].close();
	}

	outfile.close();

	for (int i = 0; i < num_children; i++) {
		remove(child_file_names[i].c_str());
	}

	return 0;
}
