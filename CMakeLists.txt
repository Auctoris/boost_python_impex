cmake_minimum_required(VERSION 3.9)
project(example)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -DHAVE_INTTYPES_NETINET_IN_H")

# Find necessary packages
find_package(PythonLibs 3.6 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIR})
 
find_package(Boost COMPONENTS python3 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(LIB_SOURCE_FILES example.cpp)
add_library(example MODULE ${LIB_SOURCE_FILES})

if(APPLE)
    set(PYTHON_LIBRARY "/usr/local/Cellar/python3/3.6.3/Frameworks/Python.framework/Versions/3.6/lib/libpython3.6.dylib")
endif()

target_link_libraries(example ${PYTHON_LIBRARY} ${Boost_LIBRARIES})

set_target_properties(example PROPERTIES PREFIX "")
