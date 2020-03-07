//programa de calibração do sensor de localização angular do sol

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// #include <wiringPi.h>  //chama biblioteca no Rasp_Pi para controle de pinos em C


int main(void){
char seta;
int i, j;
i = 0;
j = 0;
  printf("Programa de calibração do sensor de localização do sol. \n" );
  printf("-----------------------------------------------------\n");
  printf("Pressione 'w' para mover o localizador para cima. \n" );
  printf("Pressione 's' para mover o localizador para baixo. \n" );
  printf("Pressione 'a' para mover o localizador para a esquerda. \n" );
  printf("Pressione 'd' para mover o localizador para a direita. \n" );
  printf("Pressione 'o' para sair do programa. \n" );

  do {
            seta = getchar();

            if (seta=='w'){ //motor de passo zenital move o localizador para cima
              i= i+1;
              printf("1 passo para cima. \n");
            }

            if (seta=='s'){ //motor de passo zenital move o localizador para baixo
              i = i-1;
              printf("1 passo para baixo. \n");
            }

            if (seta=='a'){  //motor de passo azimuthal move o localizador para esquerda
              j = j+1;
              printf("1 passo para esquerda. \n");
            }

            if (seta=='d'){ //motor de passo azimuthal move o localizador para direita
              j= j-1;
              printf("1 passo para direita. \n");
            }

        if (!( (seta == 'w') || (seta == 'd') || (seta == 'a') || (seta == 's') || (seta == 'o') || (seta == EOF) || (seta =='\n'))) {
        printf("Direção não reconhecida. \n");
        }

  } while( seta != 'o'); //end do-while

printf("Valor de i: %d \n", i);
printf("Valor de j: %d \n", j);

return 1;
}
