#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// #include <wiringPi.h>  //chama biblioteca no Rasp_Pi para controle de pinos em C


//criando função map:

float map(float x_in, float margeminf_in, float margemsup_in, float margeminf_out, float margemsup_out){
	
	float range_in = margemsup_in - margeminf_in;
	float range_out = margemsup_out - margeminf_out;
						//esta função mapeia um intervalo de valores em outro
	
	return margeminf_out + (range_out*x_in)/range_in;
	
}



int main(){
while(1){                 //---------------loop infinito------------------

/*

wiringPiSetup();    // inicia a biblioteca WiringPi

//atribuição de gpios:

pinMode(12, INPUT); // configura o pino (GPIO) 12, que tem propriedade PWM como ENTRADA --- PHI
pinMode(13, INPUT); // configura o pino (GPIO) 13 que também é uma porta PWM como ENTRADA --- THETA

pinMode(17, OUTPUT); //configura pino gpio 17 como saída (digital) --- quando esta saída estiver HIGH, o motor SUPERIOR gira para ESQUERDA
pinMode(18, OUTPUT); //configura pino gpio 18 como saída (digital) --- quando esta saída estiver HIGH, o motor SUPERIOR gira para DIREITA
pinMode(22, OUTPUT); //configura pino gpio 22 como saída (digital) --- quando esta saída estiver HIGH, o motor INFERIOR gira para ESQUERDA
pinMode(23, OUTPUT); //configura pino gpio 23 como saída (digital) --- quando esta saída estiver HIGH, o motor INFERIOR gira para DIREITA

//-----Piscar led com um Raspberry Pi------- Exemplo para perceber o uso de comandos da biblioteca wiringPi.h -----
//digitalWrite(1, HIGH); // liga o pino 1
//delay(1000);           // espera 1 segundo
//digitalWrite(1, LOW);  // desliga o pino 1
//delay(1000);         //  espera 1 segundo
//------------------------------------------

*/

//declaração de variáveis do main:
int i, j;
float theta, phi, N[3], n[3], f[3], S[3], P[3], Mod_N, Mod_F, Mod_P, beta, rho, ghamma, erro, theta_pot, phi_pot, pot_sup, pot_inf, epsilon_phi, epsilon_theta;
double epsilon;

/*  --------------

Descrição das variáveis do main:

theta: ângulo axial (calculado por este script)
phi: ângulo azimutal (calculado por este script)
N: vetor ortogonal ao espelho não normalizado
N: vetor ortogonal ao espelho, normalizado
f: vetor normalizado que liga o centro do espelho ao ponto de concentraçao de calor
P: vetor que liga o centro do eixo superior ao ponto de concentração de calor --- este vetor é constante e único para cada espelho
S: vetor de posicionamento do sol, recebido do sensor de localização do sol
Mod_N: tamanho/norma de N
Mod_P: tamanho/norma de P
beta: ângulo entre P e N, a ser determinado (aproximadamente e recursivamente) por este script a partir do valor de S fornecido pelo sensor de localização do sol
rho: Módulo do vetor que liga o centro do espelho ao ponto de concentração de calor
ghamma: distância que liga o centro do eixo superior ao centro do espelho
erro: o raio incidente (vetor S) e o raio refletido (vetor f) devem fazer o mesmo angulo com o vetor n (lei de snell), a diferença entre eles é o erro
theta_pot: ângulo axial medido pelo potenciômetro inferior
phi_pot: ângulo azimutal medido pelo potenciômetro superior
pot_sup: valor bruto lido no potenciômetro superior
pot_inf: valor bruto lido no potenciômetro inferior
epsilon: parâmetro de tolerância do erro



------------------ */

//atribuição de gpios --- a construir


//recebe o valor de S a partir do sensor de posicionamento do sol via comunicação serial --- aqui ainda estamos fornecendo S à mão:


S[0]=1/sqrt(3);           //aqui, estes valores numéricos são um exemplo
S[1]=1/sqrt(3);
S[2]=1/sqrt(3);


//declara o vetor constante P de posicinamento do foco a partir do centro do eixo superior:
P[0]=5;
P[1]=3;     //aqui, estes valores numéricos são um exemplo
P[2]=0; 
		
Mod_P = sqrt(pow(P[0],2)+pow(P[1],2)+pow(P[2],2)); //calcula a norma de P


ghamma=0.2; //recebe o valor de ghamma (tamanho do vetor que liga o centro do eixo superior ao centro do espelho)

printf("ghamma= %f \n", ghamma);

epsilon = 0.000001;

printf("epsilon= %le \n", epsilon);

//declara o valor inicial de rho (tamanho do vetor que liga o centro do espelho ao ponto focal de aquecimento) para início do loop while mediante lei dos cossenos:
beta=0; //impomos o ângulo entre P e N igual a zero como valor inicial para início do loop que determina seu valor aproximado
printf("beta= %f \n", beta);

rho=sqrt(pow(ghamma,2) + pow(Mod_P,2)-2*ghamma*Mod_P*cos(beta)) ; 
printf("rho= %f \n", rho);
erro=1;
j=1;
while (erro>epsilon){
	for (i=0; i<3; i++){  //calcula o vetor N: 

		N[i]=(S[i]+(P[i])/rho); 
		}

	Mod_N = sqrt(pow(N[0],2)+pow(N[1],2)+pow(N[2],2)); //calcula a norma de N

	for (i=0; i<3; i++){ 

		n[i]=N[i]/Mod_N; //calcula o vetor n, normalizado de direção perpendicular 
		}

	for (i=0; i<3; i++){ 
	
		f[i]=(P[i]-ghamma*n[i])/rho;
		}
	Mod_F = sqrt(pow(f[0],2)+pow(f[1],2)+pow(f[2],2)); //calcula a norma de f

	for (i=0; i<3; i++){ 

		f[i]=f[i]/Mod_F; //normaliza o vetor f 
		}
	erro=abs(S[0]*n[0]+S[1]*n[1]+S[2]*n[2]-f[0]*n[0]-f[1]*n[1]-f[2]*n[2]); //calcula a diferença entre os ângulos do raio incidente e refletido com a normal.
	printf("Erro = %f ; j= %d \n", erro, j);
	j=j+1;
	
	beta=beta+0.0001;  //atualiza valor de ângulo entre a normal e o vetor que dá a posição do foco de calor
	rho=sqrt(pow(ghamma,2) + pow(Mod_P,2)-2*ghamma*Mod_P*cos(beta)) ; //atualiza valor de rho
	}

printf("beta= %f \n", beta);
printf("rho= %f \n", rho);
for (i=0; i<3; i++){ 
	printf("Valor de n[%d]= %f \n ", i, n[i]); //imprime o valor das componentes de n
}

phi=acos(n[2]);
printf("phi= %f \n", phi);

theta=acos(n[0]/sin(phi));
printf("theta= %f \n", theta);



//mapeando leitura pwm para radianos e estabelecendo os valores dos ângulos theta e phi medidos nos potenciômetros:
//está comentado para que não gere erros devido à impossibilidade de uso da biblioteca wiringpi no laptop

//pot_sup=Pin[5]; //recebe leitura do potenciômetro superior no pino 5    
//pot_inf=Pin[7}; //recebe leitura do potenciômetro superior no pino 7

phi_pot=map(12, 0, 1023, 0, M_PI);
printf("phi_pot=%f \n", phi_pot);

theta_pot=map(23, 0, 1023, 0, M_PI/2);
printf("theta_pot=%f \n", theta_pot);


//toma a diferença entre os valores atuais de theta e phi com os valores medidos nos potenciômetros:

//definição dos parâmetros de erro de localização:

epsilon_phi=0.001;
epsilon_theta=0.001;

if(phi<phi_pot+epsilon_phi){
//ligar ponte H num sentido de corrente
}
if(phi>phi_pot+epsilon_phi){
//ligar ponte H no outro sentido de corrente
}

if(theta<theta_pot+epsilon_theta){
//ligar ponte H num sentido de corrente
}
if(theta>theta_pot+epsilon_theta){
//ligar ponte H no outro sentido de corrente
}

/* a partir da diferença entre os valores calculados de theta e phi e os valores medidos nos potenciômetros, o programa ordena a movimentação dos motores

*/
return 0;
}           //---------------fim do loop infinito------------------
}
