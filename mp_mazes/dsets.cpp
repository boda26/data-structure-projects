/* Your code here! */
#include "dsets.h"
#include <vector>
using namespace std;

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        elements.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (elements[elem] < 0) {
        return elem;
    } else {
        int rep = find(elements[elem]);
        elements[elem] = rep;
        return rep;
    }
}

void DisjointSets::setunion(int a, int b) {
    int rep1 = find(a);
    int rep2 = find(b);
    int size_a = elements[rep1] * -1;
    int size_b = elements[rep2] * -1;
    int size_union = size_a + size_b;
    if (size_a <= size_b) {
        elements[rep2] = rep1;
        elements[rep1] = size_union * -1;
    } else {
        elements[rep1] = rep2;
        elements[rep2] = size_union * -1;
    }
}

int DisjointSets::size(int elem) {
    int size = find(elem);
    return -1 * elements[size];
}