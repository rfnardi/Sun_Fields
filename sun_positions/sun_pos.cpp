#include <stdio.h>
#include <iostream>
#include <cmath>
# define M_PI 3.14159265358979323846

int NDA_calculation(int month_day, int month){

	int month_size[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	/* int month_day = 24; */
	/* int month = 3; */

	int NDA = 0;
	for (short i = 0; i < month; ++i) {
		NDA += month_size[i];
	}

	NDA += month_day;

	return NDA;
}

int main()
{
	float Azim, Zen, Alt, decl, lat, hor, hora_local;
	
	int NDA = NDA_calculation(24,3);

	hora_local = 17.514;
	hor = (12 - hora_local)*15; //em graus 
	float rad_hor = 2*M_PI*hor/360; //em radianos

	lat = -18.9051; //Jaguaré em graus
	/* lat = -14.7973; //Ilhéus */
	float rad_lat = 2*M_PI*lat/360; //em radianos

	decl = 23.45*sin(360*(NDA -80)/365.25); //em graus
	float rad_decl = 2*M_PI*decl/360; //em radianos

	float sin_Alt = sin(rad_lat)*sin(rad_decl) + cos(rad_lat)*cos(rad_decl)*cos(rad_hor);
	float cos_Alt = sqrt(1 - pow(sin_Alt,2));

	float sin_Azim = cos(rad_decl)*sin(rad_hor)/cos_Alt;
	float cos_Azim = sqrt(1 - pow(sin_Azim,2));

	//posição do sol em coordenadas cartezianas:
	float s_z = sin_Alt;
	float s_x = cos_Alt*sin_Azim; //projeção leste-oeste
	float s_y = cos_Alt*cos_Azim; //projeção norte-sul


	std::cout << "NDA: "<< NDA << std::endl;
	std::cout << "Valor do Azimute: "<< asin(sin_Azim) << std::endl;
	std::cout << "Valor do ângulo Zenital: "<< acos(sin_Alt) << std::endl;
	std::cout << "Valor da Projeção vertical: "<< s_z << std::endl;
	std::cout << "Valor da Projeção leste-oeste: "<< s_x << std::endl;
	std::cout << "Valor da Projeção norte-sul: "<< s_y << std::endl;

	return 0;
}
