# configure tests build

add_executable(socket socket.cpp)
target_link_libraries(socket)
add_test(NAME socket COMMAND socket)

add_executable(peer_server peer_server.cpp)
target_link_libraries(peer_server)

add_executable(peer_client peer_client.cpp)
target_link_libraries(peer_client)
