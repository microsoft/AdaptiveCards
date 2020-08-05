cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(detr)

add_subdirectory(pybind11)
find_package (Python COMPONENTS Development)
find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)

message(STATUS "Pytorch status: ")
message(STATUS " libraries: ${TORCH_LIBRARIES}")
message(STATUS "    include path: ${TORCH_INCLUDE_DIRS}")

message(STATUS "Python status: ")
message(STATUS "    libraries: ${Python_LIBRARIES}")
message(STATUS "    include path: ${Python_INCLUDE_DIRS}")

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


#SET (CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${TORCH_INCLUDE_DIRS})
include_directories(${Python_INCLUDE_DIRS})

add_executable(detr detr_infer.cpp)
# pybind11_add_module(detr detr.cpp)

target_link_libraries(detr PRIVATE ${OpenCV_LIBS})
target_link_libraries(detr PRIVATE ${TORCH_LIBRARIES})
target_link_libraries(detr PRIVATE ${Python_LIBRARIES})
set_property(TARGET detr PROPERTY CXX_STANDARD 14)
