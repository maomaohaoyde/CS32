#include "StudentMultiset.h"
#include <iostream>
using namespace std;
StudentMultiset::StudentMultiset()
{
    
}// Create an empty student multiset.

bool StudentMultiset::add(unsigned long id)
{
    return stdId.insert(id);
}
// Add a student id to the StudentMultiset.  Return true if and only
// if the id was actually added.

int StudentMultiset::size() const
{
    return stdId.size();
}
// Return the number of items in the StudentMultiset.  If an id was
// added n times, it contributes n to the size.

void StudentMultiset::print() const
{
    unsigned long copy;
    for (int j=0; j<stdId.uniqueSize(); j++)
    {
        for (int k=0; k<stdId.get(j,copy); k++)
        {
            cout<<copy<<endl;
        }
    }
}
// Print to cout every student id in the StudentMultiset one per line;
// print as many lines for each id as it occurs in the StudentMultiset.
