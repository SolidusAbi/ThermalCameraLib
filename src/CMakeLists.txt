add_subdirectory("Widgets/")

target_sources(ThermalCameraLib PUBLIC
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp>
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/DebugCamera.cpp>
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/TEQ1Camera.cpp>
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/RealSenseD415Camera.cpp>
)
