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

#include <QOffice/Widgets/OfficeTooltip.hpp>
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
    , m_tooltip(new OfficeTooltip())
    , m_timer(new QTimer(this))
{
    // Prepare the timer that shows/hides the tooltip on demand.
    m_timer->setInterval(1000);
    m_tooltip->setHelpEnabled(true);
    m_tooltip->setHelpText(tr("Press F1 to receive help."));

    QObject::connect(
        m_timer,
        &QTimer::timeout,
        this,
        &OfficeWindowMenu::showTooltip
        );

    QObject::connect(
        m_tooltip,
        &OfficeTooltip::helpRequested,
        this,
        &OfficeWindowMenu::onHelpRequested
        );

    // In order to not have menu, drag rectangle and button rectangles too close
    // to each other, add a small horizontal margin.
    if (type == LabelMenu)
    {
        m_layout->setContentsMargins(10,0,10,0);

        // We do not want the item texts to be too close to one another.
        m_layout->setSpacing(10);
    }
    else if (type == QuickMenu)
    {
        m_layout->setContentsMargins(0,0,10,0);
    }

    // The menu's height will always be a fixed height (c_menuHeight). It may
    // be subject to change in the future. The menu should occupy the smallest
    // space possible horizontally, as the titlebar is cramped.
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

    // When a QWidget is already shown, adding a child to it does not
    // automatically show the child - we have to do it manually. The layout
    // also does not react immediately to changes, therefore we need to adjust
    // the menu's size forcefully.
    item->show();
    adjustSize();

    if (m_type == QuickMenu)
    {
        // For quick menus, we need the item to be aligned to top, because the
        // background color (it changes on hover and press) would be totally
        // misplaced otherwise.
        m_layout->itemAt(m_layout->indexOf(item))->setAlignment(Qt::AlignTop);
    }

    // Make the menu receive signals from the new item.
    QObject::connect(
        item,
        &priv::WindowItem::clicked,
        this,
        &OfficeWindowMenu::onItemClicked
        );

    QObject::connect(
        item,
        &priv::WindowItem::tooltipShowRequested,
        this,
        &OfficeWindowMenu::onShowTooltip
        );

    QObject::connect(
        item,
        &priv::WindowItem::tooltipHideRequested,
        this,
        &OfficeWindowMenu::onHideTooltip
        );

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
    hideTooltip();

    emit menuItemClicked(item->text());
}

void OfficeWindowMenu::onHelpRequested()
{
    emit helpRequested(m_tooltip->property("item").toString());
}

void OfficeWindowMenu::onShowTooltip(priv::WindowItem* item)
{
    m_tooltip->setProperty("item", item->text());
    m_trigger = item;
    m_timer->start();
}

void OfficeWindowMenu::onHideTooltip(priv::WindowItem*)
{
    if (!m_tooltip->geometry().contains(QCursor::pos()))
    {
        hideTooltip();
    }
}

void OfficeWindowMenu::showTooltip()
{
    QPoint pos = mapToGlobal(QPoint(m_trigger->width(), m_trigger->height()));
    QSize size(300, 200);

    m_tooltip->setGeometry(QRect(pos, size));
    m_tooltip->setTitle(m_trigger->text());
    m_tooltip->setText(m_trigger->tooltipText());
    m_tooltip->show();
    m_timer->stop();
}

void OfficeWindowMenu::hideTooltip()
{
    m_tooltip->hide();
    m_timer->stop();
}
