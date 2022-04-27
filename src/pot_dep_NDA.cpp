#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "./all_functions.cpp"
#include <vector>

int main()
{
	int NDA = NDA_calculation(25,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	vetor_3d R(0,-10,0); 

	float *sin_Alt_sin_Azim_Array = new float[2]{0.0,0.0};
	float power = 0.0;
	float hora_local = 12.0;

	vetor_3d s(0,0,0);

	float zen = 0.0;
	float zen2 = 0.0;
	std::cout << "NDA" << ";" << "POWER" << ";" << "ZEN" << ";" << "ZEN2" << ";" << "S_z" << std::endl;

	for (NDA = 1; NDA<=365; NDA++){
		sin_Alt_sin_Azim_Array = sin_Alt_sin_Azim_calculation(NDA, lat, hora_local, sin_Alt_sin_Azim_Array);
		zen = acos(sin_Alt_sin_Azim_Array[0]);
		std::cout << "---------" << std::endl;
		std::cout << "Array: "<< *sin_Alt_sin_Azim_Array <<" ; "<< *sin_Alt_sin_Azim_Array + 1 << std::endl;
		s =	sun_pos_in_cartesian_coord(sin_Alt_sin_Azim_Array, s); //problema nesta função!!!
		std::cout << "Array: "<< *sin_Alt_sin_Azim_Array <<" ; "<< *sin_Alt_sin_Azim_Array + 1 << std::endl;
		power = one_mirror_power(s, R, NDA);
		zen2 = acos(sin_Alt_sin_Azim_Array[0]);
		/* zen = acos(s.coord[2]); */
		/* std::cout << NDA << ";" << power << ";" << zen << ";" << zen2 << ";"<< s.coord[2] << std::endl; */
	}

	/* log_angulos(sin_Alt_sin_Azim_Array); */
	/* log_sun_position(s); */

	delete [] sin_Alt_sin_Azim_Array ;

	return 0;
}
