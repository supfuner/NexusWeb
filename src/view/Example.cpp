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
    std::string output = Render::render("/home/user/wrok_space/PISCO_demo/NexusWeb/www/html/ajax.html");
    resp.html(output);
}
