//
// Created by ubecerril on 2/1/26.
//
#include <iostream>
#include<vector>

using namespace std;

// Prototype functions for the first solution
void biggestArea(const vector<vector<int>>& m);
bool existsInside(const vector<vector<int>>& m, int x, int y);

// Prototype functions for the second solution
void biggestAreaOptimal(const vector<vector<int>>& m);
int min(int a, int b, int c);
int max(int a, int b);

int main(int argc, char *argv[]) {
    const vector<vector<int>> matrix {
                {0,0,0,0,0},
                {0,1,1,1,0},
                {0,1,1,1,0},
                {0,1,1,1,0},
                {0,0,0,0,0}
    };

    // First solution
    biggestArea(matrix);

    // Second solution (optimal)
    biggestAreaOptimal(matrix);
}

// Methods for the first solution
void biggestArea(const vector<vector<int>>& m) {
    // Start with the biggest possible square (assuming a square matrix)
    int y;
    int x = static_cast<int> (m.size());
    y=x;

    // Check if we have a square inside the matrix as big as the current square
    while (x > 0 && y > 0) {
        if (existsInside(m, x, y)) {
            break;
        }
        // Decrease the square size by one
        --x;
        --y;
    }
    cout << "The possible maximum area is: " << x*y << endl;
}
bool existsInside(const vector<vector<int>>& m, const int x, const int y) {
    for (int i = 0; i < m.size() -x + 1; ++i) {
        for (int j = 0; j < m[i].size() -y + 1; ++j) {
            bool exists = true;
            for (int z = 0; z<x;++z) {
                for (int k = 0; k < y;++k) {
                    if (m[i+z][j+k] == 0)
                        exists = false;
                }
            }
            if (exists)
                return true;
        }
    }
    return false;
}

// Methods for the second solution
void biggestAreaOptimal(const vector<vector<int>>& m) {
    // New matrix of the original size all in zeros
    vector<vector<int>> squareSides  (m.size(), vector<int>(m[0].size() ,0));

    int maxSide{0};

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            if (m[i][j] == 1) {
                if (i == 0 || j == 0) {
                    squareSides[i][j] = 1;
                }else { // Each cell in the new matrix indicates the left-up square's side it is part of
                    squareSides[i][j] =1 + min(squareSides[i-1][j], squareSides[i][j-1], squareSides[i-1][j-1]);
                }
                maxSide = max(maxSide, squareSides[i][j]);
            }
        }
    }
    cout << "The prossible maximum area (optimal) is: " << maxSide * maxSide << endl;
}
int min(const int a, const int b, const int c) {
    return (a <= b && a <= c) ? a : (b <= c ? b : c);
}
int max(const int a, const int b) {
    return a >= b ? a : b;
}