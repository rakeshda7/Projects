#include <iostream>
#include <vector>
#include <string>
#include <Heap.h>

using namespace std;

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
