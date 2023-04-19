#ifndef HELIOSTATO_H_JNBGHR0W
#define HELIOSTATO_H_JNBGHR0W

#include "bare_functions.h"
#include "transm_functions.h"

class Heliostato {
	private:
		//posição da base do heliostato e altura do eixo vertical são determinadas no construtor
		vetor_3d base_pos;
		float vert_axis_height;
		float mirror_height;//espelho retangular
		float mirror_width;

		//normal e ângulos azim e zenital são calculados no método 'set_normal'
		vetor_3d normal;
		float azim;
		float zenit;

		//dados necessários para estabelecer o movimento obtidos com medição em sensor (potenciômetro):
		float measured_azim;
		float measured_zenit;
		float delta_azim;
		float delta_zenit;

		//os parâmetros eta_par_unit e xi_par_unit devem ser fornecidos com valores entre 0 e 1
		vetor_3d pick_point_inside_mirror_region(float eta_par_unit, float xi_par_unit);

	public:
	    Heliostato();
		Heliostato(float x, float y, float z, float vert_axis_height, float mirror_height, float mirror_width);
		Heliostato(vetor_3d base_pos, float vert_axis_height, float mirror_height, float mirror_width);
		void set_normal(vetor_3d sun_pos, vetor_3d focus_pos);
		void Setpick_point_inside_mirror_region(float eta_par_unit, float xi_par_unit);

		//troca de informações com sensores:
		void measure_angles();
		void set_movements(vetor_3d normal);

};


#endif /* end of include guard: HELIOSTATO_H_JNBGHR0W */
