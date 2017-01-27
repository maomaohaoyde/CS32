#include <string>
#include <iostream>
#include <stack>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> mz;
    Coord a(sr, sc);
    mz.push(a);
    maze[sr][sc]='A';
    while (!mz.empty())
    {   Coord current(mz.top());
        mz.pop();
        if (current.r()==er&&current.c()==ec) {
            return true;
        }
        
        
        Coord North(current.r()-1,current.c());
        if (maze[current.r()-1][current.c()]=='.')
        {
            mz.push(North);
            maze[current.r()-1][current.c()]='A';
        }
        
        
        Coord East(current.r(),current.c()+1);
        if (maze[current.r()][current.c()+1]=='.')
        {
            mz.push(East);
            maze[current.r()][current.c()+1]='A';
        }
        
        
        Coord South(current.r()+1,current.c());
        if (maze[current.r()+1][current.c()]=='.')
        {
            mz.push(South);
            maze[current.r()+1][current.c()]='A';
        }
        
        
        Coord West(current.r(),current.c()-1);
        if (maze[current.r()][current.c()-1]=='.')
        {
            mz.push(West);
            maze[current.r()][current.c()-1]='A';
        }
        
        
        
    }
    return false;
    
    
}
