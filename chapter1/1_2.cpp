//
// Created by ubecerril on 1/5/26.
//

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Prototype functions
void solve(const vector<string>& words, const vector<vector<char>>& puzzle, const vector<pair<int,int>>& orientations);

int main() {
    const vector<vector<char>> puzzle {
        {'t', 'h', 'i', 's'},
        {'w', 'a', 't', 's'},
        {'o', 'a', 'h', 'g'},
        {'f', 'g', 'd', 't'}
    };
    const vector<string> words {"this", "two", "fat", "that"};
    const vector<pair<int,int>> orientations {
        {1,0},
        {1,1},
        {0,1},
        {-1,1},
        {-1,0},
        {-1,-1},
        {0,-1},
        {1,-1},
    };
    cout << "This program solves the word puzzle in a very bad way" << endl;
    cout << "=========================================================" << endl;
    cout << "The words are:" << endl;
    for (auto& w : words)
        cout << w << endl;

    cout << "The puzzle is:" << endl;
    for (auto& row : puzzle) {
        for (auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    cout << "Solution:" << endl;
    solve(words, puzzle, orientations);

    cout << "====================================" << endl;
}

void solve(const vector<string>& words, const vector<vector<char>>& puzzle, const vector<pair<int,int>>& orientations) {
    for (const auto& word : words) {
        for (int i = 0 ; i < puzzle.size(); ++i) { // For each row
            for (int j = 0 ; j < puzzle[i].size(); ++j) { // For each column
                for (const auto& orientation : orientations) { // For each orientation
                    // Check bounds
                    const int wordLen   = static_cast<int>(word.size());
                    const int puzzleLen = static_cast<int>(puzzle.size());

                    if (i + orientation.first * (wordLen - 1) < 0 || // Left bound
                        i + orientation.first * wordLen > puzzleLen || // Right bound
                        j + orientation.second * (wordLen - 1) < 0 || // Upper bound
                        j + orientation.second * wordLen > puzzleLen) // Lower bound
                        continue; // Go to next orientation

                    // Create new possible word
                    string newWord;
                    for (size_t k = 0 ; k < word.size(); ++k) {
                        newWord += puzzle[i + (orientation.first*k)][j + (orientation.second*k)];
                    }

                    // Compare to the word we are looking for
                    if (newWord == word)
                        cout << "Word \"" << word << "\" found at position (" << i << ", " <<j << ") with orientation (" << orientation.first << ", " << orientation.second << ")" << endl;
                }
            }
        }
    }
}