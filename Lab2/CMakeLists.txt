cmake_minimum_required(VERSION 3.11)

project(unorderedmap CXX)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(unorderedmap
   "main.cc")
set_target_properties(unorderedmap PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(unorderedmap PUBLIC cxx_std_23)


add_executable(function_test
    "functions_test.cc")
target_link_libraries(function_test gtest gtest_main unorderedmap)
target_include_directories(function_test PRIVATE "${CMAKE_SOURCE_DIR}")

add_executable(task_test
"task_test.cc")
target_link_libraries(task_test gtest gtest_main unorderedmap)
target_include_directories(task_test PRIVATE "${CMAKE_SOURCE_DIR}")

add_executable(interface_task
"interface_task.cc")
target_link_libraries(interface_task gtest gtest_main unorderedmap)
target_include_directories(interface_task PRIVATE "${CMAKE_SOURCE_DIR}")