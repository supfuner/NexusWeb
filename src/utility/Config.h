#pragma once


#include <boost/property_tree/ini_parser.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp> //-lboost_system -lboost_filesystem
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <map>

using namespace std;

const string kRouteFile = "../config/urls.route";
namespace pisco{
namespace utility{

    namespace Ini
    {
        static std::string config_filename;
        static bool read_ini_file(const std::string &filename, boost::property_tree::ptree &pt)
    {
        if(!boost::filesystem::exists(filename))
        {
            std::cerr << "File dose not exist:" << filename << std::endl;
            return false;
        }
        config_filename = filename;
        boost::property_tree::ini_parser::read_ini(filename, pt);

        return true;
    }

        template <typename T>
        bool get_ini_value(boost::property_tree::ptree &pt, const std::string &key, T &value)
    {
        try
        {
            value = pt.get<T>(key);
        }
        catch(std::exception e)
        {
            std::cout << config_filename << ":The " + key + " key does not exist!" << std::endl;
            return false;
        }
        return true;
    }

        template <typename T>
        void put_value(boost::property_tree::ptree &pt, const std::string &key, T &value)
    {
        pt.put(key, value);
    }

        static bool write_ini_file(boost::property_tree::ptree &pt,const std::string &filename)
    {
        try
        {
            boost::property_tree::ini_parser::write_ini(filename, pt);
        }
        catch(std::exception e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }

        return true;
    }

        static bool saveConfig(const std::string &_filename, std::map<std::string, std::string> &_config_params)
    {
        boost::property_tree::ptree pt;
        for(auto it : _config_params)
        {
            put_value(pt, it.first, it.second);
        }
        return write_ini_file(pt, _filename);
    }

        static bool readConfig(const std::string &_filename, std::map<std::string, std::string> &_config_params)
    {
        boost::property_tree::ptree pt;
        bool ret = read_ini_file(_filename, pt);
        if(ret)
        {
            for(auto &it : _config_params)
            {
                ret = get_ini_value(pt, it.first, it.second);
                if(!ret)
                {
                   break;
                }
            }
        }
        return ret;
    }
    };

    class Route
    {
    public:
        struct RouteInfo {
            std::string path;
            std::string controller;
        };

        static std::vector<RouteInfo> parseUrlsFile(const std::string& filename)
        {
            std::vector<RouteInfo> routes;

            std::ifstream file(filename);
            if (!file.is_open()) 
            {
                std::cerr << "Failed to open file: " << filename << std::endl;
                return routes;
            }

            std::string line;
            std::regex routeRegex(R"(\s*path\s*\(\s*[\'\"]([\w/{}<>:]+)[\'\"]\s*,\s*([\w.]+)\s*\))");
    
            while (std::getline(file, line)) {
                std::smatch match;
                if (std::regex_search(line, match, routeRegex)) 
                {
                    if (match.size() == 3)
                    {
                        RouteInfo route;
                        route.path = match[1].str();
                        route.controller = match[2].str();
                        routes.push_back(route);
                    }
                }
            }

            file.close();
            return routes;
        }

        static void GetRouteFromfile(map<string, string> &route_map)
        {
            vector<RouteInfo> routeVec = parseUrlsFile(kRouteFile);
            for (auto v : routeVec)
            {
                route_map.insert(pair<string, string>(v.path, v.controller));
            }                        
        }
    };
}
}



