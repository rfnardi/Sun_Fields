#include <iostream>
#include <stdio.h>
#include "../all_functions.cpp"
#include <vector>

int main()
{
	int NDA = NDA_calculation(25,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	float power = 0.0;
	float hora_local = 12.0;
	vetor_3d mirror_place(0,0,0);
	float r = 10.0;
	float theta = M_PI;
	vetor_3d s(0,0,0);
	s = get_sun_position(NDA, lat, hora_local,s);
	std::cout << "theta" << ";" << "power" << std::endl;
	while (theta < 2*M_PI) {
		mirror_place.transf_coord_from_spher_to_cart(r,theta,M_PI/2);
		power = one_mirror_power(s, mirror_place, NDA);
		std::cout << theta << ";" << power << std::endl;
		theta += 0.1;
	}


	return 0;
}
