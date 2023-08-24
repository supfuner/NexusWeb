#include <mutex>
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

std::mutex mtx; 
std::unordered_set<std::string> usedNames;
std::string pisco::utility::GetRandomName() 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> distribution(0, 25);

    std::string name;
    while (true) {
        for (int i = 0; i < 4; ++i) {
            char letter = 'a' + distribution(gen);
            name += letter;
        }

        // 将名字转换为小写
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (usedNames.find(name) == usedNames.end()) {
            std::lock_guard<std::mutex> lock(mtx);
            usedNames.insert(name);
            return name;
        }
        name.clear();
    }
}

void pisco::utility::ReleseRandomName(std::string & name)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (usedNames.find(name) != usedNames.end()) 
    {        
        usedNames.erase(name);
    }
}