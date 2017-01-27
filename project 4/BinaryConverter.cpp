#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

const size_t BITS_PER_UNSIGNED_SHORT = 16;

string convertNumberToBitString(unsigned short number);
bool convertBitStringToNumber(string bitString, unsigned short& number);

string BinaryConverter::encode(const vector<unsigned short>& numbers)
{
    string str="";
    vector<unsigned short>::const_iterator it=numbers.begin();
    while (it!=numbers.end()) {
        str+=convertNumberToBitString(*it);
        it++;
    }
    for (int k=0; k<str.size(); k++) {
        if (str[k]=='0') {
            str[k]=' ';
        }
        else
            str[k]='\t';
    }
    return str;  // This compiles, but may not be correct
}

bool BinaryConverter::decode(const string& bitString,
                             vector<unsigned short>& numbers)
{
    int count=0;
    string s="";
    for (int k=0; k<bitString.size(); k++) {
        if (bitString[k]=='\t') {
            s+='1';
        }
        else if (bitString[k]==' ')
            s+='0';
    }
    while (count!=bitString.size()) {
        string str=s.substr(count, 16);
        unsigned short num;
        
        if (!convertBitStringToNumber(str, num)) {
            return false;
        }
               numbers.push_back(num);
        count+=BITS_PER_UNSIGNED_SHORT;
    }
    return true;  // This compiles, but may not be correct
}

string convertNumberToBitString(unsigned short number)
{
    string result(BITS_PER_UNSIGNED_SHORT, '0');
    for (size_t k = BITS_PER_UNSIGNED_SHORT; number != 0; number /= 2)
    {
        k--;
        if (number % 2 == 1)
            result[k] = '1';
    }
    return result;
}

bool convertBitStringToNumber(string bitString, unsigned short& number)
{
    if (bitString.size() != BITS_PER_UNSIGNED_SHORT)
        return false;
    number = 0;
    for (size_t k = 0; k < bitString.size(); k++)
    {
        number *= 2;
        if (bitString[k] == '1')
            number++;
        else if (bitString[k] != '0')
            return false;
    }
    return true;
}
