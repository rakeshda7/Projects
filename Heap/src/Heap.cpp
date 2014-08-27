#include <Heap.h>
#include <vector>
#include <iostream>

using namespace std;

// This will ensure that a min-heap will be created
bool Heap::isLesser(int x, int y) {
    return minHeap?x<y:x>y;
}

void Heap::print() {
	for(int i: v) {
		cout<<i<<endl;
	}
	cout<<"---"<<endl;
}

void Heap::push_up(unsigned int index) {

	if(index==0) {
		return;
	}

	auto pIndex = (index-1)/2;
	if(isLesser(v[index], v[pIndex])) {
		std::swap(v[index], v[pIndex]);
		push_up(pIndex);
	}
}

void Heap::push_down(unsigned int index) {
	if(index>=v.size()) {
		return;
	}

	if((index*1+1<v.size() && !isLesser(v[index], v[index*1+1])) ||
	   (index*1+2<v.size() && !isLesser(v[index], v[index*1+2]))) {
		if(!isLesser(v[index*1+1], v[index*1+2])) {
			std::swap(v[index], v[index*1+2]);
			push_down(index*1+2);
		}
		else {
			std::swap(v[index], v[index*1+1]);
			push_down(index*1+1);
		}
	}
}

void Heap::push(int i) {
    v.push_back(i);
    push_up(v.size()-1);
}

int Heap::pop() {
	auto result = v.front();
	v[0] = v.back();
	v.pop_back();
	push_down(0);
	return result;
}

int Heap::getLen() {
    return v.size();
}

int calculateCost(const vector<string> &vs) {
    if(vs.size()==0) {
        return 0;
    }
    else if(vs.size()==1) {
        return vs.back().length();
    }

    //Create a Heap using only the string sizes.
    Heap h;
    for(string s: vs) {
        h.push(s.length());
    }

    //Find the Summation of all the elements
    int cost = 0;
    int cumCost = 0;
    while(h.getLen()>1) {
        cost = h.pop()+h.pop();
        cumCost += cost;
        h.push(cost);
    }
    h.pop();    // Empty the last element from heap

    return(cumCost);
}

int main()
{
    vector<string> vs;

    vs.push_back("123");
    vs.push_back("12345");
    vs.push_back("1234567");
    vs.push_back("123");
    vs.push_back("12345");
    vs.push_back("1234567");

    cout<<"Cumulitive Cost is: "<<calculateCost(vs)<<endl;

    return 0;
}
