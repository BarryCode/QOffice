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

private:

    Q_OBJECT
    Q_ENUM(Accent)
};

#endif
