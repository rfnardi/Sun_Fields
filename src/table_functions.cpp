#include <cmath>
#include <stdio.h>
#include <iostream>

//extinction factor for gas mixture absorption 
//tabela 6.13.1 Iqbal
float table_given_gas_mix_k_g(float lambda){

	float table[38][2]; //38 linhas e 2 colunas
	table[0][0] = 0.76; //coluna 0 pega o comprimento de onda em micrômetros (10^{-6}m)
	table[0][1] = 3.00; //coluna 1 pega o valor de k_g

	table[1][0] = 0.77;
	table[1][1] = 0.210;

	table[2][0] = 1.25;
	table[2][1] = 0.730*pow(10,-2);

	table[3][0] = 1.30;
	table[3][1] = 0.4*pow(10,-3);

	table[4][0] = 1.35;
	table[4][1] = 0.110*pow(10,-03);

	table[5][0] = 1.40;
	table[5][1] = 0.100*pow(10,-04);

	table[6][0] = 1.45;
	table[6][1] = 0.640*pow(10,-01);

	table[7][0] = 1.50;
	table[7][1] = 0.630*pow(10,-03);

	table[8][0] = 1.55;
	table[8][1] = 0.100*pow(10,-01);

	table[9][0] = 1.60;
	table[9][1] = 0.640*pow(10,-01);

	table[10][0] = 1.65;
	table[10][1] = 0.145*pow(10,-02);

	table[11][0] = 1.70;
	table[11][1] = 0.100*pow(10,-04);

	table[12][0] = 1.75;
	table[12][1] = 0.100*pow(10,-04);

	table[13][0] = 1.80;
	table[13][1] = 0.100*pow(10,-04);

	table[14][0] = 1.85;
	table[14][1] = 0.145*pow(10,-03);

	table[15][0] = 1.90;
	table[15][1] = 0.710*pow(10,-02);

	table[16][0] = 1.95;
	table[16][1] = 0.200*pow(10,+01);

	table[17][0] = 2.00;
	table[17][1] = 0.300*pow(10,+01);

	table[18][0] = 2.10;
	table[18][1] = 0.240*pow(10,+00);

	table[19][0] = 2.20;
	table[19][1] = 0.380*pow(10,-03);

	table[20][0] = 2.30;
	table[20][1] = 0.110*pow(10,-02);

	table[21][0] = 2.40;
	table[21][1] = 0.170*pow(10,-03);

	table[22][0] = 2.50;
	table[22][1] = 0.140*pow(10,-03);

	table[23][0] = 2.60;
	table[23][1] = 0.660*pow(10,-03);

	table[24][0] = 2.70;
	table[24][1] = 0.100*pow(10,+03);

	table[25][0] = 2.80;
	table[25][1] = 0.150*pow(10,+03);

	table[26][0] = 2.90;
	table[26][1] = 0.130*pow(10,+00);

	table[27][0] = 3.00;
	table[27][1] = 0.950*pow(10,-02);

	table[28][0] = 3.10;
	table[28][1] = 0.100*pow(10,-02);

	table[29][0] = 3.20;
	table[29][1] = 0.800*pow(10,+00);

	table[30][0] = 3.30;
	table[30][1] = 0.190*pow(10,+01);

	table[31][0] = 3.40;
	table[31][1] = 0.130*pow(10,+01);

	table[32][0] = 3.50;
	table[32][1] = 0.750*pow(10,-01);

	table[33][0] = 3.60;
	table[33][1] = 0.100*pow(10,-01);

	table[34][0] = 3.70;
	table[34][1] = 0.195*pow(10,-02);

	table[35][0] = 3.80;
	table[35][1] = 0.400*pow(10,-02);

	table[36][0] = 3.90;
	table[36][1] = 0.290*pow(10,+00);

	table[37][0] = 4.00;
	table[37][1] = 0.250*pow(10,-01);

	//INTERPOLAÇÃO:
	float k = 0.0;
	for(int i = 0; i<38; i++){
		if(lambda <= table[i][0] && lambda > table[i][0]){
			k = table[i][1] + ((table[i+1][1]-table[i][1])/(table[i+1][0]-table[i][0]))*(lambda-table[i][0]);
			break;
		}
	}

	return k;
}

