#include "random_numbers.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

void random_numbers(const int range, int &a, int &b, int &c, int &d) {
    int array[range];
    for (int i=0; i<range; i++) {
        array[i] = i;
    }
    for (int i=range-1; i>0; i--) {
        int a = rand()%i;
        swap(array[i], array[a]);
    }
    a = array[0];
    b = array[1];
    c = array[2];
    d = array[3];
}

void random_arrays(int array[], int n) {
    for (int i=n-1; i>0; i--) {
        int a = rand()%i;
        swap(array[i], array[a]);
    }
}