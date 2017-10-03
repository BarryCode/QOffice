////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the $Module module.
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
#ifndef QOFFICE_WIDGETS_OFFICEMENUPANELBAR_HPP
#define QOFFICE_WIDGETS_OFFICEMENUPANELBAR_HPP

#include <QOffice/Config.hpp>
#include <QWidget>

class OfficeMenu;

namespace priv
{
class PanelBar : public QWidget
{
public:

    OffDefaultDtor(PanelBar)
    OffDisableCopy(PanelBar)
    OffDisableMove(PanelBar)

    PanelBar(OfficeMenu* parent);

    QSize sizeHint() const override;
};
}

#endif
