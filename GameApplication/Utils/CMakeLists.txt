cmake_minimum_required (VERSION 2.8)
project (Utils)

find_package(TinyXML REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -l")

add_library(Utils STATIC src/Log.cpp src/clock.cpp src/ProgramOptions.cpp src/CommandLineParser.cpp src/XMLOptionsParser.cpp src/Timer.cpp
include/Log.h include/NonCopyable.h include/clock.h include/ProgramOptions.h include/ProgramOptions.h include/CommandLineParser.h include/XMLOptionsParser.h include/Timer.h include/Utils.h)

include_directories(Utils include/ ${TINYXML_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})
# create the program
target_link_libraries(Utils ${SDL2_LIBRARY} ${TINYXML_LIBRARIES} ${CMAKE_DL_LIBS})
