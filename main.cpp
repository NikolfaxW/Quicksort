#include <iostream>
#include <vector>
#include <list>
#include <ctime> //for measuring time
#include <chrono> //To use delay func
#include <thread> //To apply it on the used thread

using namespace std;

bool DoShowArrays = true;
int arraySizes = 100;

// Partition function - is used in the quick sort for finding a pivot
//Another partition function variant, where the right border is chosen as pivot
int partitionRight(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; //Set the right border as pivot
    int i = low - 1;
    for (int j = low; j < high; j++) {
        // if current element is smaller than pivot
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    // put pivot into correct position
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Iterative QuickSort. This version of quick sort does not use recursion in order to save memory.
void quickSort(vector<int> &arr) {
    list<pair<int, int>> ranges; //For array division - makes a stack which allows the algorithm to avoid recursion
    //Saves pairs of last and first position
    ranges.push_back({0, (int) arr.size() - 1}); //Creates initial range of the hole array

    while (!ranges.empty()) { //While the list of ranges is not emptied out
        pair<int, int> current = ranges.back(); //chooses the last range from the stack
        ranges.pop_back(); //deletes it from the stack

        int low = current.first; // stores left border
        int high = current.second; // stores right border

        if (low < high) { //while borders are not same
            int pi = partitionRight(arr, low, high); //Chooses the right border as pivot
            ranges.push_back({low, pi - 1}); // puts the left range into the stack
            ranges.push_back({pi + 1, high}); //puts the right range into the stack
        }
    }
}



//BEST CASE
// Random-like data.
// Random distribution tends to produce relatively balanced partitions, even though pivot is always the last element.
// This leads to average-case behavior.
void bestCaseTest() {
    vector<int> arr;

    if (DoShowArrays) cout << "Not sorted array : " << endl;
    for (int i = 0; i < arraySizes; i++) {
        arr.push_back(rand() % arraySizes);
        if (DoShowArrays) cout << arr.back() << ' ';
    }
    if (DoShowArrays)cout << endl;

    clock_t start = clock();
    quickSort(arr);
    clock_t end = clock();
    if (DoShowArrays) {
        cout << "Sorted array : " << endl;
        for (int i = 0; i < arraySizes; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }
    cout << "Best Case Ticks: " << (end - start) << endl;
    cout << "Seconds: "
         << (double) (end - start) / CLOCKS_PER_SEC
         << endl << endl;
}

//WORST CASE
// Already sorted array
// In that case the partition are unevenly balanced due to the pivot being always chosen the largest.
// Sorting some leads to many ticks.
// Time complexity --> O(n^2), where n is the number of elements.
void worstCaseTest() {
    vector<int> arr;

    if (DoShowArrays)cout << "Not sorted(sorted, lol) array : " << endl;
    for (int i = 0; i < arraySizes; i++) {
        arr.push_back(i);
        if (DoShowArrays)cout << i << ' ';
    }
    if (DoShowArrays)cout << endl;


    clock_t start = clock();
    quickSort(arr);
    clock_t end = clock();
    if (DoShowArrays) {
        cout << "Sorted array : " << endl;
        for (int i = 0; i < arraySizes; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }
    cout << "Worst Case Ticks: " << (end - start) << endl;
    cout << "Seconds: "
         << (double) (end - start) / CLOCKS_PER_SEC
         << endl << endl;
}


int main() {
    bestCaseTest();
    this_thread::sleep_for(chrono::milliseconds(100));// It is needed in order to have both inputs ok
    worstCaseTest();

    return 0;
}
//Zdroje
//Virius, M.: Základy algoritmizace. České vysoké učení technické v Praze, 2018.
//Jehož přednášky