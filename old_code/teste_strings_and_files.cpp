#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void){

int dia, mes, ano;
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

sprintf(filename, "sun_positions%d-%d-%d", dia, mes, ano); //imprime numa string

FILE *arq0;
arq0=fopen(filename, "w"); //abertura de arquivo para escrita

fprintf (arq0, "Hora: %d:%d:%d \n", data_hr->tm_hour, data_hr->tm_min, data_hr->tm_sec);

fclose(arq0); //fecha arquivo de gravação de dados


return 1; }
