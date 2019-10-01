add_subdirectory("Widgets/")

target_sources(ThermalCameraLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TEQ1Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RealSenseD415Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/thermalcameralib.cpp
)