//extinction factor for water-vapor absorption 
//tabela 6.13.2 Iqbal
float table_given_k_wv(float lambda){

	float table[72][2]; //72 linhas e 2 colunas

	table[0][0] = 0.69; 
	table[0][1] = 0.160*pow(10,-01); 

	table[1][0] = 0.70; 
	table[1][1] = 0.240*pow(10,-01); 

	table[2][0] = 0.71; 
	table[2][1] = 0.125*pow(10,-01); 

	table[3][0] = 0.72; 
	table[3][1] = 0.100*pow(10,+01); 

	table[4][0] = 0.73; 
	table[4][1] = 0.870*pow(10,+00); 

	table[5][0] = 0.74; 
	table[5][1] = 0.610*pow(10,-01); 

	table[6][0] = 0.75; 
	table[6][1] = 0.100*pow(10,-02); 

	table[7][0] = 0.76; 
	table[7][1] = 0.100*pow(10,-04); 

	table[8][0] = 0.77; 
	table[8][1] = 0.100*pow(10,-04); 

	table[9][0] = 0.78; 
	table[9][1] = 0.600*pow(10,-03); 

	table[10][0] = 0.79; 
	table[10][1] = 0.175*pow(10,-01); 

	table[11][0] = 0.80; 
	table[11][1] = 0.360*pow(10,-01); 

	table[12][0] = 0.81; 
	table[12][1] = 0.330*pow(10,+00); 

	table[13][0] = 0.82; 
	table[13][1] = 0.153*pow(10,+01); 

	table[14][0] = 0.83; 
	table[14][1] = 0.660*pow(10,+00); 

	table[15][0] = 0.84; 
	table[15][1] = 0.155*pow(10,+00); 

	table[16][0] = 0.85; 
	table[16][1] = 0.300*pow(10,-02); 

	table[17][0] = 0.86; 
	table[17][1] = 0.100*pow(10,-04); 

	table[18][0] = 0.87; 
	table[18][1] = 0.100*pow(10,-04); 

	table[19][0] = 0.88; 
	table[19][1] = 0.260*pow(10,-02); 

	table[20][0] = 0.89; 
	table[20][1] = 0.630*pow(10,-01); 

	table[21][0] = 0.90; 
	table[21][1] = 0.210*pow(10,+01); 

	table[22][0] = 0.91; 
	table[22][1] = 0.160*pow(10,+01); 

	table[23][0] = 0.92; 
	table[23][1] = 0.125*pow(10,+01); 

	table[24][0] = 0.93; 
	table[24][1] = 0.270*pow(10,+02); 

	table[25][0] = 0.94; 
	table[25][1] = 0.380*pow(10,+02); 

	table[26][0] = 0.95; 
	table[26][1] = 0.410*pow(10,+02); 

	table[27][0] = 0.96; 
	table[27][1] = 0.260*pow(10,+02); 

	table[28][0] = 0.97; 
	table[28][1] = 0.310*pow(10,+01); 

	table[29][0] = 0.98; 
	table[29][1] = 0.148*pow(10,+01); 

	table[30][0] = 0.99; 
	table[30][1] = 0.125*pow(10,+00); 

	table[31][0] = 1.00; 
	table[31][1] = 0.250*pow(10,-02); 

	table[32][0] = 1.05; 
	table[32][1] = 0.100*pow(10,-04); 

	table[33][0] = 1.10; 
	table[33][1] = 0.320*pow(10,+01); 

	table[34][0] = 1.15; 
	table[34][1] = 0.230*pow(10,+02); 

	table[35][0] = 1.20; 
	table[35][1] = 0.160*pow(10,-01); 

	table[36][0] = 1.25; 
	table[36][1] = 0.180*pow(10,-03); 

	table[37][0] = 1.30; 
	table[37][1] = 0.290*pow(10,+01); 

	table[38][0] = 1.35; 
	table[38][1] = 0.200*pow(10,+03); 

	table[39][0] = 1.40; 
	table[39][1] = 0.110*pow(10,+04); 

	table[40][0] = 1.45; 
	table[40][1] = 0.150*pow(10,+03); 

	table[41][0] = 1.50; 
	table[41][1] = 0.150*pow(10,+02); 

	table[42][0] = 1.55; 
	table[42][1] = 0.170*pow(10,-02); 

	table[43][0] = 1.60; 
	table[43][1] = 0.100*pow(10,-04); 

	table[44][0] = 1.65; 
	table[44][1] = 0.100*pow(10,-01); 

	table[45][0] = 1.70; 
	table[45][1] = 0.510*pow(10,+00); 

	table[46][0] = 1.75; 
	table[46][1] = 0.400*pow(10,+01); 

	table[47][0] = 1.80; 
	table[47][1] = 0.130*pow(10,+03); 

	table[48][0] = 1.85; 
	table[48][1] = 0.220*pow(10,+04); 

	table[49][0] = 1.90; 
	table[49][1] = 0.140*pow(10,+04); 

	table[50][0] = 1.95; 
	table[50][1] = 0.160*pow(10,+03); 

	table[51][0] = 2.00; 
	table[51][1] = 0.290*pow(10,+01); 

	table[52][0] = 2.10; 
	table[52][1] = 0.220*pow(10,+00); 

	table[53][0] = 2.20; 
	table[53][1] = 0.330*pow(10,+00); 

	table[54][0] = 2.30; 
	table[54][1] = 0.590*pow(10,+00); 

	table[55][0] = 2.40; 
	table[55][1] = 0.203*pow(10,+02); 

	table[56][0] = 2.50; 
	table[56][1] = 0.310*pow(10,+03); 

	table[57][0] = 2.60; 
	table[57][1] = 0.150*pow(10,+05); 

	table[58][0] = 2.70; 
	table[58][1] = 0.220*pow(10,+05); 

	table[59][0] = 2.80; 
	table[59][1] = 0.800*pow(10,+04); 

	table[60][0] = 2.90; 
	table[60][1] = 0.650*pow(10,+03); 

	table[61][0] = 3.00; 
	table[61][1] = 0.240*pow(10,+03); 

	table[62][0] = 3.10; 
	table[62][1] = 0.230*pow(10,+03); 

	table[63][0] = 3.20; 
	table[63][1] = 0.100*pow(10,+03); 

	table[64][0] = 3.30; 
	table[64][1] = 0.120*pow(10,+03); 

	table[65][0] = 3.40; 
	table[65][1] = 0.195*pow(10,+02); 

	table[66][0] = 3.50; 
	table[66][1] = 0.360*pow(10,+01); 

	table[67][0] = 3.60; 
	table[67][1] = 0.310*pow(10,+01); 

	table[68][0] = 3.70; 
	table[68][1] = 0.250*pow(10,+01); 

	table[69][0] = 3.80; 
	table[69][1] = 0.140*pow(10,+01); 

	table[70][0] = 3.90; 
	table[70][1] = 0.170*pow(10,+00); 

	table[71][0] = 4.00; 
	table[71][1] = 0.450*pow(10,-02); 

	//INTERPOLAÇÃO:
	float k = 0.0;
	for(int i = 0; i<72; i++){
		if(lambda <= table[i][0] && lambda > table[i][0]){
			k = table[i][1] + ((table[i+1][1]-table[i][1])/(table[i+1][0]-table[i][0]))*(lambda-table[i][0]);
			break;
		}
	}

	return k;
}

