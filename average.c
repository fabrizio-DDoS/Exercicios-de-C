#include <stdio.h>
int main(){
    
    int ages[] = {1,2,3,4,6,7};
    
    printf("digite sua idade:  ");
    int idade;
    
    scanf("%d", &idade);
    ages[0] = idade;
    
    
    float avrg, sum = 0;
    int len = sizeof(ages) / sizeof(ages[0]);
    
    for (int i=0; i < len; i++){
        sum += ages[i];
    }
    
    avrg = sum/len;
    
    printf("A média das idades é %f", avrg);
    
    return 0;
}
