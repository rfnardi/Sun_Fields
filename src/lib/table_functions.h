 #ifndef TABLE_FUNCTIONS_H_QD6AY3DP
#define TABLE_FUNCTIONS_H_QD6AY3DP

//extinction factor for gas mixture absorption 
//tabela 6.13.1 Iqbal
float table_given_gas_mix_k_g(float lambda);

//extinction factor for water-vapor absorption 
//tabela 6.13.2 Iqbal
float table_given_k_wv(float lambda);

//extinction factor for ozone absorption 
//tabela 6.12.1 Iqbal
float table_given_k_O(float lambda);

//Extraterrestrial Irradiance (whose integration gives the solar constant)
//tabela 3.3.2 Iqbal
double table_given_irradiance(float lambda_microns);

#endif /* end of include guard: TABLE_FUNCTIONS_H_QD6AY3DP */
