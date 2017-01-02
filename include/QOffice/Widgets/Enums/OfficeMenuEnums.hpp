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


#ifndef QOFFICE_OFFICEWINDOWENUMS_HPP
#define QOFFICE_OFFICEWINDOWENUMS_HPP


// QOffice headers
#include <QOffice/Config.hpp>


QOFFICE_BEGIN_NAMESPACE


/**
 * Holds the dirty regions for the menu top item.
 *
 * @enum TopItemDirtyRegion
 * @author Nicolas Kogler
 * @date January 2nd, 2016
 *
 */
enum class TopItemDirtyRegion
{
    None    = 0x0000,
    Text    = 0x0001,
    Bar     = 0x0002
};


Q_DECLARE_FLAGS(TI_DirtyRegions, TopItemDirtyRegion)

QOFFICE_END_NAMESPACE

Q_DECLARE_OPERATORS_FOR_FLAGS(off::TI_DirtyRegions)


#endif // QOFFICE_OFFICEWINDOWENUMS_HPP
