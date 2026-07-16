#include <stdio.h>
#include <math.h>
// Ponto A: voce pode acrescentar codigo aqui
int prazo=36; // prazo do investimento
double capital=1000.0;
// capital
int n=5;
// comprimento dos arrays / quantidade de fundos
char *nome[]={"fundo-A", "fundo-B", "fundo-C", "fundo-D", "fundo-E"};
double rentabilidade []={0.0066, 0.008, 0.01, 0.005, 0.007};
int tfundo []={36, 30, 18, 36, 30};
// Ponto B: voce pode acrescentar codigo aqui
int main () {
    int i=0;
    double maior=0;
    int marca = 0;
    
    while(i<5){
        double fund = capital * pow((1 + rentabilidade[i]), tfundo[i]);
        if (fund > maior){
            maior = fund;
            marca = i;
        }
        
        i ++;
    }

// voce pode modificar a linha abaixo
    printf ("%s, %lf,%d,%lf\n", nome[marca], rentabilidade [marca], tfundo [marca], maior);
// Ponto D: voce pode acrescentar codigo aqui
}
// Ponto E: voce pode acrescentar codigo aqui

//ADICIONEI CÓDIGO NOS PONTOS: C e modifiquei a linha do printf
