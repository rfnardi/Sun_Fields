#include <iostream>

#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"
/* #include "~/repos/Sun_Fields/src/lib/bare_functions.h" */

int main(){

Heliostato hs;
Heliostato hb;
hs.set_base_pos(0, -20, 0);
hs.vert_axis_height = 1.0;
hb.set_base_pos(0, -10, 0);
hb.vert_axis_height = 1.0;

vetor_3d Ps;
vetor_3d S(0,1,1);
vetor_3d F(0,0,40);

hs.set_normal(S, F);

Ps = hs.pick_point_inside_mirror_region(0.2,0.5, Ps);

vetor_3d Pb = hs.intersec_plano_reta(Ps, S, hs.normal, float d)



	return 0;
}
