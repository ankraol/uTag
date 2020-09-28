
cmake_minimum_required(VERSION 3.0)
project(utag LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
#
#find_package(PkgConfig)
#find_package(TAGLIB)
#
#pkg_check_modules(GTKMM gtkmm-2.4) # look into FindPkgConfig.cmake,
# it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES
# contain what you expect

add_subdirectory(app)
add_subdirectory(3dparty)
