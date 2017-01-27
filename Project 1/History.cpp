#include "History.h"
#include <iostream>
using namespace std;
History::History(int nRows, int nCols)
{   m_rows=nRows;
    m_cols=nCols;
    for (int k=0; k<nRows; k++) {
        for (int j=0; j<nCols; j++) {
            m_pit[k][j]=new int(0);
        }
    }
}
bool History::record(int r, int c)
{
    if (r<1 ||r>m_rows||c<1||c>m_cols) {
        return false;
    }
    else
    {
        (*m_pit[r-1][c-1])++;
        return true;
    }
}
void History::display() const
{
    // Position (row,col) in the pit coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < m_rows; r++)
        for (c = 0; c < m_cols; c++)
            if ((*m_pit[r][c])==0) {
                grid[r][c]='.';
            }
        else if ((*m_pit[r][c])>=26)
               grid[r][c]='Z';
        else
            grid[r][c]='A'+(*m_pit[r][c])-1;
    
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    
}