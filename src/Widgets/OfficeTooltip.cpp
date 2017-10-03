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

#include <QOffice/Design/OfficeImage.hpp>
#include <QOffice/Design/OfficePalette.hpp>
#include <QOffice/Widgets/OfficeTooltip.hpp>
#include <QOffice/Widgets/Dialogs/OfficeWindow.hpp>

#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>

OffAnonymous(QOFFICE_CONSTEXPR int c_margin  = c_shadowPadding + 10)
OffAnonymous(QOFFICE_CONSTEXPR int c_padding = c_margin * 2)
OffAnonymous(QOFFICE_CONSTEXPR int c_bodyMargin = 10)
OffAnonymous(QOFFICE_CONSTEXPR int c_iconMargin = 8)
OffAnonymous(QOFFICE_CONSTEXPR int c_helpMargin = 7)
OffAnonymous(QOFFICE_CONSTEXPR int c_separator  = 9)

OfficeTooltip::OfficeTooltip(QWidget* parent)
    : QWidget(parent)
    , m_timer(new QTimer(this))
    , m_waitTimer(new QTimer(this))
    , m_animation(new QPropertyAnimation(this))
    , m_activeWindow(nullptr)
    , m_heading("")
    , m_bodyText("Text")
    , m_helpText("")
    , m_helpIcon(":/qoffice/images/widgets/tooltip_help.png")
    , m_duration(4000)
    , m_helpKey(Qt::Key_F1)
    , m_opacity(0.0)
    , m_isHelpEnabled(false)
    , m_isLinkHovered(false)
{
    // Tells Qt that our widget is a tooltip and should be frameless.
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    m_animation->setTargetObject(this);
    m_animation->setPropertyName(QByteArray("Opacity"));
    m_animation->setDuration(200);

    // Need to use old syntax since update() has overloads :(
    QObject::connect(
        m_animation,
        SIGNAL(valueChanged(QVariant)),
        this,
        SLOT(update())
        );

    QObject::connect(
        m_timer,
        &QTimer::timeout,
        this,
        &OfficeTooltip::beginHideTooltip
        );

    QObject::connect(
        m_waitTimer,
        &QTimer::timeout,
        this,
        &OfficeTooltip::fadeInTooltip
        );
}

const QString& OfficeTooltip::title() const
{
    return m_heading;
}

const QString& OfficeTooltip::text() const
{
    return m_bodyText;
}

bool OfficeTooltip::isHelpEnabled() const
{
    return m_isHelpEnabled;
}

const QString& OfficeTooltip::helpText() const
{
    return m_helpText;
}

const QPixmap& OfficeTooltip::helpIcon() const
{
    return m_helpIcon;
}

Qt::Key OfficeTooltip::helpKey() const
{
    return m_helpKey;
}

int OfficeTooltip::duration() const
{
    return m_duration;
}

int OfficeTooltip::waitPeriod() const
{
    return m_waitPeriod;
}

void OfficeTooltip::setTitle(const QString& title)
{
    m_heading = title;
}

void OfficeTooltip::setText(const QString& text)
{
    m_bodyText = text;
}

void OfficeTooltip::setHelpEnabled(bool enabled)
{
    m_isHelpEnabled = enabled;
}

void OfficeTooltip::setHelpText(const QString& text)
{
    m_helpText = text;
}

void OfficeTooltip::setHelpIcon(const QPixmap& icon)
{
    m_helpIcon = icon;
}

void OfficeTooltip::setHelpKey(Qt::Key trigger)
{
    m_helpKey = trigger;
}

void OfficeTooltip::setDuration(int milliseconds)
{
    m_duration = milliseconds;
}

void OfficeTooltip::setWaitPeriod(int milliseconds)
{
    m_waitPeriod = milliseconds;
}

