cmake_minimum_required(VERSION 3.29)
    project(FlowCast1)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Include directories
    include_directories(include)

    # Source files
    file(GLOB_RECURSE SOURCES "src/*.cpp")
    file(GLOB_RECURSE HEADERS "include/*.h")

    # Add executable target
    add_executable(FlowCast1
        ${SOURCES}
        ${HEADERS}
            main.cpp
    )
