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

set(COLORMAPSHADERS_INCLUDE_DIR ${COLORMAPSHADERS_INSTALL_DIR}/include/colormap)
