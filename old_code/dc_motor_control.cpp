//Função de controle do motor de passo
//Programa: Ponte H L298N com motor de passo no Arduino
//ADAPTADO de Arduino e Cia


#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <wiringPi.h>  //chama biblioteca no Rasp_Pi para controle de pinos em C

  
  int main(){

      int IN1 = 0;
      int IN2 = 1;
      int tempo ;
      char options;

    wiringPiSetup();    // inicia a biblioteca WiringPi
        
    //Define os pinos como saida:
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    
    printf("Este é um programa simples de um motor dc via ponte H l298n. \n");
    
    printf("Insira o valor do tempo de funcionamento em milisegundos. \n");
    scanf("%d", &tempo);
    
    printf("Seguindo a regra da mão direita, digite 'u' para que o motor gire no sentido para cima \n e 'd' para que o motor gire para baixo. \n Finalmente digite 'q' para sair do programa.  \n");
    scanf("%s", &options);

    
    switch(options){
      
      
      case 'u': 
          digitalWrite(IN1, 0);
          digitalWrite(IN2, 1);
          delay(tempo);
          break;
          
      case 'd': 
          digitalWrite(IN1, 1);
          digitalWrite(IN2, 0);
          delay(tempo);
          break;
        
      case 'q': 
          break;
        }
           
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
    
    return 1;
  }
