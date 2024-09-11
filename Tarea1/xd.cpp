#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

void sumar(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

void restar(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
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

vector<vector<int>> leer_matriz(ifstream& file, int n) {
    vector<vector<int>> matriz(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matriz[i][j];
        }
    }
    return matriz;
}

void guardar_matriz(ofstream& file, const vector<vector<int>>& matriz) {
    int n = matriz.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << matriz[i][j] << " ";
        }
        file << endl;
    }
}

int main() {
    string input_file = "matrices.txt";
    string output_file = "resultado.txt";

    ifstream infile(input_file);
    ofstream outfile(output_file);

    if (!infile || !outfile) {
        cerr << "Error al abrir los archivos." << endl;
        return 1;
    }

    int n;
    infile >> n;

    vector<vector<int>> A = leer_matriz(infile, n);
    vector<vector<int>> B = leer_matriz(infile, n);

    vector<vector<int>> C(n, vector<int>(n, 0));

    strassen(A, B, C, n);

    guardar_matriz(outfile, C);

    cout << "Multiplicación de matrices realizada y guardada en " << output_file << endl;

    infile.close();
    outfile.close();

    return 0;
}
