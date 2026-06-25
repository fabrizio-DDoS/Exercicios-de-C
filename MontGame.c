#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    
    srand(time(NULL));
    int min = 1, max = 3;
    int aleat = min + rand() % (max - min + 1);
    printf("Numero gerado: %d\n", aleat);
    int aleatSeg = min + rand() % (2 - min + 1);
    
    int primeira;
    int segunda;
    
    
    printf("Escolha a primeira porta!\n");
    scanf("%d", &primeira);
    
    switch (primeira) {
        case 1:
            if (aleat == 1){
                printf("O carro não está na porta %d!", (aleatSeg + 1));
            } else if(aleat == 2){
                printf("O carro não está na porta 3!");
            }else if(aleat == 3){
                printf("O carro não está na porta 2!");
            }
            break;
        case 2:
            if (aleat == 2){
                if(aleatSeg == 1){
                    printf("O carro não está na porta %d!", aleatSeg);
                }else{
                    printf("O carro não está na porta %d!", (aleatSeg + 1));
                }
            } else if(aleat == 1){
                printf("O carro não está na porta 3!");
            }else if(aleat == 3){
                printf("O carro não está na porta 1!");
            }
            break;
        case 3:
            if (aleat == 3){
                printf("O carro não está na porta %d!", aleatSeg);
            } else if(aleat == 2){
                printf("O carro não está na porta 1!");
            }else if(aleat == 1){
                printf("O carro não está na porta 2!");
            }
            break;
        default:
            printf("Buggou");
    }
    
    printf("\n Vai manter?? S =1 ou N =2 \n");
    scanf("%d", &segunda);
    
    if (segunda == 1){
        if (primeira == aleat){
            printf("Você ganhou! O carro estava na porta %d!", aleat);
        } else {
            printf("Você perdeu! O carro estava na porta %d!", aleat);
        }
    } else {
        if (primeira == aleat){
            printf("Você perdeu! O carro estava na porta %d!", aleat);
        } else {
            printf("Você ganhou! O carro estava na porta %d!", aleat);
        }
    }
    
    
    
    return 0;
}
