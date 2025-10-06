#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <windows.h> //colors

using namespace std;
using namespace std::chrono_literals;

// ----------- Global Settings -----------
int VISUAL_SPEED_MS = 1000; // visualization delay --> 1000 looks the best
int COMPARISONS = 0;
int SWAPS = 0;

// ----------- Utility Functions -----------

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printArray(const vector<int>& arr, int highlightA = -1, int highlightB = -1) {
    system("cls"); // clear screen
    for (int i = 0; i < arr.size(); ++i) {
        if (i == highlightA || i == highlightB)
            setColor(12); // red 
        else
            setColor(7);  // default

        cout << arr[i] << " ";
    }
    cout << "\n";
    setColor(7);
    this_thread::sleep_for(chrono::milliseconds(VISUAL_SPEED_MS));
}

vector<int> generateArray(int n, int maxVal = 20) {
    vector<int> arr(n);
    srand(time(nullptr));
    for (int& x : arr)
        x = rand() % maxVal + 1;
    COMPARISONS = 0;
    SWAPS = 0;
    return arr;
}

// ----------- Sorting Algorithms -----------

void bubbleSort(vector<int> arr) {
    cout << "Bubble Sort Visualization\n\n";
    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            COMPARISONS++;
            printArray(arr, j, j + 1);
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                SWAPS++;
            }
        }
    }
    printArray(arr);
    cout << "Sorted! Comparisons: " << COMPARISONS << " Swaps: " << SWAPS << "\n";
}

void insertionSort(vector<int> arr) {
    cout << "Insertion Sort Visualization\n\n";
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            COMPARISONS++;
            arr[j + 1] = arr[j];
            SWAPS++;
            printArray(arr, j, j + 1);
            j--;
        }
        arr[j + 1] = key;
        SWAPS++;
    }
    printArray(arr);
    cout << "Sorted! Comparisons: " << COMPARISONS << " Swaps: " << SWAPS << "\n";
}

void selectionSort(vector<int> arr) {
    cout << "Selection Sort Visualization\n\n";
    for (int i = 0; i < arr.size() - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            COMPARISONS++;
            printArray(arr, minIndex, j);
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
        SWAPS++;
    }
    printArray(arr);
    cout << "Sorted! Comparisons: " << COMPARISONS << " Swaps: " << SWAPS << "\n";
}

// ----------- Merge Sort -----------

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < L.size() && j < R.size()) {
        COMPARISONS++;
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        SWAPS++;
        printArray(arr, k - 1);
    }
    while (i < L.size()) { arr[k++] = L[i++]; SWAPS++; printArray(arr, k - 1); }
    while (j < R.size()) { arr[k++] = R[j++]; SWAPS++; printArray(arr, k - 1); }
}

void mergeSortRec(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortRec(arr, left, mid);
    mergeSortRec(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(vector<int> arr) {
    cout << "Merge Sort Visualization\n\n";
    mergeSortRec(arr, 0, arr.size() - 1);
    printArray(arr);
    cout << "Sorted! Comparisons: " << COMPARISONS << " Swaps: " << SWAPS << "\n";
}

// ----------- Quick Sort -----------

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        COMPARISONS++;
        printArray(arr, j, high);
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]), SWAPS++;
    }
    swap(arr[i + 1], arr[high]);
    SWAPS++;
    return i + 1;
}

void quickSortRec(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortRec(arr, low, pi - 1);
        quickSortRec(arr, pi + 1, high);
    }
}

void quickSort(vector<int> arr) {
    cout << "Quick Sort Visualization\n\n";
    quickSortRec(arr, 0, arr.size() - 1);
    printArray(arr);
    cout << "Sorted! Comparisons: " << COMPARISONS << " Swaps: " << SWAPS << "\n";
}

// ----------- Main Menu -----------

int main() {
    int size, maxVal, speed;
    cout << "Welcome to Sorting Visualizer!\n";
    cout << "Enter array size: ";
    cin >> size;
    cout << "Enter max value: ";
    cin >> maxVal;
    cout << "Enter visualization speed (ms, e.g., 100): ";
    cin >> speed;
    VISUAL_SPEED_MS = speed;

    vector<int> arr = generateArray(size, maxVal);
    int choice;

    while (true) {
        cout << "\n========== Sorting Visualizer ==========\n";
        cout << "1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Merge Sort\n5. Quick Sort\n";
        cout << "6. Generate New Array\n7. Change Speed\n0. Exit\nChoose: ";
        cin >> choice;

        switch (choice) {
            case 1: bubbleSort(arr); break;
            case 2: insertionSort(arr); break;
            case 3: selectionSort(arr); break;
            case 4: mergeSort(arr); break;
            case 5: quickSort(arr); break;
            case 6: arr = generateArray(size, maxVal); break;
            case 7:
                cout << "Enter new speed (ms): ";
                cin >> speed;
                VISUAL_SPEED_MS = speed;
                break;
            case 0: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice.\n"; break;
        }

        cout << "\nPress Enter to return to menu...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
