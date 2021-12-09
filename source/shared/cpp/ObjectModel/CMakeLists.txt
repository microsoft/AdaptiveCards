cmake_minimum_required(VERSION 3.16)

# set the project name
project(ObjectModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Glob for file list -- N.B. this isn't recommended, but using as a convenience
#   Builders might need to manually clean/regenerate when new files are added.
file(GLOB ObjectModel_SRC CONFIGURE_DEPENDS "*.cpp")

find_package(jsoncpp CONFIG REQUIRED)

add_library(ObjectModel STATIC ${ObjectModel_SRC})

target_link_libraries(ObjectModel PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)

target_precompile_headers(ObjectModel
  PUBLIC
  pch.h)

