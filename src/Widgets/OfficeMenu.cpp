/*
 *  QOffice: Office UI framework for Qt
 *  Copyright (C) 2016-2017 Nicolas Kogler
 *
 *  This file is part of QOffice.
 *
 *  QOffice is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QOffice is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with QOffice. If not, see <http://www.gnu.org/licenses/>.
 *
 */


// QOffice headers
#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Design/OfficeAccents.hpp>

// Qt headers


QOFFICE_USING_NAMESPACE


OfficeMenu::OfficeMenu(QWidget* parent)
    : QMenuBar(parent)
{

}


OfficeMenu::~OfficeMenu()
{
}


IOfficeWidget::Accent
OfficeMenu::accent() const
{
    return m_Accent;
}


void
OfficeMenu::setAccent(Accent accent)
{
    m_Accent = accent;
    update();
}
