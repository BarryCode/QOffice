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

#include <QBoxLayout>
#include <QMouseEvent>
#include <QPainter>

OffAnonymous(QOFFICE_CONSTEXPR int c_collapsedHeight = 30)
OffAnonymous(QOFFICE_CONSTEXPR int c_expandedHeight = 120)
OffAnonymous(QOFFICE_CONSTEXPR Qt::Alignment c_flags = Qt::AlignLeft | Qt::AlignTop | Qt::AlignHCenter)

OfficeMenu::OfficeMenu(QWidget* parent)
    : QWidget(parent)
    , m_headerLayout(new QHBoxLayout)
    , m_panelLayout(new QHBoxLayout)
    , m_isExpanded(false)
    , m_isPinned(false)
{
    QVBoxLayout* container = new QVBoxLayout(this);
    container->setContentsMargins(0,0,0,0);
    container->setMargin(0);
    container->setSpacing(0);
    container->addLayout(m_headerLayout);
    container->addLayout(m_panelLayout);

    m_headerLayout->setContentsMargins(0,0,0,0);
    m_headerLayout->setMargin(0);
    m_headerLayout->setSpacing(2);
    m_headerLayout->addStretch(1);

    m_panelLayout->setContentsMargins(0,0,0,0);
    m_panelLayout->setMargin(0);
    m_panelLayout->setSpacing(2);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setLayout(container);
}

OfficeMenuHeader* OfficeMenu::headerById(int id) const
{
    for (auto* header : m_headers)
    {
        if (header->id() == id)
            return header;
    }

    return nullptr;
}

OfficeMenuHeader* OfficeMenu::operator [](int id) const
{
    return headerById(id);
}

bool OfficeMenu::isPinned() const
{
    return m_isPinned;
}

void OfficeMenu::setPinned(bool pinned)
{
    m_isPinned = pinned;
    setFocus();

    if (!pinned)
    {
        collapse();
    }
}

OfficeMenuHeader* OfficeMenu::appendHeader(int id, const QString& text)
{
    return insertHeader(-1, id, text);
}

OfficeMenuHeader* OfficeMenu::insertHeader(int pos, int id, const QString& text)
{
    // Ensures that no item with the given ID already exists. We need to have
    // unique IDs, otherwise we are not able to safely track item events.
    if (headerById(id) != nullptr)
    {
        return nullptr;
    }

    // Ensures that the given position is in range of the item list.
    if (pos < 0 || pos >= m_headers.size())
    {
        pos = m_headers.size();
    }

    OfficeMenuHeader* header = new OfficeMenuHeader(this);
    header->setText(text);
    header->setId(id);
    header->show();

    m_headers.insert(pos, header);
    m_headerLayout->insertWidget(pos, header, 0, c_flags);

    return header;
}

bool OfficeMenu::removeHeader(int id)
{
    auto* header = headerById(id);
    if (header != nullptr)
    {
        m_headers.removeOne(header);
        m_headerLayout->removeWidget(header);

        delete header;
    }

    return header != nullptr;
}

void OfficeMenu::expand(OfficeMenuHeader* toExpand)
{
    if (toExpand != nullptr)
    {
        // Collapses any other open headers.
        for (auto* header : m_headers)
        {
            if (header != toExpand)
                header->collapse(m_panelLayout, false);
        }

        // Increases the height of the menu. Why? Because children, that are
        // located outside the parent's bounds, are invisible. In this case, the
        // panel bar at the bottom of the headers would not be visible. In order
        // for it to be visible, we need to resize the topmost parent.
        resize(width(), c_expandedHeight);
        setFixedHeight(c_expandedHeight);
        setFocus();

        toExpand->expand(m_panelLayout, m_isExpanded);

        m_isExpanded = true;
    }
}

void OfficeMenu::collapse()
{
    // Collapses all headers.
    for (auto* header : m_headers)
    {
        header->collapse(m_panelLayout, m_isExpanded);
    }

    m_isExpanded = false;
}

QSize OfficeMenu::sizeHint() const
{
    return QSize(parentWidget()->width(), height());
}

void OfficeMenu::accentUpdateEvent()
{
    update();
}

void OfficeMenu::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect background(0, 0, width(), c_collapsedHeight);

    painter.fillRect(background, OfficeAccent::color(accent()));
}

void OfficeMenu::focusOutEvent(QFocusEvent* event)
{
    if (!m_isPinned)
    {
        // If the ribbon is not pinned, it should collapse when we focus a
        // different widget with our mouse.
        collapse();
    }

    QWidget::focusOutEvent(event);
}
