set(SOURCES
        glthread.c
        graph.c
        net.c
        topologies.c
        nwcli.c
        comm.c
        main.c
        )

cmake_minimum_required(VERSION 3.16)
project(tcp_ip_stack C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(CommandParser)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#add_library(CommandParser libcli.h)

#file(GLOB SRC_FILES "*.c")
add_executable(main.exe ${SOURCES})

target_link_libraries(main.exe PRIVATE Threads::Threads)
target_link_libraries(main.exe PUBLIC CommandParser)