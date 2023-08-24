#pragma once

#include <iostream>
#include <string>
using namespace std;

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;

namespace pisco{
namespace utility{

    class JsonValue 
    {

    };

    void CreateJsonParser(ptree &pt ,string input);

    template<typename T>
    bool GetValue(const ptree &pt, string key, T & value)
    {
        if (pt.count(key) != 0)
        {
            value = pt.get<T>(key);
            return true;
        }
        else
        {
            return false;
        }        
    };

    template<typename T>
    bool GetListValue(const ptree &pt, string key, vector<T> value)
    {
        value.clear();
        if (pt.count(key) != 0)
        {
            ptree vec = pt.get_child(key);
            for (auto pos = vec.begin(); pos != vec.end(); ++pos)
            {
                T v = pos->second.get_value<T>();
                value.push_back(v);
            }            
            return true;
        }
        else
        {
            return false;
        }
    };

    bool IsValueArray(const ptree &pt);

    bool IsValueObject(const ptree &pt);

    template<typename T>
    void SetJsonValue(ptree &pt, string key, T & value)
    {
        try
        {
            pt.put(key, value);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }     
    };

    void SetJsonChild(ptree &pt, string key, const ptree & value);

    template<typename T>
    void SetArrayValue(ptree &pt, string key, vector<T> v)
    {
        /**    
         * pt::ptree tree;
        pt::ptree arr;
        arr.push_back(std::make_pair("", "apple"));
        arr.push_back(std::make_pair("", "banana"));
        arr.push_back(std::make_pair("", "orange"));

        // 将 JSON 数组作为子节点添加到 Boost Property Tree 对象中
        tree.add_child("fruit", arr);*/
        ptree arr;
        for (size_t i = 0; i < v.size(); i++)
        {
            arr.push_back(std::make_pair("", v[i]));
        }
        SetJsonChild(pt, key, arr);
    }

    string JsonToString(ptree &pt);


}
}