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
#include <QOffice/Widgets/OfficeMenuPanel.hpp>
#include <QOffice/Design/OfficePalette.hpp>

// Qt headers
#include <QPainter>
#include <QTextOption>


QOFFICE_USING_NAMESPACE


OfficeMenuPanel::OfficeMenuPanel(OfficeMenuTopItem* parent)
    : QWidget(parent)
    , m_ParentItem(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
}


OfficeMenuPanel::~OfficeMenuPanel()
{
}


const QString&
OfficeMenuPanel::text() const
{
    return m_Text;
}


const QRect&
OfficeMenuPanel::bounds() const
{
    return m_Bounds;
}


const QList<OfficeMenuItem*>&
OfficeMenuPanel::items() const
{
    return m_Items;
}


void
OfficeMenuPanel::setText(const QString& text)
{
    m_Text = text;
}


void
OfficeMenuPanel::addItem(OfficeMenuItem* item)
{
    m_Items.append(item);
}


void
OfficeMenuPanel::insertItem(int pos, OfficeMenuItem* item)
{
    m_Items.insert(pos, item);
}


void
OfficeMenuPanel::removeItem(int index)
{
    if (index >= 0 || index < m_Items.size())
        m_Items.removeAt(index);
}


void
OfficeMenuPanel::removeItem(OfficeMenuItem* item)
{
    removeItem(m_Items.indexOf(item));
}


void
OfficeMenuPanel::removeAll()
{
    for (auto* item : m_Items)
        removeItem(item);
}


void
OfficeMenuPanel::paintEvent(QPaintEvent*)
{
    // Gathers all the needed rects/points for rendering.
    QPainter painter(this);
    QRect rectText = m_Bounds.adjusted(0, 0, 0, -4);
    QPoint ptSepa1 = m_Bounds.topRight() + QPoint(0, 4);
    QPoint ptSepa2 = m_Bounds.bottomRight() - QPoint(0, 4);
    QTextOption opText(Qt::AlignHCenter | Qt::AlignBottom);

    // Gathers all the colors needed for rendering.
    const QColor& colorSepar = OfficePalette::get(OfficePalette::MenuSeparator);
    const QColor& colorForeg = OfficePalette::get(OfficePalette::Foreground);

    // Renders the text
    painter.setPen(colorForeg);
    painter.drawText(rectText, m_Text, opText);
    painter.setPen(colorSepar);
    painter.drawLine(ptSepa1, ptSepa2);
}
