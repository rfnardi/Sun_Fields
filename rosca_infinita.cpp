#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// #include <wiringPi.h>  //chama biblioteca no Rasp_Pi para controle de pinos em C

float z;


		float R_flat_cilinder(float zeta){
				float Cil ;

				Cil=0.5;

				return Cil;
		}

		float R_trapezoidal(float zeta){     //perfil trapezoidal da rosca do parafuso

				float Rmax = 1; //altura da crista
				float Rmin = 0.75;		//altura do vale
				float s = 2;		//largura da "ladeira"
				float l = 2;		//largura do vale (= largura da crista)
				float Trapez;

				//tamanho do passo: 2*s+2*l

				if (zeta>=0 && zeta<s) {
					Trapez = -((Rmax-Rmin)/s)*zeta+Rmax;
				}
				if (zeta>=s && zeta<s+l) {
					Trapez = Rmin;
				}
				if (zeta>=s+l && zeta<2*s+l) {
					Trapez = ((Rmax-Rmin)/s)*zeta+(Rmin*(2*s+l)-Rmax*(s+l))/s;
				}
				if (zeta>=2*s+l && zeta<2*s+2*l) {
					Trapez = Rmax;
				}

				return Trapez;
		}

		float R_parabolico(float zeta){

				float Parab;
				float H, h, v;
				h = 2; //valor da parábola no vértice
				H = 2; //valor da parábola na origem
				v = 2; //posição do vértice

				if (zeta<=2*v) {
	  		  	Parab = ((H-h)/pow(v,2))*pow(zeta,2)+(2*(h-H)/v)*zeta + H;
				}

				if (zeta>2*v) {
					Parab = H;
				}

		return Parab;
		}

int main (void) {

struct tm *data_hr;

/*
descrição do tipo de dados struct tm :

struct tm {
int tm_sec; //representa os segundos de 0 a 59
int tm_min; //representa os minutos de 0 a 59
int tm_hour; //representa as horas de 0 a 24
int tm_mday: //dia do mês de 1 a 31
int tm_mon; //representa os meses do ano de 0 a 11
int tm_year; //representa o ano a partir de 1900
int tm_wday; //dia da semana de 0 (domingo) até 6 (sábado)
int tm_yday; // dia do ano de 1 a 365
int tm_isdst; //indica horário de verão se for diferente de zero
};

*/


time_t segundos; //cria variável para armazenar tempo em segundos

time(&segundos); //obtém tempo em segundos

data_hr=localtime(&segundos);

int dia, mes, ano, hora, min;

dia=data_hr->tm_mday;
mes=data_hr->tm_mon;
mes=mes+1;
ano=data_hr->tm_year;
ano=ano+1900;
hora=data_hr->tm_hour;
min=data_hr->tm_min;

char filename[27]; // cria variável char para armazenar string com o nome do arquivo de log

sprintf(filename, "screw_thread-%d-%d-%d_%d_%d", dia, mes, ano, hora, min); //imprime data numa string

FILE *arq0;
arq0=fopen(filename, "w"); //abertura de arquivo para escrita

float raio, passo, theta, R_max;
double x, y, bigx, bigy, bigz;
int i;

passo=8; //tamanho do período transversal da rosca

/*
printf("Entre com o valor do raio. \n" );
//raio = getchar();
scanf("%f \n", &raio);
printf("Confirmando valor do raio = %f \n", raio);

printf("Entre com o valor do passo. \n" );
//passo = getchar();
scanf("%f \n", &passo);
printf("Confirmando valor do passo = %f \n", passo);
*/


		float z_min = 0;
		float z_max = 30;
		R_max = 1;
		raio = 0.0001;
		theta=0;
		printf("Iniciando desenho da tampa inferior. \n");
		while (raio<R_max) {     //desenhando pontos da tampa de baixo do parafuso
					theta=0;
					while (theta<=2*M_PI) {
						bigx= raio*cos(theta);
						bigy= raio*sin(theta);
						bigz= z_min;
						fprintf(arq0, " %E %E %E \n", bigx , bigy, bigz );
						theta=theta+0.01;
						}
				raio=raio+0.01;
		}

		raio = 0.0001;

		printf("Iniciando desenho da tampa superior. \n");
		while (raio<R_max) {		//desenhando pontos da tampa de cima do parafuso
					theta=0;
					while (theta<=2*M_PI) {
						bigx= raio*cos(theta);
						bigy= raio*sin(theta);
						bigz= z_min;
						fprintf(arq0, " %E %E %E \n", bigx , bigy, bigz );
						theta=theta+0.01;
						}
				raio=raio+0.01;
		}


theta=0;
z=passo;
i=0;
printf("Iniciando desenho do perfil da rosca. \n");
		do {

			//perfil da rosca:
					//R_flat_cilinder(z);
					//raio= R_parabolico(z);
					raio=R_trapezoidal(z);

						theta=0;
						while (theta<8*M_PI | bigz<z_max) {
							bigx= raio*cos(theta);
							bigy= raio*sin(theta);
							bigz= z+(theta*passo)/(2*M_PI);
							fprintf(arq0, " %E %E %E \n", bigx , bigy, bigz ); //escrevendo no arquivo
							theta = theta + 0.04;
						}

			//fprintf(arq0, " %E %E \n", z , raio ); //escrevendo no arquivo desenho 2-dimensional do perfil da rosca
			//printf("i=%d ; z=%lf \n", i, z);
			i=i+1;
			z=z-0.04;
		} while(z>0);

fclose(arq0); //fecha arquivo de gravação de dados

printf("Desenho concluído com sucesso. \n \n");
printf("O valor do passo da rosca é %f \n", passo);
printf("Nome do arquivo gerado: %s\n", filename);

return 0; }
