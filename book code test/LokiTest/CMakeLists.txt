cmake_minimum_required (VERSION 2.6)

project (test)
set(CMAKE_CXX_COMPILER g++)
SET(CMAKE_CXX_FLAG "-std=c++11 -O0")

# assume we put project in code folder 
INCLUDE_DIRECTORIES(/home/username/code/LokiTest/Loki)

set (PRO_SRC
test.cpp
FunctorTest.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Loki/SmallObj.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Loki/Singleton.cpp
)

add_executable(test ${PRO_SRC})
