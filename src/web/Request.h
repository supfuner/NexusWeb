#pragma once

#include <string>
#include <map>
#include "../utility/Json.h"
using namespace std;


namespace pisco {
namespace web {

class Request
{
public:
    Request();
    ~Request();

    bool parse(const char * buf, int len);

    bool is_get() const;
    bool is_post() const;

    string get(const string & name) const;
    string header(const string & name) const;
    string cookie(const string & name) const;
    string path() const;
    string user_agent() const;
    string user_host() const;
    string GetUri() const;
    void show() const;

private:
    string m_method;
    string m_uri;
    string m_proto;
    string m_path;
    string m_body;
    string m_query_string;
    std::map<string, string> m_get;
    std::map<string, string> m_headers;
    std::map<string, string> m_cookies;
};

}}
