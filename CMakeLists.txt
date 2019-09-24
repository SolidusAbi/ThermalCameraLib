cmake_minimum_required(VERSION 3.5)

project(ThermalCameraLib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)

add_library(ThermalCameraLib SHARED
  ThermalCameraLib_global.h
  thermalcameralib.cpp
  thermalcameralib.h
  cameraviewer.h
  cameraviewer.cpp
  cameraviewer.ui
  cameraglviewer.h
  cameraglviewer.cpp
)

target_link_libraries(ThermalCameraLib PRIVATE Qt5::Core Qt5::Widgets usb-1.0)

target_compile_definitions(ThermalCameraLib PRIVATE THERMALCAMERALIB_LIBRARY)
