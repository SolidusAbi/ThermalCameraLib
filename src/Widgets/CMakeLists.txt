set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

target_sources(ThermalCameraLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CameraGLViewer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CameraViewer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CameraViewer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/cameraviewer.ui
)
