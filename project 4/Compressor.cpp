#include "provided.h"
#include <string>
#include <vector>
#include "HashTable.h"
#include <iostream>
using namespace std;

void Compressor::compress(const string& s, vector<unsigned short>& numbers)
{   int capacity=16384;
    if ((s.size()/2+512)<capacity)
    {
        capacity=s.size()/2+512;
    }
    HashTable<string, unsigned short> H(capacity*2,capacity);
    string temp(1,static_cast<char>(0));
    H.set(temp, 0);
    for (int k=1; k<256; k++) {
        string str="";
        str+=static_cast<char>(k);
        H.set(str, k,true);
    }
    int nextFreeID=256;
    string runSoFar="";
    vector<unsigned short> num;
    for (int k=0; k<s.size(); k++)
    {
        string expandedRun=runSoFar+s[k];
        unsigned short value;
        if (H.get(expandedRun, value))
        {
            runSoFar=expandedRun;
            
            }
        else
        {
            H.get(runSoFar, value);
            num.push_back(value);
            H.touch(runSoFar);
            runSoFar="";
            string temp="";
            temp+=s[k];
            H.get(temp, value);
            num.push_back(value);
            if (!H.isFull())
            {
                H.set(expandedRun, nextFreeID);

                nextFreeID++;
            }
            else
            {
                unsigned short reuseID;
                string trash;
                H.discard(trash, reuseID);
                H.set(expandedRun, reuseID);
            }
            
            
        }
    }
    unsigned short tempValue;
    if (runSoFar.size()!=0) {
        H.get(runSoFar, tempValue);
        num.push_back(tempValue);
    }
   num.push_back(capacity);
    numbers=num;
    
    // This compiles, but may not be correct
}

bool Compressor::decompress(const vector<unsigned short>& numbers, string& s)
{
    if (numbers.empty()) {
        return false;
    }
    HashTable<unsigned short, string> H(numbers.back()*2,numbers.back());

    for (int k=0; k<256; k++) {
        string str="";
        str+=static_cast<char>(k);
        H.set(k, str,true);
    }
    int nextFreeID=256;
    string runSoFar="";
    string output="";
    for (int k=0; k<numbers.size()-1; k++) {
        unsigned short us= numbers[k];
        if (us<=255)
        {
            string temp;
            H.get(us, temp);
            output+=temp;
            if (runSoFar=="") {
                runSoFar=temp;
                continue;
            }
            else if (runSoFar.size()!=0)
           
            {
                string expandedRun=runSoFar+temp;
                
            if (!H.isFull()) {
                H.set(nextFreeID, expandedRun);
                nextFreeID++;
                  }
                else
                {
                    unsigned short a;
                    string trash;
                    H.discard(a, trash);
                    H.set(a, expandedRun);
                }
            }
            runSoFar="";
            continue;
        }
        else
        {
            string tempStr;
            if (!H.get(us, tempStr)) {
                return false;
            }
            H.touch(us);
            output+=tempStr;
            runSoFar=tempStr;
            continue;
        }
        
    }
    s=output;

    return true;  // This compiles, but may not be correct
}
