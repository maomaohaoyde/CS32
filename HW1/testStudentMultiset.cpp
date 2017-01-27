#include "StudentMultiset.h"
#include "Multiset.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    StudentMultiset classA;
    classA.add(12345);
    classA.add(23456);
    classA.add(34567);
    assert(classA.add(45678));
    assert(classA.size()==4);
    classA.print();
}
