#include <stdio.h>
#include <iostream>
#include <cmath>
# define M_PI 3.14159265358979323846

int NDA_calculation(int month_day, int month){

	int month_size[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int NDA = 0;
	for (short i = 0; i < month; ++i) {
		NDA += month_size[i];
	}
	NDA += month_day;

	return NDA;
}

float deg_to_rad(float deg){ //transforma graus em radianos
	return 2*M_PI*deg/360;
}

float ang_hor_rad(float hora_local){
	
	float ang_hor_deg = (12 - hora_local)*15; //em graus 
	return deg_to_rad(ang_hor_deg);
}

float decl_calculation(int NDA){

	float decl = 23.45*sin(360*(NDA -80)/365.25); //em graus
	return deg_to_rad(decl);
}

class vetor_3d {
	float v_x;
	float v_y; 
	float v_z;

	vetor_3d(float v_x, float v_y, float v_z){
		this->v_x = v_x;	
		this->v_y = v_y;	
		this->v_z = v_z;	
	}
	
	float scalar_prod(vetor_3d vetor_2){
		
		return sqrt(this->v_x * vetor_2.v_x + this->v_y * vetor_2.v_y + this->v_z * vetor_2.v_z);
	}

};

int main()
{
	int NDA = NDA_calculation(24,3);

	float rad_hor = ang_hor_rad(17.514);

	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */
	float rad_lat = deg_to_rad(lat);

	float rad_decl = decl_calculation(NDA);

	float sin_Alt = sin(rad_lat)*sin(rad_decl) + cos(rad_lat)*cos(rad_decl)*cos(rad_hor);
	float cos_Alt = sqrt(1 - pow(sin_Alt,2));
	//ângulo/distância zenital é o complementar da altura Alt
	float zen = acos(sin_Alt);

	float sin_Azim = cos(rad_decl)*sin(rad_hor)/cos_Alt;
	float cos_Azim = sqrt(1 - pow(sin_Azim,2));

	//posição do sol em coordenadas cartezianas:
	float s_z = sin_Alt;
	float s_x = cos_Alt*sin_Azim; //projeção leste-oeste (positivo se ao leste)
	float s_y = cos_Alt*cos_Azim; //projeção norte-sul (positivo se ao norte)


	std::cout << "NDA: "<< NDA << std::endl;
	std::cout << "Valor do Azimute: "<< asin(sin_Azim) << std::endl;
	std::cout << "Valor do ângulo Zenital: "<< zen << std::endl;
	std::cout << "Valor da Projeção vertical: "<< s_z << std::endl;
	std::cout << "Valor da Projeção leste-oeste: "<< s_x << std::endl;
	std::cout << "Valor da Projeção norte-sul: "<< s_y << std::endl;

	return 0;
}
