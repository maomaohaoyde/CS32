#include "Multiset.h"
#include <iostream>
#include <cassert>

using namespace std;


void unsignedLongtest1()
{

        Multiset ulms;
        assert(ulms.insert(20));
        assert(ulms.insert(10));
        assert(ulms.insert(20));
        assert(ulms.insert(30));
        assert(ulms.insert(20));
        assert(ulms.insert(10));
        assert(ulms.size() == 6  &&  ulms.uniqueSize() == 3);
        assert(ulms.count(10) == 2);
        assert(ulms.count(20) == 3);
        assert(ulms.count(30) == 1);
        assert(ulms.count(40) == 0);
        cout << "Passed all tests" << endl;

}

void unsignedLongtest2()
{
    Multiset ms;
    assert(ms.empty());
    unsigned long x = 999;
    assert(ms.get(0, x) == 0  &&  x == 999);  // x unchanged by get failure
    assert( ! ms.contains(42));
    ms.insert(42);
    ms.insert(42);
    assert(ms.size() == 2  &&  ms.uniqueSize() == 1);
    assert(ms.get(1, x) == 0  &&  x == 999);  // x unchanged by get failure
    assert(ms.get(0, x) == 2  &&  x == 42);
    cout << "Passed all tests" << endl;
}

void unsignedLongtest3()
{
    Multiset ms1;
    ms1.insert(10);
    ms1.insert(10);
    ms1.insert(10);
    ms1.insert(20);
    Multiset ms2;
    ms2.insert(30);
    ms2.insert(10);
    ms2.insert(40);
    ms1.swap(ms2);  // exchange contents of ms1 and ms2
    assert(ms1.size() == 3  &&  ms1.count(30) == 1  &&
           ms1.count(10) == 1  &&  ms1.count(40) == 1);
    assert(ms1.erase(30)==1 && ms1.erase(35)==0);
    assert(ms2.size() == 4  &&  ms2.count(10) == 3  &&
           ms2.count(20) == 1);
    assert(ms2.eraseAll(10)==3);
    cout << "Passed all tests" << endl;
}

void unsignedLongtest4()
{
    Multiset ms2;
    for (unsigned long k=0; k<DEFAULT_MAX_ITEMS; k++)
    {
        assert(ms2.insert(k));
    }
    assert(!ms2.insert(DEFAULT_MAX_ITEMS));
    cout << "Passed all tests" << endl;
}

void unsignedLongtest5()
{
    Multiset ms1;
    ms1.insert(10);
    ms1.insert(10);
    ms1.insert(10);
    ms1.insert(20);
    Multiset ms2;
    ms2.insert(30);
    ms2.insert(10);
    ms2.insert(40);
    Multiset ms3;
    ms3=ms2;
    assert(ms3.size() == 3  &&  ms3.count(30) == 1  &&
           ms3.count(10) == 1  &&  ms3.count(40) == 1);
    ms1=ms2;
    assert(ms2.size() == 3  &&  ms2.count(30) == 1  &&
           ms2.count(10) == 1  &&  ms2.count(40) == 1);
    cout << "Passed all tests" << endl;
}
int main()
{
    unsignedLongtest1();
    unsignedLongtest2();
    unsignedLongtest3();
    unsignedLongtest4();
    unsignedLongtest5();
}