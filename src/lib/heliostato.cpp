
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
vetor_3d Heliostato::pick_point_inside_mirror_region(float eta_par_unit, float xi_par_unit, vetor_3d result){

	//setting local base versors (eta and xi):
	vetor_3d eta;

	{
		float eta_x = 1/sqrt(1-std::pow(normal.coord[0]/normal.coord[1],2));
		float eta_y = -(normal.coord[0]/normal.coord[1])*eta_x;

		eta.reset_coord(eta_x, eta_y, 0);
		eta.get_unitary_vector();
	}

	vetor_3d xi;
	xi = vector_product(normal, eta, xi);
	xi.get_unitary_vector();

	vetor_3d mirror_center_pos = this->base_pos;
	mirror_center_pos.coord[2] = mirror_center_pos.coord[2] + this->vert_axis_height;

	float eta_par = this->mirror_width*(eta_par_unit - 0.5);
	float xi_par = this->mirror_height*(xi_par_unit - 0.5);

	eta.multiply_by_scalar(eta_par);
	xi.multiply_by_scalar(xi_par);

	/* vetor_3d result; */

	result = mirror_center_pos.vector_sum(eta, result);
	result = result.vector_sum(xi, result);

	return result;
}
