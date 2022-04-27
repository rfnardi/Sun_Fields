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
      int IN3 = 2;
      int IN4 = 3;

    wiringPiSetup();    // inicia a biblioteca WiringPi
        
    //Define os pinos como saida:
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);

    int i, n, r, tempo;
    printf("Insira o valor do intervalo de tempo.\n");
    scanf("%d", &tempo);
    printf("Insira o valor do número de passos para frente.\n");
    scanf("%d", &n);
    i=0;
    
    r=i % 8;
  while (i<n){
    switch (r) {
      
       case 0 : 
       //Passo 1
       digitalWrite(IN1, 1);
       digitalWrite(IN2, 0);
       digitalWrite(IN3, 0);
       digitalWrite(IN4, 0);
       delay(tempo);
       i=i+1;
       r=i % 8;
       printf("i= %d r= %d \n", i, r);
        break;
        
       case 1 :
       //Passo 2
       digitalWrite(IN1, 0);
       digitalWrite(IN2, 1);
       digitalWrite(IN3, 0);
       digitalWrite(IN4, 0);
       delay(tempo);
       i=i+1;       
       r=i % 8;
       printf("i= %d r= %d \n", i, r);
        break;
       
       case 2 :
       //Passo 3
       digitalWrite(IN1, 0);
       digitalWrite(IN2, 0);
       digitalWrite(IN3, 1);
       digitalWrite(IN4, 0);
       delay(tempo);
       i=i+1;
       r=i % 8;
       printf("i= %d r= %d \n", i, r);
        break;
        
        case 3:
       //Passo 4
       digitalWrite(IN1, 0);
       digitalWrite(IN2, 0);
       digitalWrite(IN3, 0);
       digitalWrite(IN4, 1);
       delay(tempo);
       i=i+1;       
       r=i % 8;
       printf("i= %d r= %d \n", i, r);
        break;
        
       case 4 :
       //Passo 5
       digitalWrite(IN1, 1);
       digitalWrite(IN2, 0);
       digitalWrite(IN3, 0);
       digitalWrite(IN4, 0);
       delay(tempo);
       i=i+1;
       r=i % 8;
       printf("i= %d r= %d \n", i, r);
        break;

       case 5 :
       //Passo 6
       digitalWrite(IN1, 0);
       digitalWrite(IN2, 1);
       digitalWrite(IN3, 0);
       digitalWrite(IN4, 0);
       delay(tempo);
       i=i+1;
       r=i % 8;
       printf("i= %d r= %d \n", i, r);
        break;
       
       case 6 :
       //Passo 7
       digitalWrite(IN1, 0);
       digitalWrite(IN2, 0);
       digitalWrite(IN3, 1);
       digitalWrite(IN4, 0);
       delay(tempo);
       i=i+1;
       r=i % 8;
       printf("i= %d r= %d \n", i, r);
        break;

       case 7 :
       //Passo 8
       digitalWrite(IN1, 0);
       digitalWrite(IN2, 0);
       digitalWrite(IN3, 0);
       digitalWrite(IN4, 1);
       delay(tempo);
       i=i+1;
       r=i % 8;
       printf("i= %d r= %d \n", i, r);
        break;
            
   }
  }
      //desligando todos os pinos:
       digitalWrite(IN1, 0);
       digitalWrite(IN2, 0);
       digitalWrite(IN3, 0);
       digitalWrite(IN4, 0);
   
    printf("Sequencia de passos para frente concluída. \n");
return 0;
}
/*
int stepper_motor_backward(){


      int IN1 = 0;
      int IN2 = 1;
      int IN3 = 2;
      int IN4 = 3;


  wiringPiSetup();    // inicia a biblioteca WiringPi

  //Define os pinos como saida
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  int tempo = 10;
  int j, m;
  printf("Insira o valor do número de passos para trás.\n");
  scanf("%d", &m);
    j=0;
    while (j<m) {

        //Passo 8
        digitalWrite(IN1, 1);
        digitalWrite(IN2, 0);
        digitalWrite(IN3, 0);
        digitalWrite(IN4, 0);
        delay(tempo);
        j=j+1;
        printf("j= %d \n", j);

        //Passo 7
        digitalWrite(IN1, 1);
        digitalWrite(IN2, 0);
        digitalWrite(IN3, 1);
        digitalWrite(IN4, 0);
        delay(tempo);
        j=j+1;
        printf("j= %d \n", j);

        //Passo 6
        digitalWrite(IN1, 0);
        digitalWrite(IN2, 0);
        digitalWrite(IN3, 1);
        digitalWrite(IN4, 0);
        delay(tempo);
        j=j+1;
        printf("j= %d \n", j);

        //Passo 5
        digitalWrite(IN1, 0);
        digitalWrite(IN2, 1);
        digitalWrite(IN3, 1);
        digitalWrite(IN4, 0);
        delay(tempo);
        j=j+1;
        printf("j= %d \n", j);

        //Passo 4
        digitalWrite(IN1, 0);
        digitalWrite(IN2, 1);
        digitalWrite(IN3, 0);
        digitalWrite(IN4, 0);
        delay(tempo);
        j=j+1;
        printf("j= %d \n", j);

        //Passo 3
        digitalWrite(IN1, 0);
        digitalWrite(IN2, 1);
        digitalWrite(IN3, 0);
        digitalWrite(IN4, 1);
        delay(tempo);
        j=j+1;
        printf("j= %d \n", j);

        //Passo 2
        digitalWrite(IN1, 0);
        digitalWrite(IN2, 0);
        digitalWrite(IN3, 0);
        digitalWrite(IN4, 1);
        delay(tempo);
        j=j+1;
        printf("j= %d \n", j);

        //Passo 1
       digitalWrite(IN1, 1);
       digitalWrite(IN2, 0);
       digitalWrite(IN3, 0);
       digitalWrite(IN4, 1);
       delay(tempo);
       j=j+1;
       printf("j= %d \n", j);
     }
printf("Sequencia de passos para trás concluída. \n");
return 0;
}

*/
