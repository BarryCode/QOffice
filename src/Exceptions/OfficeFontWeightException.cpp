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


#include <QOffice/Exceptions/OfficeFontweightException.hpp>

OfficeFontweightException::OfficeFontweightException(
    const QString& func,
    const int value
    ) QOFFICE_NOEXCEPT : std::exception()
{
    m_reason = std::string(
        std::string("@@@") +
        std::string("    QOffice reported an exception\n") +
        std::string("    type: OfficeFontweightException\n") +
        std::string("    func: ") + func.toStdString() + "\n" +
        std::string("    The value \"") + std::to_string(value) +
        std::string("\" is not a valid font weight.\n") +
        std::string("@@@")
        );
}

const char* OfficeFontweightException::what() const QOFFICE_NOEXCEPT
{
    return m_reason.c_str();
}
