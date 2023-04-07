cmake_minimum_required(VERSION 2.8)

project( dummy )

include_directories(include)

add_executable( dummy main.cpp)

target_link_libraries( dummy zmqpp )

target_link_libraries( dummy zmq )

target_link_libraries( dummy sodium )

target_link_libraries(dummy pthread)

target_compile_features(dummy PUBLIC cxx_std_17)