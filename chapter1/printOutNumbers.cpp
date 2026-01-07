#include <iostream>

using namespace std;

// Prototype functions
void printInteger(int number);
void printDouble(double number);
void printDigit(int digit);

int main()
{
    printInteger(76234);
    cout << endl;

    printDouble(76234.734);
    cout << endl;
}

void printInteger(const int number)
{
    if(number >= 10)
        printInteger(number / 10);
    printDigit(number % 10);
}

void printDouble(double number) {
    if(number < 0.0) {
        cout<<"-";
        number = -number;
    }
    int integer = (int)number;
    double decimal = number-integer;

    // Print integer part
    if (integer >= 10)
        printInteger(integer/10);
    printDigit(integer % 10);

    // Print point
    cout << ".";

    // Print decimal part
    for (int i = 0; i<3; ++i) {
        decimal *=10;
        int digit = (int)decimal;
        printDigit(digit);
        decimal -= digit;
    }
}

void printDigit(const int digit)
{
    cout << digit;
}
