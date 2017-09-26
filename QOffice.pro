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

###########################################################
# COMPILER SETTINGS
#
###########################################################
gcc {
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
             resources/qoffice_fonts.qrc

###########################################################
# HEADER FILES
#
###########################################################
HEADERS += include/QOffice/Config.hpp \
           include/QOffice/Exceptions/OfficePaletteException.hpp \
           include/QOffice/Exceptions/OfficeImageException.hpp \
           include/QOffice/Exceptions/OfficeAccentException.hpp \
           include/QOffice/Widgets/OfficeWidget.hpp \
           include/QOffice/Design/OfficeAccent.hpp \
           include/QOffice/Design/OfficePalette.hpp \
           include/QOffice/Design/OfficeImage.hpp \
           include/QOffice/Design/OfficeFont.hpp \
           include/QOffice/Exceptions/OfficeFontWeightException.hpp \
           include/QOffice/Widgets/Dialogs/OfficeWindow.hpp \
           include/QOffice/Widgets/Dialogs/OfficeWindowResizeArea.hpp \
           include/QOffice/Design/Office.hpp

###########################################################
# SOURCE FILES
#
###########################################################
SOURCES += src/Exceptions/OfficeAccentException.cpp \
           src/Exceptions/OfficePaletteException.cpp \
           src/Exceptions/OfficeImageException.cpp \
           src/Widgets/OfficeWidget.cpp \
           src/Design/OfficeAccent.cpp \
           src/Design/OfficePalette.cpp \
           src/Design/OfficeImage.cpp \
           src/Design/OfficeFont.cpp \
           src/Exceptions/OfficeFontWeightException.cpp \
    src/Widgets/Dialogs/OfficeWindowResizeArea.cpp \
    src/Widgets/Dialogs/OfficeWindow.cpp

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
