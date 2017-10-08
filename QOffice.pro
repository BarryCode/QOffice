###########################################################
#
#   QOffice: The office framework for Qt
#   Copyright (C) 2016-2018 Nicolas Kogler
#   License: Lesser General Public License 3.0
#
###########################################################

###########################################################
# GENERAL SETTINGS
#
###########################################################
TARGET   = QOffice
TEMPLATE = lib
QT      += widgets uiplugin designer uitools
CONFIG  += plugin c++11
DEFINES += QOFFICE_BUILD_SHARED

###########################################################
# WINDOWS SETTINGS
#
###########################################################
win32 {
    QMAKE_TARGET_COMPANY     = Nicolas Kogler
    QMAKE_TARGET_PRODUCT     = QOffice
    QMAKE_TARGET_DESCRIPTION = The office framework for Qt
    QMAKE_TARGET_COPYRIGHT   = Copyright (C) 2016-2018 Nicolas Kogler
}

####################################################### ####
# COMPILER SETTINGS
#
###########################################################
msvc {
    QMAKE_CXXFLAGS += /EHsc
} gcc {
    QMAKE_CXXFLAGS += -fno-exceptions
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
}

###########################################################
# INCLUDE PATHS
#
###########################################################
INCLUDEPATH += include \
               include/QOffice \
               include/QOffice/Widgets

###########################################################
# RESOURCES & MISCELLANEOUS
#
###########################################################
RESOURCES += resources/qoffice_plugins.qrc \
             resources/qoffice_images.qrc \
             resources/qoffice_editors.qrc \
             resources/qoffice_fonts.qrc \
    resources/qoffice_stylesheets.qrc

###########################################################
# HEADER FILES
#
###########################################################
HEADERS += include/QOffice/Config.hpp \
           include/QOffice/Widgets/OfficeWidget.hpp \
           include/QOffice/Design/OfficeAccent.hpp \
           include/QOffice/Design/OfficePalette.hpp \
           include/QOffice/Design/OfficeImage.hpp \
           include/QOffice/Design/OfficeFont.hpp \
           include/QOffice/Widgets/Dialogs/OfficeWindow.hpp \
           include/QOffice/Widgets/Dialogs/OfficeWindowResizeArea.hpp \
           include/QOffice/Design/Office.hpp \
           include/QOffice/Widgets/OfficeWindowMenu.hpp \
           include/QOffice/Widgets/OfficeWindowMenuItem.hpp \
           include/QOffice/Widgets/OfficeTooltip.hpp \
           include/QOffice/Widgets/OfficeMenu.hpp \
           include/QOffice/Widgets/OfficeMenuHeader.hpp \
           include/QOffice/Widgets/OfficeMenuPanel.hpp \
           include/QOffice/Widgets/OfficeMenuItem.hpp \
           include/QOffice/Widgets/Dialogs/OfficeWindowTitlebar.hpp \
           include/QOffice/Widgets/OfficeMenuPinButton.hpp \
           include/QOffice/Widgets/OfficeMenuPanelBar.hpp \
           include/QOffice/Widgets/OfficeMenuEvent.hpp \
           include/QOffice/Widgets/OfficeTextbox.hpp \
           include/QOffice/Widgets/MenuItems/OfficeMenuTextboxItem.hpp \
           include/QOffice/Widgets/OfficeLineEdit.hpp

###########################################################
# SOURCE FILES
#
###########################################################
SOURCES += src/Widgets/OfficeWidget.cpp \
           src/Design/OfficeAccent.cpp \
           src/Design/OfficePalette.cpp \
           src/Design/OfficeImage.cpp \
           src/Design/OfficeFont.cpp \
           src/Widgets/Dialogs/OfficeWindowResizeArea.cpp \
           src/Widgets/Dialogs/OfficeWindow.cpp \
           src/Widgets/OfficeWindowMenu.cpp \
           src/Widgets/OfficeWindowMenuItem.cpp \
           src/Widgets/OfficeTooltip.cpp \
           src/Widgets/OfficeMenu.cpp \
           src/Widgets/OfficeMenuHeader.cpp \
           src/Widgets/OfficeMenuPanel.cpp \
           src/Widgets/OfficeMenuItem.cpp \
           src/Widgets/Dialogs/OfficeWindowTitlebar.cpp \
           src/Widgets/OfficeMenuPinButton.cpp \
           src/Widgets/OfficeMenuPanelBar.cpp \
           src/Widgets/OfficeMenuEvent.cpp \
           src/Design/Office.cpp \
           src/Widgets/OfficeTextbox.cpp \
           src/Widgets/MenuItems/OfficeMenuTextboxItem.cpp \
           src/Widgets/OfficeLineEdit.cpp

################################################################################
## OUTPUT
##
################################################################################
include(platforms.pri)
message(Writing library to: $${PWD}/bin/$${kgl_path})

DESTDIR     = $${PWD}/bin/$${kgl_path}
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR     = $${OBJECTS_DIR}
RCC_DIR     = $${OBJECTS_DIR}
UI_DIR      = $${OBJECTS_DIR}
