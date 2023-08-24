#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <random>
#include <ctime>
#include <algorithm>

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace pisco {
namespace utility {
    
class SString
{
public:
    static void split(vector<string> & output, const string & input, const string & separator);
};

std::string GetRandomName();
void ReleseRandomName(std::string & name);

}
}