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

#include <QOffice/Design/OfficeAccent.hpp>
#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Widgets/OfficeMenuHeader.hpp>
#include <QOffice/Widgets/OfficeMenuPanel.hpp>

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>

OffAnonymous(QOFFICE_CONSTEXPR int c_headerHeight = 30)
OffAnonymous(QOFFICE_CONSTEXPR int c_panelHeight  = 90)
OffAnonymous(QOFFICE_CONSTEXPR int c_textPadding  = 30)

OfficeMenuHeader::OfficeMenuHeader(OfficeMenu* parent)
    : QWidget(parent)
    , m_parent(parent)
    , m_panelBar(new QWidget(parent))
    , m_text("Header")
    , m_isHovered(false)
    , m_isSelected(false)
    , m_id(-1)
{
    m_panelBar->hide();
    m_panelBar->setLayout(new QHBoxLayout(m_panelBar));
    m_panelBar->setFixedHeight(c_panelHeight);

    barLayout()->setSpacing(4);
    barLayout()->setContentsMargins(0,0,0,0);
}

int OfficeMenuHeader::id() const
{
    return m_id;
}

bool OfficeMenuHeader::isSelected() const
{
    return m_isSelected;
}

const QString& OfficeMenuHeader::text() const
{
    return m_text;
}

OfficeMenu* OfficeMenuHeader::menu() const
{
    return m_parent;
}

OfficeMenuPanel* OfficeMenuHeader::panelById(int id) const
{
    for (auto* panel : m_panels)
    {
        if (panel->id() == id)
            return panel;
    }

    return nullptr;
}

OfficeMenuPanel* OfficeMenuHeader::operator [](int id) const
{
    return panelById(id);
}

void OfficeMenuHeader::setId(int id)
{
    m_id = id;
}

void OfficeMenuHeader::setText(const QString& text)
{
    m_text = text;
}

OfficeMenuPanel* OfficeMenuHeader::appendPanel(int id, const QString& text)
{
    return insertPanel(-1, id, text);
}

OfficeMenuPanel* OfficeMenuHeader::insertPanel(int pos, int id, const QString& text)
{
    // Ensures that no item with the given ID already exists. We need to have
    // unique IDs, otherwise we are not able to safely track item events.
    if (panelById(id) != nullptr)
    {
        return nullptr;
    }

    // Ensures that the given position is in range of the item list.
    if (pos < 0 || pos >= m_panels.size())
    {
        pos = m_panels.size();
    }

    auto* panel = new OfficeMenuPanel(m_panelBar, this);
    panel->setText(text);
    panel->setId(id);
    panel->show();

    m_panels.insert(pos, panel);
    barLayout()->insertWidget(pos, panel, 0);

    return panel;
}

bool OfficeMenuHeader::removePanel(int id)
{
    auto* panel = panelById(id);
    if (panel != nullptr)
    {
        m_panels.removeOne(panel);
        barLayout()->removeWidget(panel);

        delete panel;
    }

    return panel != nullptr;
}

QSize OfficeMenuHeader::sizeHint() const
{
    return QSize(fontMetrics().width(m_text) + c_textPadding, c_headerHeight);
}

void OfficeMenuHeader::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    const QColor& colorAccent = OfficeAccent::color(m_parent->accent());
    const QColor& colorLight = OfficeAccent::lightColor(m_parent->accent());
    const QColor& colorBackg = OfficePalette::color(OfficePalette::Background);
    const QRect background(0, 0, width(), c_headerHeight);

    // Background
    if (m_isSelected)
    {
        painter.fillRect(background, colorBackg);
        painter.setPen(colorAccent);
    }
    else if (m_isHovered)
    {
        painter.fillRect(background, colorLight);
        painter.setPen(colorBackg);
    }
    else
    {
        painter.fillRect(background, colorAccent);
        painter.setPen(colorBackg);
    }

    // Text
    painter.drawText(background, m_text, QTextOption(Qt::AlignCenter));
}

void OfficeMenuHeader::enterEvent(QEvent* event)
{
    m_isHovered = true;
    update();

    QWidget::enterEvent(event);
}

void OfficeMenuHeader::leaveEvent(QEvent* event)
{
    m_isHovered = false;
    update();

    QWidget::leaveEvent(event);
}

void OfficeMenuHeader::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_parent->expand(this);
    }
}

QHBoxLayout* OfficeMenuHeader::barLayout()
{
    return static_cast<QHBoxLayout*>(m_panelBar->layout());
}

void OfficeMenuHeader::expand()
{
    m_panelBar->show();
    m_panelBar->move(0, c_headerHeight);
    m_isSelected = true;
    update();

    emit headerExpanded();
}

void OfficeMenuHeader::collapse()
{
    m_panelBar->hide();
    m_isSelected = false;
    update();

    emit headerCollapsed();
}
