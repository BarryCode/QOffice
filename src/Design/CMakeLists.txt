#
#  Lesser General Public License 3.0
#  Copyright (C) 2016-2018 Nicolas Kogler
#
#  QOffice: The office framework for Qt
#

set(DESIGN_SOURCES
    Office.cpp
    OfficeAccent.cpp
    OfficeFont.cpp
    OfficeImage.cpp
    OfficePalette.cpp
)

set(DESIGN_HEADERS
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Config.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Design/Office.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Design/OfficeAccent.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Design/OfficeFont.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Design/OfficeImage.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Design/OfficePalette.hpp
)

qt5_add_resources(DESIGN_RESOURCES
    ${QOFFICE_RESOURCE_ROOT}/qoffice_fonts.qrc
    ${QOFFICE_RESOURCE_ROOT}/qoffice_images.qrc
)

add_library(${QOFFICE_LIBRARY}-design
    ${QOFFICE_LIBRARY_TYPE}
    ${DESIGN_SOURCES}
    ${DESIGN_HEADERS}
    ${DESIGN_RESOURCES}
)

target_include_directories(${QOFFICE_LIBRARY}-design
    PUBLIC
        $<BUILD_INTERFACE:${QOFFICE_INCLUDE_ROOT}>
        $<INSTALL_INTERFACE:../../include>
)

target_compile_features(${QOFFICE_LIBRARY}-design
    PRIVATE
        ${QOFFICE_COMPILE_FEATURES}
)

target_compile_definitions(${QOFFICE_LIBRARY}-design
    PRIVATE
        ${QOFFICE_COMPILE_DEFINITIONS}
)

target_link_libraries(${QOFFICE_LIBRARY}-design
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

install(
    TARGETS ${QOFFICE_LIBRARY}-design
    EXPORT qoffice-targets
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
