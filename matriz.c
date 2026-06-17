#include <stdio.h>
int main(){
    
    int ages[3][5] = {{1,2,3,4,5}, {6,7,8,9,10}, {11,12,13,14,15}};
    
    int primeira;
    int segunda;
    
    printf("Quais cordenadas você quer acessar? ");
    scanf("%d", &primeira);
    scanf("%d", &segunda);
    
    printf("%d", ages[primeira-1][segunda-1]);
    
    return 0;
}
