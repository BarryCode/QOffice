////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
//
// This file is part of the Widget module.
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

#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Widgets/OfficeMenuPanelBar.hpp>

priv::PanelBar::PanelBar(OfficeMenu* parent)
    : QWidget(parent)
{
    QString css = "QWidget { border-bottom: 1px solid %0; }";
    QString color = Office::colorToHex(
                OfficePalette::color(
                OfficePalette::MenuSeparator
                ));

    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    setStyleSheet(css.arg(color));
}

QSize priv::PanelBar::sizeHint() const
{
    return QSize(parentWidget()->width(), 90);
}
