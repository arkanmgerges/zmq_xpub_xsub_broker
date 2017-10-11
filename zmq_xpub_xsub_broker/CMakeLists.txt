cmake_minimum_required(VERSION 3.8)
project(zmq_xpub_xsub_broker)

set(CMAKE_C_STANDARD 11)

add_subdirectory(test)

link_directories(/usr/local/lib)
set(SOURCE_FILES main.c app.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} zmq)
