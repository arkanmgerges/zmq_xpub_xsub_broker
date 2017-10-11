project(appTest)

link_directories(/usr/local/lib)
include_directories(/usr/local/include/google)

add_executable(${PROJECT_NAME} checkZmq.c)

target_link_libraries(${PROJECT_NAME} cmockery zmq pthread)