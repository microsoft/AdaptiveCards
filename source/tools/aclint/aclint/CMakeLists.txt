# CMakeList.txt : CMake project for aclint, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(cxxopts 2.2.0 REQUIRED)

# Add source to this project's executable.
add_executable (aclint "aclint.cpp" "aclint.h")

target_link_libraries(aclint PRIVATE nlohmann_json::nlohmann_json)

# TODO: Add tests and install targets if needed.
