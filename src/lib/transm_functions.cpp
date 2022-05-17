#include <iostream>
#include <stdio.h>
#include <cmath>
#include "./bare_functions.h"
#include "./table_functions.h"

float dry_air_opt_mass(float theta_z){
	return 1/(cos(theta_z) + 0.15*pow(93.885 - theta_z,-1.253)) ;
}

float water_vapor_opt_mass(float theta_z){
	return 1/(cos(theta_z) + 0.00548*pow(92.650 - theta_z,0-1.452)) ;
}

//Fonte original: equation 5.4.6 Iqbal
float preciptable_water(float rel_air_humid, float temp_Kelvin, float altitude){

	float partial_pressure_water = exp(26.23 - (5416/temp_Kelvin));

	//Iqbal
	//float w = (0.4930*rel_air_humid*partial_pressure_water)/temp_Kelvin;

	//Leckner paper, equations 14, 16 and 20
	float R = 461.51;
	float rho_w0 = (rel_air_humid*partial_pressure_water)/(R*temp_Kelvin);
	// float rho_w(h) = rho_w0*exp(-0.439*altitude); 
	// w é a integral de rho_w(h') dh' de h até \infty
	// cujo resultado é:
	float w = 2.28*rho_w0*exp(0-0.439*altitude);

	return w;
}

float pressure_given_by_altitude(float altitude){
	float sea_level_pressure = 1013.25; //pressão em milibars
	return sea_level_pressure*exp(0-0.0001184*altitude);//altitude em metros
}

//equation 5.7.3 Iqbal
float m_a_calc(float pressure, float m_r){
	return (pressure*m_r)/1013.25;
}

float k_Rayleigh_dry_air_scattering_lambda(float lambda){//lambda aqui sempre está medido em micrômetros
	return 0.0087352*pow(lambda,0-4.08);
}

float k_Mie_water_droplets_scattering_lambda(float lambda){
	return 0.008635*pow(lambda,0-2);
}

float k_Mie_dust_scattering_lambda(float lambda){
	return 0.08128*pow(lambda,0-0.75);
}

//d: amount of dust particles in a cm^3 (200 is clean air; 800 is very dirty air)
//w: preciptable water 
float scattering_transm_lambda(float lambda, float theta_z, float w, float d, float altitude){

	float k_dry_air = k_Rayleigh_dry_air_scattering_lambda(lambda);
	float k_water_droplets = k_Mie_water_droplets_scattering_lambda(lambda);
	float k_dust = k_Mie_dust_scattering_lambda(lambda);
	float m_r = dry_air_opt_mass(theta_z);
	float pressure = pressure_given_by_altitude(altitude);
	float m_a = m_a_calc(pressure, m_r);
	
	float tau_scattering_lambda = exp(0-(k_dry_air*m_a + k_water_droplets*w*m_r + k_dust*(d/800)*m_a));

	return tau_scattering_lambda;
}


float gas_mix_absorp_transm_lambda(float lambda, float theta_z, float altitude){

	float m_r = dry_air_opt_mass(theta_z);
	float pressure = pressure_given_by_altitude(altitude);
	float m_a = m_a_calc(pressure, m_r);

	/* float table_given_gas_mix_k_g(float lambda){ tabela definida de 0.76 a 4.00 microns */
	float k_g = 0.0;
	if(lambda>=0.76 && lambda <= 4.00){
		k_g = table_given_gas_mix_k_g(lambda);
	}
	else { k_g = 0.0; }

	float tau_absorp_lambda = exp(0-(1.41*k_g*m_a)*pow(1+(118.93*k_g*m_a), 0-0.45));

	return tau_absorp_lambda;
}

float water_vapor_absorp_transm_lambda(float lambda, float theta_z, float altitude, float w){

	float m_r = dry_air_opt_mass(theta_z);

	/* float table_given_k_wv(float lambda){ tabela definida de 0.69 a 4.00 microns */
	float k_wv = 0.0;
	if(lambda>=0.690 && lambda <= 4.00){
		k_wv = table_given_k_wv(lambda);
	}
	else { k_wv = 0.0; }

	float tau_absorp_lambda = exp(0-(0.2385*k_wv*w*m_r)*pow(1+(20.07*k_wv*w*m_r), -0.45));

	return tau_absorp_lambda;
}

float ozone_absorp_transm_lambda(float lambda, float theta_z){

	float m_r = dry_air_opt_mass(theta_z);

	/* float table_given_k_O(float lambda){ tabela definida de 0.290 a 0.790 microns */
	float k_O_lambda = 0.0;
	if(lambda>=0.290 && lambda <= 0.790){
		k_O_lambda = table_given_k_O(lambda);
	}
	else { k_O_lambda = 0.0; }

	float tau_absorp_lambda = exp(0-(k_O_lambda*m_r));

	return tau_absorp_lambda;
}

