#include <iostream>
#include "../lib/heliostato.h"
#include "../lib/bare_functions.h"
/* #include "./heliostato.cpp" */

int main(){


/* Heliostato h1; //criando objeto */
vetor_3d base_pos(20,20,0);
float vert_axis_height = 1.5;
float mirror_height = 2.0;
float mirror_width = 2.0;

Heliostato h1(base_pos, vert_axis_height, mirror_height, mirror_width);

vetor_3d result(0,0,0);

h1.set_point_inside_mirror_region(0.2,0.5);

result = h1.pick_point_inside_mirror_region(0.1,0.3, result);
std::cout << "Coordenada x: " << result.coord[0] << std::endl; 
std::cout << "Coordenada y: " << result.coord[1] << std::endl; 
std::cout << "Coordenada z: " << result.coord[2] << std::endl; 
//std::cout<<result; //esta linha não vai funcionar pois o objeto result não é um tipo simples

	return 0;
}
