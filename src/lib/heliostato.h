#ifndef HELIOSTATO_H_JNBGHR0W
#define HELIOSTATO_H_JNBGHR0W

#include "bare_functions.h"
#include "transm_functions.h"

class Heliostato {
	public:
		//posição da base do heliostato e altura do eixo vertical são determinadas no construtor

		float vert_axis_height;
		float mirror_height;//espelho retangular
		float mirror_width;
		float d;
		vetor_3d mirror_center_position;

		//normal e ângulos azim e zenital são calculados no método 'set_normal'
		vetor_3d normal;
		float azim;
		float zenit;

		//versores que expandem o plano do espelho:
		vetor_3d vector_eta;
		vetor_3d vector_xi;

		//dados necessários para estabelecer o movimento obtidos com medição em sensor (potenciômetro):
		float measured_azim;
		float measured_zenit;
		float delta_azim;
		float delta_zenit;

		Heliostato();
		Heliostato(float x, float y, float z, float vert_axis_height, float mirror_height, float mirror_width);
		Heliostato(vetor_3d base_pos, float vert_axis_height, float mirror_height, float mirror_width);

		vetor_3d base_pos;
		void set_normal(vetor_3d sun_pos, vetor_3d focus_pos);
		void set_eta_vec();
		void set_xi_vec();
		void set_base_pos(float bpx, float bpy, float bpz);
		float calculate_d();
		void calculate_D();

		//os parâmetros eta_par_unit e xi_par_unit devem ser fornecidos com valores entre 0 e 1
		vetor_3d pick_point_inside_mirror_region(float eta_par_unit, float xi_par_unit);

		//troca de informações com sensores:
		void measure_angles();
		void set_movements(vetor_3d normal);

		//calcula a intersenção de um plano com uma reta (retorna um vetor 3d)
		vetor_3d intersec_plano_reta(vetor_3d vetor_origem_da_reta, vetor_3d sun_direction, vetor_3d normal_do_espelho_cortado_pela_reta, float d);

		bool check_if_picked_point_is_inside_mirror(vetor_3d point, bool print);
};

#endif /* end of include guard: HELIOSTATO_H_JNBGHR0W */
