#include <sstream>
#include "File.h"

using namespace pisco::utility;

int PFile::ReadFile(const std::string fileName, std::string & output)
{
    // 打开文件
    std::ifstream file(fileName);
    
    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << fileName << std::endl;
        return 1;
    }    
    // file >> std::noskipws;
    // output = "";
    // std::string line;
    // while (std::getline(file, line)) {
    //     output += line;
    // }    
    // // 关闭文件
    // file.close();
    if (file)
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        output = buffer.str();
    }
    
    return 0;
}