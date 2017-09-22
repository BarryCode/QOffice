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
#ifndef QOFFICE_EXCEPTIONS_OFFICEACCENTEXCEPTION_HPP
#define QOFFICE_EXCEPTIONS_OFFICEACCENTEXCEPTION_HPP

#include <QOffice/Config.hpp>
#include <exception>

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeAccentException
/// \brief This exception is thrown when an invalid accent was provided.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 22, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_CORE_API OfficeAccentException : std::exception
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of the OfficeAccentException class. Instead
    /// of manually passing the function name to \p func, the OffCurrentFunc
    /// macro should be used to retrieve function and namespace dynamically.
    ///
    /// \param[in] func The name of the function that threw the exception.
    /// \param[in] value The value that caused the exception.
    ///
    /// \throw This function does not throw exceptions.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeAccentException(const QString& func, const uint value) QOFFICE_NOEXCEPT;

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
/// \class OfficeAccentException
/// \ingroup Core
///
/// This exception is thrown when an invalid accent enum value was provided.
/// Always make sure that your value is between 0 and IOfficeWidget::MaxAccent.
///
/// \code
/// try
/// {
///     // This code will never actually throw, since RedAccent is valid.
///     OfficeAccent::get(IOfficeWidget::RedAccent);
/// }
/// catch (const OfficeAccentException& e)
/// {
///     // Print the exception.
/// }
/// \endcode
///
/// It is also possible to have a custom accent color that is definable
/// through the user of the QOffice-application.
///
/// \code
/// OfficeAccent::set(QColor(...));
///
/// m_officeWindow->setAccent(IOfficeWidget::CustomAccent);
/// \endcode
///
/// The call to IOfficeWidget::setAccent will populate all child widgets with
/// the custom accent color. In this case, the entire window will be colored.
///
////////////////////////////////////////////////////////////////////////////////
