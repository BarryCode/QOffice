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

#include <QOffice/Design/OfficeAccent.hpp>
#include <QOffice/Widgets/OfficeWidget.hpp>

OfficeWidget::OfficeWidget()
    : m_accent(Office::BlueAccent)
{
}

Office::Accent OfficeWidget::accent() const
{
    return m_accent;
}

void OfficeWidget::setAccent(Office::Accent accent)
{
    // In order to avoid exceptions during QWidget::paintEvent, always ensure
    // that a valid accent is available anytime, anywhere.
    if (OfficeAccent::isValid(accent))
    {
        m_accent = accent;
        accentUpdateEvent();
    }
}

void OfficeWidget::accentUpdateEvent()
{
}
