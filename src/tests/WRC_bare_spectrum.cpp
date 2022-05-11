# include "../lib/transm_functions.cpp"


//integração do espectro pelo método de barras
int main() {

	double delta = 0.01;
	double lambda = 0.250;
	double I_lambda = 0.00;
	double integral = 0.0;

	std::cout << " lambda;I;Integral" << std::endl;
	while(lambda < 2.0){
		
		I_lambda = table_given_irradiance(lambda);
		integral += I_lambda*delta;
		std::cout << lambda << ";" << I_lambda << ";"<< integral << std::endl;

		lambda += delta;
	}	
	return 0;
}
