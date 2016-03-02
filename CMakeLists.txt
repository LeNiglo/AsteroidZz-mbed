#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME "asteroidzz")
project(${PROJECT_NAME})

# Enable debug symbols by default
if (CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

set(asteroidzz_VERSION_MAJOR 1)
set(asteroidzz_VERSION_MINOR 1)
configure_file(
	"${PROJECT_SOURCE_DIR}/inc/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/inc")

# Define sources and executable
file(GLOB ALL_SRCS "src/*.cpp")

add_executable(${PROJECT_NAME} ${ALL_SRCS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

file(COPY "${PROJECT_SOURCE_DIR}/resources" DESTINATION ${PROJECT_BINARY_DIR})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

# boost::filesystem
find_package(Boost 1.34.0 REQUIRED system filesystem)
if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()


# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${asteroidzz_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${asteroidzz_VERSION_MINOR}")
include(CPack)