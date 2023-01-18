#include "bare_functions.h"

float dry_air_opt_mass(float theta_z);

float water_vapor_opt_mass(float theta_z);

//Fonte original: equation 5.4.6 Iqbal
float preciptable_water(float rel_air_humid, float temp_Kelvin);

float pressure_given_by_altitude(float altitude);

//equation 5.7.3 Iqbal
float m_a_calc(float pressure, float m_r);

float k_Rayleigh_dry_air_scattering_lambda(float lambda);

float k_Mie_water_droplets_scattering_lambda(float lambda);

float k_Mie_dust_scattering_lambda(float lambda);

//d: amount of dust particles in a cm^3 (200 is clean air; 800 is very dirty air)
//w: preciptable water 
float scattering_transm_lambda(float lambda, float theta_z, float w, float d, float altitude);

float gas_mix_absorp_transm_lambda(float lambda, float theta_z, float altitude);

float water_vapor_absorp_transm_lambda(float lambda, float theta_z, float altitude, float w);

float ozone_absorp_transm_lambda(float lambda, float theta_z);

float absorp_transm_lambda(float lambda, float theta_z, float w, float d, float altitude);

float total_transmitance(float lambda, float theta_z, float w, float d, float altitude);

//Esta função dá o espectro de corpo negro.
//Vamos preferir usar a versão experimental/tabelada 
//da distribuição de potência de radiação do sol: função table_given_irradiance
float planck_distribution(float T_kelvin, float lambda_microns);


//d: quantidade de partículas de poeira em suspensão por cm^3.
//d == 200 é ar limpo. 
//d == 800 é ar muito sujo.
float corrected_irradiance(int NDA, float lat, float local_time, float rel_air_humid, float altitude, float d, float temp_Kelvin);

//potência refletida por um espelho de area mirror_area
//localizado na posição R
//quando a posição do sol for s
//e quando o foco for Focus
float one_mirror_corrected_power(vetor_3d s, vetor_3d R, vetor_3d Focus, float J, float mirror_area);

class Heliostato {
	public:
		//posição do heliostato é determinada no construtor
		vetor_3d pos;

		//normal e ângulos azim e zenital são calculados no método 'set_normal'
		vetor_3d normal;
		float azim;
		float zenit;

		//dados necessários para estabelecer o movimento:
		float mesured_azim;
		float measured_zenit;
		float delta_azim;
		float delta_zenit;

		Heliostato(float x, float y, float z);
		void set_normal(vetor_3d sun_pos, vetor_3d focus_pos);

		//troca de informações com o arduino:
		void measure_angles();
		void set_movements(vetor_3d normal);

};
