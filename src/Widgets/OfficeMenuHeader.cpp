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
#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeMenu.hpp>
#include <QOffice/Widgets/OfficeMenuHeader.hpp>
#include <QOffice/Widgets/OfficeMenuPanel.hpp>
#include <QOffice/Widgets/OfficeMenuPanelBar.hpp>
#include <QOffice/Widgets/OfficeMenuPinButton.hpp>

#include <QGraphicsEffect>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>

static QOFFICE_CONSTEXPR int c_headerHeight = 30;
static QOFFICE_CONSTEXPR int c_panelHeight  = 90;
static QOFFICE_CONSTEXPR int c_textPadding  = 30;
static QOFFICE_CONSTEXPR int c_space = 10000;

OfficeMenuHeader::OfficeMenuHeader(OfficeMenu* parent)
    : QWidget(parent)
    , m_parent(parent)
    , m_panelBar(new priv::PanelBar(parent))
    , m_panelLayout(new QHBoxLayout)
    , m_effectIn(new QGraphicsOpacityEffect(m_panelBar))
    , m_animationIn(new QPropertyAnimation(m_panelBar, "size"))
    , m_animationOut(new QPropertyAnimation(m_panelBar, "size"))
    , m_text("Header")
    , m_isHovered(false)
    , m_isSelected(false)
    , m_id(-1)
{
    // Split the layout up into two separate layouts. This is needed for the
    // sticky button to always stay on the bottom right.
    QHBoxLayout* stickyLayout = new QHBoxLayout;
    stickyLayout->setSpacing(2);
    stickyLayout->setMargin(0);
    stickyLayout->setContentsMargins(0,0,0,0);

    // Put the sticky button into a separate layout.
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin(0);
    buttonLayout->setContentsMargins(0,0,0,0);
    buttonLayout->setSizeConstraint(QLayout::SetFixedSize);
    buttonLayout->addWidget(new priv::PinButton(this), 0, Qt::AlignBottom);

    QSpacerItem* spacer = new QSpacerItem(
        c_space, 0,
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
        );

    m_panelBar->hide();
    m_panelBar->setGraphicsEffect(m_effectIn);
    m_panelBar->setAutoFillBackground(true);
    m_panelBar->setLayout(stickyLayout);
    m_panelBar->resize(0, 0);

    m_panelLayout->setSpacing(4);
    m_panelLayout->setContentsMargins(0,0,0,0);
    m_panelLayout->setSizeConstraint(QLayout::SetMaximumSize);

    stickyLayout->addLayout(m_panelLayout);
    stickyLayout->addSpacerItem(spacer);
    stickyLayout->addLayout(buttonLayout);

    QObject::connect(
        m_animationIn,
        &QPropertyAnimation::finished,
        this,
        &OfficeMenuHeader::animationInFinished
        );

    QObject::connect(
        m_animationOut,
        &QPropertyAnimation::finished,
        this,
        &OfficeMenuHeader::animationOutFinished
        );
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

    OfficeMenuPanel* panel = new OfficeMenuPanel(m_panelBar, this);
    panel->setText(text);
    panel->setId(id);
    panel->show();

    m_panels.insert(pos, panel);
    m_panelLayout->insertWidget(pos, panel, 0);

    return panel;
}

bool OfficeMenuHeader::removePanel(int id)
{
    auto* panel = panelById(id);
    if (panel != nullptr)
    {
        m_panels.removeOne(panel);
        m_panelLayout->removeWidget(panel);

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
    if (event->button() == Qt::LeftButton && !m_isSelected)
    {
        m_parent->expand(this);
    }
}

void OfficeMenuHeader::animationInFinished()
{
}

void OfficeMenuHeader::animationOutFinished()
{
    m_parent->resize(width(), c_headerHeight);
    m_parent->setFixedHeight(c_headerHeight);
}

void OfficeMenuHeader::expand(QHBoxLayout* panel, bool isExpanded)
{
    panel->addWidget(m_panelBar, 0, Qt::AlignLeft);

    if (!isExpanded)
    {
        // Huge hack: QWidget::show appearantly resizes the widget immediately,
        // no matter what I do. Even explicit calls to QWidget::resize or
        // QWidget::updateGeometry failed. This behaviour caused the widget to
        // be visible at full height for a split second, before the QProperty-
        // Animation kicked in and changed the QWidget::height to zero.
        m_effectIn->setOpacity(0.0);
        m_panelBar->show();

        // This undesirable effect can only be eliminated by hiding the widget
        // visually (via QGraphicsOpacityEffect) for a split second, too.
        QTimer::singleShot(100, [&]() { m_effectIn->setOpacity(1.0); });

        // The menu is not pinned yet, therefore show it using an animation.
        m_animationIn->setDuration(200);
        m_animationIn->setStartValue(QSize(m_parent->width(), 0));
        m_animationIn->setEndValue(QSize(m_parent->width(), c_panelHeight));
        m_animationIn->start();
    }
    else
    {
        m_panelBar->show();
    }

    m_isSelected = true;
    update();

    emit headerExpanded();
}

void OfficeMenuHeader::collapse(QHBoxLayout* panel, bool isExpanded)
{
    panel->removeWidget(m_panelBar);

    if (isExpanded && m_isSelected)
    {
        // Hides the menu using a smooth animation.
        m_animationOut->setDuration(200);
        m_animationOut->setStartValue(QSize(m_parent->width(), c_panelHeight));
        m_animationOut->setEndValue(QSize(m_parent->width(), 0));
        m_animationOut->start();
    }
    else
    {
        m_panelBar->hide();
    }

    m_isSelected = false;
    update();

    emit headerCollapsed();
}
