//
// Created by ubecerril on 12/17/25.
//

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Prototype functions
int solve(vector<int> numbers, int k);
int secondSolution(vector<int> numbers, int k);

int main () {
    const vector<int> numbers {
        42, 17, 93, 58, 21, 76, 34, 89, 5, 61,
        72, 14, 67, 29, 90, 3, 81, 46, 55, 38,
        64, 11, 97, 24, 70, 19, 86, 31, 49, 8,
        60, 27, 75, 12, 99, 40, 68, 22, 84, 6,
        57, 33, 91, 16, 73, 26, 88, 44, 52, 10
      };
    const int k = numbers.size()/2;

    cout << "This program solves the selection problem in two different ways" << endl;
    cout << "===============================================================" << endl;
    cout << "1.- Sort the array in decreasing order and return the element in position k" << endl;
    cout << solve(numbers, k) << endl;
    cout << "2.- Sort the first k elements, place each next element in its correct spot and finally return the k element" << endl;
    cout << secondSolution(numbers, k) << endl;
}

int solve(vector<int> numbers, const int k) {
    if (k > numbers.size())
        return 0;
    sort(numbers.begin(), numbers.end(), [](const int a, const int b){return a > b;});
    return numbers[k-1];
}

int secondSolution( vector<int> numbers, const int k )
{
    if( k > numbers.size() )
        return 0;
    // Sort first k elements
    vector<int> shortenArray( numbers.begin(), numbers.begin() + k);
    sort( shortenArray.begin(), shortenArray.end(), [](const int a, const int b){return a > b;} );

    // Place each next element in its correct spot
    for( int i = k; i<numbers.size(); ++i )
    {
        if( numbers[ i ] > shortenArray[ k - 1 ] )
        {
            int j = k - 2;
            while( j>=0 && numbers[ i ] > shortenArray[j] )
            {
                shortenArray[j + 1] = shortenArray[j];
                --j;
            }
            shortenArray[j+1] = numbers[i];
        }
    }
    // Return the k element
    return shortenArray[k-1];
}
