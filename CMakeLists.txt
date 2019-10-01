cmake_minimum_required(VERSION 3.9)

project(ThermalCameraLib VERSION 0.01
                         LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
find_package(i3system REQUIRED)

message("Codigo fuente poderoso!!")
message("${SRC_FILES}")

message("Cabeceras poderosas")
message("${HEADERS_FILES}")



add_library(ThermalCameraLib SHARED)

target_sources(ThermalCameraLib PUBLIC
    include/ThermalCameraLib/Camera.h
    include/ThermalCameraLib/CameraGLViewer.h
    include/ThermalCameraLib/TEQ1Camera.h
    include/ThermalCameraLib/CameraViewer.h
    include/ThermalCameraLib/thermalcameralib.h
    include/ThermalCameraLib/ThermalCameraLib_global.h
)

add_subdirectory("src/")

target_include_directories(ThermalCameraLib PUBLIC include/ThermalCameraLib)
target_include_directories(ThermalCameraLib PRIVATE /usr/local/include/i3system)

#include_directories(/usr/local/include/i3system)
link_directories(/usr/local/lib)
target_link_libraries(ThermalCameraLib PRIVATE Qt5::Core Qt5::Widgets i3system_imgproc_64 i3system_usb_64 i3system_te_64 usb-1.0)

target_compile_definitions(ThermalCameraLib PRIVATE THERMALCAMERALIB_LIBRARY)

