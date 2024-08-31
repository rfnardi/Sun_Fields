#include <iostream>
#include <random>
#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"

int main(){

	float vert_axis_height = 1.0;

Heliostato Hs(0, -20, 0, vert_axis_height, 1.0, 1.0);
Heliostato Hb(0, -18, 0, vert_axis_height, 0.8, 0.8);

std::cout << "Coordenadas do ponto central do espelho Hs:" << std::endl;
vetor_3d mirror_center_position(Hs.base_pos.coord[0], Hs.base_pos.coord[1] , Hs.base_pos.coord[2] + vert_axis_height);
mirror_center_position.log_coords();

vetor_3d Ps;
vetor_3d S(0,0.4,0.1); // sun position
S.get_unitary_vector();

std::cout << "tamanho de S:" << std::endl;

S.log_coords();

vetor_3d F(0,0,20); // focus position

Hs.set_normal(S, F);
Hb.set_normal(S, F);

Hs.set_eta_vec();
Hs.set_xi_vec();
Hb.set_eta_vec();
Hb.set_xi_vec();

std::cout << "Normal do espelho Hs:" << std::endl;
Hs.normal.log_coords();
std::cout << " ----------------- " << std::endl;
std::cout << "Normal do espelho Hb:" << std::endl;
Hb.normal.log_coords();
std::cout << " ----------------- " << std::endl;

float d = Hb.calculate_d();

std::random_device rd;  // Usado para obter um seed inicial
std::mt19937 gen(rd()); // Mersenne Twister engine
std::uniform_real_distribution<> distrib(0.0, 1.0);

double random_xi, random_eta;
int count_yes = 0;
int count_no = 0;
bool is_inside;

for (int i = 0; i < 10000; i++) {

	random_eta = distrib(gen);
	random_xi = distrib(gen);

Ps = Hs.pick_point_inside_mirror_region(random_eta,random_xi, Ps);
	
/* std::cout << "Coordenadas de Ps:" << std::endl; */
/* Ps.log_coords(); */
/* std::cout << " ----------------- " << std::endl; */

vetor_3d Pb = Hs.intersec_plano_reta(Ps, S, Hb.normal, d);

/* std::cout << "Coordenadas de Pb:" << std::endl; */
/* Pb.log_coords(); */
/* std::cout << " ----------------- " << std::endl; */

is_inside = Hb.check_if_picked_point_is_inside_mirror(Pb);

if (is_inside) {count_yes++;}
else{ count_no++;}

}

std::cout << "Total de yes:" << count_yes << std::endl;

std::cout << "Total de no:" << count_no << std::endl;

	return 0;
}
