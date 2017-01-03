/*
 *  QOffice: Office UI framework for Qt
 *  Copyright (C) 2016-2017 Nicolas Kogler
 *
 *  This file is part of QOffice.
 *
 *  QOffice is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QOffice is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with QOffice. If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef QOFFICE_OFFICEMENUENUMS_HPP
#define QOFFICE_OFFICEMENUENUMS_HPP


// QOffice headers
#include <QOffice/Config.hpp>


QOFFICE_BEGIN_NAMESPACE


enum class PanelLayoutType
{
    Vertical,
    Horizontal,
    Form,
    Grid
};

/**
 * Holds all the possible states of a menu item button.
 *
 * @enum MenuButtonState
 * @author Nicolas Kogler
 * @date January 2nd, 2016
 *
 */
enum class MenuButtonState
{
    None,
    Hovered,
    Pressed
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEMENUENUMS_HPP
