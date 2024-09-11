#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include "tar.cpp"

using namespace std;
using namespace std::chrono;

//funcion obtenida a través de chatgpt
void leerMatricesDesdeArchivo(const string& nombreArchivo, vector<vector<int>>& matriz1, vector<vector<int>>& matriz2) {
    ifstream archivo(nombreArchivo);
    string linea;
    vector<int> fila;
    bool leyendoPrimeraMatriz = true;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea.empty()) {
                leyendoPrimeraMatriz = false;
                continue;
            }

            fila.clear();
            stringstream ss(linea);
            int numero;

            while (ss >> numero) {
                fila.push_back(numero);
            }

            if (leyendoPrimeraMatriz) {
                matriz1.push_back(fila);
            } else {
                matriz2.push_back(fila);
            }
        }
        archivo.close();}
}

int** convertirAVectorPunteros(vector<vector<int>>& matriz) {
    int** resultado = new int*[matriz.size()];
    for (size_t i = 0; i < matriz.size(); ++i) {
        resultado[i] = &matriz[i][0];
    }
    return resultado;
}


int main() {
    int i = 0;
    while (i < 12) {
        vector<vector<int>> matriz1, matriz2;
        // Nota: Cambiar nombre de los .txt de acceso cuando sea necesario
        string nombreArchivo = "hilbert_matrices_" + to_string(i) + ".txt";

        leerMatricesDesdeArchivo(nombreArchivo, matriz1, matriz2);

        int** M1 = convertirAVectorPunteros(matriz1);
        int** M2 = convertirAVectorPunteros(matriz2);

        int filas = matriz1.size();
        int columnas = matriz2[0].size();
        vector<vector<int>> matrizResultado(filas, vector<int>(columnas, 0));
        int** M3 = convertirAVectorPunteros(matrizResultado);

        auto inicio = high_resolution_clock::now();

        iterativo_cubico_optimizado(M1, filas, matriz1[0].size(), M2, matriz2.size(), columnas, M3);

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio).count();
        cout << "Tiempo de ejecucion archivo " << i << ": " << duracion << " microsegundos" << endl;

        delete[] M1;
        delete[] M2;
        delete[] M3;
        i += 1;
    }
    return 0;
}
