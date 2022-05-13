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
	for(int i = 0; i<37; i++){
		if(lambda >= table[i][0] && lambda < table[i+1][0]){
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
	for(int i = 0; i<71; i++){
		if(lambda >= table[i][0] && lambda < table[i+1][0]){
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
	for(int i = 0; i<65; i++){
		if(lambda >= table[i][0] && lambda < table[i+1][0]){
			k = table[i][1] + ((table[i+1][1]-table[i][1])/(table[i+1][0]-table[i][0]))*(lambda-table[i][0]);
			break;
		}
	}

	return k;
}

//Extraterrestrial Irradiance (whose integration gives the solar constant)
//tabela 3.3.2 Iqbal
double table_given_irradiance(float lambda_microns){

	double table[168][2];

	table[0][0] = 0.250;
	table[0][1] = 64.56;
	table[1][0] = 0.255;
	table[1][1] = 91.25;
	table[2][0] = 0.260;
	table[2][1] = 122.50;
	table[3][0] = 0.265;
	table[3][1] = 253.75;
	table[4][0] = 0.270;
	table[4][1] = 275.00;
	table[5][0] = 0.275;
	table[5][1] = 212.50;
	table[6][0] = 0.280;
	table[6][1] = 162.50;
	table[7][0] = 0.285;
	table[7][1] = 286.25;
	table[8][0] = 0.290;
	table[8][1] = 535.00;
	table[9][0] = 0.295;
	table[9][1] = 560.00;
	table[10][0] = 0.300;
	table[10][1] = 527.50;
	table[11][0] = 0.305;
	table[11][1] = 557.50;
	table[12][0] = 0.310;
	table[12][1] = 602.51;
	table[13][0] = 0.315;
	table[13][1] = 705.00;
	table[14][0] = 0.320;
	table[14][1] = 747.50;
	table[15][0] = 0.325;
	table[15][1] = 782.50;
	table[16][0] = 0.330;
	table[16][1] = 997.50;
	table[17][0] = 0.335;
	table[17][1] = 906.25;
	table[18][0] = 0.340;
	table[18][1] = 960.00;
	table[19][0] = 0.345;
	table[19][1] = 877.50;
	table[20][0] = 0.350;
	table[20][1] = 955.00;
	table[21][0] = 0.355;
	table[21][1] = 1044.99;
	table[22][0] = 0.360;
	table[22][1] = 940.00;
	table[23][0] = 0.365;
	table[23][1] = 1125.01;
	table[24][0] = 0.370;
	table[24][1] = 1165.00;
	table[25][0] = 0.375;
	table[25][1] = 1081.25;
	table[26][0] = 0.380;
	table[26][1] = 1210.00;
	table[27][0] = 0.385;
	table[27][1] = 931.25;
	table[28][0] = 0.390;
	table[28][1] = 1200.00;
	table[29][0] = 0.395;
	table[29][1] = 1033.74;
	table[30][0] = 0.400;
	table[30][1] = 1702.49;
	table[31][0] = 0.405;
	table[31][1] = 1643.75;
	table[32][0] = 0.410;
	table[32][1] = 1710.00;
	table[33][0] = 0.415;
	table[33][1] = 1747.50;
	table[34][0] = 0.420;
	table[34][1] = 1747.50;
	table[35][0] = 0.425;
	table[35][1] = 1692.51;
	table[36][0] = 0.430;
	table[36][1] = 1492.50;
	table[37][0] = 0.435;
	table[37][1] = 1761.25;
	table[38][0] = 0.440;
	table[38][1] = 1755.02;
	table[39][0] = 0.445;
	table[39][1] = 1922.49;
	table[40][0] = 0.450;
	table[40][1] = 2099.99;
	table[41][0] = 0.455;
	table[41][1] = 2017.51;
	table[42][0] = 0.460;
	table[42][1] = 2032.49;
	table[43][0] = 0.465;
	table[43][1] = 2000.00;
	table[44][0] = 0.470;
	table[44][1] = 1979.99;
	table[45][0] = 0.475;
	table[45][1] = 2016.25;
	table[46][0] = 0.480;
	table[46][1] = 2055.00;
	table[47][0] = 0.485;
	table[47][1] = 1901.26;
	table[48][0] = 0.490;
	table[48][1] = 1920.00;
	table[49][0] = 0.495;
	table[49][1] = 1965.00;
	table[50][0] = 0.500;
	table[50][1] = 1862.52;
	table[51][0] = 0.505;
	table[51][1] = 1943.75;
	table[52][0] = 0.510;
	table[52][1] = 1952.50;
	table[53][0] = 0.515;
	table[53][1] = 1835.01;
	table[54][0] = 0.520;
	table[54][1] = 1802.49;
	table[55][0] = 0.525;
	table[55][1] = 1894.99;
	table[56][0] = 0.530;
	table[56][1] = 1947.49;
	table[57][0] = 0.535;
	table[57][1] = 1926.24;
	table[58][0] = 0.540;
	table[58][1] = 1857.50;
	table[59][0] = 0.545;
	table[59][1] = 1895.01;
	table[60][0] = 0.550;
	table[60][1] = 1902.50;
	table[61][0] = 0.555;
	table[61][1] = 1885.00;
	table[62][0] = 0.560;
	table[62][1] = 1840.02;
	table[63][0] = 0.565;
	table[63][1] = 1850.00;
	table[64][0] = 0.570;
	table[64][1] = 1817.50;
	table[65][0] = 0.575;
	table[65][1] = 1848.76;
	table[66][0] = 0.580;
	table[66][1] = 1840.00;
	table[67][0] = 0.585;
	table[67][1] = 1817.50;
	table[68][0] = 0.590;
	table[68][1] = 1742.49;
	table[69][0] = 0.595;
	table[69][1] = 1785.00;
	table[70][0] = 0.600;
	table[70][1] = 1720.00;
	table[71][0] = 0.605;
	table[71][1] = 1751.25;
	table[72][0] = 0.610;
	table[72][1] = 1715.00;
	table[73][0] = 0.620;
	table[73][1] = 1715.00;
	table[74][0] = 0.630;
	table[74][1] = 1637.50;
	table[75][0] = 0.640;
	table[75][1] = 1622.50;
	table[76][0] = 0.650;
	table[76][1] = 1597.50;
	table[77][0] = 0.660;
	table[77][1] = 1555.00;
	table[78][0] = 0.670;
	table[78][1] = 1505.00;
	table[79][0] = 0.680;
	table[79][1] = 1472.50;
	table[80][0] = 0.690;
	table[80][1] = 1415.02;
	table[81][0] = 0.700;
	table[81][1] = 1427.50;
	table[82][0] = 0.710;
	table[82][1] = 1402.50;
	table[83][0] = 0.720;
	table[83][1] = 1355.00;
	table[84][0] = 0.730;
	table[84][1] = 1355.00;
	table[85][0] = 0.740;
	table[85][1] = 1300.00;
	table[86][0] = 0.750;
	table[86][1] = 1272.52;
	table[87][0] = 0.760;
	table[87][1] = 1222.50;
	table[88][0] = 0.770;
	table[88][1] = 1187.50;
	table[89][0] = 0.780;
	table[89][1] = 1195.00;
	table[90][0] = 0.790;
	table[90][1] = 1142.50;
	table[91][0] = 0.800;
	table[91][1] = 1144.70;
	table[92][0] = 0.810;
	table[92][1] = 1113.00;
	table[93][0] = 0.820;
	table[93][1] = 1070.00;
	table[94][0] = 0.830;
	table[94][1] = 1041.00;
	table[95][0] = 0.840;
	table[95][1] = 1019.99;
	table[96][0] = 0.850;
	table[96][1] = 994.00;
	table[97][0] = 0.860;
	table[97][1] = 1002.00;
	table[98][0] = 0.870;
	table[98][1] = 972.00;
	table[99][0] = 0.880;
	table[99][1] = 966.00;
	table[100][0] = 0.890;
	table[100][1] = 945.00;
	table[101][0] = 0.900;
	table[101][1] = 913.00;
	table[102][0] = 0.910;
	table[102][1] = 876,00;
	table[103][0] = 0.920;
	table[103][1] = 841.00;
	table[104][0] = 0.930;
	table[104][1] = 830.00;
	table[105][0] = 0.940;
	table[105][1] = 801.00;
	table[106][0] = 0.950;
	table[106][1] = 778.00;
	table[107][0] = 0.960;
	table[107][1] = 771.00;
	table[108][0] = 0.970;
	table[108][1] = 764.00;
	table[109][0] = 0.980;
	table[109][1] = 769.00;
	table[110][0] = 0.990;
	table[110][1] = 762.00;
	table[111][0] = 1.000;
	table[111][1] = 743.99;
	table[112][0] = 1.050;
	table[112][1] = 665.98;
	table[113][0] = 1.100;
	table[113][1] = 606.04;
	table[114][0] = 1.150;
	table[114][1] = 551.04;
	table[115][0] = 1.200;
	table[115][1] = 497.99;
	table[116][0] = 1.250;
	table[116][1] = 469.99;
	table[117][0] = 1.300;
	table[117][1] = 436.99;
	table[118][0] = 1.350;
	table[118][1] = 389.03;
	table[119][0] = 1.400;
	table[119][1] = 354.03;
	table[120][0] = 1.450;
	table[120][1] = 318.99;
	table[121][0] = 1.500;
	table[121][1] = 296.99;
	table[122][0] = 1.550;
	table[122][1] = 273.99;
	table[123][0] = 1.600;
	table[123][1] = 247.02;
	table[124][0] = 1.650;
	table[124][1] = 234.02;
	table[125][0] = 1.700;
	table[125][1] = 215.00;
	table[126][0] = 1.750;
	table[126][1] = 187.00;
	table[127][0] = 1.800;
	table[127][1] = 170.00;
	table[128][0] = 1.850;
	table[128][1] = 149.01;
	table[129][0] = 1.900;
	table[129][1] = 136.01;
	table[130][0] = 1.950;
	table[130][1] = 126.00;
	table[131][0] = 2.000;
	table[131][1] = 118.50;
	table[132][0] = 2.100;
	table[132][1] = 93.00;
	table[133][0] = 2.200;
	table[133][1] = 74.75;
	table[134][0] = 2.300;
	table[134][1] = 63.25;
	table[135][0] = 2.400;
	table[135][1] = 56.50;
	table[136][0] = 2.500;
	table[136][1] = 48.25;
	table[137][0] = 2.600;
	table[137][1] = 42.00;
	table[138][0] = 2.700;
	table[138][1] = 36.50;
	table[139][0] = 2.800;
	table[139][1] = 32.00;
	table[140][0] = 2.900;
	table[140][1] = 28.00;
	table[141][0] = 3.000;
	table[141][1] = 24.75;
	table[142][0] = 3.100;
	table[142][1] = 21.75;
	table[143][0] = 3.200;
	table[143][1] = 19.75;
	table[144][0] = 3.300;
	table[144][1] = 17.25;
	table[145][0] = 3.400;
	table[145][1] = 15.75;
	table[146][0] = 3.500;
	table[146][1] = 14.00;
	table[147][0] = 3.600;
	table[147][1] = 12.75;
	table[148][0] = 3.700;
	table[148][1] = 11.50;
	table[149][0] = 3.800;
	table[149][1] = 10.50;
	table[150][0] = 3.900;
	table[150][1] = 9.50;
	table[151][0] = 4.000;
	table[151][1] = 8.50;
	table[152][0] = 4.100;
	table[152][1] = 7.75;
	table[153][0] = 4.200;
	table[153][1] = 7.00;
	table[154][0] = 4.300;
	table[154][1] = 6.50;
	table[155][0] = 4.400;
	table[155][1] = 6.00;
	table[156][0] = 4.500;
	table[156][1] = 5.50;
	table[157][0] = 4.600;
	table[157][1] = 5.00;
	table[158][0] = 4.700;
	table[158][1] = 4.50;
	table[159][0] = 4.800;
	table[159][1] = 4.00;
	table[160][0] = 4.900;
	table[160][1] = 3.75;
	table[161][0] = 5.000;
	table[161][1] = 3.47;
	table[162][0] = 6.000;
	table[162][1] = 1.75;
	table[163][0] = 7.000;
	table[163][1] = 0.95;
	table[164][0] = 8.000;
	table[164][1] = 0.55;
	table[165][0] = 9.000;
	table[165][1] = 0.35;
	table[166][0] = 10.000;
	table[166][1] = 0.20;
	table[167][0] = 25.000;
	table[167][1] = 0.12;


	//INTERPOLAÇÃO:
	float I = 0.0;
	for(int i = 0; i<167; i++){
		if(lambda_microns >= table[i][0] && lambda_microns < table[i+1][0]){
			I = table[i][1] + ((table[i+1][1]-table[i][1])/(table[i+1][0]-table[i][0]))*(lambda_microns-table[i][0]);
			break;
		}
	}

	return I;
}
