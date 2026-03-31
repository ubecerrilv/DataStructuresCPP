//
// Created by ubecerril on 3/25/26.
//
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
int groupCeros(const vector<int> &x ) {
    vector<int> pos;

    for (int i = 0; i < x.size(); i++) {
        if (x[i] == 0) pos.push_back(i);
    }
    if (pos.size() == 0) return false;

    // Get median
    const int middle = pos.size() / 2;
    const int median = pos[middle];

    // Get the sum for each cero
    int res{0};
    for (int i = 0; i < pos.size(); i++) {
        res += abs(pos[i] - (median - (middle - i)));
    }
    return res;
}

int minInside(const vector<int> &x, const int begin, const int end) {
    int res{x[begin]};
    for (int i = begin; i <= end; i++) {
        if (x[i] < res) res = x[i];
    }
    return res;
}
int maxMinSubarray(const vector<int> &x, const int k) {
    if (x.size() == 0) return 0;

    // Go the firs k elements looking for the first minimum
    int min = x[0];
    for (int i = 1; i<k; i++) {
        if (x[i] < min) min = x[i];
    }

    int begin = 0, end = k - 1;
    int maxMin = min;
    while (end < x.size()) {
        int newMin = minInside(x, begin, end);
        maxMin = max(maxMin, newMin);
        begin++;
        end++;
    }
    return maxMin;
}
int main(int argc, char *argv[]) {
    //cout << groupCeros({1,0,1,0,1}) << endl;
    cout << maxMinSubarray({8,2,4,6,5},3) << endl;
}
