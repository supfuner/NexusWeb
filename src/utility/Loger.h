#pragma once

#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <memory>
#include <time.h>
#include <chrono>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/logger.h"
 
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/common.h"


#define ZLOG_PATH "./log/"
#define ZLOG_FILENAME "mylog.log"

namespace pisco{
namespace utility{

static inline int NowDateToInt()
{
	time_t now;
	time(&now);
 
	// choose thread save version in each platform
	tm p;
#ifdef _WIN32
	localtime_s(&p, &now);
#else
	localtime_r(&now, &p);
#endif // _WIN32
	int now_date = (1900 + p.tm_year) * 10000 + (p.tm_mon + 1) * 100 + p.tm_mday;
	return now_date;
}
 
static inline int NowTimeToInt()
{
	time_t now;
	time(&now);
	// choose thread save version in each platform
	tm p;
#ifdef _WIN32
	localtime_s(&p, &now);
#else
	localtime_r(&now, &p);
#endif // _WIN32
 
	int now_int = p.tm_hour * 10000 + p.tm_min * 100 + p.tm_sec;
	return now_int;
}

class ZLOG{
public:

    static ZLOG *getInstance(std::string filePath = ZLOG_PATH, std::string fileName = ZLOG_FILENAME, int mode = 0){
        static ZLOG zlog(filePath, fileName, mode);
        return &zlog;
    }
    std::shared_ptr<spdlog::logger> getLogger(){
        return m_logger;
    }

private:
	std::shared_ptr<spdlog::logger> m_logger;   //创建的logger指针

    ZLOG() = default;
    ZLOG(std::string filePath, std::string fileName, int mode){
        std::string logger_name;
        if(fileName == ZLOG_FILENAME){

            std::string file_name_prefix = fileName.substr(0, fileName.rfind("."));        
            int date = NowDateToInt();
            int time = NowTimeToInt();
            logger_name = file_name_prefix + "_" + std::to_string(date) + "_" + std::to_string(time) + ".log";
        }else{
            logger_name = fileName;
        }

        std::stringstream log_full_path;
		log_full_path << filePath << logger_name;
		if(access(filePath.c_str(), F_OK) != 0)
		{
			mkdir(filePath.c_str(), S_IRWXU);  //首先检查log目录是否存在，不存在则创建
		}

        // 限制 mode 范围
        mode = mode < 0 ? 0 : mode;
        mode = mode > 2 ? 2 : mode;
        
        
        try{

            if(mode == 0){
                // 控制台模式
                m_logger = spdlog::stdout_color_st(log_full_path.str());

            }else if(mode == 1){
                // 日志模式
                m_logger = spdlog::basic_logger_mt("basic_logger", log_full_path.str());	

            }else if(mode == 2){
                // 控制台 + 日志 模式

                // file sink
                auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_full_path.str(), true);

                /* 控制台sink */
		        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

                std::vector<spdlog::sink_ptr> sinks;
		        sinks.push_back(console_sink);
		        sinks.push_back(file_sink);
        		m_logger = std::make_shared<spdlog::logger>("", begin(sinks), end(sinks));

            }
      
            m_logger->set_level(spdlog::level::trace); // 打印等级，等级 trace 以下的将不会被打印出来，可更改
            //m_logger->set_pattern("[%Y-%m-%d %T][thread %t][%l]%v");   // 打印模板
            //m_logger->set_pattern("[%Y-%m-%d %T][thread %t][%l][%@:%#] %v");
            m_logger->set_pattern("[%Y-%m-%d %T][thread %t][%l][%s:%#][%!] %v");
            m_logger->flush_on(spdlog::level::level_enum::trace);

        }catch(const spdlog::spdlog_ex& ex){
            std::cout << "LOG error !" << "Log initialization failed: " << ex.what() << std::endl;

        }
    }

    
    ~ZLOG(){
        spdlog::drop_all();   //logger使用完成后，要执行drop操作，否则不能循环创建同一类型的logger
    }


};

// #define SPDLOG_LOGGER_CALL0(logger, level, ...) (logger)->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__)
// use embedded macro to support file and line number
#define LOG_TRACE(...) SPDLOG_LOGGER_CALL(ZLOG::getInstance()->getLogger().get(), spdlog::level::trace, __VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_LOGGER_CALL(ZLOG::getInstance()->getLogger().get(), spdlog::level::debug, __VA_ARGS__)
#define LOG_INFO(...)  SPDLOG_LOGGER_CALL(ZLOG::getInstance()->getLogger().get(), spdlog::level::info, __VA_ARGS__)
#define LOG_WARN(...)  SPDLOG_LOGGER_CALL(ZLOG::getInstance()->getLogger().get(), spdlog::level::warn, __VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_LOGGER_CALL(ZLOG::getInstance()->getLogger().get(), spdlog::level::err, __VA_ARGS__)
}
}



