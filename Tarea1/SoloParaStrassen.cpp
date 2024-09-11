#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include "tar.cpp"

using namespace std;
using namespace std::chrono;

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
        archivo.close();
    }
}

int main() {
    for (int i = 0; i <= 11; ++i) {
        vector<vector<int>> matriz1, matriz2;
        // Nota: Cambiar nombre de los .txt de acceso cuando sea necesario
        string nombreArchivo = "matricescxf" + to_string(i) + ".txt";
        cout << "Leyendo archivo: " << nombreArchivo << endl;

        leerMatricesDesdeArchivo(nombreArchivo, matriz1, matriz2);

        if (matriz1.empty() || matriz2.empty()) {
            cout << "Error al leer las matrices del archivo: " << nombreArchivo << endl;
            continue;
        }
        
        int n = matriz1.size();
        vector<vector<int>> matrizResultado(n, vector<int>(n, 0));
        if (matriz1.size() != matriz2.size() || matriz1.size() != matrizResultado.size()) {
            cout << "Las matrices no tienen el mismo tamaño. No se puede ejecutar Strassen." << endl;
            continue;
        }
        auto inicio = high_resolution_clock::now();

        strassen(matriz1, matriz2, matrizResultado, n);

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<microseconds>(fin - inicio).count();

        cout << "Tiempo de ejecucion para " << nombreArchivo << ": " << duracion << " microsegundos" << endl;
    }

    return 0;
}
