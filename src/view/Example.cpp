#include "Example.h"

using namespace pisco::view;
#include <iostream>


REGISTER_CLASS(Example);
REGISTER_CLASS_METHOD(Example, TestAjax, void, const Request &, Response &);
// REGISTER_CLASS_METHOD(Index, test, void);


Example::~Example()
{

}

void Example::TestAjax(const Request & req, Response & resp)
{
    std::cout<<"Get Param:" << req.get("name") << std::endl;
    UserData user;
    user.elements["name"] = "John";
    user.data["fruits"] = { "Apple", "Banana", "Orange" };
    user.data["V"] = { "Q", "W", "E" };

    std::string output = Render::render(user, "/home/user/wrok_space/NexusWeb/www/html/ajax.html");
    resp.html(output);
}
