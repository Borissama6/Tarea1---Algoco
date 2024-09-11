#include <iostream>
using namespace std;


// Selection sort
void selection_sort(int arreglo[], int n){
    int minimo, min_actual, aux;
    for(int i = 0; i < n - 1; i++){
        minimo = arreglo[i];
        for (int c = i + 1; c < n; c++){
            if (minimo > arreglo[c]){
                minimo = arreglo[c];
                min_actual = c;
            }
        }
        if (minimo != arreglo[i]){
            aux = arreglo[i];
            arreglo[i] = minimo;
            arreglo[min_actual] = aux;
        }
    }
}


// Merge sort
void merge(int arr[], int left, int mid, int right) {
    int izq = mid - left + 1;
    int der = right - mid;

    int L[izq], R[der];

    for(int i = 0; i < izq; i++){
        L[i] = arr[left + i];
    }
    for(int k = 0; k < der; k++){
        R[k] = arr[mid + k + 1];
    }

    int i = 0, j = 0, k = left;
    while (i < izq && j < der) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < izq) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < der) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick sort
int partition(int arreglo[], int left, int right) {
    int pivote = arreglo[right], aux; // Seleccionamos el último elemento como pivote
    int i = left - 1; // Índice del menor elemento

    for (int j = left; j < right; ++j) {
        if (arreglo[j] <= pivote) {
            ++i;
            aux = arreglo[i];
            arreglo[i] = arreglo[j];
            arreglo[j] = aux;
        }
    }
    aux = arreglo[i + 1];
    arreglo[i + 1] = arreglo[right];
    arreglo[right] = aux;
    return i + 1;
}

void quick_sort(int arreglo[], int left, int right) {
    if (left < right) {
        int pivote = partition(arreglo, left, right);
        quick_sort(arreglo, left, pivote - 1);
        quick_sort(arreglo, pivote + 1, right);
    }
}


// Heap Sort
void heapify(int arreglo[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1; 
    int right = 2 * i + 2;

    if (left < n && arreglo[left] > arreglo[largest])
        largest = left;

    if (right < n && arreglo[right] > arreglo[largest])
        largest = right;

    if (largest != i) {
        int aux = arreglo[largest];
        arreglo[largest] = arreglo[i];
        arreglo[i] = aux;
        heapify(arreglo, n, largest);
    }
}

void heap_sort(int arreglo[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arreglo, n, i);

    for (int i = n - 1; i > 0; i--) {
        int aux = arreglo[0];
        arreglo[0] = arreglo[i];
        arreglo[i] = aux;
        heapify(arreglo, i, 0);
    }
}

void print(int arreglo[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}
