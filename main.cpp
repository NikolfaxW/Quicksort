#include <iostream>
#include <vector>
#include <list>
#include <ctime> //for measuring time
#include <chrono> //To use delay func
#include <thread> //To apply it on the used thread

using namespace std;

bool DoShowArrays = false;
int arraySizes = 1000;

// Partition function - is used in the quick sort for finding a pivot
int partition(vector<int>& arr, int low, int high) {
    int mid = (low + high) / 2; //finds the serial number for pivot
    int pivot = arr[mid]; // actually saves pivot

    while (low <= high) { //So the left border does not cross right one
        while (arr[low] < pivot) //Is the left border value less than pivot?
            low++; //moves the left border to the pivot
        while (arr[high] > pivot) //Is the right border value bigger than pivot?
            high--; //moves right border to the pivot
        if (low <= high) { //Is the left border not bigger thar right one?
            swap(arr[low], arr[high]); //we swap the values of borders
            low++; //Moves closer to the pivot - to the right
            high--; //Moves closer to the pivot - to the left
        }
    }
    //So while borders do not cross we slowly move them towards each other. We can meet three cases:
    //1.The value of the left side from the pivot is lesser than pivot - it should be so, we skip it. If not, we go to 2.
    //2.The value of right side from the pivot is greater than pivot - it should be so, we skip it. If not, we go to 3.
    //3. The values can meet - the ideal case scenario we exit cycle.
    // However, if not => 1. 2. indicates that we have iterate left and right side to the values which do not belong to them. => They have to be swapped

    return low;
}

// Iterative QuickSort. This version of quick sort does not use recursion in order to save memory.
void quickSort(vector<int>& arr) {
    list<pair<int, int>> ranges; //For array division - makes a front which allows the algorithm to avoid recursion
    //Saves pairs of last and first position
    ranges.push_back({0, (int)arr.size() - 1}); //Creates initial range of the hole array

    while (!ranges.empty()) { //While the list of ranges is not emptied out
        pair<int, int> current = ranges.back(); //chooses the last range from the front
        ranges.pop_back(); //deletes it from the front

        int low = current.first; // stores left border
        int high = current.second; // stores right border

        if (low < high) { //while borders are not same
            int pi = partition(arr, low, high); // find the pivot with Hoare partition scheme
            ranges.push_back({low, pi - 1}); // puts the left range into the front
            ranges.push_back({pi + 1, high}); //puts the right range into the front
        }
    }
}

//BEST CASE
// Random-like balanced data.
// In that case the partitions are evenly balanced. It leads to statistically average time lost per partition.
// Time complexity --> O(nLog_2(n)), where n is the number of elements.
void bestCaseTest() {
    vector<int> arr;
    if(DoShowArrays) {
        cout << "Not sorted array : " << endl;
        for (int i = 0; i < arraySizes; i++) {
            arr.push_back(rand() % arraySizes);
            cout << arr.back() << ' ';
        }
        cout << endl;
    }
    clock_t start = clock();
    quickSort(arr);
    clock_t end = clock();
    if(DoShowArrays) {
        cout << "Sorted array : " << endl;
        for (int i = 0; i < arraySizes; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }
    cout << "Best Case Ticks: " << (end - start) << endl;
    cout << "Seconds: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << endl << endl;
}

//WORST CASE
// Already sorted array
// In that case the partition are unevenly balanced and sorting some leads to many ticks
// Time complexity --> O(n^2), where n is the number of elements.
void worstCaseTest() {
    vector<int> arr;
    if(DoShowArrays) {
        cout << "Not sorted(sorted, lol) array : " << endl;
        for (int i = 0; i < arraySizes; i++) {
            arr.push_back(i);
            cout << i << ' ';
        }
        cout << endl;
    }

    clock_t start = clock();
    quickSort(arr);
    clock_t end = clock();
    if(DoShowArrays) {
        cout << "Sorted array : " << endl;
        for (int i = 0; i < arraySizes; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }
    cout << "Worst Case Ticks: " << (end - start) << endl;
    cout << "Seconds: "
         << (double)(end - start) / CLOCKS_PER_SEC
         << endl << endl;
}



int main() {
    bestCaseTest();
    this_thread::sleep_for(chrono::milliseconds(100));// It is needed in order to have both inputs ok
    worstCaseTest();

    return 0;
}