void OfficeTooltip::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Retrieves a standardized set of colors for this tooltip.
    const QColor& colorBorder = OfficePalette::color(OfficePalette::TooltipBorder);
    const QColor& colorBackg = OfficePalette::color(OfficePalette::TooltipBackground);
    const QColor& colorText1 = OfficePalette::color(OfficePalette::TooltipText);
    const QColor& colorText2 = OfficePalette::color(OfficePalette::TooltipHelpText);
    const QColor& colorSeparator = OfficePalette::color(OfficePalette::TooltipSeparator);

    // Drop-shadow
    painter.setOpacity(m_opacity);
    painter.drawPixmap(QPoint(), m_dropShadow);

    // Background and border
    painter.setPen(colorBorder);
    painter.fillRect(m_clientRectangle, colorBackg);
    painter.drawRect(m_borderRectangle);

    // Title
    if (!m_heading.isEmpty())
    {
        QFont currentFont = font();
        currentFont.setBold(true);

        painter.setFont(currentFont);
        painter.setPen(colorText1);
        painter.drawText(m_headingRectangle, m_heading);
    }

    // Body
    if (!m_bodyText.isEmpty())
    {
        painter.setFont(font());
        painter.setPen(colorText1);
        painter.drawText(m_bodyRectangle, Qt::TextWordWrap, m_bodyText);
    }

    // Help
    if (m_isHelpEnabled && !m_helpText.isEmpty())
    {
        QFont currentFont = font();
        currentFont.setBold(true);

        painter.setFont(currentFont);
        painter.setPen(colorText2);

        painter.fillRect(m_sepaRectangle, colorSeparator);
        painter.drawPixmap(m_iconRectangle, m_helpIcon);
        painter.drawText(m_helpRectangle, m_helpText);

        if (m_isLinkHovered)
        {
            QPoint p1(m_helpRectangle.left(),  m_helpRectangle.bottom());
            QPoint p2(m_helpRectangle.right(), m_helpRectangle.bottom());

            painter.drawLine(p1, p2);
        }
    }
}

void OfficeTooltip::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isHelpEnabled && !m_helpText.isEmpty())
    {
        bool previousState = m_isLinkHovered;

        if (m_helpRectangle.contains(event->pos()))
        {
            m_isLinkHovered = true;
            setCursor(Qt::PointingHandCursor);
        }
        else
        {
            m_isLinkHovered = false;
            unsetCursor();
        }

        if (m_isLinkHovered != previousState)
        {
            update();
        }
    }
}

void OfficeTooltip::mousePressEvent(QMouseEvent* event)
{
    if (m_isHelpEnabled && !m_helpText.isEmpty())
    {
        // When the link is pressed, the helpRequested signal should be emitted.
        // It is your responsibility to handle the signal and open some sort of
        // help dialog.
        if (m_isLinkHovered && event->button() == Qt::LeftButton)
        {
            hide();

            emit helpRequested();
        }
    }
}

void OfficeTooltip::keyPressEvent(QKeyEvent* event)
{
    if (m_isHelpEnabled && !m_helpText.isEmpty())
    {
        // When the trigger key is pressed, the helpRequested signal should be
        // emitted. It is your responsibility to handle the signal and open some
        // sort of help dialog.
        if (event->key() == m_helpKey)
        {
            hide();

            emit helpRequested();
        }
    }
}

void OfficeTooltip::showEvent(QShowEvent*)
{
    if (m_waitPeriod != 0)
    {
        m_waitTimer->setInterval(m_waitPeriod);
        m_waitTimer->setSingleShot(true);
        m_waitTimer->start();
    }
    else
    {
        fadeInTooltip();
    }
}

void OfficeTooltip::hideEvent(QHideEvent*)
{
    if (m_activeWindow != nullptr)
    {
        m_activeWindow->m_tooltipVisible = false;
    }

    m_timer->stop();
    m_waitTimer->stop();

    m_opacity = 0.0;
    m_isLinkHovered = false;
    m_activeWindow  = nullptr;

    QObject::disconnect(
        m_animation,
        &QPropertyAnimation::finished,
        this,
        &OfficeTooltip::hide
        );
}

void OfficeTooltip::leaveEvent(QEvent*)
{
    m_timer->setInterval(400);
    m_timer->start();

    unsetCursor();
}

