cmake_minimum_required(VERSION 3.10)

# set the project name
project(EmbeddedProfiler)

# add the executable
add_executable(ProfilerExample main.cpp)

target_include_directories(ProfilerExample PRIVATE ../include)

if (UNIX)
target_link_libraries(ProfilerExample PRIVATE pthread)
endif()
