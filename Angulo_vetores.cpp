#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void angulo_vetores(const vector<int>& A, const vector<int>& B) {
    if (A.size() != B.size()) {
        cout << "Os vetores devem ter o mesmo tamanho." << endl;
        return;
    }

    int tamanho = A.size();
    double produto_escalar = 0.0;
    double moduloA = 0.0;
    double moduloB = 0.0;

    for (int i = 0; i < tamanho; i++) {
        produto_escalar += A[i] * B[i];
        moduloA += A[i] * A[i];
        moduloB += B[i] * B[i];
    }

    moduloA = sqrt(moduloA);
    moduloB = sqrt(moduloB);

    if (moduloA == 0 || moduloB == 0) {
        cout << "Nao e possivel calcular o angulo com vetor nulo." << endl;
        return;
    }

    double cos_theta = produto_escalar / (moduloA * moduloB);

    // Corrige erros de arredondamento (às vezes cos_theta pode ser ligeiramente >1 ou < -1)
    if (cos_theta > 1.0) cos_theta = 1.0;
    if (cos_theta < -1.0) cos_theta = -1.0;

    double angulo_radianos = acos(cos_theta);
    double angulo_graus = angulo_radianos * (180.0 / M_PI);

    cout << "Produto escalar: " << produto_escalar << endl;
    cout << "Modulo de A: " << moduloA << endl;
    cout << "Modulo de B: " << moduloB << endl;
    cout << "Cosseno do angulo: " << cos_theta << endl;
    cout << "Angulo entre os vetores: " << angulo_graus << " graus" << endl;
}

int main() {
    vector<int> A = {1, 2, 3};
    vector<int> B = {4, 5, 6};

    angulo_vetores(A, B);

    return 0;
}