void OfficeTooltip::beginHideTooltip()
{
    m_animation->setStartValue(1.0);
    m_animation->setEndValue(0.0);
    m_animation->start();

    QObject::connect(
        m_animation,
        &QPropertyAnimation::finished,
        this,
        &OfficeTooltip::emitTooltipHidden
        );
}

void OfficeTooltip::emitTooltipHidden()
{
    hide();

    emit tooltipHidden();
}

void OfficeTooltip::fadeInTooltip()
{
    m_timer->setInterval(m_duration);
    m_timer->setSingleShot(true);
    m_timer->start();

    // Tells the active window that a tooltip was shown. This prevents the
    // OfficeWindow from rendering in "deactivated mode".
    if (OfficeWindow::activeWindow() != nullptr)
    {
        OfficeWindow::activeWindow()->m_tooltipVisible = true;

        // After the next calls, the active window function will return nullptr.
        // Therefore, temporarily store it in a private member variable.
        m_activeWindow = OfficeWindow::activeWindow();
    }

    updateRectangles();
    activateWindow();

    // Tells Qt that our newly shown tooltip should get the focus.
    setFocus(Qt::PopupFocusReason);

    m_opacity = 0.0;
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(1.0);
    m_animation->start();

    emit tooltipShown();
}

void OfficeTooltip::updateRectangles()
{
    QFont normFont = font(); normFont.setBold(false);
    QFont boldFont = font(); boldFont.setBold(true);

    QFontMetrics normMetrics(normFont);
    QFontMetrics boldMetrics(boldFont);

    int currentX = c_margin;
    int currentY = c_margin;

    // Title
    if (!m_heading.isEmpty())
    {
        QRect bounds = boldMetrics.boundingRect(m_heading);

        m_headingRectangle.setX(currentX);
        m_headingRectangle.setY(currentY);
        m_headingRectangle.setSize(bounds.size() + QSize(5, 5));

        currentY += (bounds.height() + c_bodyMargin);
    }

    // Body
    if (!m_bodyText.isEmpty())
    {
        QRect max(0, 0, width() - c_padding, 300);
        QRect bounds = normMetrics.boundingRect(max, Qt::TextWordWrap, m_bodyText);

        m_bodyRectangle.setX(currentX);
        m_bodyRectangle.setY(currentY);
        m_bodyRectangle.setSize(bounds.size());

        currentY += bounds.height();
    }

    // Help
    if (!m_helpText.isEmpty())
    {
        currentY += c_separator;

        // Separator
        m_sepaRectangle.setX(currentX);
        m_sepaRectangle.setY(currentY);
        m_sepaRectangle.setSize(QSize(width() - c_padding, 1));

        currentY += c_separator;

        // Icon
        m_iconRectangle.setX(currentX);
        m_iconRectangle.setY(currentY);
        m_iconRectangle.setSize(m_helpIcon.size());

        currentX += (m_helpIcon.width() + c_iconMargin);

        // Text
        m_helpRectangle.setX(currentX);
        m_helpRectangle.setY(currentY);
        m_helpRectangle.setWidth(boldMetrics.width(m_helpText));
        m_helpRectangle.setHeight(boldMetrics.height());

        currentY += m_helpRectangle.height();
    }

    currentY += c_margin;
    resize(width(), currentY);
    generateDropShadow();

    // Client
    m_clientRectangle.setTopLeft(QPoint(c_shadowPadding, c_shadowPadding));
    m_clientRectangle.setWidth(width() - c_shadowPadding * 2);
    m_clientRectangle.setHeight(height() - c_shadowPadding * 2);

    // Border
    m_borderRectangle = m_clientRectangle.adjusted(0,0,-1,-1);
}

void OfficeTooltip::generateDropShadow()
{
    m_dropShadow = OfficeImage::generateDropShadow(size());
}

qreal OfficeTooltip::opacity() const
{
    return m_opacity;
}

void OfficeTooltip::setOpacity(qreal opacity)
{
    m_opacity = opacity;
}