//extinction factor for ozone absorption 
//tabela 6.12.1 Iqbal
float table_given_k_O(float lambda){

	float table[72][2]; //72 linhas e 2 colunas

	table[0][0] = 0.290; 
	table[0][1] = 38.000; 

	table[1][0] = 0.295; 
	table[1][1] = 20.000; 

	table[2][0] = 0.300; 
	table[2][1] = 10.000; 

	table[3][0] = 0.305; 
	table[3][1] = 4.800; 

	table[4][0] = 0.310; 
	table[4][1] = 2.700; 

	table[5][0] = 0.315; 
	table[5][1] = 1.350; 

	table[6][0] = 0.320; 
	table[6][1] = 0.800; 

	table[7][0] = 0.325; 
	table[7][1] = 0.380; 

	table[8][0] = 0.330; 
	table[8][1] = 0.160; 

	table[9][0] = 0.335; 
	table[9][1] = 0.075; 

	table[10][0] = 0.340; 
	table[10][1] = 0.040; 

	table[11][0] = 0.345; 
	table[11][1] = 0.019; 

	table[12][0] = 0.350; 
	table[12][1] = 0.007; 

	table[13][0] = 0.355; 
	table[13][1] = 0.000; 

	table[14][0] = 0.445; 
	table[14][1] = 0.003; 

	table[15][0] = 0.450; 
	table[15][1] = 0.003; 

	table[16][0] = 0.455; 
	table[16][1] = 0.004; 

	table[17][0] = 0.460; 
	table[17][1] = 0.006; 

	table[18][0] = 0.465; 
	table[18][1] = 0.008; 

	table[19][0] = 0.470; 
	table[19][1] = 0.009; 

	table[20][0] = 0.475; 
	table[20][1] = 0.012; 

	table[21][0] = 0.480; 
	table[21][1] = 0.014; 

	table[22][0] = 0.485; 
	table[22][1] = 0.017; 

	table[23][0] = 0.490; 
	table[23][1] = 0.021; 

	table[24][0] = 0.495; 
	table[24][1] = 0.025; 

	table[25][0] = 0.500; 
	table[25][1] = 0.030; 

	table[26][0] = 0.505; 
	table[26][1] = 0.035; 

	table[27][0] = 0.510; 
	table[27][1] = 0.040; 

	table[28][0] = 0.515; 
	table[28][1] = 0.045; 

	table[29][0] = 0.520; 
	table[29][1] = 0.048; 

	table[30][0] = 0.525; 
	table[30][1] = 0.057; 

	table[31][0] = 0.530; 
	table[31][1] = 0.063; 

	table[32][0] = 0.535; 
	table[32][1] = 0.070; 

	table[33][0] = 0.540; 
	table[33][1] = 0.075; 

	table[34][0] = 0.545; 
	table[34][1] = 0.080; 

	table[35][0] = 0.550; 
	table[35][1] = 0.085; 

	table[36][0] = 0.555; 
	table[36][1] = 0.095; 

	table[37][0] = 0.560; 
	table[37][1] = 0.103; 

	table[38][0] = 0.565; 
	table[38][1] = 0.110; 

	table[39][0] = 0.570; 
	table[39][1] = 0.120; 

	table[40][0] = 0.575; 
	table[40][1] = 0.122; 

	table[41][0] = 0.580; 
	table[41][1] = 0.120; 

	table[42][0] = 0.585; 
	table[42][1] = 0.118; 

	table[43][0] = 0.590; 
	table[43][1] = 0.115; 

	table[44][0] = 0.595; 
	table[44][1] = 0.120; 

	table[45][0] = 0.600; 
	table[45][1] = 0.125; 

	table[46][0] = 0.605; 
	table[46][1] = 0.130; 

	table[47][0] = 0.610; 
	table[47][1] = 0.120; 

	table[48][0] = 0.620; 
	table[48][1] = 0.105; 

	table[49][0] = 0.630; 
	table[49][1] = 0.090; 

	table[50][0] = 0.640; 
	table[50][1] = 0.079; 

	table[51][0] = 0.650; 
	table[51][1] = 0.067; 

	table[52][0] = 0.660; 
	table[52][1] = 0.057; 

	table[53][0] = 0.670; 
	table[53][1] = 0.048; 

	table[54][0] = 0.680; 
	table[54][1] = 0.036; 

	table[55][0] = 0.690; 
	table[55][1] = 0.028; 

	table[56][0] = 0.700; 
	table[56][1] = 0.023; 

	table[57][0] = 0.710; 
	table[57][1] = 0.018; 

	table[58][0] = 0.720; 
	table[58][1] = 0.014; 

	table[59][0] = 0.730; 
	table[59][1] = 0.011; 

	table[60][0] = 0.740; 
	table[60][1] = 0.010; 

	table[61][0] = 0.750; 
	table[61][1] = 0.009; 

	table[62][0] = 0.760; 
	table[62][1] = 0.007; 

	table[63][0] = 0.770; 
	table[63][1] = 0.004; 

	table[64][0] = 0.780; 
	table[64][1] = 0.000; 

	table[65][0] = 0.790; 
	table[65][1] = 0.000; 

	//INTERPOLAÇÃO:
	float k = 0.0;
	for(int i = 0; i<66; i++){
		if(lambda <= table[i][0] && lambda > table[i][0]){
			k = table[i][1] + ((table[i+1][1]-table[i][1])/(table[i+1][0]-table[i][0]))*(lambda-table[i][0]);
			break;
		}
	}

	return k;
}
