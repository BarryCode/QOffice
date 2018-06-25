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
#ifndef QOFFICE_DESIGN_OFFICEACCENT_HPP
#define QOFFICE_DESIGN_OFFICEACCENT_HPP

#include <QOffice/Design/Office.hpp>
#include <QColor>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeAccent
/// \ingroup Design
///
/// \brief Holds all the color values of the available accents.
/// \author Nicolas Kogler
/// \date September 23, 2017
///
/// Every QOffice-widget should use the functionality of this class in their
/// QWidget::paintEvent method. Use as follows:
///
/// \code
/// void paintEvent(QPaintEvent*)
/// {
///     QPainter painter(this);
///     const QColor& accentColor = OfficeAccent::color(accent());
///     painter.fillRect(rect(), accentColor);
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_DESIGN_API OfficeAccent
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the color associated with the specified accent.
    ///
    /// \param[in] accent The accent name of the color to get.
    /// \return The color associated with the given accent.
    ///
    /// \sa OfficeAccent::setCustomColor
    /// \threadsafe Only call this function on the GUI thread.
    /// \throws OfficeAccentException
    ///
    ////////////////////////////////////////////////////////////////////////////
    static const QColor& color(Office::Accent accent);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves a color being a bit lighter than the color associated with the
    /// specified accent.
    ///
    /// \param[in] accent The accent name of the color to get.
    /// \return A color lighter than the one associated with the given accent.
    ///
    /// \sa OfficeAccent::veryLightColor
    /// \threadsafe Only call this function on the GUI thread.
    /// \throws OfficeAccentException
    ///
    ////////////////////////////////////////////////////////////////////////////
    static const QColor lightColor(Office::Accent accent);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves a color being much lighter than the color associated with the
    /// specified accent.
    ///
    /// \param[in] accent The accent name of the color to get.
    /// \return A color much lighter than the one associated with the given accent.
    ///
    /// \sa OfficeAccent::lightColor
    /// \threadsafe Only call this function on the GUI thread.
    /// \throws OfficeAccentException
    ///
    ////////////////////////////////////////////////////////////////////////////
    static const QColor veryLightColor(Office::Accent accent);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves a color being a bit darker than the color associated with the
    /// specified accent.
    ///
    /// \param[in] accent The accent name of the color to get.
    /// \return A color darker than the one associated with the given accent.
    ///
    /// \sa OfficeAccent::veryDarkColor
    /// \threadsafe Only call this function on the GUI thread.
    /// \throws OfficeAccentException
    ///
    ////////////////////////////////////////////////////////////////////////////
    static const QColor darkColor(Office::Accent accent);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves a color being much darker than the color associated with the
    /// specified accent.
    ///
    /// \param[in] accent The accent name of the color to get.
    /// \return A color much darker than the one associated with the given accent.
    ///
    /// \sa OfficeAccent::darkColor
    /// \threadsafe Only call this function on the GUI thread.
    /// \throws OfficeAccentException
    ///
    ////////////////////////////////////////////////////////////////////////////
    static const QColor veryDarkColor(Office::Accent accent);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the given accent is a valid accent within QOffice.
    ///
    /// \param[in] accent The accent to check.
    /// \return True if the given \p accent is valid, false otherwise.
    ///
    /// \threadsafe This function is thread-safe.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isValid(Office::Accent accent);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the color of the custom accent.
    ///
    /// \param[in] color The color to specify for the custom accent.
    ///
    /// \sa OfficeAccent::color
    /// \threadsafe Only call this function on the GUI thread
    ///
    ////////////////////////////////////////////////////////////////////////////
    static void setCustomColor(const QColor& color);
};

#endif