float absorp_transm_lambda(float lambda, float theta_z, float w, float d, float altitude){


	float ozone_transm = ozone_absorp_transm_lambda(lambda, theta_z);
	float wv_aborp_transm = water_vapor_absorp_transm_lambda(lambda, theta_z, altitude, w);
	float gas_mixt_transm = gas_mix_absorp_transm_lambda(lambda, theta_z, altitude);

	float tau_absorp_lambda = ozone_transm*wv_aborp_transm*gas_mixt_transm;

	return tau_absorp_lambda;
}

float total_transmitance(float lambda, float theta_z, float w, float d, float altitude){

	float tau_scattering_lambda = scattering_transm_lambda(lambda, theta_z, w, d, altitude);
	float tau_absorp_lambda = absorp_transm_lambda(lambda, theta_z, w, d, altitude);

	return tau_scattering_lambda*tau_absorp_lambda; //transmitância total da radiação direta de comprimento de onda lambda
}

//Esta função dá o espectro de corpo negro.
//Vamos preferir usar a versão experimental/tabelada 
//da distribuição de potência de radiação do sol: função table_given_irradiance
float planck_distribution(float T_kelvin, float lambda_microns){
	//Iqbal - page 38:
	//"the intensity of radiation of a surface is the rate of energy
	//propagation in a given direction per unit solid angle and per unit area per­
	//pendicular to the axis of the solid angle"
	
	//Potência de radiação emitida por unidade transversa de área no comprimento de onda lambda:
	//http://hyperphysics.phy-astr.gsu.edu/hbase/quantum/radfrac.html#c1
	//na expressão deste site acima aparece a Area multiplicada. 
	//Aqui estamos considerando a potência POR UNIDADE DE ÁREA. Portanto não deve aparecer A.
	// P = 2*pi*h*c^2/(lambda^{5}*(e^{-hc/K*lambda*T} - 1)) 
	

	//2*pi*h*c^2/lambda^5 = 2*pi*(6.62607015)*3*10^2*c/(n^5) = sigma
	//onde lambda = n*10^{-6}
	float sigma = 2*M_PI*(6.62607015)*900000000;

	//h*c/K*lambda = (6.62607015)*3*10/(1.380649*n)
	//onde lambda = n*10^{-6}
	float alpha = (6.62607015)*30/(1.380649);

	//aqui estamos assumindo que o parâmetro lamdba que entra na função já é medido em micrôns. 
	//assim, na expressão abaixo, "lambda = n"
	return (sigma)/(pow(lambda_microns,5)*(exp(-alpha/(T_kelvin*lambda_microns)) - 1)); //dimensão: potência; unidade: watt

}


//d: quantidade de partículas de poeira em suspensão por cm^3.
//d == 200 é ar limpo. 
//d == 800 é ar muito sujo.
float corrected_irradiance(int NDA, float lat, float local_time, float rel_air_humid, float altitude, float d, float temp_Kelvin){
	
	float sin_Alt = sin_Alt_calculation(NDA, lat, local_time);
	float theta_z = acos(sin_Alt);

	float m_r = dry_air_opt_mass(theta_z);
	float pressure =  pressure_given_by_altitude(altitude);
	float m_a = m_a_calc(pressure, m_r);
	float w = preciptable_water(rel_air_humid, temp_Kelvin, altitude );

	float tau_lambda  = 0.0;
	float irradiance = 0.0;
	float total_irradiance = 0.0;
	float lambda = 0.250;
	float delta = 0.001;
	while(lambda <= 25){

		irradiance = table_given_irradiance(lambda);
		tau_lambda = total_transmitance(lambda, theta_z, w, d, altitude);
		irradiance = irradiance*tau_lambda*delta;
		total_irradiance += irradiance;
		lambda += delta;
	}

	total_irradiance = total_irradiance*elliptic_correction_factor(NDA);

	return total_irradiance;
}

//potência refletida por um espelho de area mirror_area
//localizado na posição R
//quando a posição do sol for s
float one_mirror_corrected_power(vetor_3d s, vetor_3d R, float J, float mirror_area){

	vetor_3d r(0,0,0);
	r = get_unitary_vector(R,r);

	vetor_3d n(0,0,0);
	n = get_normal_vector(s, r, n);

	return J*n.scalar_prod(s)*mirror_area;
}

