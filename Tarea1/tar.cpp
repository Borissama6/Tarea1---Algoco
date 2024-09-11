#include <iostream>
#include<vector>
using namespace std;

// Función para multiplicar dos matrices usando el algoritmo cúbico tradicional
void iterativo_cubico_tradicional(int** M1, int f1, int c1, int** M2, int f2, int c2, int** M3) {
    if(c1 == f2){
        for (int i = 0; i < f1; ++i) {
            for (int j = 0; j < c2; ++j) {
                M3[i][j] = 0;
                for (int k = 0; k < c1; ++k) {
                    M3[i][j] += M1[i][k] * M2[k][j];
                }
            }
        }
    }
}


// Función para imprimir una matriz
void imprimirMatriz(int** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void iterativo_cubico_optimizado(int** M1, int f1, int c1, int** M2, int f2, int c2, int** M3) {
    if (c1 != f2) {
        std::cout << "Las dimensiones no son compatibles para la multiplicación de matrices." << std::endl;
        return;
    }

    int** M2_transpuesta = new int*[c2];
    for (int i = 0; i < c2; ++i) {
        M2_transpuesta[i] = new int[f2];
        for (int j = 0; j < f2; ++j) {
            M2_transpuesta[i][j] = M2[j][i];
        }
    }

    for (int i = 0; i < f1; ++i) {
        for (int j = 0; j < c2; ++j) {
            M3[i][j] = 0;
            for (int k = 0; k < c1; ++k) {
                M3[i][j] += M1[i][k] * M2_transpuesta[j][k];
            }
        }
    }

    for (int i = 0; i < c2; ++i) {
        delete[] M2_transpuesta[i];
    }
    delete[] M2_transpuesta;
}

// Función para sumar dos matrices
void sumar(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& resultado, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = A[i][j] + B[i][j];
}

// Función para restar dos matrices
void restar(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& resultado, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = A[i][j] - B[i][j];
}

// Implementación del algoritmo de Strassen
void strassen(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    vector<int> inner(newSize);
    vector<vector<int>> 
        A11(newSize, inner), A12(newSize, inner), A21(newSize, inner), A22(newSize, inner),
        B11(newSize, inner), B12(newSize, inner), B21(newSize, inner), B22(newSize, inner),
        C11(newSize, inner), C12(newSize, inner), C21(newSize, inner), C22(newSize, inner),
        M1(newSize, inner), M2(newSize, inner), M3(newSize, inner), M4(newSize, inner),
        M5(newSize, inner), M6(newSize, inner), M7(newSize, inner),
        AResult(newSize, inner), BResult(newSize, inner);

    // Dividir las matrices A y B en submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    sumar(A11, A22, AResult, newSize);
    sumar(B11, B22, BResult, newSize);
    strassen(AResult, BResult, M1, newSize);

    // M2 = (A21 + A22) * B11
    sumar(A21, A22, AResult, newSize);
    strassen(AResult, B11, M2, newSize);

    // M3 = A11 * (B12 - B22)
    restar(B12, B22, BResult, newSize);
    strassen(A11, BResult, M3, newSize);

    // M4 = A22 * (B21 - B11)
    restar(B21, B11, BResult, newSize);
    strassen(A22, BResult, M4, newSize);

    // M5 = (A11 + A12) * B22
    sumar(A11, A12, AResult, newSize);
    strassen(AResult, B22, M5, newSize);

    // M6 = (A21 - A11) * (B11 + B12)
    restar(A21, A11, AResult, newSize);
    sumar(B11, B12, BResult, newSize);
    strassen(AResult, BResult, M6, newSize);

    // M7 = (A12 - A22) * (B21 + B22)
    restar(A12, A22, AResult, newSize);
    sumar(B21, B22, BResult, newSize);
    strassen(AResult, BResult, M7, newSize);

    // C11 = M1 + M4 - M5 + M7
    sumar(M1, M4, AResult, newSize);
    restar(AResult, M5, BResult, newSize);
    sumar(BResult, M7, C11, newSize);

    // C12 = M3 + M5
    sumar(M3, M5, C12, newSize);

    // C21 = M2 + M4
    sumar(M2, M4, C21, newSize);

    // C22 = M1 - M2 + M3 + M6
    restar(M1, M2, AResult, newSize);
    sumar(AResult, M3, BResult, newSize);
    sumar(BResult, M6, C22, newSize);

    // Combinar los resultados en la matriz final C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}
