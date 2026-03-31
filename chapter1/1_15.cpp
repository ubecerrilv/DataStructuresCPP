#include <vector>
#include <iostream>
//
// Created by ubecerril on 3/30/26.
//
using namespace std;

class  Rectangle {
private:
    int width;
    int height;

public:
    Rectangle(const int w, const int h) : width{w}, height{h} {}
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void print(ostream &out = cout) const {
        out << "Rectangle: " << width << "x" << height << "; area: " << width * height <<"; perimeter: " << 2*width + 2*height <<endl;
    }
};

// Generic findMax with a function object
template <typename Object, typename Comparator>
const Object & findMax(const vector<Object> &vec, Comparator comp) {
    int maxIndex {0};

    for (int i = 0; i < vec.size(); ++i) {
        if (comp(vec[maxIndex], vec[i])) {
            maxIndex = i;
        }
    }
    return vec[maxIndex];
}

// Generic findMax, default ordering
#include <functional>
template<typename Object>
const Object & findMax(const vector<Object> &vec) {
    return findMax(vec, less<Object>());
}

// Define the two function objects, by area and by perimeter
class AreaCompare {
public:
    bool operator()(const Rectangle &lhs, const Rectangle &rhs) const {
        return lhs.getWidth() * lhs.getHeight() < rhs.getWidth() * rhs.getHeight();
    }
};
class PerimeterCompare {
public:
    bool operator()(const Rectangle &lhs, const Rectangle &rhs) const {
        return 2*lhs.getWidth() + 2*lhs.getHeight() < 2*rhs.getWidth() + 2*rhs.getHeight();
    }
};

// Function to print rectangle
ostream & operator<<(ostream &out, const Rectangle &rhs) {
    rhs.print(out);
    return out;
}

int main(int argc, char *argv[]) {
    const vector<Rectangle> vec = {Rectangle{5,3}, Rectangle{5,12}, Rectangle{5,5}, Rectangle{1,50}};

    cout << "Largest rectangle by area: " << endl;
    cout << findMax(vec, AreaCompare{}) << endl;

    cout << "Largest rectangle by perimeter: " << endl;
    cout << findMax(vec, PerimeterCompare{}) << endl;
}
