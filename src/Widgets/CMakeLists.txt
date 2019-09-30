#set(SRC_FILES
#    ${SRC_FILES}
#    ${CMAKE_CURRENT_SOURCE_DIR}/CameraGLViewer.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.ui
#    PARENT_SCOPE
#)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

target_sources(ThermalCameraLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CameraGLViewer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/cameraviewer.ui
)
