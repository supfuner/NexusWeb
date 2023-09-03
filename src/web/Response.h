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
        JSON,
        IMG,
        JS,
        CSS,
    };

    Response();
    ~Response();

    void code(int code);
    void html(const string & data);
    void json(const string & data);
    void Image(const string & data);
    void JavaScrip(const string & data);
    void Css(const string & data);
    
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
