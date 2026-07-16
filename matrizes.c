#include <stdio.h>


int main(){
    
    int primeirax,segundax,terceirax,quartax,quintax,sextax,setimax,oitavax;
    int primeirao,segundao,terceirao,quartao,quintao,sextao,setimao,oitavao;
    
    int arr[3][3];
    for (int i =0; i < 3; i ++){
        for (int j=0; j< 3; j++){
            arr[j][i] = 2;
        }
    }
    
    printf("%d | %d | %d \n_________\n%d | %d | %d\n_________\n%d | %d | %d", arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
    
    printf("\n Vez do X: ");
    scanf("%d", &primeirax);
    scanf("%d", &segundax);
    arr[primeirax][segundax] = 1;
    
    printf("%d | %d | %d \n_________\n%d | %d | %d\n_________\n%d | %d | %d", arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
    
    printf("\n Vez do O: ");
    scanf("%d", &primeirao);
    scanf("%d", &segundao);
    arr[primeirao][segundao] = 0;
    
    
    printf("%d | %d | %d \n_________\n%d | %d | %d\n_________\n%d | %d | %d", arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
    
    printf("\n Vez do X: ");
    scanf("%d", &terceirax);
    scanf("%d", &quartax);
    arr[terceirax][quartax] = 1;
    
    printf("%d | %d | %d \n_________\n%d | %d | %d\n_________\n%d | %d | %d", arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
    
    printf("\n Vez do O: ");
    scanf("%d", &terceirao);
    scanf("%d", &quartao);
    arr[terceirao][quartao] = 0;
    
    printf("%d | %d | %d \n_________\n%d | %d | %d\n_________\n%d | %d | %d", arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
    
    printf("\n Vez do X: ");
    scanf("%d", &quintax);
    scanf("%d", &sextax);
    arr[terceirax][quartax] = 1;
    
    printf("%d | %d | %d \n_________\n%d | %d | %d\n_________\n%d | %d | %d", arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
    
    printf("\n Vez do O: ");
    scanf("%d", &quintao);
    scanf("%d", &sextao);
    arr[terceirao][quartao] = 0;
    printf("%d | %d | %d \n_________\n%d | %d | %d\n_________\n%d | %d | %d", arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
    
    printf("\n Vez do X: ");
    scanf("%d", &setimax);
    scanf("%d", &oitavax);
    arr[terceirax][quartax] = 1;
    
    printf("%d | %d | %d \n_________\n%d | %d | %d\n_________\n%d | %d | %d", arr[0][0], arr[0][1], arr[0][2], arr[1][0], arr[1][1], arr[1][2], arr[2][0], arr[2][1], arr[2][2]);
    
    printf("\n Vez do O: ");
    scanf("%d", &setimao);
    scanf("%d", &oitavao);
    arr[terceirao][quartao] = 0;
    
    
    
    
    return 0;
}
