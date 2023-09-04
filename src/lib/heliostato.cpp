#include <iostream>
#include "./heliostato.h"
#include "./bare_functions.h"
#include <cmath>

Heliostato::Heliostato(){
	this->base_pos.coord[0] = 0;
	this->base_pos.coord[1] = 0;
	this->base_pos.coord[2] = 0;
}

void Heliostato::set_point_inside_mirror_region(float eta_par_unit, float xi_par_unit){
	float parameters[] = {eta_par_unit, xi_par_unit};
		
	
		std::cout << "set_point_inside_mirror_region parameters: " << parameters << std::endl;
	return;
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
	
	std::cout << "normal x: " << normal_x << std::endl;
	std::cout << "normal y: " << normal_y << std::endl;
	std::cout << "zenital: " << zenit << std::endl;
	 std::cout << "azimutal: " << zenit << std::endl;
	 
	 return;// alteração
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
contruir função que calcaula a intersenção de um plano com uma reta (retorna um vetor 3d)
*/
vetor_3d Heliostato::intersec_plano_reta(vetor_3d vetor_origem_da_reta, vetor_3d sun_direction, vetor_3d normal_do_espelho_cortado_pela_reta, float d){

	//vetor_3d result_p;

	// equação da reta:
	// bi-dimensional: y = a*x + b 
	// 3-dimensional: (v_x, v_y, v_z)*t + V_o = p 
	// Plano:
	// a*x + b*y + c*z + d = 0 
	// onde a, b e c são as componentes da normal do plano. E d é a constante que dá a altura plano.
	//
	// Afirmação: p é um ponto do plano!
	// componente x de p: v_x*t + vetor_origem_x
	// componente y de p: v_y*t + vetor_origem_y
	// componente z de p: v_z*t + vetor_origem_z
	// a*(v_x*t + V_o_x) + b*(v_y*t + V_o_y) + c*(v_z*t + V_o_z) + d = 0 ---> encontrar o valor de t ---> escrever o valor de p.
	//

	normal_do_espelho_cortado_pela_reta; //a,b,c,d
	vetor_origem_da_reta; //x,y,z
    sun_direction; //t_x,t_y,t_z

	//calcula o valor de t
	float A = normal_do_espelho_cortado_pela_reta.scalar_prod(sun_direction);
	float B = normal_do_espelho_cortado_pela_reta.scalar_prod(vetor_origem_da_reta);
	float t = -(-d + B)/A;

	// calcula o ponto P em que a reta corta o plano do espelho:
    sun_direction.multiply_by_scalar(t);
	vetor_3d P;
   // vetor_origem_da_reta.vector_sum(sun_direction, P);
for (short i=0; i<3; i++) {
		P.coord[i]= vetor_origem_da_reta.coord[i] * sun_direction.coord[i];
	}
	return P;
}

//Criar função que verifica se os pontos estão no interior da região do espelho.
//saber as dimenções do espelho
//se distancia
