#include <algorithm>
#include "Render.h"
#include "File.h"
using namespace pisco::utility;

std::string Render::render(const UserData& data, const std::string htmlFile) {
    std::string htmlTemplate = getHtmlTemplate(htmlFile);  // 获取HTML模板
    if (!htmlTemplate.empty())
    {
        // 替换模板中的循环标签
        renderForeach(htmlTemplate, data);    
        renderElement(htmlTemplate, data);
        // 替换其他占位符或特定标记...
    }    
    return htmlTemplate;
}

std::string Render::render(const std::string htmlFile) {
    std::string htmlTemplate = getHtmlTemplate(htmlFile);  // 获取HTML模板   
    return htmlTemplate;
}

void Render::renderElement(std::string & htmlTemplate, const UserData& data)
{
        size_t elementStart = htmlTemplate.find(kLeftBraces);
        while(elementStart != std::string::npos)
        {
            size_t elementEnd = htmlTemplate.find(kRightBraces);
            std::string content = htmlTemplate.substr(elementStart, elementEnd - elementStart + kRightBraces.size());
            int contentSize = content.size();
            std::string element = htmlTemplate.substr(elementStart + kLeftBraces.size(), elementEnd - elementStart - kRightBraces.size());
            element.erase(std::remove(element.begin(), element.end(), ' '), element.end());
            auto e = data.elements.find(element);
            if (e != data.elements.end())
            {
                replaceBraces(content, e->second);
                htmlTemplate.replace(elementStart, contentSize, content);
            }
            else
            {
                break;
            }
            elementStart = htmlTemplate.find(kLeftBraces);            
        }
};

void Render::renderForeach(std::string & htmlTemplate, const UserData& data)
{
        size_t forLoopPos = htmlTemplate.find(kForStart);
        while (forLoopPos != std::string::npos) {
            size_t endLoopPos = htmlTemplate.find(kForEndMark, forLoopPos);
            if (endLoopPos == std::string::npos) {
                break;
            }

            std::string loopStatement = htmlTemplate.substr(forLoopPos + kForStart.size(), endLoopPos - forLoopPos - kForStart.size());

            std::string loopVariable, loopKey;
            size_t inKeywordPos = loopStatement.find(kForIn);
            if (inKeywordPos != std::string::npos) {
                loopVariable = loopStatement.substr(0, inKeywordPos);
                loopVariable.erase(remove(loopVariable.begin(), loopVariable.end(), ' '), loopVariable.end());
                loopKey = loopStatement.substr(inKeywordPos + kForIn.size(), endLoopPos-inKeywordPos);
                loopKey.erase(remove(loopKey.begin(), loopKey.end(), ' '), loopKey.end());
            }
            
            std::string loopContent = htmlTemplate.substr(endLoopPos + kForEndMark.size());
            size_t endLoopContentPos = loopContent.find(kForEnd);
            if (endLoopContentPos != std::string::npos) {
                loopContent = loopContent.substr(0, endLoopContentPos);
            }

            std::string renderedLoopContent;
            bool loopVariableExist = false;
            for (const auto& item : data.data) {
                if (item.first == loopKey) {
                    loopVariableExist = true;
                    const std::vector<std::string>& loopData = item.second;
                    for (const auto& item : loopData) {
                        std::string loopContentCopy = loopContent;
                        size_t itemPlaceholderPos = loopContentCopy.find(kLeftBraces + loopVariable + kRightBraces);
                        if (itemPlaceholderPos != std::string::npos) {
                            loopContentCopy.replace(itemPlaceholderPos, loopVariable.length() + 4, item);
                        }
                        renderedLoopContent += loopContentCopy;
                    }
                    break;
                }
            }

            if (!loopVariableExist) {
                renderedLoopContent = "Loop variable '" + loopVariable + "' does not exist.";
            }

            htmlTemplate.replace(forLoopPos, endLoopContentPos + kForEnd.size() + (endLoopPos - forLoopPos + kForEndMark.size()), renderedLoopContent);

            forLoopPos = htmlTemplate.find(kForStart);
        }
}

void Render::replaceBraces(std::string & htmlTemplate, const std::string data)
{
        size_t elementStart = htmlTemplate.find(kLeftBraces);
        size_t elementEnd   = htmlTemplate.find(kRightBraces);   
        std::string element = htmlTemplate.substr(elementStart + kLeftBraces.size(), elementEnd - elementStart - kRightBraces.size());
        element.erase(remove(element.begin(), element.end(), ' '), element.end());
        htmlTemplate.replace(elementStart, elementEnd - elementStart + kRightBraces.size(), data);        
}    

std::string Render::getHtmlTemplate(const std::string htmlFile){
    std::string output;
    if (0 == PFile::ReadFile(htmlFile, output))
    {
        return output;
    }
    return output;
}