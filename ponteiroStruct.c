#include <stdio.h>

struct Pessoa {
    int idade;
};
void mudar(struct Pessoa *p) {

    p -> idade = 67;    
}
int main() {
    struct Pessoa p1;
    p1.idade = 22;
    
    mudar(&p1);
    
    printf("%d", p1.idade);
    
    return 0;
}
