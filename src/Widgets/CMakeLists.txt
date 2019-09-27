#set(SRC_FILES
#    ${SRC_FILES}
#    ${CMAKE_CURRENT_SOURCE_DIR}/CameraGLViewer.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.ui
#    PARENT_SCOPE
#)

target_sources(ThermalCameraLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CameraGLViewer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cameraviewer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/cameraviewer.ui
)
