#include "Json.h"





void pisco::utility::CreateJsonParser(ptree &pt ,string input)
{
    std::istringstream iss(input);
    read_json(iss, pt);
}

bool pisco::utility::IsValueArray(const ptree& pt) {
    if (pt.empty()) {
        // 值为空
        return false;
    } else if (pt.size() > 0) {
        // 值有子节点，进一步判断
        bool isArray = true;

        for (const auto& child : pt) {
            // 如果子节点有关联的键-值对，判定为对象
            if (!child.first.empty()) {
                isArray = false;
                break;
            }
        }

        return isArray;
    } else {
        return false;
    }
}

bool pisco::utility::IsValueObject(const ptree& pt) {
    if (pt.empty()) {
        // 值为空，既不是对象也不是数组
        return false;
    } else if (pt.size() > 0) {
        // 值有子节点，进一步判断
        bool isObject = true;
        bool isArray = true;

        for (const auto& child : pt) {
            if (!child.first.empty()) {
                // 子节点有关联的键-值对，判定为对象
                isArray = false;
            }

            if (!std::all_of(child.second.begin(), child.second.end(),
                             [](const ptree::value_type& item) { return item.first.empty(); })) {
                // 子节点中包含非空键的子节点，判定为对象
                isArray = false;
            }

            if (std::any_of(child.second.begin(), child.second.end(),
                            [](const ptree::value_type& item) { return item.first.empty(); })) {
                // 子节点中包含空键的子节点，判定为数组
                isObject = false;
            }
        }

        return isObject && !isArray;
    } else {
        return false;
    }
}

void pisco::utility::SetJsonChild(ptree &pt, string key, const ptree & value)
{
    try
    {
        pt.add_child(key, value);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    } 
}

string pisco::utility::JsonToString(ptree &pt)
{
    std::stringstream ss;
    write_json(ss, pt);
    return ss.str();
}
