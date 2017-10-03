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

#include <QOffice/Widgets/OfficeTooltip.hpp>
#include <QOffice/Widgets/OfficeWindowMenu.hpp>
#include <QOffice/Widgets/Dialogs/OfficeWindow.hpp>
#include <QOffice/Widgets/Dialogs/OfficeWindowTitlebar.hpp>

#include <QHBoxLayout>
#include <QtEvents>

OffAnonymous(QOFFICE_CONSTEXPR int c_menuHeight = 28)

OfficeWindowMenu::OfficeWindowMenu(priv::Titlebar* parent, Type type)
    : QWidget(parent),
      m_type(type)
    , m_parent(parent->m_window)
    , m_tooltip(new OfficeTooltip)
{
    setLayout(new QHBoxLayout(this));

    // Prepare the timer that shows/hides the tooltip on demand.
    m_tooltip->setHelpEnabled(true);
    m_tooltip->setHelpText(tr("Press F1 to receive help."));
    m_tooltip->setWaitPeriod(1000);

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
        layout()->setContentsMargins(10,0,10,0);

        // We do not want the item texts to be too close to one another.
        layout()->setSpacing(10);
    }
    else if (type == QuickMenu)
    {
        layout()->setContentsMargins(0,0,10,0);
    }

    // The menu's height will always be a fixed height (c_menuHeight). It may
    // be subject to change in the future. The menu should occupy the smallest
    // space possible horizontally, as the titlebar is cramped.
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setFixedHeight(c_menuHeight);
    setMouseTracking(true);
}

OfficeWindowMenu::~OfficeWindowMenu()
{
    delete m_tooltip;
}

bool OfficeWindowMenu::addLabelItem(int id, const QString& t, const QString& tt)
{
    if (m_type != LabelMenu)
    {
        return false;
    }

    return addItem(id, t, QPixmap(), tt);
}

bool OfficeWindowMenu::addQuickItem(int id, const QPixmap& i, const QString &tt)
{
    if (m_type != QuickMenu)
    {
        return false;
    }

    return addItem(id, QString(), i, tt);
}

bool OfficeWindowMenu::removeItem(int id)
{
    for (auto* item : m_items)
    {
        if (item->id() == id)
        {
            m_items.removeOne(item);
            layout()->removeWidget(item);

            delete item;
            return true;
        }
    }

    return false;
}

void OfficeWindowMenu::leaveEvent(QEvent*)
{
    m_tooltip->hide();
}

void OfficeWindowMenu::onItemClicked(priv::WindowItem* item)
{
    emit itemClicked(item->id());
}

void OfficeWindowMenu::onHelpRequested()
{
    emit helpRequested(m_tooltip->property("item").toInt());
}

void OfficeWindowMenu::onShowTooltip(priv::WindowItem* item)
{
    QPoint pos = mapToGlobal(QPoint(item->width(), item->height()));
    QSize size(300, 200);

    m_tooltip->setProperty("item", item->id());
    m_tooltip->setGeometry(QRect(pos, size));
    m_tooltip->setTitle(item->text());
    m_tooltip->setText(item->tooltipText());
    m_tooltip->show();
}

void OfficeWindowMenu::onHideTooltip(priv::WindowItem*)
{
    if (!m_tooltip->isVisible() || !m_tooltip->geometry().contains(QCursor::pos()))
    {
        m_tooltip->hide();
    }
}

bool OfficeWindowMenu::addItem(
    const int id,
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

    auto* item = new priv::WindowItem(this, m_type, id, text, img, tooltip);

    m_items.append(item);
    layout()->addWidget(item);

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
        layout()->itemAt(layout()->indexOf(item))->setAlignment(Qt::AlignTop);
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
