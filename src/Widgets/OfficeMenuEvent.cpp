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

#include <QOffice/Widgets/OfficeMenuEvent.hpp>

OfficeMenuEvent::OfficeMenuEvent(Type type, int id)
    : m_type(type)
    , m_id(id)
{
}

OfficeMenuEvent::Type OfficeMenuEvent::type() const
{
    return m_type;
}

int OfficeMenuEvent::id() const
{
    return m_id;
}

bool OfficeMenuEvent::isAccepted() const
{
    return m_accepted;
}

void OfficeMenuEvent::accept()
{
    m_accepted = true;
}

void OfficeMenuEvent::ignore()
{
    m_accepted = false;
}

OfficeMenuTextChangedEvent::OfficeMenuTextChangedEvent(
    OfficeMenuEvent::Type type, int id,
    const QString &oldT, const QString &newT
    ) : OfficeMenuEvent(type, id)
      , m_oldText(oldT)
      , m_newText(newT)
{
}

QString OfficeMenuTextChangedEvent::previousText() const
{
    return m_oldText;
}

QString OfficeMenuTextChangedEvent::currentText() const
{
    return m_newText;
}

OfficeMenuButtonClickedEvent::OfficeMenuButtonClickedEvent(
    OfficeMenuEvent::Type type, int id,
    bool toggable, bool toggled
    ) : OfficeMenuEvent(type, id)
      , m_isToggable(toggable)
      , m_isToggled(toggled)
{
}

bool OfficeMenuButtonClickedEvent::isToggable() const
{
    return m_isToggable;
}

bool OfficeMenuButtonClickedEvent::isToggled() const
{
    return m_isToggled;
}

OfficeMenuItemChangedEvent::OfficeMenuItemChangedEvent(
    OfficeMenuEvent::Type type, int id, int index,
    const QString &text, const QVariant &value
    ) : OfficeMenuEvent(type, id)
      , m_index(index)
      , m_text(text)
      , m_value(value)
{
}

int OfficeMenuItemChangedEvent::index() const
{
    return m_index;
}

QString OfficeMenuItemChangedEvent::text() const
{
    return m_text;
}

QVariant OfficeMenuItemChangedEvent::value() const
{
    return m_value;
}
