cmake_minimum_required (VERSION 2.8)

project (simple_light_filter)

# Platform specifics.
#
if (MSVC)
	add_definitions (-D_CRT_SECURE_NO_DEPRECATE)
	add_definitions (-D_CRT_SECURE_NO_WARNINGS)
	add_definitions (-D_SCL_SECURE_NO_DEPRECATE)
	add_definitions (-D_SCL_SECURE_NO_WARNINGS)
	add_definitions (-D_SECURE_SCL=0)
elseif (CMAKE_COMPILER_IS_GCC)
	add_definitions (-fPIC)
	add_definitions (-mmmx)
	add_definitions (-msse)
	add_definitions (-msse2)
endif ()

# ER SDK.
#
find_path (ER_SDK_INCLUDE_DIR REQUIRED)
find_path (ER_SDK_LIB_DIR REQUIRED)

set (CURRENT_SOURCE_DIR "${CMAKE_SOURCE_DIR}")

# Setup build path.
#
set (ER_INSTALL_BINARY_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set (ER_INSTALL_LIBRARY_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ER_INSTALL_BINARY_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ER_INSTALL_LIBRARY_DIR})

# Include directories
#
include_directories ("${ER_SDK_INCLUDE_DIR}")
include_directories ("${CURRENT_SOURCE_DIR}")

# Source files
#
file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.c")
file(GLOB SOURCES "*.cpp")

# Library dependencies
#
add_library (simple_light_filter SHARED ${HEADERS} ${SOURCES})
target_link_libraries (simple_light_filter "${ER_SDK_LIB_DIR}/liber.lib")

INSTALL (TARGETS simple_light_filter RUNTIME DESTINATION current/bin)
INSTALL (TARGETS simple_light_filter LIBRARY DESTINATION current/lib ARCHIVE DESTINATION current/lib)
