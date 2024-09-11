#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "tarea.cpp"

using namespace std;
using namespace std::chrono;

int main() {
    int count = 0;
    while (count <= 5) {
        cout << count;
        // Nota: Cambiar nombre de los .txt de acceso cuando sea necesario
        string data = "desordenadoyordenado" + to_string(count) + ".txt";
        string ordenado = "Selectionsort_ordenado" + to_string(count) + ".txt";

        ifstream dataset(data);
        ofstream dataset_ordenado(ordenado);

        if (!dataset) {
            cerr << "No se pudo abrir el archivo de entrada: " << data << endl;
            return 1;
        }

        vector<int> datos;
        int numero;
        while (dataset >> numero) {
            datos.push_back(numero);
        }

        dataset.close();

        int n = datos.size();
        if (n == 0) {
            cerr << "El archivo de entrada está vacío: " << data << endl;
            count++;
            continue; // Pasar al siguiente archivo
        }

        auto inicio = high_resolution_clock::now();
        selection_sort(datos.data(), n);                                    // Importante: Solo se debe usar un algoritmo a la vez
        //mergeSort(datos.data(), 0, n);
        //quick_sort(datos.data(), 0, n-1);
        //heap_sort(datos.data(), n);
        auto final = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(final - inicio);

        if (dataset_ordenado.is_open()) {
            for (int i = 0; i < n; i++) {
                dataset_ordenado << datos[i] << ' ';
            }
            dataset_ordenado.close();
            cout << "Datos ordenados y escritos en " << ordenado << endl;
            cout << "Tiempo de ordenación del archivo " << data << ": " << duration.count() << " us" << endl;
        } else {
            cerr << "No se pudo abrir el archivo de salida: " << ordenado << endl;
            return 1;
        }

        count++;
    }

    return 0;
}


