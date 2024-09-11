#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include "tar.cpp"

using namespace std;
using namespace std::chrono;

void leerMatricesDesdeArchivo(const string& nombreArchivo, vector<vector<double>>& matriz1, vector<vector<double>>& matriz2) {
    ifstream archivo(nombreArchivo);
    string linea;
    vector<double> fila;
    bool leyendoPrimeraMatriz = true;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea.empty()) {
                leyendoPrimeraMatriz = false;
                continue;
            }

            fila.clear();
            stringstream ss(linea);
            double numero;

            while (ss >> numero) {
                fila.push_back(numero);
            }

            if (leyendoPrimeraMatriz) {
                matriz1.push_back(fila);
            } else {
                matriz2.push_back(fila);
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }
}

double** convertirAVectorPunteros(vector<vector<double>>& matriz) {
    double** resultado = new double*[matriz.size()];
    for (size_t i = 0; i < matriz.size(); ++i) {
        resultado[i] = new double[matriz[i].size()];
        for (size_t j = 0; j < matriz[i].size(); ++j) {
            resultado[i][j] = matriz[i][j];
        }
    }
    return resultado;
}

int** convertirAVectorPunteros(vector<vector<int>>& matriz) {
    int** resultado = new int*[matriz.size()];
    for (size_t i = 0; i < matriz.size(); ++i) {
        resultado[i] = new int[matriz[i].size()];
        for (size_t j = 0; j < matriz[i].size(); ++j) {
            resultado[i][j] = matriz[i][j];
        }
    }
    return resultado;
}

int** convertirADoubleAPunterosEnteros(double** matriz, int filas, int columnas) {
    int** resultado = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        resultado[i] = new int[columnas];
        for (int j = 0; j < columnas; ++j) {
            resultado[i][j] = static_cast<int>(matriz[i][j]);
        }
    }
    return resultado;
}

template<typename T>
void liberarMatriz(T** matriz, int filas) {
    for (int i = 0; i < filas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

int main() {
    for (int i = 0; i < 12; ++i) {
        vector<vector<double>> matriz1, matriz2;

        string nombreArchivo = "hilbert_matrices_" + to_string(i) + ".txt";
        leerMatricesDesdeArchivo(nombreArchivo, matriz1, matriz2);

        if (matriz1.empty() || matriz2.empty()) {
            cout << "Error al leer las matrices del archivo: " << nombreArchivo << endl;
            continue;
        }

        int filas = matriz1.size();
        int columnas = matriz2[0].size();

        double** M1_double = convertirAVectorPunteros(matriz1);
        double** M2_double = convertirAVectorPunteros(matriz2);

        int** M1 = convertirADoubleAPunterosEnteros(M1_double, filas, matriz1[0].size());
        int** M2 = convertirADoubleAPunterosEnteros(M2_double, matriz2.size(), columnas);

        vector<vector<int>> matrizResultado(filas, vector<int>(columnas, 0));
        int** M3 = convertirAVectorPunteros(matrizResultado);  // Utiliza la versión de `int`

        auto inicio = high_resolution_clock::now();
        iterativo_cubico_optimizado(M1, filas, matriz1[0].size(), M2, matriz2.size(), columnas, M3);
        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio).count();

        cout << "Tiempo de ejecucion archivo " << i << ": " << duracion << " microsegundos" << endl;
        liberarMatriz(M1, filas);
        liberarMatriz(M2, matriz2.size());
        liberarMatriz(M3, filas);
        liberarMatriz(M1_double, filas);
        liberarMatriz(M2_double, matriz2.size());
    }
    return 0;
}

