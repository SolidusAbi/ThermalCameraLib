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
find_package(realsense2 REQUIRED)
find_package(ColorMapShaders REQUIRED)

add_library(ThermalCameraLib SHARED)

target_include_directories(ThermalCameraLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ThermalCameraLib>
    $<INSTALL_INTERFACE:include/ThermalCameraLib>
)

target_include_directories(ThermalCameraLib PRIVATE
    $<BUILD_INTERFACE:${I3SYSTEM_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${realsense2_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${COLORMAPSHADERS_INCLUDES_DIR}>
)


target_sources(ThermalCameraLib PUBLIC
     $<BUILD_INTERFACE:include/ThermalCameraLib/ThermalCameraLib_global.h>
     $<BUILD_INTERFACE:include/ThermalCameraLib/Camera.h>
     $<BUILD_INTERFACE:include/ThermalCameraLib/DebugCamera.h>
     $<BUILD_INTERFACE:include/ThermalCameraLib/TEQ1Camera.h>
     $<BUILD_INTERFACE:include/ThermalCameraLib/RealSenseD415Camera.h>
     $<BUILD_INTERFACE:include/ThermalCameraLib/CameraGLViewer.h>
     $<BUILD_INTERFACE:include/ThermalCameraLib/CameraViewer.h>
)

add_subdirectory("src/")

target_link_libraries(ThermalCameraLib PRIVATE
    Qt5::Core Qt5::Widgets
    ${I3SYSTEM_LIBRARIES}
    ${realsense2_LIBRARY}
)

target_compile_definitions(ThermalCameraLib PRIVATE THERMALCAMERALIB_LIBRARY)

