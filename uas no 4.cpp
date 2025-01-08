#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Fungsi untuk mendapatkan digit ke-i dari angka
int getDigit(int num, int i) {
    int divisor = 1;
    for (int j = 0; j < i; j++) {
        divisor *= 10;
    }
    return (num / divisor) % 10;
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = *max_element(arr.begin(), arr.end());
    int numDigits = 0;
    while (maxVal > 0) {
        maxVal /= 10;
        numDigits++;
    }

    for (int i = 0; i < numDigits; i++) {
        vector<vector<int>> buckets(10);
        for (int num : arr) {
            int digit = getDigit(num, i);
            buckets[digit].push_back(num);
        }
        arr.clear();
        for (auto& bucket : buckets) {
            arr.insert(arr.end(), bucket.begin(), bucket.end());
        }
    }
}

// Fungsi partisi untuk Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Fungsi merge untuk Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

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

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
	
	cout << "Nama  : Muhammad Raihan" << endl;
	cout << "NIM   : 231011401201" << endl;
	cout << "Kelas : 03TPLP029" << endl << endl;
	
    vector<int> data = {170, 45, 75, 90, 802, 24, 2, 66};

    vector<int> data_radix = data;
    auto start = high_resolution_clock::now();
    radixSort(data_radix);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Radix Sort Time: " << duration.count() << " microseconds" << endl;


    vector<int> data_quick = data;
    start = high_resolution_clock::now();
    quickSort(data_quick, 0, data_quick.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Quick Sort Time: " << duration.count() << " microseconds" << endl;

    vector<int> data_merge = data;
    start = high_resolution_clock::now();
    mergeSort(data_merge, 0, data_merge.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Merge Sort Time: " << duration.count() << " microseconds" << endl;

    return 0;
}
