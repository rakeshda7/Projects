#include <Heap.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// This will ensure that a min-heap will be created
bool isGreater(int x, int y) {
    return x>y;
}

void Heap::push(int i) {
    v.push_back(i);
    push_heap(v.begin(), v.end(), ptr_fun(isGreater));
}

int Heap::pop() {
    pop_heap(v.begin(), v.end(), ptr_fun(isGreater));
    int result = v.back();
    v.pop_back();
    return result;
}

int Heap::getLen() {
    return v.size();
}
