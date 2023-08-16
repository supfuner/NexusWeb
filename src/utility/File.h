#pragma once
#include <iostream>
#include <fstream>
#include <string>



namespace pisco{
namespace utility{
    class PFile
    {
    public:
        static int ReadFile(const std::string fileName, std::string & output);


    };    
}
}