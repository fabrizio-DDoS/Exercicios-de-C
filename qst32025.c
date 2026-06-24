// Online C compiler to run C program online
#include <stdio.h>

int main() {
    
    int p[] = {1 , 2 , 3 , 2 , 1 , 7 , 8 , 9 , 4 , 5 , 6 , 7 , 8 , 1 , 9};
    int np = 15;
    int saldo = 15;
    
    for(int i = 0; i < np; i++){
        if(saldo >= p[i]){
            printf("item %d comprado pelo preço %d", i, p[i]);
            saldo -= p[i];
        }
    }
    
    return 0;
}
