#
#  Lesser General Public License 3.0
#  Copyright (C) 2016-2018 Nicolas Kogler
#
#  QOffice: The office framework for Qt
#

set(BASICWINDOW_SOURCES
    main.cpp
)

add_executable(BasicWindow ${BASICWINDOW_SOURCES})
target_compile_features(BasicWindow PRIVATE ${QOFFICE_COMPILE_FEATURES})
target_link_libraries(BasicWindow
    ${QOFFICE_LIBRARY}-design
    ${QOFFICE_LIBRARY}-widget
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
