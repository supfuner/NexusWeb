#include "Response.h"
using namespace pisco::web;

#include <fstream>
#include <sstream>
using std::ostringstream;

Response::Response() : m_code(200)
{
}

Response::~Response()
{
}

void Response::code(int code)
{
    m_code = code;
}

void Response::html(const string & data)
{
    m_type = HTML;
    m_data = data;
}

void Response::json(const string & data)
{
    m_type = JSON;
    m_data = data;
}

string Response::data() const
{
    ostringstream os;
    os << "HTTP/1.1 " << m_code << " OK\r\n";
    switch (m_type)
    {
        case HTML:
            os << "Content-Type: text/html; charset: utf-8\r\n";
            break;
        case JSON:
            os << "Content-Type: application/json; charset: utf-8\r\n";
            break;
        default:
            break;
    }
    os << "Content-Length: " << m_data.size() << "\r\n\r\n";
    os << m_data << "\r\n";
    return os.str();
}

string Response::page_not_found() const
{
    string body =  "<!DOCTYPE html> \
                    <html> \
                        <head> \
                            <meta charset=\"utf-8\"> \
                            <title>pisco-web</title> \
                        </head> \
                        <body> \
                            <h1 style=\"text-align: center;\">404 Page Not Found</h1> \
                            <p style=\"text-align: center;\">request not matched</p> \
                        </body> \
                    </html>";
    ostringstream os;
    os << "HTTP/1.1 404 Not Found\r\n";
    os << "Content-Type: text/html; charset: UTF-8\r\n";
    os << "Content-Length: " << body.size() << "\r\n\r\n";
    os << body << "\r\n";
    return os.str();
}

string Response::test_page() const
{
    string body = R"(<!DOCTYPE html>
  <html>
  <head>
  <meta charset="UTF-8">
  <title>动态页面更新示例</title>
  <script src="https://code.jquery.com/jquery-3.5.1.min.js"></script> <!-- 引入 jQuery 库 -->
</head>
<body>
  <h1>动态页面更新示例</h1>

  <div id="data-container">
    <!-- 这里显示后台返回的数据 -->
  </div>

  <button id="update-btn">点击更新数据</button>

  <script>
    // 当按钮点击时触发事件
    $('#update-btn').click(function() {
      // 发送异步请求到后台获取数据
      $.ajax({
        url: 'count',  // 替换为后台数据接口的实际URL
        type: 'GET',  // 根据实际情况选择请求类型
        success: function(data) {
          // 请求成功的回调函数
          // 根据后台返回的数据，对页面进行更新操作
          $('#data-container').text(data);
        },
        error: function() {
          // 请求失败的回调函数
          console.log('请求数据失败');
        }
      });
    });
  </script>
</body>
</html>)";

    ostringstream os;
    os << "HTTP/1.1 404 Not Found\r\n";
    os << "Content-Type: text/html; charset: UTF-8\r\n";
    os << "Content-Length: " << body.size() << "\r\n\r\n";
    os << body << "\r\n";
return os.str();
}
static int cnt = 0;
string Response::test_json() const
{
    std::string mm = std::to_string(cnt++);
    ostringstream os;
    os << "HTTP/1.1 " << m_code << " OK\r\n";
    os << "Content-Type: application/json; charset: utf-8\r\n";
    os << "Content-Length: " << mm.size() << "\r\n\r\n";
    os << mm << "\r\n";
return os.str();
}