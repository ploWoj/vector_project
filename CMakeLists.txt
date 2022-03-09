cmake_minimum_required(VERSION 3.21)
project(vector_project)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(UT vector-gt test.cpp)
target_link_libraries(UT gtest_main)

//////////////////////////////////////
# add_test(NAME vector_test COMMAND vector-gt)
# add_executable(vector vector.cpp)