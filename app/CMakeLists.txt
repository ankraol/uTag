cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(app_project LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
set(SOURCE_EXE main.cpp)

#now you can add subdirectories
add_subdirectory(src)
include_directories(../3dparty/taglib-master/taglib/)

add_compile_options(
        -std=c++17
        -Werror
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-parameter
)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

if (GTKMM_FOUND)
    link_directories(${GTKMM_LIBRARY_DIRS})
    include_directories(${GTKMM_INCLUDE_DIRS})
    add_executable(utag main.cpp src/AudioFileInfo.cpp render/mainWin.cpp src/getDirs.cpp src/getDirs.h src/setTags.cpp src/setTags.h render/DirectoryChooser.cpp render/DirectoryChooser.h render/Dir.cpp render/Dir.h render/AudioList.cpp render/AudioList.h render/MultiTagEditor.cpp render/MultiTagEditor.h render/EditPopupMenu.cpp render/EditPopupMenu.h render/TagEditor.cpp render/TagEditor.h)
    target_link_libraries(utag taglib ${GTKMM_LIBRARIES})
endif()