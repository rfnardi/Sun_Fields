#include <iostream>
#include <stdio.h>
#include "../lib/bare_functions.h"
#include <vector>

int main()
{
	int NDA = NDA_calculation(25,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	float power = 0.0;
	float hora_local = 12.0;
	vetor_3d mirror_place(0,0,0);
	float south_distance = 10.0;
	float x_pos = -100.0;
	vetor_3d s(0,0,0);
	s = get_sun_position(NDA, lat, hora_local,s);
	std::cout << "x_pos" << ";" << "power" << std::endl;
	while (x_pos < 100.1) {
		mirror_place.reset_coord(x_pos,-south_distance,0.0);
		power = one_mirror_power(s, mirror_place, NDA);
		std::cout << x_pos << ";" << power << std::endl;
		x_pos += 0.1;
	}


	return 0;
}
