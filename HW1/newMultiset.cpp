#include "newMultiset.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
Multiset::Multiset(int maxUni)
{   if (maxUni<0)
{cerr<<"Invalid input!"<<endl;
    exit(1);
}
    itmsUniNum=0;
    itmsNum=0;
    itms=new items[maxUni];
    max=maxUni;
}// Create an empty multiset.

Multiset::Multiset(const Multiset& old)
{
    itmsNum=old.itmsNum;
    itmsUniNum=old.itmsUniNum;
    max=old.max;
    itms=new items[max];
    for (int k=0; k<itmsUniNum; k++) {
        itms[k].item=old.itms[k].item;
        itms[k].count=old.itms[k].count;
    }
}


Multiset::~Multiset()
{
    delete [] itms;
}

Multiset &  Multiset::operator=(const Multiset &ori)
{
    if (&ori==this) {
        return *this;
    }
    delete []itms;
    itmsNum=ori.itmsNum;
    itmsUniNum=ori.itmsUniNum;
    max=ori.max;
    itms=new items[max];
    for (int k=0; k<itmsUniNum; k++) {
        itms[k].item=ori.itms[k].item;
        itms[k].count=ori.itms[k].count;
    }
    return (*this);
}

bool Multiset::empty() const
{
    if (itmsNum==0) {
        return true;
    }
    return false;
}// Return true if the multiset is empty, otherwise false.

int Multiset::size() const
{
    return itmsNum;
}
// Return the number of items in the multiset.  For example, the size
// of a multiset containing "cumin", "cumin", "cumin", "turmeric" is 4.

int Multiset::uniqueSize() const
{
    return itmsUniNum;
}
// Return the number of distinct items in the multiset.  For example,
// the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
// "turmeric" is 2.

bool Multiset::insert(const ItemType& value)
{    bool appearBefore=false;
    for (int j=0; j<itmsUniNum; j++)
    {
        if (value==itms[j].item)
        {
            itms[j].count++;
            itmsNum++;
            appearBefore=true;
            break;
        }
    }
    if (appearBefore) {
        return true;
    }
    else if (itmsUniNum<max)
{
    
        itms[itmsUniNum].item=value;
        itms[itmsUniNum].count++;
    itmsUniNum++;
    itmsNum++;
    
    
    return true;
}
    else return false;
}
// Insert value into the multiset.  Return true if the value was
// actually inserted.  Return false if the value was not inserted
// (perhaps because the multiset has a fixed capacity and is full).

int Multiset::erase(const ItemType& value)
{
    for (int k=0; k<itmsUniNum; k++) {
        if (itms[k].item==value) {
            if (itms[k].count>1) {
                itms[k].count--;
            }
            else
            {itms[k].item=itms[itmsUniNum-1].item;
                itms[k].count=itms[itmsUniNum-1].count;
                itms[itmsUniNum-1].count=0;
                itmsUniNum--;}
            itmsNum--;
            return 1;
        }
    }
    return 0;
}
// Remove one instance of value from the multiset if present.
// Return the number of instances removed, which will be 1 or 0.

int Multiset::eraseAll(const ItemType& value)
{
    int cnt=0;
    for (int k=0; k<itmsUniNum; k++) {
        if (itms[k].item==value) {
            cnt=itms[k].count;
            itmsNum-=itms[k].count;
            itms[k].item=itms[itmsUniNum-1].item;
            itms[k].count=itms[itmsUniNum-1].count;
            itms[itmsUniNum-1].count=0;
            itmsUniNum--;
            
        }
    }
    return cnt;
}
// Remove all instances of value from the multiset if present.
// Return the number of instances removed.

bool Multiset::contains(const ItemType& value) const
{
    for (int k=0; k<itmsUniNum; k++) {
        if (itms[k].item==value) {
            
            return true;
        }
    }
    return false;
}
// Return true if the value is in the multiset, otherwise false.

int Multiset::count(const ItemType& value) const
{
    
    for (int k=0; k<itmsUniNum; k++) {
        if (itms[k].item==value) {
            return itms[k].count;
        }
    }
    return 0;
}
// Return the number of instances of value in the multiset.

int Multiset::get(int i, ItemType & value) const
{   if (i<uniqueSize() && i>=0)
{
    value=itms[i].item;
    return itms[i].count;
}
    return 0;
}
// If 0 <= i < uniqueSize(), copy into value an item in the
// multiset and return the number of instances of that item in
// the multiset.  Otherwise, leave value unchanged and return 0.
// (See below for details about this function.)

void Multiset::swap(Multiset& other)
{
    int tempNum=itmsNum;
    int tempUniNum=itmsUniNum;
    int tempMax=max;
    items* tempP=itms;
    itms=other.itms;
    itmsNum=other.itmsNum;
    itmsUniNum=other.itmsUniNum;
    max=other.max;
    other.itms=tempP;
    other.itmsNum=tempNum;
    other.itmsUniNum=tempUniNum;
    other.max=tempMax;
    
}
// Exchange the contents of this multiset with the other one.
