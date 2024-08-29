#include <iostream>

#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"
#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.cpp"

int main(){

Heliostato Hs;
Heliostato Hb;
Hs.set_base_pos(0, -20, 0);
Hs.vert_axis_height = 1.0;
Hb.set_base_pos(0, -10, 0);
Hb.vert_axis_height = 1.0;

vetor_3d Ps;
vetor_3d S(0,1,1); // sun position
vetor_3d F(0,0,40); // focus position

Hs.set_normal(S, F);

float d = Hs.calculate_d();

Ps = Hs.pick_point_inside_mirror_region(0.2,0.5, Ps);

vetor_3d Pb = Hs.intersec_plano_reta(Ps, S, Hs.normal, d);

bool is_inside = Hb.check_if_picked_point_is_inside_mirror(Pb);

std::cout << "Ponto está dentro do espelho? Answear:" << is_inside << std::endl;

	return 0;
}
