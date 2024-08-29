#ifndef HELIOSTATO_CPP
#define HELIOSTATO_CPP

#include <iostream>
#include "./heliostato.h"
#include "./bare_functions.h"
#include <cmath>

Heliostato::Heliostato(){
	this->base_pos.coord[0] = 0;
	this->base_pos.coord[1] = 0;
	this->base_pos.coord[2] = 0;
}

Heliostato::Heliostato(float x, float y, float z, float vert_axis_height, float mirror_height, float mirror_width){
	this->base_pos.coord[0] = x;
	this->base_pos.coord[1] = y;
	this->base_pos.coord[2] = z;

	this->vert_axis_height = vert_axis_height;
	this->mirror_height = mirror_height;
	this->mirror_width = mirror_width;

	//dados necessários para estabelecer o movimento (all set to 0):
	this->measured_azim = 0.0;
	this->measured_zenit = 0.0;
	this->delta_azim = 0.0;
	this->delta_zenit = 0.0;
}

Heliostato::Heliostato(vetor_3d base_pos, float vert_axis_height, float mirror_height, float mirror_width){
	this->base_pos = base_pos;
	this->vert_axis_height = vert_axis_height;
	this->mirror_height = mirror_height;
	this->mirror_width = mirror_width;

	//dados necessários para estabelecer o movimento (all set to 0):
	this->measured_azim = 0.0;
	this->measured_zenit = 0.0;
	this->delta_azim = 0.0;
	this->delta_zenit = 0.0;
}

//calcula a normal do espelho e os ângulos azimutal e zenital teóricos
void Heliostato::set_normal(vetor_3d sun_pos, vetor_3d focus_pos){
	vetor_3d mirror_pos = this->base_pos;
	mirror_pos.coord[2] = mirror_pos.coord[2] + vert_axis_height;
	this->normal = get_normal_vector(sun_pos, mirror_pos, focus_pos, this->normal);
	//projeção no plano xy:
	float normal_x = this->normal.coord[0];
	float normal_y = this->normal.coord[1];
	float norm_2d = sqrt(std::pow(normal_x,2) + std::pow(normal_y,2));
	normal_x = normal_x/norm_2d;
	normal_y = normal_y/norm_2d;

	if (normal_x > 0) { std::acos(normal_y); }//vetor 2_dim no hemisfério leste
	else if (normal_x < 0) { this->azim = (-1)*std::acos(normal_y) ;}//vetor 2_dim no hemisf oeste
	else { this->azim = 0.0; }

	this->zenit = std::acos(this->normal.coord[2]);

	/* std::cout << "normal x: " << normal_x << std::endl; */
	/* std::cout << "normal y: " << normal_y << std::endl; */
	/* std::cout << "zenital: " << zenit << std::endl; */
	/* std::cout << "azimutal: " << zenit << std::endl; */

}

float Heliostato::calculate_d(){
	vetor_3d mirror_center_pos, vector_height;

	mirror_center_pos.reset_coord(this->base_pos.coord[0], this->base_pos.coord[1], this->base_pos.coord[2] + this->mirror_height);

float d;

	d = - this->normal.scalar_prod(mirror_center_pos);

	return d;
}

void Heliostato::set_eta_vec(){
	float theta_eta = std::atan(- this->normal.coord[0]/this->normal.coord[1]);

	vetor_3d eta(std::sin(theta_eta), std::cos(theta_eta), 0);

	this->vector_eta = eta;
}

void Heliostato::set_xi_vec(){
	vetor_3d xi;
	xi = vector_product(this->normal, this->vector_eta, this->vector_xi);

	this->vector_xi = xi;
}

void Heliostato::set_base_pos(float bpx, float bpy, float bpz){
	this->base_pos.reset_coord(bpx, bpy, bpz);
}

void Heliostato::set_movements(vetor_3d normal){
	this->delta_azim = this->azim - this->measured_azim;
	this->delta_zenit = this->zenit - this->measured_zenit;
	//após calcular os valores dos deltas, enviá-los ao arduino para acionar os motores
}

// mexer nesse método para captar dados do potenciômetro com o arduino
void Heliostato::measure_angles(){
	this->measured_zenit = 0.0;
	this->measured_azim = 0.0;
}

