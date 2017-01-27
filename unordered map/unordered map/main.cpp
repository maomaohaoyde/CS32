#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;
int main()
{
    unordered_map<int, set<int>> m_map;
    int nCases;
    cin>>nCases;
    set<int> container;
    for (int k=0; k<nCases; k++)
    {
        int start,end;
        cin>>start>>end;
        unordered_map<int,set<int>>::const_iterator got = m_map.find (start);
        if (got==m_map.end()) {
            m_map.at(start).insert(end);
            container.insert(start);
        }
        else
            m_map.insert(start,end);
        unordered_map<int,set<int>>::const_iterator got1 = m_map.find (end);
        if (got1==m_map.end())
        {m_map.at(end).insert(start);
            container.insert(end);
        }
        else
        m_map.insert(end,start);
    }
    set<int>::iterator it=container.begin();
    for (; it!=container.end(); it++) {
        if (m_map[*it].size()==1) {
            break;
        }
    }
    }
