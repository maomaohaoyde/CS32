#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

bool Steg::hide(const string& hostIn, const string& msg, string& hostOut)
{
    if (hostIn.size()==0)
    return false;
    hostOut=""; string sub="";
    int count=1;
    for (int k=0; k<hostIn.size(); k++) {
        if (hostIn[k]=='\n'&&k!=hostIn.size()-1)
            count++;
       
    }
    vector<unsigned short> num;
    Compressor::compress(msg, num);
    string scrtmsg;
    scrtmsg=BinaryConverter::encode(num);

    int numOfSub, numOfchar;
    numOfSub=scrtmsg.size()%count;
    numOfchar=(scrtmsg.size()/count)+1;

    int k=0,pos=0,subCount=0;
    bool recording=false,changed=false;
    while (k<hostIn.size())
    {
        if (hostIn[k]==' '||hostIn[k]=='\t') {
            sub+=hostIn[k];
            recording=true;
            
        }
        else if (hostIn[k]=='\n')
        {
            hostOut+=scrtmsg.substr(pos,numOfchar)+'\n';
            pos+=numOfchar;
            subCount++;
            sub="";
            recording=false;
        }
        else if (hostIn[k]=='\r'&&k!=(hostIn.size()-1)&& hostIn[k+1]=='\n')
        {
            hostOut+=scrtmsg.substr(pos,numOfchar);
            pos+=numOfchar;
            subCount++;
            sub="";
            recording=false;
            k++;
        }else if (recording==true)
        {
            recording=false;
            hostOut+=sub;
            sub="";
        }
        else
            hostOut+=hostIn[k];
        if (subCount>=numOfSub&&!changed) {
            numOfchar--;
            changed=true;
        }
        k++;
    }
    if (subCount<=count) {
        hostOut+=scrtmsg.substr(pos,numOfchar);
    }
  
  return true;
    // This compiles, but may not be correct
}

bool Steg::reveal(const string& hostIn, string& msg)
{
    string result="",sub="";
    int k=0;
    bool recording=false;
    while (k<hostIn.size())
    {
        if (hostIn[k]==' '||hostIn[k]=='\t') {
            sub+=hostIn[k];
            recording=true;
            if (k==hostIn.size()-1) {
                result+=sub;
                sub="";
            }
        }
        else if (hostIn[k]=='\n')
        {
            result+=sub;
            sub="";
            recording=false;
        }
        else if (hostIn[k]=='\r'&&k!=(hostIn.size()-1)&& hostIn[k+1]=='\n')
        {
            result+=sub;
            sub="";
            recording=false;
            k++;
        }
        else if (recording==true)
        {
            recording=false;
            sub="";
        }
        k++;
    }
        vector<unsigned short> num;
    if (BinaryConverter::decode(result, num))
    { 
        if ( Compressor::decompress(num, msg))
        {
            return true;}}
    return false;// This compiles, but may not be correct
}
