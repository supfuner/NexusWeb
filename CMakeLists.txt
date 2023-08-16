#cmake最小版本需求
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#设置此项目的名称,并且赋值给系统变量${PROJECT_NAME}
PROJECT(NexusWeb) 

#设置选项开关，例如cmake .. -DEBUG=ON,那么就需要里面设置好开关
OPTION(TEST_DEBUG "option for debug" OFF)
if(DEBUG)
  	set(CMAKE_BUILD_TYPE Debug)
  	MESSAGE("**********debug") 
else()
	set(CMAKE_BUILD_TYPE Debug)
	MESSAGE("**********Debug") 
endif()

# 指定编译器
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11   -g  -Wall  ")

#导入需要使用的boost库，如regex filesystem thread
find_package(Boost REQUIRED COMPONENTS system filesystem thread)

# 添加include路径，也就是头文件路径
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# 添加源码
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/web DIR_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/socket DIR_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/thread DIR_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/utility DIR_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/control DIR_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/view DIR_SRCS)
message(${DIR_SRCS})
# 添加lib文件路径
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")

#生成可执行文件target ，后面填写的是生成此可执行文件所依赖的源文件列表。
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# 给目标添加依赖库
target_link_libraries(${PROJECT_NAME} 
	pthread
	${Boost_LIBRARIES} 
	)

# 生成库文件，SHARED代表动态库，STATIC代表静态库， 最后一个参数代表此库的源文件列表
# add_library(lib_name SHARED or STATIC lib_source_code) 

install(
	TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION   ${CMAKE_CURRENT_SOURCE_DIR}/output/lib #动态库
        ARCHIVE DESTINATION   ${CMAKE_CURRENT_SOURCE_DIR}/output/lib #静态库
        RUNTIME DESTINATION   ${CMAKE_CURRENT_SOURCE_DIR}/output/bin #可执行文件
)

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/demo.cpp  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output/include/ #安装文件
)
