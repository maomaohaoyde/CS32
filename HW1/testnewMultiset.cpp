#include "newMultiset.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
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
    Multiset c(-1);
}

void test2()
{
    Multiset a(1000);   // a can hold at most 1000 distinct items
    Multiset b(5);      // b can hold at most 5 distinct items
    Multiset c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = { 123,234,345,456,567,678 };
    // No failures inserting 5 distinct items twice each into b
    for (int k = 0; k < 5; k++)
    {
        assert(b.insert(v[k]));
        assert(b.insert(v[k]));
    }
    assert(b.size() == 10  &&  b.uniqueSize() == 5  &&  b.count(v[0]) == 2);
    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));
    
    // When two Multisets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5])  &&  b.insert(v[5]));
    cout << "Passed all tests" << endl;

}

void test3()
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

void test4()
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


int main()
{
    test4();
    test3();
    test2();
    test();
}