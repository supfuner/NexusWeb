#include "Request.h"
using namespace pisco::web;

#include <string.h>
#include <vector>

#include "../utility/Loger.h"
#include "../utility/SString.h"
#include "../utility/Loger.h"
using namespace pisco::utility;

Request::Request()
{
}

Request::~Request()
{
}

bool Request::parse(const char * buf, int len)
{
    /* Parse request line: method, URI, proto */
    const char * s = buf;
    const char * e = buf + len - 1;
    const char * i = s;

    /* Request is fully buffered. Skip leading whitespaces. */
    while ((i < e) && (isspace(*i))) i++;
    s = i;

    // parse http request's method
    while ((i < e) && (strchr(" ", *i) == NULL)) i++;
    m_method = string(s, 0, i - s);

    while ((i < e) && (strchr(" ", *i) != NULL)) i++;
    s = i;

    // parse http request's uri
    while ((i < e) && (strchr(" ", *i) == NULL)) i++;
    m_uri = string(s, 0, i - s);

    while ((i < e) && (strchr(" ", *i) != NULL)) i++;
    s = i;

    // parse http request's protocol
    while ((i < e) && (strchr("\r\n", *i) == NULL)) i++;
    m_proto = string(s, 0, i - s);

    while ((i < e) && (strchr("\r\n", *i) != NULL)) i++;
    s = i;

    /* If URI contains '?' character, initialize query_string */
    size_t pos = m_uri.find_first_of('?');
    if (pos != string::npos)
    {
        m_path = m_uri.substr(0, pos);
        m_query_string = m_uri.substr(pos + 1);

        std::vector<string> output;
        SString::split(output, m_query_string, "&");
        for (std::vector<string>::iterator it = output.begin(); it != output.end(); it++)
        {
            std::vector<string> out;
            SString::split(out, (*it), "=");
            if (out.size() == 2)
            {
                m_get[out[0]] = out[1];
            }
            else
            {
                m_get[out[0]] = "";
            }
        }
    }
    else
    {
        m_path = m_uri;
    }
    

    /* Parse request headers */
    while (i < e)
    {
        // parse http request header's name
        while ((i < e) && (strchr(": ", *i) == NULL)) i++;
        string name = string(s, 0, i - s);

        while ((i < e) && (strchr(": ", *i) != NULL)) i++;
        s = i;

        // parse http request header's value
        while ((i < e) && (strchr("\r\n", *i) == NULL)) i++;
        string value = string(s, 0, i - s);

        m_headers[name] = value;

        if (strncmp(i, "\r\n\r\n", 4) == 0)
        {
            break;
        }

        while ((i < e) && (strchr("\r\n", *i) != NULL)) i++;
        s = i;
    }

    while ((i < e) && (strchr("\r\n", *i) != NULL)) i++;
    s = i;

    m_body = string(s);
    if (header("Content-Type") == "application/json")
    {
        //m_post.parse(m_body);
    }
    return true;
}

bool Request::is_get() const
{
    return (m_method == "GET");
}

bool Request::is_post() const
{
    return (m_method == "POST");
}

string Request::get(const string & name) const
{
    std::map<string, string>::const_iterator it = m_get.find(name);
    if (it != m_get.end())
    {
        return it->second;
    }
    return "";
}

// Json Request::post(const string & name) const
// {
//     if (name == "")
//     {
//         return m_post;
//     }
//     return m_post.get(name);
// }

string Request::header(const string & name) const
{
    std::map<string, string>::const_iterator it = m_headers.find(name);
    if (it != m_headers.end())
    {
        return it->second;
    }
    return "";
}

string Request::cookie(const string & name) const
{
    std::map<string, string>::const_iterator it = m_cookies.find(name);
    if (it != m_cookies.end())
    {
        return it->second;
    }
    return "";
}

string Request::path() const
{
    return m_path;
}

string Request::user_host() const
{
    return header("Host");
}

string Request::user_agent() const
{
    return header("User-Agent");
}

void Request::show() const
{
    LOG_DEBUG("http method: {}", m_method);
    LOG_DEBUG("http uri: {}", m_uri);
    LOG_DEBUG("http proto: {}", m_proto.c_str());
    LOG_DEBUG("http path: {}", m_path.c_str());
    LOG_DEBUG("http query string: {}", m_query_string.c_str());
    LOG_DEBUG("http headers -- start");
    for (std::map<string, string>::const_iterator it = m_headers.begin(); it != m_headers.end(); it++)
    {
        LOG_DEBUG("http header: {}={}", it->first.c_str(), it->second.c_str());
    }
    LOG_DEBUG("http headers -- end");
    LOG_DEBUG("http get params -- start");
    for (std::map<string, string>::const_iterator it = m_get.begin(); it != m_get.end(); it++)
    {
        LOG_DEBUG("http get: {}={}", it->first.c_str(), it->second.c_str());
    }
    LOG_DEBUG("http get params -- end");
    LOG_DEBUG("http post params -- start");
    //LOG_DEBUG("http post %s", m_post.str().c_str());
    LOG_DEBUG("http post params -- end");
    LOG_DEBUG("http body: {}", m_body.c_str());
}