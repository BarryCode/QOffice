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
#ifndef QOFFICE_EXCEPTIONS_OFFICEFONTWEIGHTEXCEPTION_HPP
#define QOFFICE_EXCEPTIONS_OFFICEFONTWEIGHTEXCEPTION_HPP

#include <QOffice/Config.hpp>
#include <exception>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeFontweightException
/// \brief This exception is thrown when an invalid accent was provided.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 22, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_CORE_API OfficeFontweightException : std::exception
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of the OfficeFontweightException class.
    /// Instead of manually passing the function name to \p func, the
    /// OffCurrentFunc macro should be used to retrieve function and namespace
    /// dynamically.
    ///
    /// \param[in] func The name of the function that threw the exception.
    /// \param[in] value The value that caused the exception.
    ///
    /// \throw This function does not throw exceptions.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeFontweightException(const QString& func, const int value) QOFFICE_NOEXCEPT;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the cause of this exception.
    ///
    /// \return The cause as C-string.
    ///
    /// \threadsafe This function is thread safe.
    /// \throw This function does not throw exceptions.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const char* what() const QOFFICE_NOEXCEPT override;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    std::string m_reason; ///< Holds the exception message, ready for use.
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeFontweightException
/// \ingroup Core
///
/// This exception is thrown when an invalid font weight enum value was provided.
/// Always make sure your value is between 0 and OfficeFont::MaximumWeight.
///
/// \code
/// try
/// {
///     // This code will never actually throw, since Light is valid.
///     OfficeFont::font(OfficeFont::Light, OfficeFont::Title);
/// }
/// catch (const OfficeFontweightException& e)
/// {
///     // Print the exception.
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
