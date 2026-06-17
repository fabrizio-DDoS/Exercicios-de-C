#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int primeira;
    srand(time(NULL));
    
    int escolhido = (rand() %100);

    
    printf("Adivinhe o número:    ");
    scanf("%d", &primeira);
    
    
    while (primeira != escolhido){
        if (primeira > escolhido){
            printf("Menor!  ");
            scanf("%d", &primeira);
        } else {
            printf("Maior!  ");      
            scanf("%d", &primeira);
        }
    }
    printf("Você acertou! O número era %d", escolhido);
    
    return 0;
}
