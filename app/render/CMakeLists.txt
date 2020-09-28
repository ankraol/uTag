cmake_minimum_required(VERSION 3.1)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../../3dparty/taglib-master/taglib
        ${CMAKE_CURRENT_SOURCE_DIR}/../../3dparty/taglib-master/taglib/toolkit
        ${CMAKE_CURRENT_SOURCE_DIR}/../../3dparty/taglib-master/taglib/ape
        ${CMAKE_CURRENT_SOURCE_DIR}/../../3dparty/taglib-master/taglib/mpeg
        ${CMAKE_CURRENT_SOURCE_DIR}/../../3dparty/taglib-master/taglib/mpeg/id3v1
        ${CMAKE_CURRENT_SOURCE_DIR}/../../3dparty/taglib-master/taglib/mpeg/id3v2
        ${CMAKE_CURRENT_SOURCE_DIR}/../../3dparty/taglib-master/taglib/mpeg/id3v2/frames
        ${CMAKE_CURRENT_SOURCE_DIR}/../../3dparty/taglib-master/bindings/c/
)

project(render LANGUAGES CXX)
add_library(render mainWin.cpp DirectoryChooser.cpp Dir.cpp AudioList.cpp MultiTagEditor.cpp EditPopupMenu.cpp TagEditor.cpp)

target_link_libraries(render taglib)