# configure tests build

add_executable(socket socket.cpp)
target_link_libraries(socket)
add_test(NAME socket COMMAND socket)
