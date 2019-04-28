project(credis)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
MESSAGE(STATUS "#########################")

SET(CMAKE_BUILD_TYPE Release)
ADD_DEFINITIONS(-std=c++11 -g -Wall )

SET(EXTRA_INC_DIR /home/ext)


INCLUDE_DIRECTORIES( 
					/usr/local/include
					${PROJECT_SOURCE_DIR}/credis/clog
					${PROJECT_SOURCE_DIR}/credis/cconfig
					${PROJECT_SOURCE_DIR}/credis/cutil
					${PROJECT_SOURCE_DIR}/credis/credis
					${PROJECT_SOURCE_DIR}/credis/cserver
					${PROJECT_SOURCE_DIR}/credis/cnet
					${PROJECT_SOURCE_DIR}/credis/ctime
					${EXTRA_INC_DIR}/hiredis/include
					)
LINK_DIRECTORIES(
				${EXTRA_INC_DIR}/hiredis/lib
				
				)

file(GLOB ALL_CXX_SRCS
					${PROJECT_SOURCE_DIR}/credis/clog/*.cpp
					${PROJECT_SOURCE_DIR}/credis/cconfig/*.cpp
					${PROJECT_SOURCE_DIR}/credis/cutil/*.cpp
					${PROJECT_SOURCE_DIR}/credis/credis/*.cpp
					${PROJECT_SOURCE_DIR}/credis/cserver/*.cpp
					${PROJECT_SOURCE_DIR}/credis/cnet/*.cpp
					${PROJECT_SOURCE_DIR}/credis/ctime/*.cpp
					./credis/*.cpp
					)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/linux/lib )
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/linux)



add_executable(${PROJECT_NAME} ${ALL_CXX_SRCS})

set(ALL_LIB  	pthread
				libhiredis.a
				)


target_link_libraries(${PROJECT_NAME} ${ALL_LIB})
