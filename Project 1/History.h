
#ifndef __CS_32__History__
#define __CS_32__History__
#include "globals.h"
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int* m_pit[MAXROWS][MAXCOLS];
    int m_rows,m_cols;
};

#endif /* defined(__CS_32__History__) */
