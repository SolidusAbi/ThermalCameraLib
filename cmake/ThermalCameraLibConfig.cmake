# ThermalCameraLibConfig.cmake - package configuration file

get_filename_component(SELF_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
if (EXISTS ${SELF_DIR}/ThermalCameraLib.cmake)
    include(${SELF_DIR}/ThermalCameraLib.cmake)

    get_target_property(THERMALCAMERALIB_INCLUDE_DIR ThermalCameraLib INTERFACE_INCLUDE_DIRECTORIES)
    get_target_property(THERMALCAMERALIB_LIB_DIR ThermalCameraLib IMPORTED_LOCATION_DEBUG) #A cambiar
    message(STATUS "Found ThermalCameraLib:")
    message(STATUS " - Includes: ${THERMALCAMERALIB_INCLUDE_DIR}")
    message(STATUS " - Library: ${THERMALCAMERALIB_INCLUDE_DIR}")
    
else()
    message(STATUS "Not Found ThermalCameraLib")
endif()
