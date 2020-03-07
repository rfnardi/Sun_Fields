#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){

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

        sprintf(filename, "stl_converted-%d-%d-%d_%d_%d", dia, mes, ano, hora, min); //imprime data numa string

        FILE *arq0;
        arq0=fopen(filename, "w"); //abertura de arquivo para escrita

//ler a primeira faixa de dados do arquivo: 0<=z<=S ; S é o passo vertical de leitura, que deve ser pouco maior que o passo vertical de escrita
    //contar o número N de pontos dentro da faixa e criar uma matriz 3xN onde os dados do arquivo são copiados

//medir as distâncias d(P_i,P_j) entre todos os pontos da faixa e criar associação entre pontos próximos (d<=1.3*S) dentro da faixa: criação de arestas

//considere todos os ciclos de de 3 arestas tais que o tamanho de uma das arestas não seja maior do que 1.3 vezes o tamanho de qualquer outra aresta do ciclo

//grave os ciclos no arquivo gerado

//crie conjunto de pontos da borda superior

//leia a segunda faixa de dados e adicione os pontos da borda superior ao conjunto

//repita até computar todas as faixas de dados


}
