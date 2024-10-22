#include <iostream>
#include <random>
#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"

int main() {

	// definir um heliostato
	float vert_axis_height = 0.0;
	Heliostato H(0, -30, 0, vert_axis_height, 1.0, 1.0);

	vetor_3d Sun(0,1,1);
	Sun = Sun.get_unitary_vector();

	vetor_3d Focus(0,0, 20);

	H.set_normal(Sun, Focus);
	std::cout << "Normal: " << std::endl;
	H.normal.log_coords();

	H.set_eta_vec();
	std::cout << "eta coords:" << std::endl;
	H.vector_eta.log_coords();

	H.set_xi_vec();
	std::cout << "xi coords:" << std::endl;
	H.vector_xi.log_coords();

	vetor_3d P(0,-30,1);
	
	bool result = H.check_if_picked_point_is_inside_mirror(P);

	std::cout << "Ponto está dentro? Resposta:" << result << std::endl;

	return 0;
}
