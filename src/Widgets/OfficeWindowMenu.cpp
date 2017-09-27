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

#include <QOffice/Widgets/OfficeWindowMenu.hpp>
#include <QOffice/Widgets/Dialogs/OfficeWindow.hpp>

#include <QHBoxLayout>
#include <QtEvents>

OffAnonymous(QOFFICE_CONSTEXPR int c_menuHeight = 28)

OfficeWindowMenu::OfficeWindowMenu(OfficeWindow* parent, Type type)
    : QWidget(parent),
      m_type(type)
    , m_parent(parent)
    , m_layout(new QHBoxLayout(this))
{
    if (type == LabelMenu)
    {
        // We do not want the item texts to be too close to one another.
        m_layout->setSpacing(10);
    }

    // In order to not have menu, drag rectangle and button rectangles too close
    // to each other, add a small horizontal margin.
    m_layout->setContentsMargins(10,0,10,0);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setFixedHeight(c_menuHeight);
    setLayout(m_layout);
    setMouseTracking(true);
}

bool OfficeWindowMenu::addItem(
    const QString& text,
    const QPixmap& img,
    const QString& tooltip
    )
{
    // Determines whether the text already exists. The text needs to be unique
    // because signals emitted by this class rely on the item's text, not index.
    // Even for OfficeWindowMenu::QuickMenu, a text should be specified in order
    // to receive signals for that item.
    for (auto* item : m_items)
    {
        if (item->text() == text)
            return false;
    }

    auto* item = new priv::WindowItem(this, m_type, text, img, tooltip);

    m_items.append(item);
    m_layout->addWidget(item);

    item->show();
    adjustSize();

    // Make the menu receive signals from the new item.
    QObject::connect(
        item,
        &priv::WindowItem::clicked,
        this,
        &OfficeWindowMenu::onItemClicked
        );

    // TODO: Tooltip

    return true;
}

bool OfficeWindowMenu::removeItem(const QString& text)
{
    for (auto* item : m_items)
    {
        if (item->text() == text)
        {
            m_items.removeOne(item);
            m_layout->removeWidget(item);

            delete item;
            return true;
        }
    }

    return false;
}

void OfficeWindowMenu::onItemClicked(priv::WindowItem* item)
{
    emit menuItemClicked(item->text());
}

void OfficeWindowMenu::onHelpRequested(priv::WindowItem* item)
{
    emit helpRequested(item->text());
}
