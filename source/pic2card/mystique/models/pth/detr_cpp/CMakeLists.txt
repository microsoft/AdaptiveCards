cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(detr_inference)

# add_subdirectory(libs/pybind11)

find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)
find_package(Python3 REQUIRED)

message(STATUS "Pytorch status: ")
message(STATUS " libraries: ${TORCH_LIBRARIES}")
message(STATUS "    include path: ${TORCH_INCLUDE_DIRS}")
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

#SET (CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${TORCH_INCLUDE_DIRS})
add_executable(detr_inference detr_infer.cpp)
#
target_link_libraries(detr_inference ${OpenCV_LIBS})
target_link_libraries(detr_inference ${TORCH_LIBRARIES})
set_property(TARGET detr_inference PROPERTY CXX_STANDARD 14)
