#include "Index.h"
#include "../utility/File.h"
using namespace pisco::view;
#include <iostream>
#include <thread>

REGISTER_CLASS(Index);
REGISTER_CLASS_METHOD(Index, show, void, const Request &, Response &);
REGISTER_CLASS_METHOD(Index, test, void, const Request &, Response &);


Index::~Index()
{

}

void Index::show(const Request & req, Response & resp)
{
    UserData user;
    user.elements["name"] = "John";
    user.data["fruits"] = { "Apple", "Banana", "Orange" };
    user.data["V"] = { "Q", "W", "E" };
    std::string output = Render::render(user, "/home/user/wrok_space/NexusWeb/www/html/index.html");
    resp.html(output);
}


void Index::test(const Request & req, Response & resp)
{
    std::string output;
    pisco::utility::PFile::ReadFile("/home/user/wrok_space/NexusWeb/src/README.md", output);
    resp.Image(output);
}

