#
#  Lesser General Public License 3.0
#  Copyright (C) 2016-2018 Nicolas Kogler
#
#  QOffice: The office framework for Qt
#

set(WIDGET_SOURCES
    OfficeLineEdit.cpp
    OfficeMenu.cpp
    OfficeMenuEvent.cpp
    OfficeMenuHeader.cpp
    OfficeMenuItem.cpp
    OfficeMenuPanel.cpp
    OfficeMenuPanelBar.cpp
    OfficeMenuPinButton.cpp
    OfficeTextbox.cpp
    OfficeTooltip.cpp
    OfficeWidget.cpp
    OfficeWindowMenu.cpp
    OfficeWindowMenuItem.cpp
    MenuItems/OfficeMenuTextboxItem.cpp
    Dialogs/OfficeWindow.cpp
    Dialogs/OfficeWindowResizeArea.cpp
    Dialogs/OfficeWindowTitlebar.cpp
)

set(WIDGET_HEADERS
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/OfficeMenuItem.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/OfficeMenuPanel.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/OfficeMenuPanelBar.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/OfficeMenuPinButton.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/OfficeTextbox.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/OfficeTooltip.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/OfficeWidget.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/OfficeWindowMenu.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/OfficeWindowMenuItem.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/MenuItems/OfficeMenuTextboxItem.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/Dialogs/OfficeWindow.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/Dialogs/OfficeWindowResizeArea.hpp
    ${QOFFICE_INCLUDE_ROOT}/QOffice/Widgets/Dialogs/OfficeWindowTitlebar.hpp
)

qt5_add_resources(WIDGET_RESOURCES
    ${QOFFICE_RESOURCE_ROOT}/qoffice_editors.qrc
    ${QOFFICE_RESOURCE_ROOT}/qoffice_plugins.qrc
    ${QOFFICE_RESOURCE_ROOT}/qoffice_stylesheets.qrc
)

add_library("${QOFFICE_LIBRARY}-widget"
    ${QOFFICE_LIBRARY_TYPE}
    ${WIDGET_SOURCES}
    ${WIDGET_HEADERS}
    ${WIDGET_RESOURCES}
)

target_include_directories("${QOFFICE_LIBRARY}-widget"
    PUBLIC
        $<BUILD_INTERFACE:${QOFFICE_INCLUDE_ROOT}>
        $<INSTALL_INTERFACE:../../include>
)

target_compile_features("${QOFFICE_LIBRARY}-widget"
    PRIVATE
        ${QOFFICE_COMPILE_FEATURES}
)

target_link_libraries("${QOFFICE_LIBRARY}-widget"
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

install(
    TARGETS "${QOFFICE_LIBRARY}-widget"
    EXPORT qoffice-targets
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
