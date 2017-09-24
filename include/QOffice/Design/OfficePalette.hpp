////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the Design module.
//
// QOffice is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// QOffice is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with QOffice. If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef QOFFICE_DESIGN_OFFICEPALETTE_HPP
#define QOFFICE_DESIGN_OFFICEPALETTE_HPP

#include <QOffice/Config.hpp>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficePalette
/// \brief $Classdesc
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 23, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_DESIGN_API OfficePalette
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines all palette roles available in QOffice.
    /// \enum PaletteRole
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum PaletteRole
    {
        Background,
        Foreground,
        DisabledText,
        TooltipBorder,
        TooltipBackground,
        TooltipSeparator,
        TooltipText,
        TooltipHelpText,
        MenuSeparator,
        MenuItemHover,
        MenuItemPress,
        MaximumRole
    };

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the color associated to the specified palette role.
    ///
    /// \param[in] role The palette role of the color to retrieve.
    /// \return The color associated with the given palette role.
    ///
    /// \threadsafe This function is thread-safe.
    /// \throws OfficePaletteException
    ///
    ////////////////////////////////////////////////////////////////////////////
    static const QColor& color(PaletteRole role);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the specified palette role corresponds to a value.
    ///
    /// \param[in] role The palette role to check.
    /// \return True if the given \p role is valid, false otherwise.
    ///
    /// \threadsafe This function is thread-safe.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isValid(PaletteRole role);
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficePalette
/// \ingroup Design
///
/// Every QOffice-widget should use the functionality of this class in their
/// QWidget::paintEvent method. Use as follows:
///
/// \code
/// void paintEvent(QPaintEvent*)
/// {
///     QPainter painter(this);
///     const QColor& backColor = OfficePalette::color(OfficePalette::Background);
///     painter.fillRect(rect(), backColor);
/// }
/// \endcode
///
/// You must not use dynamic methods to retrieve a color from OfficePalette,
/// since OfficePalette::color throws exceptions. You want to avoid them at
/// all costs in QWidget::paintEvent (it might even crash the Qt Designer!).
///
/// If you really need to use a dynamic OfficePalette::PaletteRole, use the
/// OfficePalette::isValid function in order to validate the value beforehand.
///
////////////////////////////////////////////////////////////////////////////////
