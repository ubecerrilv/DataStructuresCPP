//
// Created by ubecerril on 1/14/26.
//
#include <iostream>
#include <list>

using namespace std;

list<int> intersection(const list<int>& L1, const list<int>& L2) {
    list<int> result;

    auto itr1 = L1.begin();
    auto itr2 = L2.begin();
    while (itr1 != L1.end() && itr2 != L2.end()) {
        if (*itr1 == *itr2) {
            result.push_back(*itr1++);
        } else if (*itr1 < *itr2) {
            ++itr1;
        }else {
            ++itr2;
        }
    }
    return result;
}
list<int> unionList(const list<int>& L1, const list<int>& L2) {
    list<int> result;
    auto it1 = L1.begin();
    auto it2 = L2.begin();

    while (it1 != L1.end() && it2 != L2.end()) {
        if (*it1 == *it2) {
            result.push_back(*it1++);
            ++it2;
        }
        else if (*it1 < *it2) {
            result.push_back(*it1++);
        }
        else {
            result.push_back(*it2++);
        }
    }

    while (it1 != L1.end()) {
        result.push_back(*it1++);
    }

    while (it2 != L2.end()) {
        result.push_back(*it2++);
    }

    return result;
}

void printList(const list<int>& L) {
    for (int x : L)
        cout << x << " ";
    cout << endl;
}

int main() {
    list<int> L1 = {1, 3, 5, 7};
    list<int> L2 = {3, 4, 5, 8};

    cout << "L1: ";
    printList(L1);

    cout << "L2: ";
    printList(L2);

    list<int> inter = intersection(L1, L2);
    cout << "Intersección: ";
    printList(inter);

    list<int> uni = unionList(L1, L2);
    cout << "Unión: ";
    printList(uni);

    return 0;
}
