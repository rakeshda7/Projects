#ifndef HEAP_H
#define HEAP_H

#include <vector>

using namespace std;

class Heap {
    vector<int> v;
    bool minHeap;

    void push_up(unsigned int index);
    void push_down(unsigned int index);
    bool isLesser(int x, int y);

public:
    Heap(bool isMinHeap=true): minHeap(isMinHeap) {}
    void push(int i);
    int pop();
    int getLen();
    void print();
};

#endif // HEAP_H
