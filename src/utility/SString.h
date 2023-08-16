#pragma once

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

}
}