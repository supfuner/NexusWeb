#include "ControlHandler.h"
#include "../utility/File.h"

static int counter = 0;
void CounterTest(const Request & req, Response & resp)
{
    // string name = req.get("name");
    std::string cnt = std::to_string(counter++);
    resp.json(cnt);
}

void StaticHandler(const Request & req, Response & resp)
{
    std::string output;
    std::string path = "/home/user/wrok_space/NexusWeb" + req.GetUri();
    pisco::utility::PFile::ReadFile(path, output);
    std::ifstream file(path, std::ios::binary);
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::cout<<"uri:"<<req.GetUri()<<"\tlen:"<<fileSize<<"\tdataLen:"<<output.size()<<std::endl;
    if (path.find(".js") != std::string::npos) 
    {
        resp.JavaScrip(output);
    }
    else if (path.find(".css") != std::string::npos)
    {
        resp.Css(output);
    }
    else if (path.find(".png") != std::string::npos || path.find(".jpg") != std::string::npos)
    {
        resp.Image(output);
    }
}