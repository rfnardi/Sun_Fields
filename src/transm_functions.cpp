#include <stdio.h>
#include <cmath>
#include "./table_functions.cpp"

float dry_air_opt_mass(float theta_z){
	return 1/(cos(theta_z) + 0.15*pow(93.885 - theta_z,-1.253)) ;
}

float water_vapor_opt_mass(float theta_z){
	return 1/(cos(theta_z) + 0.00548*pow(92.650 - theta_z,-1.452)) ;
}

float pressure_given_by_altitude(float altitude){
	float sea_level_pressure = 1013.25; //pressão em milibars
	return sea_level_pressure*exp(-0.0001184*altitude);//altitude em metros
}

float m_a_calc(float pressure, float m_z){
	return pressure*m_z/1013.25;
}

float k_Rayleigh_dry_air_scattering_lambda(float lambda){//lambda aqui sempre está medido em micrômetros
	return 0.0087352*pow(lambda,-4.08);
}

float k_Mie_water_droplets_scattering_lambda(float lambda){
	return 0.008635*pow(lambda,-2);
}

float k_Mie_dust_scattering_lambda(float lambda){
	return 0.08128*pow(lambda,-0.75);
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
	
	float tau_scattering_lambda = exp(-(k_dry_air*m_a + k_water_droplets*w*m_r + k_dust*(d/800)*m_a));

	return tau_scattering_lambda;
}


float gas_mix_absorp_transm_lambda(float lambda, float theta_z, float altitude){

	float m_r = dry_air_opt_mass(theta_z);
	float pressure = pressure_given_by_altitude(altitude);
	float m_a = m_a_calc(pressure, m_r);
	float k_g = table_given_gas_mix_k_g(lambda);
	float tau_absorp_lambda = exp(-1.41*k_g*m_a*pow(1+118.93*k_g*m_a, -0.45));

	return tau_absorp_lambda;
}

float water_vapor_absorp_transm_lambda(float lambda, float theta_z, float altitude, float w){

	float m_r = dry_air_opt_mass(theta_z);
	float k_wv = table_given_k_wv(lambda);
	float tau_absorp_lambda = exp(-0.2385*k_wv*w*m_r*pow(1+20.07*k_wv*w*m_r, -0.45));

	return tau_absorp_lambda;
}

float ozone_absorp_transm_lambda(float lambda, float theta_z, float altitude, float w){

	float m_r = dry_air_opt_mass(theta_z);
	float k_O_lambda = table_given_k_O(lambda);
	float tau_absorp_lambda = exp(-k_O_lambda*m_r);

	return tau_absorp_lambda;
}

float absorp_transm_lambda(float lambda, float theta_z, float w, float d, float altitude){

	float ozone_transm = ozone_absorp_transm_lambda(lambda, theta_z, altitude, w);
	float wv_aborp_transm = water_vapor_absorp_transm_lambda(lambda, theta_z, altitude, w);
	float gas_mixt_transm = gas_mix_absorp_transm_lambda(lambda, theta_z, altitude);

	float tau_absorp_lambda = ozone_transm*wv_aborp_transm*gas_mixt_transm;

	return tau_absorp_lambda;
}

float total_transmitance(float lambda, float theta_z, float w, float d, float altitude){

	float tau_scattering_lambda = scattering_transm_lambda(lambda, theta_z, w, d, altitude);
	float tau_absorp_lambda = absorp_transm_lambda(lambda, theta_z, w, d, altitude);

	return tau_scattering_lambda*tau_absorp_lambda; //transmitância total da radiação direta
}

float planck_distribution(float T_kelvin, float lambda){
	
	//Potência de radiação emitida por unidade transversa de área no comprimento de onda lambda:
	//http://hyperphysics.phy-astr.gsu.edu/hbase/quantum/radfrac.html#c1
	// P = 2*pi*h*c^2/(lambda^{5}*(e^{-hc/K*lambda*T} - 1)) 
	

	//2*pi*h*c^2/lambda^5 = 2*pi*(6.62607015)*3*10^2*c/(n^5) = sigma
	//onde lambda = n*10^{-6}
	float sigma = 2*M_PI*(6.62607015)*900000000;

	//h*c/K*lambda = (6.62607015)*3*10/(1.380649*n)
	//onde lambda = n*10^{-6}
	float alpha = (6.62607015)*30/(1.380649);

	//aqui estamos assumindo que o parâmetro lamdba que entra na função já é medido em micrôns. 
	//assim, na expressão abaixo, "lambda = n"
	return sigma/(pow(lambda,5)*(exp(-alpha/(T_kelvin*lambda)) - 1)); //dimensão: potência; unidade: watt

}


