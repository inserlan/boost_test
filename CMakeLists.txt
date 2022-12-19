cmake_minimum_required(VERSION 3.0.0)
project(boost_geometry VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(CTest)
enable_testing()

include_directories("../3rdparty/PCL 1.11.1/3rdParty/Boost/include/boost-1_74")

add_executable(boost_geometry main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
