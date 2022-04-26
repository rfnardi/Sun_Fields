#include <ostream>
#include <stdio.h>
#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323846
#define J_0 1367

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
		float result = 0.0;
		for (short i=0; i<3; i++) {
			result += this->coord[i] * vetor_2.coord[i];
		}
		return result;
	}

	void log_coords(){
		std::cout << "Coordenada x: "<< this->coord[0] << std::endl;
		std::cout << "Coordenada y: "<< this->coord[1] << std::endl;
		std::cout << "Coordenada z: "<< this->coord[2] << std::endl;
	}
};

float * sin_Alt_sin_Azim_calculation(int NDA, float lat, float local_time){

	float hora_local = local_time;
	float hor_rad = ang_hor_rad(hora_local);

	float lat_rad = deg_to_rad(lat);

	float decl_rad = decl_calculation(NDA);

	float sin_Alt = sin(lat_rad)*sin(decl_rad) + cos(lat_rad)*cos(decl_rad)*cos(hor_rad); //THIS GUY
	float cos_Alt = sqrt(1 - pow(sin_Alt,2));

	//ângulo/distância zenital é o complementar da altura Alt
	/* float zen = acos(sin_Alt); */

	float sin_Azim = cos(decl_rad)*sin(hor_rad)/cos_Alt;  //AND THIS GUY
	/* float cos_Azim = sqrt(1 - pow(sin_Azim,2)); */

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
	std::cout << "Valor da Projeção leste-oeste: "<< s.coord[0] << std::endl; //positivo ao leste
	std::cout << "Valor da Projeção norte-sul: "<< s.coord[1] << std::endl; //positivo ao norte
}

vetor_3d get_normal_vector(vetor_3d s, vetor_3d r){

	float prod_escalar = s.scalar_prod(r);
	/* std::cout << "Valor do produto escalar: "<< prod_escalar << std::endl; */
	float denominador = sqrt(2)*sqrt(1 - prod_escalar);
	/* std::cout << "valor do denominador: "<< denominador << std::endl; */
	float n[3];
	for (short i = 0; i < 3; i++) {
		n[i] = (s.coord[i] - r.coord[i])/denominador; 
	}

	static vetor_3d normal_vector(n[0],n[1],n[2]);

	return normal_vector;
}

vetor_3d get_unitary_vector(vetor_3d v){
	float v_hat[3];
	for (short i = 0; i < 3; ++i) {
		v_hat[i] = v.coord[i]/v.scalar_prod(v); 
	}
	static vetor_3d unitary(v_hat[0],v_hat[1],v_hat[2]);

	return unitary;
}

//calcula a correção na constante solar devido à variação na distância Terra-Sol ~ (d/D)^2
float J_elliptic_correction(int NDA){ 
	float J = J_0*(1 + 0.033*cos(deg_to_rad(360*NDA/365.25)));
	return J;
}

//distância de atmosfera cortada pelo raio de luz em termos do ângulo zenital
float atm_cross_distance(float zenital_angle){ 
	float A = 12000; //12 km
	float R_t = 12700000; //12.700 km

	return (pow(A,2) + 2*A*R_t)/(2*R_t*cos(zenital_angle));
}

float refl_power_from_scalar_product(vetor_3d n, vetor_3d s, float J){
	float power = 0.47*J*n.scalar_prod(s);

	return power;
}

float one_mirror_power(vetor_3d s, vetor_3d R, int NDA){
	/* std::cout << "Coordenadas de s unitário:" << std::endl; */
	/* s.log_coords(); */

	vetor_3d r = get_unitary_vector(R);
	/* std::cout << "Coordenadas de r unitário:" << std::endl; */
	/* r.log_coords(); */

	vetor_3d n = get_normal_vector(s, r);
	/* std::cout << "Coordenadas do vetor normal à superfície n unitário:" << std::endl; */
	/* n.log_coords(); */

	float J = J_elliptic_correction(NDA);
	/* std::cout << "Valor de J: "<< J << std::endl; */

	float power = refl_power_from_scalar_product(n, s, J);
	/* std::cout << "Valor de power: "<< power << std::endl; */

	return power;
}

int main()
{
	int NDA = NDA_calculation(24,3);
	float lat = -18.9051; //Jaguaré em graus
	/* float lat = -14.7973; //Ilhéus em graus */

	vetor_3d R(0,-12,0); //espelho localizado a 12 metros ao sul do ponto focal

	float * sin_Alt_sin_Azim_Array;
	float power;
	float hora_local = 8.0;
	vetor_3d s(0,0,0);
	while(hora_local<18){
		sin_Alt_sin_Azim_Array = sin_Alt_sin_Azim_calculation(NDA, lat, hora_local);
		s = sun_pos_in_cartesian_coord(sin_Alt_sin_Azim_Array);
		power = one_mirror_power(s, R, NDA);
		std::cout << "Hora local: "<< hora_local ;
		std::cout << "\t ; Projeção vertical do sol: " << s.coord[2] ; 
		std::cout << "\t ; Potência: "<< power << std::endl;
		hora_local += 1;
	}

	/* log_entrada(NDA, lat, hora_local); */
	/* log_angulos(sin_Alt_sin_Azim_Array); */
	/* log_sun_position(s); */



	return 0;
}
