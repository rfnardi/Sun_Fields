#include <iostream>
#include "./heliostato.h"
#include "./bare_functions.h"
/* #include "./heliostato.cpp" */

int main(){


Heliostato h1; //criando objeto
vetor_3d result;

h1.set_point_inside_mirror_region(0.2,0.5);

result = h1.pick_point_inside_mirror_region(0.1,0.3, result);
std::cout << "Coordenada x: " << result.coord[0] << std::endl; 
std::cout << "Coordenada y: " << result.coord[1] << std::endl; 
std::cout << "Coordenada z: " << result.coord[2] << std::endl; 
//std::cout<<result; //esta linha não vai funcionar pois o objeto result não é um tipo simples

	return 0;
}
