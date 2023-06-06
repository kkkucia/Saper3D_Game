cmake_minimum_required(VERSION 3.25)
project(saper)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lGL -lGLU -lglut")

find_package(OpenAL REQUIRED)
include_directories(${OPENAL_INCLUDE_DIR})

find_package(ALSA REQUIRED)
include_directories(${ALSA_INCLUDE_DIRS})

add_executable(saper main.cpp board.cpp board.h GameFrontend.h GameFrontend.cpp globalBoard.h)
target_link_libraries(saper ${OPENAL_LIBRARY} ${ALSA_LIBRARIES} GL GLU glut)



