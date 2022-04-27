#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// #include <wiringPi.h>  //chama biblioteca no Rasp_Pi para controle de pinos em C


//criando função map (que no fundo nada mais é do que uma regra de três):
float map(float x_in, float margeminf_in, float margemsup_in, float margeminf_out, float margemsup_out){

	// (margeminf_in) |-----------------|(x_in)-------------------------------------|(margemsup_in)

	// (margeminf_out)|-----------------|(map?)-------------------------------------|(margemsup_out)

	float range_in = margemsup_in - margeminf_in;
	float range_out = margemsup_out - margeminf_out;
	
	//esta função mapeia um intervalo de valores em outro

	return margeminf_out + (range_out*x_in)/range_in;

}


//disposição geométrica dos sensores LDR:
//                                   xxxxxxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxxxxxx
//                                   xxxxxxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxxxxxx
//                                   xxxxxxxxxx(SENSOR_LDR1)|(SENSOR_LDR2)xxxxxxxxxx
//       --------------------------------------------------------------------------------------------
//                                   xxxxxxxxxx(SENSOR_LDR4)|(SENSOR_LDR3)xxxxxxxxxx
//                                   xxxxxxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxxxxxx
//                                   xxxxxxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxxxxxx

//disposição geométrica dos motores de passo:

// motor axial   ----    perfaz um giro de no máximo 180 graus seguindo o sol de leste a oeste.
// motor zenital ----    perfaz um giro de no máximo 90 graus seguindo o sol conforme ele levanta e/ou abaixa sobre o horizonte.

int main (void) {

float epsilon, ldr1, ldr2, ldr3, ldr4, pot_axial, THETA, pot_zenital, PHI, luminosidade, temperatura, humidade;
int passo_azi, passo_zen; // variáveis de controle/registro dos passos nos motores de passo


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

dia=data_hr->tm_mday;
mes=data_hr->tm_mon;
mes=mes+1;
ano=data_hr->tm_year;
ano=ano+1900;


char filename[23]; // cria variável char para armazenar string com o nome do arquivo de log

sprintf(filename, "sun_positions-%d-%d-%d", dia, mes, ano); //imprime data numa string

FILE *arq0;
arq0=fopen(filename, "w"); //abertura de arquivo para escrita

passo_azi = 0; //inicializa valor do passo_azi
passo_zen = 0; //inicializa valor do passo_zen

#define lumin 123 //define luminosidade mínima de operação do sistema. Valor 123 escolhido apenas para dar algum valor.

while(min(ldr1, ldr2, ldr3, ldr4)>lumin){     //estabelece luminosidade mínima de operação
	/*

	//atribuição de gpios:

	pinMode(12, INPUT); // configura o pino (GPIO) 12, que tem propriedade PWM como ENTRADA --- PHI --- conferir quanto a superposição com o uso pelo heliostato
	pinMode(13, INPUT); // configura o pino (GPIO) 13 que também é uma porta PWM como ENTRADA --- THETA ----- conferir quanto a superposição com o uso pelo heliostato
	*/

	while (ldr1<(ldr2+epsilon) || ldr4<(ldr3+epsilon)){  // se esta condição for verdadeira, significa que está chegando mais luz aos sensores 1 e/ou 4, consequentemente, o conjunto deverá operar uma rotação no sentido horário.

	//motor de passo ligado ao eixo axial deve dar um passo no sentido horário(considerando que o motor de passo e o eixo giram no mesmo sentido)
	passo_azi++; //atualiza a contagem de passos
	}

	while (ldr1>(ldr2+epsilon) || ldr4>(ldr3+epsilon)){  // se esta condição for verdadeira, significa que está chegando mais luz aos sensores 1 e/ou 4, consequentemente, o conjunto deverá operar uma rotação no sentido ANTI-horário.

	//motor de passo ligado ao eixo axial deve dar um passo no sentido ANTI-horário(considerando que o motor de passo e o eixo giram no mesmo sentido)
	passo_azi--; //atualiza a contagem de passos
	}

	while (ldr1<(ldr4+epsilon) || ldr2<(ldr3+epsilon)){  // se esta condição for verdadeira, significa que está chegando mais luz aos sensores 1 e/ou 2, consequentemente, o conjunto deverá operar uma rotação que aponte para cima.

	//motor de passo ligado ao eixo zenital deve dar um passo no sentido horário (considerando que o motor de passo e o eixo giram no mesmo sentido)
	passo_zen++; //atualiza a contagem de passos
	}

	while (ldr1>(ldr4+epsilon) || ldr2>(ldr3+epsilon)){  // se esta condição for verdadeira, significa que está chegando mais luz aos sensores 3 e/ou 4, consequentemente, o conjunto deverá operar uma rotação que aponte para baixo.

	//motor de passo ligado ao eixo zenital deve dar um passo no sentido ANTI-horário (considerando que o motor de passo e o eixo giram no mesmo sentido)
	passo--; //atualiza a contagem de passos
	}

	//escreve valores dos angulos axial e zenital, medidos em pot_axial e pot_zenital em arquivo
	fprintf (arq0, "Hora: %d:%d:%d ; Luminosidade: %f; Temperatura: %f; Humidade: %f; Azimutal: %f ; Zenital: %f \n", data_hr->tm_hour, data_hr->tm_min, data_hr->tm_sec, luminosidade, temperatura, humidade, pot_axial, pot_zenital); //escrevendo resultados no arquivo ---- escrever ângulos mapeados e não valores lidos nos potenciômetros

	sleep(300000); //espera por 5 minutos

}

fclose(arq0); //fecha arquivo de gravação de dados

return 1; }
