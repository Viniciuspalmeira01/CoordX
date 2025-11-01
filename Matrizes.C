#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> // Para seed da função rand()

// O Produto Misto é o Determinante da matriz 3x3 formada pelos 3 vetores.
// As funções agora são simples e globais.

// =======================================================
// Funções Auxiliares
// =======================================================

/**
 * Cria uma submatriz (menor) removendo a primeira linha (linha 0) 
 * e a coluna 'col_to_remove'.
 * * @param original Matriz original (n x n)
 * @param n Tamanho da matriz (n)
 * @param col_to_remove Índice da coluna a ser removida
 * @return Ponteiro para a nova submatriz ((n-1) x (n-1))
 */
double** criar_submatriz(double** original, int n, int col_to_remove) {
    int new_n = n - 1;
    if (new_n == 0) return NULL;

    // Alocação da matriz (n-1) x (n-1)
    double** menor = (double**)malloc(new_n * sizeof(double*));
    if (menor == NULL) {
        perror("Erro de alocação de memória (linhas)");
        return NULL;
    }
    for (int i = 0; i < new_n; i++) {
        menor[i] = (double*)malloc(new_n * sizeof(double));
        if (menor[i] == NULL) {
            perror("Erro de alocação de memória (colunas)");
            // Liberar memória já alocada antes de retornar
            for (int k = 0; k < i; k++) free(menor[k]);
            free(menor);
            return NULL;
        }
    }

    // Preenchimento da submatriz
    int row_menor = 0;
    for (int i = 1; i < n; i++) { // Pula a primeira linha (i=0)
        int col_menor = 0;
        for (int j = 0; j < n; j++) {
            if (j == col_to_remove) continue; // Pula a coluna
            menor[row_menor][col_menor] = original[i][j];
            col_menor++;
        }
        row_menor++;
    }

    return menor;
}

/**
 * Libera a memória alocada para uma matriz n x n.
 * * @param matriz A matriz a ser liberada.
 * @param n O tamanho (n) da matriz.
 */
void free_matriz(double** matriz, int n) {
    if (matriz == NULL) return;
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}


// =======================================================
// Funções Principais (Determinante, Produto Escalar e Misto)
// =======================================================

/**
 * Calcula o determinante de uma matriz n x n usando o Método de Laplace.
 * * @param matriz A matriz (double**)
 * @param n O tamanho da matriz (n)
 * @return O valor do determinante (double)
 */
double determinante_lap(double** matriz, int n) {
    if (n == 0) return 0.0;
    if (n == 1) return matriz[0][0];

    if (n == 2)
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];

    double det = 0.0;

    // Expansão pela primeira linha
    for (int j = 0; j < n; j++) {
        // Criar a matriz menor (submatriz)
        double** menor = criar_submatriz(matriz, n, j);
        if (menor == NULL) return 0.0; // Em caso de erro de alocação

        // Cálculo do cofator (inclui o sinal e o elemento matriz[0][j])
        // pow(-1, j) é equivalente a (j % 2 == 0) ? 1.0 : -1.0
        double sinal = (j % 2 == 0) ? 1.0 : -1.0;
        double cofator = sinal * matriz[0][j];

        // Chamada recursiva
        det += cofator * determinante_lap(menor, n - 1);
        
        // Liberar a submatriz após o uso recursivo
        free_matriz(menor, n - 1);
    }

    return det;
}

/**
 * Calcula o produto escalar (dot product) de dois vetores de inteiros.
 * * @param A Ponteiro para o primeiro vetor.
 * @param B Ponteiro para o segundo vetor.
 * @param size O tamanho dos vetores.
 * @return O valor do produto escalar (int).
 */
int ortogonalidade(const int* A, const int* B, int size) {
    if (size <= 0) return 0;

    int produto = 0;
    for (int i = 0; i < size; i++) {
        produto += A[i] * B[i];
    }
    return produto;
}


/**
 * Calcula o Produto Misto de 3 vetores 3D.
 * O Produto Misto é o determinante da matriz 3x3 formada pelos vetores.
 * * @param A Ponteiro para o vetor A (tamanho 3).
 * @param B Ponteiro para o vetor B (tamanho 3).
 * @param C Ponteiro para o vetor C (tamanho 3).
 * @return O valor do Produto Misto (double).
 */
double produto_misto(const int* A, const int* B, const int* C) {
    // Para simplificar, assumimos que os vetores têm tamanho 3.

    // 1. Alocação e conversão dos vetores para uma matriz 3x3 de doubles
    double** matriz_mista = (double**)malloc(3 * sizeof(double*));
    if (matriz_mista == NULL) return 0.0;
    
    for (int i = 0; i < 3; i++) {
        matriz_mista[i] = (double*)malloc(3 * sizeof(double));
        if (matriz_mista[i] == NULL) {
            // Liberar memória alocada antes de erro
            for(int k = 0; k < i; k++) free(matriz_mista[k]);
            free(matriz_mista);
            return 0.0;
        }
    }

    // Preenche a matriz com os dados dos vetores
    for (int j = 0; j < 3; j++) {
        matriz_mista[0][j] = (double)A[j];
        matriz_mista[1][j] = (double)B[j];
        matriz_mista[2][j] = (double)C[j];
    }
    
    // 2. Cálculo do determinante
    double det = determinante_lap(matriz_mista, 3);
    
    // 3. Liberação da memória da matriz
    free_matriz(matriz_mista, 3);
    
    return det;
}


// =======================================================
// Função Principal (Main) para Teste em C
// =======================================================

int main() {
    // Inicialização do gerador de números aleatórios
    srand((unsigned int)time(NULL));

    const int tamanho = 3; 

    // Vetores de exemplo
    int A[] = {4, 5, 6};   
    int B[] = {1, 2, 3};
    int C[] = {1, 1, 1};

    // --- Parte da Matriz (Alocação dinâmica em C) ---
    
    // Alocação da matriz dinâmica
    double** matriz_quadrada = (double**)malloc(tamanho * sizeof(double*));
    if (matriz_quadrada == NULL) return 1;

    for (int i = 0; i < tamanho; i++) {
        matriz_quadrada[i] = (double*)malloc(tamanho * sizeof(double));
        if (matriz_quadrada[i] == NULL) {
            free_matriz(matriz_quadrada, i);
            return 1;
        }
    }

    // Inicialização da matriz com números aleatórios (0 a 9)
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            matriz_quadrada[i][j] = (double)(rand() % 10);
        }
    }
    
    printf("--- Matriz 3x3 Gerada ---\n");
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%.0f ", matriz_quadrada[i][j]);
        }
        printf("\n");
    }

    double det_final = determinante_lap(matriz_quadrada, tamanho);
    printf("Determinante (Método de Laplace): %.2f\n", det_final);

    // Liberar a matriz dinâmica
    free_matriz(matriz_quadrada, tamanho);
    
    printf("\n--- Operações com Vetores ---\n");
    
    // Calculando o produto escalar e verificando ortogonalidade.
    int produto_esc = ortogonalidade(A, B, tamanho);
    printf("Produto Escalar de A e B: %d\n", produto_esc);
    if (produto_esc == 0) {
        printf("Os vetores sao ortogonais.\n");
    } else {
        printf("Os vetores nao sao ortogonais.\n");
    }
    
    // Calculando o produto misto (volume)
    double prod_misto = produto_misto(A, B, C);
    printf("Volume do Paralelepípedo (Produto Misto): %.2f\n", prod_misto);
    
    return 0;
}
