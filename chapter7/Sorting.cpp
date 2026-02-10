#include <algorithm>
#include<iostream>
#include <queue>
#include <vector>

using namespace std;

void insertionSort(vector<int> m) ;
void shellSort(vector<int> m);
void heapSort(vector<int> m);
void mergeSort(vector<int> m);
    void mergeSort(vector<int>& a, vector<int>& temp, int left, int right);
    void merge(vector<int>& a, vector<int>& temp, int left, int center, int right);
void quickSort(vector<int> m);
void quickSort(vector<int>& m, int left, int right);
int median(vector<int>& m, int left, int right);

void printArray(const vector<int>& m);

int main(int argc, char *argv[]) {
    cout << "This program shows different algorithms to sort an array" << endl;
    const vector<int> input {34, 2, 1, 34, 7, 3, 76, 43, 56, 7, 4, 4, 235, 234, 5, 25, 2, 45, 52, 5, 245, 3, 5, 6, 2, 6, 5, 3, 4, 7, 636, 7, 3, 34};

    insertionSort(input);
    shellSort(input);
    heapSort(input);
    mergeSort(input);
    quickSort(input);
}

void insertionSort(vector<int> m) {
    cout << "Insertion sort: " << endl;

    for (int i = 1; i < m.size(); i++) {
        const int toInsert = m[i];
        int j;
        for (j = i; j > 0 && toInsert < m[j-1]; j--) {
            m[j] = m[j - 1];
        }
        m[j] = toInsert;
    }

    printArray(m);
}

void shellSort(vector<int> m) {
    cout << "Shell sort: " << endl;
    for (size_t gap = m.size() / 2; gap > 0; gap /=2) {
        for (size_t i = gap; i<m.size(); i++) {
            const int toInsert = m[i];

            size_t j;
            for (j = i; j >= gap && toInsert < m[j-gap]; j -= gap) {
                m[j] = m[j-gap];
            }
            m[j] = toInsert;
        }
    }
    printArray(m);
}

void heapSort(vector<int> m) {
    cout << "Heap sort: " << endl;
    // Make the vector a heap (priority queue)
    priority_queue<int, vector<int>, greater<>> pq (m.begin(), m.end());

    cout << "[";
    while (!pq.empty()) {
        const int top = pq.top();
        pq.pop();
        if (pq.empty()) {
            cout << top << "]";
        }else {
            cout << top << ", ";
        }
    }
    cout << endl;
}

void mergeSort(vector<int> m) {
    cout << "Merge sort: " << endl;

    vector<int> temp(m.size());
    mergeSort(m, temp, 0, m.size()-1);

    printArray(m);
}
void mergeSort(vector<int>& a, vector<int>& temp, int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        mergeSort(a, temp, left, center);
        mergeSort(a, temp, center + 1, right);
        merge(a, temp, left, center + 1, right);
    }
}
void merge(vector<int>& a, vector<int>& temp, int left, int center, int right) {
    int endLeft = center -1;
    // This indicates the position in the temp array where we must put the merged elements
    int tempPost = left;

    // Save the number of elements
    int elements = right - left + 1;

    // Merge the arrays
    while (left <= endLeft && center <= right) {
        if (a[left] < a[center]) {
            temp[tempPost++] = a[left++];
        }else {
            temp[tempPost++] = a[center++];
        }
    }

    // Rest of the arrays copied into temp
    while (center <= right) {
        temp[tempPost++] = a[center++];
    }
    while (left <= endLeft) {
        temp[tempPost++] = a[left++];
    }

    // Copy the result in temp back into a
    for (int i =0; i < elements; i++, right--) {
        a[right] = temp[right];
    }
}

void quickSort(vector<int> m) {
    cout << "Quick sort: " << endl;
    quickSort(m, 0, m.size()-1);
    printArray(m);
}
void quickSort(vector<int> &m, int left, int right) {
    if (left + 10 <= right) {
        int v = median(m, left, right);

        // Partitioning
        int i = left, j = right-1;
        for ( ; ; ) {
            while (m[++i] < v){}
            while (m[--j] > v){}
            if (i < j) {
                swap(m[i], m[j]);
            }else {
                break;
            }
        }

        // Bring back the pivot to the correct position
        swap(m[i], m[right-1]);

        quickSort(m, left, i-1);
        quickSort(m, i+1, right);

    }else { // use another sort method (insertion sort)
        sort(m.begin() + left, m.begin() + right + 1);
    }
}
int median(vector<int> &m, int left, int right) {
    int center = (left + right) / 2;

    // Leave the median at the center
    if (m[left] < m[center] )
        swap(m[left], m[center]);
    if (m[right] < m[left])
        swap(m[right], m[left]);
    if (m[right] < m[center])
        swap(m[center], m[right]);

    swap (m[left], m[right-1]);
    return m[right-1];
}

void printArray(const vector<int>& m) {
    cout << "[";
    for (int i = 0; i < m.size(); i++) {
        if (i == m.size() - 1) {
            cout << m[i]  << "]" << endl;
        }else {
            cout << m[i] << ", ";
        }
    }
}