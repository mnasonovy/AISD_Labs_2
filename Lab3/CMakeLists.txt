cmake_minimum_required(VERSION 3.11)

project(grafs CXX)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

add_library(grafs
    Graph.cpp)
set_target_properties(grafs PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(grafs PUBLIC cxx_std_23)


add_executable(task_test
    task_test.cpp)
target_link_libraries(task_test grafs)
target_include_directories(task_test PRIVATE "${CMAKE_SOURCE_DIR}")


