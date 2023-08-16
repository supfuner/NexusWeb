#include "ControlHandler.h"


static int counter = 0;
void CounterTest(const Request & req, Response & resp)
{
    // string name = req.get("name");
    // string age = req.get("age");
    // string host = req.user_host();
    std::string cnt = std::to_string(counter++);
    resp.json(cnt);
}