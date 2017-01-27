#include <functional>
#include "provided.h"
#include "http.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

bool WebSteg::hideMessageInPage(const string& url, const string& msg, string& host)
{
    string page;
    if (HTTP().get(url, page)) {
            if (Steg::hide(page, msg, host)) {
            return true;
        }
    }
    return false;  // This compiles, but may not be correct
}

bool WebSteg::revealMessageInPage(const string& url, string& msg)
{
    string page;
    if (HTTP().get(url, page))
    {
        if (Steg::reveal(page, msg))
        {  
            return true;
        }
    }
    return false;  // This compiles, but may not be correct
}


unsigned int computeHash(const string&s)
{
    hash<string> str_hash;
    return str_hash(s);
}
unsigned int computeHash(unsigned short num)
{
    hash<unsigned short> short_hash;
    return short_hash(num);
}

