add_subdirectory("Widgets/")

#set(SRC_FILES
#    ${SRC_FILES}
#    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/TEQ1Camera.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/thermalcameralib.cpp
#    PARENT_SCOPE
#)

target_sources(ThermalCameraLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TEQ1Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/thermalcameralib.cpp
)
