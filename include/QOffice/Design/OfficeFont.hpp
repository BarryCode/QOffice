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
#ifndef QOFFICE_DESIGN_OFFICEFONT_HPP
#define QOFFICE_DESIGN_OFFICEFONT_HPP

#include <QOffice/Config.hpp>
#include <QMap>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeFont
/// \brief Caches all fonts used by the QOffice framework.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 23, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_DESIGN_API OfficeFont
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines all available font weights in QOffice.
    /// \enum Weight
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum Weight
    {
        Light,
        Regular,
        Semibold,
        Bold,
        TypeWriter,
        MaximumWeight
    };

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines optional-to-use point sizes for QOffice fonts.
    /// \enum Size
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum Size
    {
        Tiny        = 6,
        Small       = 8,
        Medium      = 10,
        Large       = 12,
        Heading4    = 12,
        Heading3    = 14,
        Heading2    = 18,
        Heading1    = 24,
        Title       = 30
    };

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the font with the given font size and weight. One can either
    /// specify a font size directly or use the OfficeFont::Size enum values.
    ///
    /// \param[in] weight The weight of the font.
    /// \param[in] size The size of the font, in Point.
    /// \return The font that corresponds to the given parameters.
    ///
    /// \threadsafe Access to the cache is synchronised.
    /// \throws OfficeFontWeightException
    ///
    ////////////////////////////////////////////////////////////////////////////
    static const QFont& font(Weight weight, float pointSize);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the given font weight is a valid value.
    ///
    /// \param weight The weight to check, as OfficeFont::Weight value.
    /// \return True if the specified weight is valid, false otherwise.
    ///
    /// \threadsafe This function is thread-safe.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isValid(int weight);

private:

    ////////////////////////////////////////////////////////////////////////////
    // Functions
    //
    ////////////////////////////////////////////////////////////////////////////
    static uint generateKey(int, float);
    static QString fontPath(int);
    static bool indexExists(int);
    static bool fontExists(int);
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeFont
/// \ingroup Design
///
/// Currently, QOffice makes use of the OpenSans font for normal UI typography
/// and the DroidSans font for widgets that need a typewriter font. In order to
/// receive different standardized font weights and sizes on the fly, one can
/// use this class.
///
/// In order to have maximum flexibility but reasonable performance at the same
/// time, QOffice caches the fonts in a QMap<uint,QFont>. Whenever a font is
/// requested, QOffice determines whether there already is a cache entry for it.
/// If not, a new QFont is constructed and populated into the map, while the key
/// is built using the font size and weight in a fancy way.
///
/// The front-end way to use it is as follows:
///
/// \code
/// void paintEvent(QPaintEvent*)
/// {
///     QPainter painter(this);
///     painter.setFont(OfficeFont::font(OfficeFont::Light, OfficeFont::Title));
///     painter.drawText(...);
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
