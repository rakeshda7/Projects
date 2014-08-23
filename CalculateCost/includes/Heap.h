#ifndef HEAP_H
#define HEAP_H

#include <vector>

class Heap {
    std::vector<int> v;

public:
    void push(int i);
    int pop();
    int getLen();
};

#endif // HEAP_H
