#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../web/Request.h"
#include "../web/Response.h"
using namespace pisco::web;
// 模板类用于生成并渲染HTML模板
const std::string kForStart     = "{%- for ";
const std::string kForIn        = " in ";
const std::string kForEndMark   = " -%}";
const std::string kForEnd       = "{%- endfor -%}";
const std::string kLeftBraces   = "{{";
const std::string kRightBraces  = "}}";

namespace pisco{
namespace utility{

// 后台数据结构
struct UserData {
    std::map<std::string, std::string> elements;
    std::map<std::string, std::vector<std::string>> data;//for in 
};

class Render {
public:
    static std::string render(const UserData& data, const std::string htmlFile);
    static std::string render(const std::string htmlFile);

private:
    static void renderElement(std::string & htmlTemplate, const UserData& data);

    static void renderForeach(std::string & htmlTemplate, const UserData& data);    

    static void replaceBraces(std::string & htmlTemplate, const std::string data);
    
    static std::string getHtmlTemplate() {
        // 返回HTML模板的字符串，可以从文件读取或硬编码在此函数中
        return R"(
            <!DOCTYPE html>
            <html>
            <head>
                <title>Greetings</title>
            </head>
            <body>
                <h1>Hello, {{name}}!</h1>
                {%- for fruit  in fruits -%}
                    <p>{{ fruit}}</p>
                {%- endfor -%}
                {%- for C in V -%}
                    <p>{{C}}</p>
                {%- endfor -%}
            </body>
            </html>
        )";
    }

    static std::string getHtmlTemplate(const std::string htmlFile);
};

}
}
