cmake_minimum_required(VERSION 3.7)
project(3_raya_p2p)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        client.cpp
        DieWithError.cpp
        game.h
        HandleTCPClient.h
        TCPEchoServer.cpp)

add_executable(3_raya_p2p ${SOURCE_FILES})