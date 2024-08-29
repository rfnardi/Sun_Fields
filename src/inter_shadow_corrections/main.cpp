#include <iostream>
#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"

int main(){

	float vert_axis_height = 1.0;

Heliostato Hs(0, -20, 0, vert_axis_height, 1.0, 1.0);
Heliostato Hb(0, -18, 0, vert_axis_height, 1.0, 1.0);

std::cout << "Coordenadas do ponto central do espelho Hs:" << std::endl;
vetor_3d mirror_center_position(Hs.base_pos.coord[0], Hs.base_pos.coord[1] , Hs.base_pos.coord[2] + vert_axis_height);
mirror_center_position.log_coords();

vetor_3d Ps;
vetor_3d S(0,0.4,0.1); // sun position
S.get_unitary_vector();
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

Ps = Hs.pick_point_inside_mirror_region(0.5,0.5, Ps);

std::cout << "Coordenadas de Ps:" << std::endl;
Ps.log_coords();
std::cout << " ----------------- " << std::endl;
vetor_3d Pb = Hs.intersec_plano_reta(Ps, S, Hb.normal, d);
std::cout << "Coordenadas de Pb:" << std::endl;
Pb.log_coords();
std::cout << " ----------------- " << std::endl;

bool is_inside = Hb.check_if_picked_point_is_inside_mirror(Pb);

std::cout << "Ponto está dentro do espelho? Answear:" << is_inside << std::endl;

	return 0;
}
