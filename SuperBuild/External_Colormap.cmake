include(ExternalProject)

###############################################################################
# ColorMap Shaders
###############################################################################

set(COLORMAPSHADERS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/src/colormap-shaders)
set(COLORMAPSHADERS_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/install/colormap-shaders)

ExternalProject_Add(
    ColorMapShaders

    GIT_REPOSITORY "https://github.com/SolidusAbi/colormap-shaders.git"
    GIT_TAG "cmake"
  
    SOURCE_DIR ${COLORMAPSHADERS_SOURCE_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${COLORMAPSHADERS_INSTALL_DIR}
)

# ExternalProject_Add_Step(
#   HumbleLogging CopyToBin
#   COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLOBAL_OUTPUT_PATH}/humblelogging/bin ${GLOBAL_OUTPUT_PATH}
#   COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLOBAL_OUTPUT_PATH}/humblelogging/lib ${GLOBAL_OUTPUT_PATH}
#   DEPENDEES install
# )

# set(HumbleLogging_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/3rdparty/humblelogging/include")
# set(HumbleLogging_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}humblelogging${CMAKE_SHARED_LIBRARY_SUFFIX}")

# include(ExternalProject)
# 
# set(COLORMAPSHADERS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/colormap-shaders/src)
# set(COLORMAPSHADERS_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/colormap-shaders/install)
# 
# ExternalProject_Add(colormap-shaders
#     PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/colormap-shaders/src
#     GIT_REPOSITORY https://github.com/SolidusAbi/colormap-shaders.git
#     GIT_TAG "cmake"
#     SOURCE_DIR ${COLORMAPSHADERS_SOURCE_DIR}
#     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=COLORMAPSHADERS_INSTALL_DIR
#     BUILD_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR> ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_CHIBIOS}
#     INSTALL_COMMAND ${MAKE} DESTDIR=${COLORMAPSHADERS_INSTALL_DIR} install
# ) 
