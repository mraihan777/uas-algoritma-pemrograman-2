#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void findPairs(vector<int>& arr1, vector<int>& arr2, int K) {
    unordered_map<int, bool> map1; // Menyimpan elemen arr1

    // Memasukkan elemen arr1 ke hash map
    for (int num : arr1) {
        map1[num] = true;
    }

    cout << "Pasangan yang jumlahnya " << K << ":\n";
    for (int num2 : arr2) {
        int complement = K - num2;
        if (map1.count(complement)) { // Memeriksa apakah complement ada di map
            cout << "(" << complement << ", " << num2 << ")\n";
        }
    }
}

int main() {
	
	cout << "Nama  : Muhammad Raihan" << endl;
	cout << "NIM   : 231011401201" << endl;
	cout << "Kelas : 03TPLP029" << endl <<endl;
	
    vector<int> arr1 = {1, 2, 3, 4, 5};
    vector<int> arr2 = {2, 4, 6, 8, 10};
    int K = 7;

    findPairs(arr1, arr2, K);

    arr1 = {1, 2, 3, 4, 5};
    arr2 = {1, 2, 3, 4, 5};
    K = 6;
    findPairs(arr1, arr2, K);

    return 0;
}
