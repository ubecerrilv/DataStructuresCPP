//
// Created by ubecerril on 3/20/26.
//

#include <iostream>
#include <ostream>

using namespace std;

int numberOfOnesIn(const int n) {
    if (n==0) return 0;
    return n%2 + numberOfOnesIn(n/2);
}

int main(int argc, char *argv[]) {
    cout << "Type the number to know its number of ones in its binary representation: " << endl;
    int n ;
    cin >> n;

    cout << "The number of ones in " << n << " is: " << numberOfOnesIn(n) << endl;
}
