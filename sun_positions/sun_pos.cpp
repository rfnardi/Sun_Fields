#include <ostream>
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

float decl_calculation(int NDA){ //a declinação mede o ângulo da linha Terra-Sol com o plano do equador

	float angulo_rad = deg_to_rad(360*(NDA - 80)/365.25); //dia 80 é o 21 de março: equinócio de outono
	float decl = 23.45*sin(angulo_rad); //em graus
	return deg_to_rad(decl);
}

class vetor_3d {
	public:
	float coord[3];

	vetor_3d(float v_x, float v_y, float v_z){
		this->coord[0] = v_x;	
		this->coord[1] = v_y;	
		this->coord[2] = v_z;	
	}
	
	float scalar_prod(vetor_3d vetor_2){
		float square = 0.0;
		for (short i=0; i<3; i++) {
			square += this->coord[i] * vetor_2.coord[i];
		}
		return sqrt(square);
	}
};

float * sin_Alt_sin_Azim_calculation(int NDA, float lat, float local_time){

	float hora_local = local_time;
	float hor_rad = ang_hor_rad(hora_local);

	float lat_rad = deg_to_rad(lat);

	float decl_rad = decl_calculation(NDA);

	float sin_Alt = sin(lat_rad)*sin(decl_rad) + cos(lat_rad)*cos(decl_rad)*cos(hor_rad); //#############
	float cos_Alt = sqrt(1 - pow(sin_Alt,2));
	//ângulo/distância zenital é o complementar da altura Alt
	float zen = acos(sin_Alt);

	float sin_Azim = cos(decl_rad)*sin(hor_rad)/cos_Alt;  //#############
	float cos_Azim = sqrt(1 - pow(sin_Azim,2));

	static float result[2] = {sin_Alt, sin_Azim};

	return result;
}

vetor_3d sun_pos_in_cartesian_coord(float * sin_Alt_sin_Azim_Array){

	float sin_Alt = sin_Alt_sin_Azim_Array[0];
	float sin_Azim = sin_Alt_sin_Azim_Array[1];
	float cos_Alt = sqrt(1 - pow(sin_Alt,2));
	float cos_Azim = sqrt(1 - pow(sin_Azim,2));

	//posição do sol em coordenadas cartezianas:
	float s_z = sin_Alt;
	float s_x = cos_Alt*sin_Azim; //projeção leste-oeste (positivo se ao leste)
	float s_y = cos_Alt*cos_Azim; //projeção norte-sul (positivo se ao norte)

	static vetor_3d s(s_x, s_y, s_z);

	return s;
}

void log_entrada(int NDA, float latitude, float local_time){
	
	std::cout << "Latitude: " << latitude << std::endl;
	std::cout << "Hora local: " << local_time << std::endl;
	std::cout << "NDA: "<< NDA << std::endl;
}

void log_angulos(float * sin_Alt_sin_Azim_Array ){
	std::cout << "Valor do Azimute: "<< asin(sin_Alt_sin_Azim_Array[1]) << std::endl;
	std::cout << "Valor do ângulo Zenital: "<< acos(sin_Alt_sin_Azim_Array[0]) << std::endl;
}

void log_sun_position(vetor_3d s){
	std::cout << "Valor da Projeção vertical: "<< s.coord[2] << std::endl;
	std::cout << "Valor da Projeção leste-oeste: "<< s.coord[0] << std::endl;
	std::cout << "Valor da Projeção norte-sul: "<< s.coord[1] << std::endl;
}

int main()
{
	int NDA = NDA_calculation(24,3);
	float hora_local = 17.693;
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	float * sin_Alt_sin_Azim_Array = sin_Alt_sin_Azim_calculation(NDA, lat, hora_local);

	vetor_3d s = sun_pos_in_cartesian_coord(sin_Alt_sin_Azim_Array);

	vetor_3d r(s.coord[0], s.coord[1], s.coord[2]);

	float norma = s.scalar_prod(r);

	log_entrada(NDA, lat, hora_local);
	log_angulos(sin_Alt_sin_Azim_Array);
	log_sun_position(s);

	std::cout << "Testando cálculo da Norma: "<< norma << std::endl;

	return 0;
}
