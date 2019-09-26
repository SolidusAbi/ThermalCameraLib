cmake_minimum_required(VERSION 3.5)

project(ThermalCameraLib VERSION 0.01
                         LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
find_package(i3system REQUIRED)

add_library(ThermalCameraLib SHARED
  ThermalCameraLib_global.h
  thermalcameralib.cpp
  thermalcameralib.h
  cameraviewer.h
  cameraviewer.cpp
  cameraviewer.ui
  cameraglviewer.h
  cameraglviewer.cpp
  Camera.h
  TEQ1Camera.h
  TEQ1Camera.cpp
)

#target_include_directories(ThermalCameraLib PUBLIC include)
target_link_libraries(ThermalCameraLib PRIVATE Qt5::Core Qt5::Widgets ${I3SYSTEM_LIBRARIES} usb-1.0)

target_compile_definitions(ThermalCameraLib PRIVATE THERMALCAMERALIB_LIBRARY)
