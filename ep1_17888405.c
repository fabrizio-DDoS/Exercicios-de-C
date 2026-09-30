/*
 NOME: Fabrízio Machado de Moura
 NUSP: 1788405
 */

#include <stdio.h>
#include <stdlib.h>

// Valor sentinela
#define VAZIO -999999.0f

// Função para gerar um número aleatório
float get_random_roughness(float roughness) {
    float r = (float)rand() / (float)RAND_MAX;
    return (r * 2.0f * roughness) - roughness;
}

// Função recursiva de divisão e conquista para preencher o terreno
void generate_terrain(float **M, int r, int c, int size, float roughness) {
    // Se o bloco for menor ou igual a 1 pixel de distância, não é possível dividir mais
    if (size <= 1) return;

    int half = size / 2;
    int r_mid = r + half;
    int c_mid = c + half;

    // Calcula o Lote Central X
    if (M[r_mid][c_mid] == VAZIO) {
        float A = M[r][c];
        float B = M[r][c + size];
        float C = M[r + size][c];
        float D = M[r + size][c + size];
        M[r_mid][c_mid] = (A + B + C + D) / 4.0f + get_random_roughness(roughness);
    }
    float X = M[r_mid][c_mid];

    // Calcula Aresta Superior (entre A e B)
    if (M[r][c_mid] == VAZIO) {
        float A = M[r][c];
        float B = M[r][c + size];
        M[r][c_mid] = (A + B + X) / 3.0f + get_random_roughness(roughness);
    }
    // Calcula Aresta Esquerda (entre A e C)
    if (M[r_mid][c] == VAZIO) {
        float A = M[r][c];
        float C = M[r + size][c];
        M[r_mid][c] = (A + C + X) / 3.0f + get_random_roughness(roughness);
    }
    // Calcula Aresta Direita (entre B e D)
    if (M[r_mid][c + size] == VAZIO) {
        float B = M[r][c + size];
        float D = M[r + size][c + size];
        M[r_mid][c + size] = (B + D + X) / 3.0f + get_random_roughness(roughness);
    }
    // Calcula Aresta Inferior (entre C e D)
    if (M[r + size][c_mid] == VAZIO) {
        float C = M[r + size][c];
        float D = M[r + size][c + size];
        M[r + size][c_mid] = (C + D + X) / 3.0f + get_random_roughness(roughness);
    }

    // Chamadas recursivas para os 4 quadrantes
    generate_terrain(M, r, c, half, roughness);
    generate_terrain(M, r, c + half, half, roughness); 
    generate_terrain(M, r + half, c, half, roughness);
    generate_terrain(M, r + half, c + half, half, roughness);
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Erro na quantidade de entradas!\n");
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        printf("Erro ao ler a entrada %s.\n", argv[1]);
        return 1;
    }

    int n, seed;
    float roughness, A, B, C, D;
    int line_num = 1;

    // Lê linha por linha 
    while (fscanf(fin, "%d %d %f %f %f %f %f", &n, &seed, &roughness, &A, &B, &C, &D) == 7) {
        
        srand(seed);

        int m = (1 << n) + 1; // 2^n + 1

        // Aloca a matriz dinamicamente
        float **M = (float **)malloc(m * sizeof(float *));
        for (int i = 0; i < m; i++) {
            M[i] = (float *)malloc(m * sizeof(float));
            for (int j = 0; j < m; j++) {
                M[i][j] = VAZIO; // Inicializa as células como não preenchidas
            }
        }

        // Define os 4 cantos originais
        M[0][0]= A;
        M[0][m - 1] = B;
        M[m - 1][0] = C;
        M[m - 1][m - 1] = D;

        generate_terrain(M, 0, 0, m - 1, roughness);

        float min_val = M[0][0];
        float max_val = M[0][0];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (M[i][j] < min_val) min_val = M[i][j];
                if (M[i][j] > max_val) max_val = M[i][j];
            }
        }

        char out_filename[50];
        sprintf(out_filename, "saida%d.txt", line_num);
        FILE *fout = fopen(out_filename, "w");

        // Cabeçalho PGM
        fprintf(fout, "P2\n");
        fprintf(fout, "%d %d\n", m, m);
        fprintf(fout, "255\n");

        // Normalizados na escala [0, 255]
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                int pixel_val = 0;
                
                // Evita divisão por zero
                if (max_val != min_val) {
                    // Mapeamento inverso: altitude maior -> pixel menor (cor mais escura)
                    pixel_val = (int)((255.0 * (max_val - M[i][j]) / (max_val - min_val)) + 0.5f);
                }

                fprintf(fout, "%d ", pixel_val);
            }
            fprintf(fout, "\n");
        }

        fclose(fout);

        // Liberta a memória
        for (int i = 0; i < m; i++) {
            free(M[i]);
        }
        free(M);

        line_num++;
    }

    fclose(fin);
    return 0;
}