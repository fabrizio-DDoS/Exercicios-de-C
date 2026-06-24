// Online C compiler to run C program online
#include <stdio.h>

int main() {
    
    int i = 0;
    
    int a = 0;
    int e = 0;
    int vogalI = 0;
    int o = 0;
    int u = 0;
    
    while(texto[i]!= "\0"){
        if(texto[i] == "a" || texto[i] == "A"){
            a ++;
        }else if(texto[i] == "e" || texto[i] == "E"){
            e ++;
        }else if(texto[i] == "i" || texto[i] == "I"){
            vogalI ++;
        }else if(texto[i] == "o" || texto[i] == "O"){
            o ++;
        }else if(texto[i] == "u" || texto[i] == "U"){
            u ++;
        }
        
         printf( "\ ncontagens: a: %d e: %d i: %d o: %d u:%d \n", a, e, vogalI, o, u);
        
        i++;
    }

    return 0;
}