//os parâmetros eta_unit e xi_unit devem ser fornecidos com valores entre 0 e 1
//eta_par_unit e xi_par_unit: localização do ponto dentro do espelho
// recebe como parametro uma coordenada bidimensional e retorna a localização tridimensional deste ponto
vetor_3d Heliostato::pick_point_inside_mirror_region(float eta_par_unit, float xi_par_unit, vetor_3d result){

	//setting local base versors (eta and xi): 
	//eta e xi formam uma base que expande o espaço linear do plano em que o espelho se encontra
	vetor_3d eta;

	{
		//coordenada x do vetor eta está sendo calculada como: 1 / sqrt(1 - (n_0/n_1)^2)
		//eta é um vetor puramente na horizontal. Portanto possui coordenada z nula.
		//eta é ortogonal à normal do espelho 
		//eta é unitário
		float eta_x = 1/sqrt(1+std::pow(this->normal.coord[0]/this->normal.coord[1],2));
		float eta_y = -(this->normal.coord[0]/this->normal.coord[1])*eta_x;

		eta.reset_coord(eta_x, eta_y, 0);
		eta.get_unitary_vector();
	}

	vetor_3d xi;
	xi = vector_product(this->normal, eta, xi);
	xi.get_unitary_vector();

	vetor_3d mirror_center_pos = this->base_pos;//armazena a posição do centro do espelho
	mirror_center_pos.coord[2] = mirror_center_pos.coord[2] + this->vert_axis_height;// vert_axis_height:altura do heliostato

	//translação da origem do sistema de coordenadas dentro do plano:
	//transformando as coordenadas que vão de 0-1 para coordenadas que vão de -1/2 a 1/2
	float eta_par = this->mirror_width*(-1 + 2*eta_par_unit)/2;
	float xi_par = this->mirror_height*(-1 + 2*xi_par_unit)/2;

	eta.multiply_by_scalar(eta_par);
	xi.multiply_by_scalar(xi_par);

	result = mirror_center_pos.vector_sum(eta, result);
	result = result.vector_sum(xi, result);

	return result;
}

/*
	 Construir reta ao longo da direção dos raios do sol a partir do ponto de um dos espelhos, ver onde essa reta cruza o plano de outro espelho.
	 contruir função que calcaula a intersecção de um plano com uma reta (retorna um vetor 3d)
	 */
vetor_3d Heliostato::intersec_plano_reta(vetor_3d vetor_origem_da_reta, vetor_3d sun_direction, vetor_3d normal_do_espelho_cortado_pela_reta, float d){

	//vetor_3d result_p;

	// straight line equation:
	// bi-dimensional: y = a*x + b 
	// 3-dimensional: (v_x, v_y, v_z)*t + V_o = p 
	// Plane equation:
	// a*x + b*y + c*z + d = 0 
	// onde a, b e c são as componentes da normal do plano. E d é a constante que dá a altura plano.
	//
	// Afirmação: p é um ponto do plano!
	// componente x de p: v_x*t + vetor_origem_x
	// componente y de p: v_y*t + vetor_origem_y
	// componente z de p: v_z*t + vetor_origem_z
	// a*(v_x*t + V_o_x) + b*(v_y*t + V_o_y) + c*(v_z*t + V_o_z) + d = 0 ---> encontrar o valor de t ---> escrever o valor de p.

	/* normal_do_espelho_cortado_pela_reta; //a,b,c,d */
	/* vetor_origem_da_reta; //x,y,z */
	/* sun_direction; //t_x,t_y,t_z */

	//calcula o valor de t
	float A = normal_do_espelho_cortado_pela_reta.scalar_prod(sun_direction);
	float B = normal_do_espelho_cortado_pela_reta.scalar_prod(vetor_origem_da_reta);
	float t = (d - B)/A;

	// calcula o ponto P em que a reta corta o plano do espelho:
	sun_direction.multiply_by_scalar(t);
	vetor_3d P;
	// vetor_origem_da_reta.vector_sum(sun_direction, P);
	for (short i=0; i<3; i++) {
		P.coord[i]= vetor_origem_da_reta.coord[i] * sun_direction.coord[i];
	}
	return P;
}

//Criar função que verifica se o ponto está no interior da região do espelho.
//saber as dimensões do espelho

bool Heliostato::check_if_picked_point_is_inside_mirror(vetor_3d point){

	// primeiro a função deve calcular o valor dos parametros xi e eta.
	float xi = this->vector_xi.scalar_prod(point);
	float eta = this->vector_eta.scalar_prod(point);

	// em seguida aplica uma condição que verifica se os valores dos parâmetros
	// são os de um ponto no interior do espelho
	bool result;
	if ((- this->mirror_height/2 < xi && xi < this->mirror_height/2) && (- this->mirror_width/2 < eta && eta < this->mirror_width/2)) {
		result = 1;	
	}
	else{
		result = 0;
	}

	return result;
}


#endif /* end of include guard: HELIOSTATO_CPP */
