#pragma once

#include <string>
using namespace std;

namespace pisco {
namespace web {

class Response
{
public:
    enum Type
    {
        HTML = 0,
        JSON
    };

    Response();
    ~Response();

    void code(int code);
    void html(const string & data);
    void json(const string & data);
    string data() const;
    string page_not_found() const;
    string test_page() const;
    string test_json() const;

private:
    int m_code;
    Type m_type;
    string m_data;
};

}}
