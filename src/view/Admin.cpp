#include "Admin.h"

using namespace pisco::view;
#include <iostream>
#include <thread>

REGISTER_CLASS(Admin);
REGISTER_CLASS_METHOD(Admin, Login,     void, const Request &, Response &);
REGISTER_CLASS_METHOD(Admin, Index,     void, const Request &, Response &);
REGISTER_CLASS_METHOD(Admin, Content,   void, const Request &, Response &);
REGISTER_CLASS_METHOD(Admin, System,    void, const Request &, Response &);


Admin::~Admin()
{

}

void Admin::Login(const Request & req, Response & resp)
{
    UserData user;
    user.elements["name"] = "John";
    user.data["fruits"] = { "Apple", "Banana", "Orange" };
    user.data["V"] = { "Q", "W", "E" };
    std::string output = Render::render(user, "/home/user/wrok_space/NexusWeb/www/admin/login.html");
    resp.html(output);
}

void Admin::Index(const Request & req, Response & resp)
{
    UserData user;
    user.elements["name"] = "John";
    user.data["fruits"] = { "Apple", "Banana", "Orange" };
    user.data["V"] = { "Q", "W", "E" };
    std::string output = Render::render(user, "/home/user/wrok_space/NexusWeb/www/admin/index.html");
    resp.html(output);
}

void Admin::Content(const Request & req, Response & resp)
{
    UserData user;
    user.elements["name"] = "John";
    user.data["fruits"] = { "Apple", "Banana", "Orange" };
    user.data["V"] = { "Q", "W", "E" };
    std::string output = Render::render(user, "/home/user/wrok_space/NexusWeb/www/admin/content.html");
    resp.html(output);
}

void Admin::System(const Request & req, Response & resp)
{
    UserData user;
    user.elements["name"] = "John";
    user.data["fruits"] = { "Apple", "Banana", "Orange" };
    user.data["V"] = { "Q", "W", "E" };
    std::string output = Render::render(user, "/home/user/wrok_space/NexusWeb/www/admin/system.html");
    resp.html(output);
}


void Admin::test()
{
    std::cout<<"========test()\n";
}

