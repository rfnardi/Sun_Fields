#include <iostream>
#include <random>
#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"

int main() {

	// definir um heliostato
	float vert_axis_height = 0.0;
	Heliostato H(0, 0, 0, vert_axis_height, 1.0, 1.0);

	vetor_3d Sun(0,0,1);

	H.set_normal(Sun, Sun);
	H.set_eta_vec();
	H.set_xi_vec();

	vetor_3d P(0,0,0);
	
	bool result = H.check_if_picked_point_is_inside_mirror(P);

	std::cout << "Normal: " << std::endl;

	H.normal.log_coords();

	std::cout << "Ponto está dentro? Resposta:" << result << std::endl;

	return 0;
}
