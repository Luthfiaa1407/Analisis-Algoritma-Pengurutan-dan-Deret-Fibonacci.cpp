#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

void measureTime(void (*sortFunc)(int[], int), int arr[], int n, const string& sortName, const string& dataType) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << sortName << " (" << dataType << "): " << duration.count() << " microseconds" << endl;
}

void measureTime(void (*sortFunc)(int[], int, int), int arr[], int low, int high, const string& sortName, const string& dataType) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, low, high);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << sortName << " (" << dataType << "): " << duration.count() << " microseconds" << endl;
}

int main() {
    vector<int> sizes = {10, 100, 500, 1000, 10000};
    
    for (int n : sizes) {
        int* randomArr = new int[n];
        int* reverseArr = new int[n];
        int* sortedArr = new int[n];

        for (int i = 0; i < n; i++) {
            randomArr[i] = rand() % 10000;
        }

        copyArray(randomArr, reverseArr, n);
        sort(reverseArr, reverseArr + n, greater<int>());

        copyArray(randomArr, sortedArr, n);
        sort(sortedArr, sortedArr + n);

        int* arr = new int[n];
        cout << "Array Size: " << n << endl;

        cout << "Random"<<endl;
        copyArray(randomArr, arr, n);
        measureTime(bubbleSort, arr, n, "Bubble Sort", "Random");

        copyArray(randomArr, arr, n);
        measureTime(insertionSort, arr, n, "Insertion Sort", "Random");

        copyArray(randomArr, arr, n);
        measureTime(selectionSort, arr, n, "Selection Sort", "Random");

        copyArray(randomArr, arr, n);
        measureTime(mergeSort, arr, 0, n-1, "Merge Sort", "Random");

        copyArray(randomArr, arr, n);
        measureTime(quickSort, arr, 0, n-1, "Quick Sort", "Random");

        cout << endl;

        cout << "Reverse Sorted"<<endl;
        copyArray(reverseArr, arr, n);
        measureTime(bubbleSort, arr, n, "Bubble Sort", "Reverse Sorted");

        copyArray(reverseArr, arr, n);
        measureTime(insertionSort, arr, n, "Insertion Sort", "Reverse Sorted");

        copyArray(reverseArr, arr, n);
        measureTime(selectionSort, arr, n, "Selection Sort", "Reverse Sorted");

        copyArray(reverseArr, arr, n);
        measureTime(mergeSort, arr, 0, n-1, "Merge Sort", "Reverse Sorted");

        copyArray(reverseArr, arr, n);
        measureTime(quickSort, arr, 0, n-1, "Quick Sort", "Reverse Sorted");

        cout<< endl;

        cout << "Sorted" << endl;
        copyArray(sortedArr, arr, n);
        measureTime(bubbleSort, arr, n, "Bubble Sort", "Sorted");

        copyArray(sortedArr, arr, n);
        measureTime(insertionSort, arr, n, "Insertion Sort", "Sorted");

        copyArray(sortedArr, arr, n);
        measureTime(selectionSort, arr, n, "Selection Sort", "Sorted");

        copyArray(sortedArr, arr, n);
        measureTime(mergeSort, arr, 0, n-1, "Merge Sort", "Sorted");

        copyArray(sortedArr, arr, n);
        measureTime(quickSort, arr, 0, n-1, "Quick Sort", "Sorted");

        cout << endl;

        delete[] randomArr;
        delete[] reverseArr;
        delete[] sortedArr;
        delete[] arr;
        
        cout << endl;
    }

    return 0;
}
