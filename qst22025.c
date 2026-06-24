// Online C compiler to run C program online
#include <stdio.h>

void soma(int array[], int tamanho){
    
    int conta = 0;
    
    for(int i = 0; i < tamanho; i++){
        conta += array[i];
    }
    array[tamanho-1] = conta;
    
}


int main() {
    
    int a[] = {1,2,3,4,5};
    int na = 5;
    
    soma(a, na);
    
    return 0;
}
