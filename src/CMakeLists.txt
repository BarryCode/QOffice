#
#  Lesser General Public License 3.0
#  Copyright (C) 2016-2018 Nicolas Kogler
#
#  QOffice: The office framework for Qt
#

if (QOFFICE_BUILD_DESIGN)
    add_subdirectory(Design)
endif()

if (QOFFICE_BUILD_WIDGET)
    add_subdirectory(Widgets)
endif()

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/QOffice
    DESTINATION include
)

install(
    EXPORT qoffice-targets
    FILE qoffice-targets.cmake
    DESTINATION lib/cmake/qoffice
)
