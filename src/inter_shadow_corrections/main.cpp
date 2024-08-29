#include <iostream>
#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"

int main(){

Heliostato Hs(0, -20, 0, 1.0, 1.0, 1.0);
Heliostato Hb(0, -18, 0, 1.0, 1.0, 1.0);

vetor_3d Ps;
vetor_3d S(0,1,0.5); // sun position
vetor_3d F(0,0,20); // focus position

Hs.set_normal(S, F);
Hb.set_normal(S, F);

Hs.set_eta_vec();
Hs.set_xi_vec();
Hb.set_eta_vec();
Hb.set_xi_vec();

std::cout << "Normal do espelho Hs:" << std::endl;
Hs.normal.log_coords();

std::cout << "Normal do espelho Hb:" << std::endl;
Hb.normal.log_coords();

float d = Hs.calculate_d();

Ps = Hs.pick_point_inside_mirror_region(0.2,0.5, Ps);

std::cout << "Coordenadas de Ps:" << std::endl;

Ps.log_coords();

std::cout << " ----------------- " << std::endl;

vetor_3d Pb = Hs.intersec_plano_reta(Ps, S, Hs.normal, d);

std::cout << "Coordenadas de Pb:" << std::endl;

Pb.log_coords();

std::cout << " ----------------- " << std::endl;

bool is_inside = Hb.check_if_picked_point_is_inside_mirror(Pb);

std::cout << "Ponto está dentro do espelho? Answear:" << is_inside << std::endl;

	return 0;
}
