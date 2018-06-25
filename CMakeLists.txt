#
#  Lesser General Public License 3.0
#  Copyright (C) 2016-2018 Nicolas Kogler
#
#  QOffice: The office framework for Qt
#

cmake_minimum_required(VERSION 3.10)

project(QOffice)

# version
set(QOFFICE_VERSION_MAJOR "1")
set(QOFFICE_VERSION_MINOR "0")
set(QOFFICE_VERSION_PATCH "0")
set(QOFFICE_VERSION "${QOFFICE_VERSION_MAJOR}.${QOFFICE_VERSION_MINOR}")
set(QOFFICE_VERSION_FULL "${QOFFICE_VERSION}.${QOFFICE_VERSION_PATCH}")

# build options
option(QOFFICE_BUILD_SHARED "Build as shared library" ON)
option(QOFFICE_BUILD_EXAMPLES "Build the examples" OFF)
option(QOFFICE_BUILD_DOCS "Build the documentation" OFF)

# module options
option(QOFFICE_BUILD_DESIGN "Build the design module" ON)
option(QOFFICE_BUILD_WIDGET "Build the widget module" ON)

if (QOFFICE_BUILD_SHARED AND UNIX)
    # unix can make use of links for shared libraries.
    set(QOFFICE_LIBRARY qoffice)
else()
    # windows needs static library names. We use the major version as suffix
    # since we want to keep QOffice binary compatible within each major version.
    set(QOFFICE_LIBRARY qoffice${QOFFICE_VERSION_MAJOR})
endif()

set(QOFFICE_INCLUDE_ROOT ${CMAKE_SOURCE_DIR}/include)
set(QOFFICE_RESOURCE_ROOT ${CMAKE_SOURCE_DIR}/resources)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# dependencies
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

# features
set(QOFFICE_COMPILE_FEATURES cxx_std_11 cxx_auto_type)

# definitions
if (QOFFICE_BUILD_SHARED)
    set(QOFFICE_COMPILE_DEFINITIONS QOFFICE_BUILD_SHARED)
    set(QOFFICE_LIBRARY_TYPE SHARED)
else()
    set(QOFFICE_COMPILE_DEFINITIONS QOFFICE_BUILD_STATIC)
    set(QOFFICE_LIBRARY_TYPE STATIC)
endif()

# subdirectories
add_subdirectory(src)

if (QOFFICE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (QOFFICE_BUILD_DOCS)
    add_subdirectory(docs)
endif()
