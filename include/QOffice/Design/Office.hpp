////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the Core module.
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
#ifndef QOFFICE_DESIGN_OFFICE_HPP
#define QOFFICE_DESIGN_OFFICE_HPP

#include <QOffice/Config.hpp>

#include <QColor>
#include <QObject>

////////////////////////////////////////////////////////////////////////////////
/// \class Office
/// \brief Holds all enums visible to the Qt designer.
/// \author Nicolas Kogler
/// \date September 24, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_CORE_API Office : public QObject
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines all predefined accents and a custom one.
    /// \enum Accent
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum Accent
    {
        BlueAccent,
        RedAccent,
        GreenAccent,
        OrangeAccent,
        PurpleAccent,
        CustomAccent
    };

    ////////////////////////////////////////////////////////////////////////////
    /// Converts a QColor to a hexadecimal representation of that color.
    ///
    /// \param[in] color Color to convert.
    /// \return The hex as string. A hash character is prepended.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static QString colorToHex(const QColor& color);

    ////////////////////////////////////////////////////////////////////////////
    /// Loads the stylesheet with the given name from the QOffice resources.
    ///
    /// \param[in] name Name of the stylesheet, without extension.
    /// \return The contents of the stylesheet.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static QString loadStyleSheet(const QString& name);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the given string is exclusively ASCII.
    ///
    /// \param str The string to check.
    /// \return True if ASCII, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isAscii(const QString& str);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the given string is an integer.
    ///
    /// \param str The string to check.
    /// \return True if integer, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isInteger(const QString& str);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the given string is a floating-point number.
    ///
    /// \param str The string to check.
    /// \return True if decimal, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isDecimal(const QString& str);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the given string is a number, i.e. either of integer
    /// or floating-point.
    ///
    /// \param str The string to check.
    /// \return True if number, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isNumber(const QString& str);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the given string is a hexadecimal number.
    ///
    /// \param str The string to check.
    /// \return True if hex number, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isHexadecimal(const QString& str);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the given string is an octal number.
    ///
    /// \param str The string to check.
    /// \return True if octal, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isOctal(const QString& str);

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the given string is a binary number.
    ///
    /// \param str The string to check.
    /// \return True if binary, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    static bool isBinary(const QString& str);

private:

    Q_OBJECT
    Q_ENUM(Accent)
};

#endif
