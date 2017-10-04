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

#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Widgets/OfficeMenuEvent.hpp>
#include <QOffice/Widgets/OfficeMenuHeader.hpp>
#include <QOffice/Widgets/OfficeMenuItem.hpp>
#include <QOffice/Widgets/OfficeMenuPanel.hpp>

int OfficeMenuItem::id() const
{
    return m_id;
}

OfficeMenuPanel* OfficeMenuItem::panel() const
{
    return m_parent;
}

void OfficeMenuItem::setId(int id)
{
    m_id = id;
}

void OfficeMenuItem::setPanel(OfficeMenuPanel* panel)
{
    m_parent = panel;
}

void OfficeMenuItem::emitItemEvent(OfficeMenuEvent* event)
{
    // Climbs up the hierarchy latter and forwards the event.
    if (m_parent != nullptr &&
        m_parent->header() != nullptr &&
        m_parent->header()->menu() != nullptr)
    {
        OfficeMenu* menu = m_parent->header()->menu();

        if (event->type() == OfficeMenuEvent::TextChanged)
        {
            emit menu->textChangedEvent(
                static_cast<OfficeMenuTextChangedEvent*>(event));
        }
        else if (event->type() == OfficeMenuEvent::ButtonClicked)
        {
            emit menu->buttonClickedEvent(
                static_cast<OfficeMenuButtonClickedEvent*>(event));
        }
        else if (event->type() == OfficeMenuEvent::ComboboxItemChanged ||
                 event->type() == OfficeMenuEvent::DropdownItemChanged)
        {
            emit menu->itemChangedEvent(
                static_cast<OfficeMenuItemChangedEvent*>(event));
        }
        else
        {
            emit m_parent->header()->menu()->itemEvent(event);
        }
    }
}
