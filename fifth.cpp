#include <bits/stdc++.h>
using namespace std;

int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for(int j = low; j<high; j++) {
        if(arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1; 
}

void quickSort(vector<int> &arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int randomPartition(vector<int> &arr, int low, int high) {
    int randomPivot = low + rand() % (high - low + 1);
    swap(arr[randomPivot], arr[high]);
    return partition(arr, low, high);
}

void randomQuickSort(vector<int> &arr, int low, int high) {
    if(low < high) {
        int pi = randomPartition(arr, low, high);
        randomQuickSort(arr, low, pi-1);
        randomQuickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    cout<<"Enter Array size: ";
    cin>>n;

    vector<int> arr;
    for(int i =0; i<n; i++) {
        int k;
        cin>>k;
        arr.push_back(k);
    }

    vector<int> arr1 = arr;
    quickSort(arr1, 0, arr1.size() -1);
    cout<<"Deterministic Quick Sort: ";
    for(int x : arr1) cout<<x<<" ";

    vector<int> arr2 = arr;
    randomQuickSort(arr2, 0, arr2.size() - 1);
    cout<<"Randomized Quick Sort: ";
    for(int x : arr2) cout<<x<<" ";
}