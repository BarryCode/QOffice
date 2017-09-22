////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
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
#ifndef QOFFICE_EXCEPTIONS_OFFICEIMAGEEXCEPTION_HPP
#define QOFFICE_EXCEPTIONS_OFFICEIMAGEEXCEPTION_HPP

#include <QOffice/Config.hpp>
#include <exception>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeImageException
/// \brief This exception is thrown when an invalid image was provided.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 22, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_CORE_API OfficeImageException : std::exception
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of the OfficeImageException class. Instead
    /// of manually passing the function name to \p func, the OffCurrentFunc
    /// macro should be used to retrieve function and namespace dynamically.
    ///
    /// \param[in] func The name of the function that threw the exception.
    ///
    /// \throw This function does not throw exceptions.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeImageException(const QString& func) QOFFICE_NOEXCEPT;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the cause of this exception.
    ///
    /// \return The cause as C-string.
    ///
    /// \threadsafe This function is thread safe.
    /// \throw This function does not throw exceptions.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const char* what() const noexcept override;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    //
    ////////////////////////////////////////////////////////////////////////////
    std::string m_reason; ///< Holds the exception message, ready for use.
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeImageException
/// \ingroup Core
///
/// This exception is thrown when an invalid QImage was provided.
/// Always make sure that your QImage is not null (QImage::isNull).
///
/// \code
/// try
/// {
///     OfficeImage::convertToGrayscale(QImage());
/// }
/// catch (const OfficeImageException& e)
/// {
///     // Print the exception.
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
