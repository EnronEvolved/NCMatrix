cmake_minimum_required(VERSION 3.14) # I guess?

project(NCMatrix
	VERSION 0.9.0
	DESCRIPTION "CMatrix clone written using notcurses"
	LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# adding an uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

# Makefile generation
string(APPEND CMAKE_C_FLAGS_DEBUG " -O0")
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -O0")
# ^ Shameless notcurses copypasta

find_package(notcurses 1.3.4 REQUIRED)

add_library(libnotcurses SHARED IMPORTED)
set_target_properties(libnotcurses PROPERTIES
	IMPORTED_LOCATION "/usr/local/lib")

add_executable(ncmatrix ./src/main.cxx ./src/planepool.cxx ./src/planepoolelement.cxx ./src/ncm_utils.cxx)
target_link_libraries(ncmatrix ${notcurses_LIBRARIES})
set_target_properties(ncmatrix PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")

# Installation target
install(TARGETS ncmatrix DESTINATION bin)
