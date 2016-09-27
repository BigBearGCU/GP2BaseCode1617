cmake_minimum_required (VERSION 2.8)
project (GameApplication)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -l")

find_package(TinyXML REQUIRED)

add_subdirectory(Utils)

add_library(GameApplication STATIC src/GameApplication.cpp include/Common.h include/GameApplication.h)

include_directories(GameApplication include/ Utils/include ${TINYXML_INCLUDE_DIR})
# create the program
target_link_libraries(GameApplication Utils ${TINYXML_LIBRARIES} ${CMAKE_DL_LIBS})
