#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;


void matrizIdentidade(int matriz[][3], int tamanho){
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if(i == j){
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

void Matriz_determinante(int matriz[][3], int tamanho){
    int det = 0;
    if(tamanho == 1){
        det = matriz[0][0];
    } else if(tamanho == 2){
        det = matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    } else if(tamanho == 3){
        det = matriz[0][0] * (matriz[1][1] * matriz[2][2] - matriz[1][2] * matriz[2][1]) -
              matriz[0][1] * (matriz[1][0] * matriz[2][2] - matriz[1][2] * matriz[2][0]) +
              matriz[0][2] * (matriz[1][0] * matriz[2][1] - matriz[1][1] * matriz[2][0]);
    }
    cout << "Determinante: " << det << endl;
}


// Funções para manipular a matriz (usando std::vector)
using Matriz = vector<vector<int>>;

// -----------------------------------------------------------------------------
// FUNÇÃO AUXILIAR: Constrói a submatriz (o Menor Complementar)
// Retorna a matriz que sobra ao remover uma linha e uma coluna.
// -----------------------------------------------------------------------------
Matriz criarMenor(const Matriz& matriz, int linhaIgnorar, int colunaIgnorar) {
    int N = matriz.size();
    if (N <= 1) {
        return {}; 
    }

    Matriz menor(N - 1, vector<int>(N - 1));
    int menorLinha = 0;
    
    for (int i = 0; i < N; ++i) {
        if (i == linhaIgnorar) continue;
        
        int menorColuna = 0;
        for (int j = 0; j < N; ++j) {
            if (j == colunaIgnorar) continue;
            
            menor[menorLinha][menorColuna] = matriz[i][j];
            menorColuna++;
        }
        menorLinha++;
    }
    return menor;
}

// -----------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL: Calcula o determinante de forma RECURSIVA (Teorema de Laplace)
// -----------------------------------------------------------------------------
int calcularDeterminante(const Matriz& matriz) {
    int N = matriz.size();

    // 1. CASO BASE 1x1
    if (N == 1) {
        return matriz[0][0];
    }

    // 2. CASO BASE 2x2 (Mais eficiente que chamar recursivamente)
    if (N == 2) {
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    }
    
    int determinante = 0;

    // Expandimos pela primeira linha (i=0)
    for (int j = 0; j < N; ++j) {
        
        // A. COFATOR (Sinal)
        // O sinal é dado por (-1)^(i+j). Como i=0, é (-1)^j.
        // É positivo se j for par (0, 2, 4...) e negativo se j for ímpar (1, 3, 5...)
        int sinal = (j % 2 == 0) ? 1 : -1; 
        
        // B. MENOR COMPLEMENTAR (Submatriz)
        Matriz menor = criarMenor(matriz, 0, j);

        // C. Chamada RECURSIVA para calcular o determinante do menor
        int detMenor = calcularDeterminante(menor);

        // D. Soma o termo: sinal * elemento * detMenor
        determinante += sinal * matriz[0][j] * detMenor;
    }

    return determinante;
}
// -----------------------------------------------------------------------------
// FUNÇÃO PARA IMPRIMIR A MATRIZ
// -----------------------------------------------------------------------------
void imprimirMatriz(const Matriz& matriz) {
    for (const auto& linha : matriz) {
        for (int elemento : linha) {
            cout << setw(4) << elemento << " ";
        }
        cout << endl;
    }
}

int main(){
    cout << "--- Teorema de Laplace para Matriz 3x3 ---\n";
    
    // Matriz de exemplo 3x3 (determinante = 30)
    Matriz matriz_3x3 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    // Corrigido: Usando uma matriz onde o determinante não é zero para demonstrar
    Matriz matriz_exemplo = {
        {1, 0, 2},
        {3, 4, 5},
        {6, 7, 8}
    };
    
    // Verificações
    int linhas = matriz_exemplo.size();
    int colunas = (linhas > 0) ? matriz_exemplo[0].size() : 0;

    if (linhas != colunas) {
        cout << "Erro: A matriz não é quadrada (" << linhas << "x" << colunas << "). O Teorema de Laplace só se aplica a matrizes quadradas." << endl;
    } else {
        cout << "Matriz de Entrada (" << linhas << "x" << colunas << "):" << endl;
        imprimirMatriz(matriz_exemplo);
        
        // Chama a função recursiva
        int det = calcularDeterminante(matriz_exemplo);
        
        cout << "\nO determinante da matriz é: " << det << endl;
    }

    return 0;
}
