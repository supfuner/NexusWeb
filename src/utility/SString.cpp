#include "SString.h"
using namespace pisco::utility;


void SString::split(vector<string> & output, const string & input, const string & separator)
{
    //output.clear();
    size_t last = 0;
    size_t index = input.find_first_of(separator, last);
    while (index != string::npos)
    {
        string str = input.substr(last, index - last);
        output.push_back(str);
        last = index + 1;
        index = input.find_first_of(separator, last);
    }
    if (index - last > 0)
    {
        output.push_back(input.substr(last , index - last));
    }
}