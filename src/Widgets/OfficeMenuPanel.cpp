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

#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeMenuItem.hpp>
#include <QOffice/Widgets/OfficeMenuPanel.hpp>
#include <QOffice/Widgets/OfficeMenuHeader.hpp>

#include <QGridLayout>
#include <QPainter>
#include <QTextOption>

OfficeMenuPanel::OfficeMenuPanel(QWidget* panelBar, OfficeMenuHeader* header)
    : QWidget(panelBar)
    , m_layout(new QGridLayout(this))
    , m_parent(header)
    , m_text("Panel")
    , m_id(-1)
{
    setLayout(m_layout);
}

int OfficeMenuPanel::id() const
{
    return m_id;
}

OfficeMenuHeader* OfficeMenuPanel::header() const
{
    return m_parent;
}

const QString& OfficeMenuPanel::text() const
{
    return m_text;
}

OfficeMenuItem* OfficeMenuPanel::itemById(int id) const
{
    for (auto* item : m_items)
    {
        if (item->id() == id)
            return item;
    }

    return nullptr;
}

OfficeMenuItem* OfficeMenuPanel::operator [](int id) const
{
    return itemById(id);
}

void OfficeMenuPanel::setId(int id)
{
    m_id = id;
}

void OfficeMenuPanel::setText(const QString& text)
{
    m_text = text;
}

bool OfficeMenuPanel::insertItem(int id, OfficeMenuItem* item, int row, int column)
{
    if (item->widget() == nullptr || itemById(id) != nullptr)
    {
        return false;
    }

    item->setId(id);
    item->widget()->show();

    m_items.append(item);
    m_layout->addWidget(item->widget(), row, column);

    return true;
}

bool OfficeMenuPanel::insertItem(
    int id, OfficeMenuItem* item,
    int row, int column,
    int rowSpan, int columnSpan
    )
{
    if (item->widget() == nullptr || itemById(id) != nullptr)
    {
        return false;
    }

    item->setId(id);
    item->widget()->show();

    m_items.append(item);
    m_layout->addWidget(item->widget(), row, column, rowSpan, columnSpan);

    return true;
}

bool OfficeMenuPanel::removeItem(int id)
{
    auto* item = itemById(id);
    if (item != nullptr)
    {
        m_items.removeOne(item);

        if (item->widget() != nullptr)
            m_layout->removeWidget(item->widget());

        delete item;
    }

    return item != nullptr;
}

void OfficeMenuPanel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    const QRect textRect = rect().adjusted(0,0,0,-4);
    const QPoint separatorTop = rect().topRight() + QPoint(0,4);
    const QPoint separatorBtm = rect().bottomRight() - QPoint(0,4);
    const QTextOption textOption(Qt::AlignHCenter | Qt::AlignBottom);
    const QColor& colorSeparator = OfficePalette::color(OfficePalette::MenuSeparator);
    const QColor& colorForeground = OfficePalette::color(OfficePalette::Foreground);

    // Text
    painter.setPen(colorForeground);
    painter.drawText(textRect, m_text, textOption);

    // Separator
    painter.setPen(colorSeparator);
    painter.drawLine(separatorTop, separatorBtm);
}
