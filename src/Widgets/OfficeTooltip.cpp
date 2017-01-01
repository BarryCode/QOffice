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
#include <QOffice/Widgets/OfficeTooltip.hpp>
#include <QOffice/Widgets/OfficeWindow.hpp>
#include <QOffice/Widgets/Constants/OfficeTooltipConstants.hpp>
#include <QOffice/Design/OfficePalette.hpp>

// Qt headers
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>


QOFFICE_USING_NAMESPACE


OfficeTooltip::OfficeTooltip(QWidget* parent)
    : QWidget(parent)
    , m_Duration(4000)
    , m_Timer(new QTimer(this))
    , m_IsLinkHovered(false)
{
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    m_OpacAnim = new QPropertyAnimation(this);
    m_OpacAnim->setTargetObject(this);
    m_OpacAnim->setPropertyName(QByteArray("Opacity"));
    m_OpacAnim->setDuration(200);

    connect(m_OpacAnim, SIGNAL(valueChanged(QVariant)), this, SLOT(update()));
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(beginHideTooltip()));
    m_HelpIcon = QPixmap(":/qoffice/images/widgets/tooltip_help.png");
}


OfficeTooltip::~OfficeTooltip()
{
}


void
OfficeTooltip::setHeading(const QString& heading)
{
    m_Heading = heading;
}


void
OfficeTooltip::setText(const QString& text)
{
    m_BodyText = text;
}


void
OfficeTooltip::setHelpText(const QString& text)
{
    m_HelpText = text;
}


void
OfficeTooltip::setHelpIcon(const QPixmap& icon)
{
    if (icon.isNull())
        m_HelpIcon = QPixmap(":/qoffice/images/widgets/tooltip_help.png");
    else
        m_HelpIcon = icon;
}


void
OfficeTooltip::setDisplayDuration(int milliseconds)
{
    m_Duration = milliseconds;
}


void
OfficeTooltip::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Retrieves all needed colors for rendering this tooltip.
    const QColor& colorBordr = OfficePalette::get(OfficePalette::TooltipBorder);
    const QColor& colorBackg = OfficePalette::get(OfficePalette::TooltipBackground);
    const QColor& colorTextn = OfficePalette::get(OfficePalette::TooltipText);
    const QColor& colorTexth = OfficePalette::get(OfficePalette::TooltipHelpText);
    const QColor& colorSepar = OfficePalette::get(OfficePalette::TooltipSeparator);


    painter.setOpacity(m_Opacity);
    painter.drawPixmap(QPoint(), m_DropShadow);

    // Renders the background and the border of the tooltip.
    painter.fillRect(m_ClientRect, colorBackg);
    painter.setPen(colorBordr);
    painter.drawRect(m_BorderRect);

    // Renders the heading.
    if (!m_Heading.isEmpty())
    {
        QFont f = font();

        f.setBold(true);
        painter.setFont(f);
        painter.setPen(colorTextn);
        painter.drawText(m_HeadingRect, m_Heading);
    }

    // Renders the body.
    if (!m_BodyText.isEmpty())
    {
        painter.setFont(font());
        painter.setPen(colorTextn);
        painter.drawText(m_BodyRect, Qt::TextWordWrap, m_BodyText);
    }

    // Renders the separator and the help text.
    if (!m_HelpText.isEmpty())
    {
        QFont f = font();

        f.setBold(true);
        painter.setFont(f);
        painter.fillRect(m_SeparatorRect, colorSepar);
        painter.drawPixmap(m_HelpIconRect, m_HelpIcon);
        painter.setPen(colorTexth);
        painter.drawText(m_HelpTextRect, m_HelpText);

        // Renders the link underline.
        if (m_IsLinkHovered)
        {
            QPoint p1(m_HelpTextRect.x(), m_HelpTextRect.bottom());
            QPoint p2(m_HelpTextRect.right(), m_HelpTextRect.bottom());

            painter.drawLine(p1, p2);
        }
    }
}


void
OfficeTooltip::mouseMoveEvent(QMouseEvent* event)
{
    if (m_HelpText.isEmpty())
        return;

    bool oldState = m_IsLinkHovered;

    // Determines whether the cursor hovers the link.
    if (m_HelpTextRect.contains(event->pos()))
        m_IsLinkHovered = true;
    else
        m_IsLinkHovered = false;

    if (m_IsLinkHovered != oldState)
        update();
}


void
OfficeTooltip::mousePressEvent(QMouseEvent* event)
{
    if (m_HelpText.isEmpty())
        return;

    // Determines whether the link is pressed.
    if (m_IsLinkHovered && event->button() == Qt::LeftButton)
    {
        hide();
        emit helpRequested();
    }
}


void
OfficeTooltip::keyPressEvent(QKeyEvent* event)
{
    if (!m_HelpText.isEmpty() && event->key() == Qt::Key_F1)
    {
        hide();
        emit helpRequested();
    }
}


void
OfficeTooltip::showEvent(QShowEvent*)
{
    m_Timer->setInterval(m_Duration);
    m_Timer->start();
    updateRectangles();

    // Tells the active window that a tooltip was shown.
    // This prevents the window to render incorrectly.
    if (OfficeWindow::g_ActiveWindow != nullptr)
    {
        OfficeWindow::g_ActiveWindow->m_IsTooltipShown = true;
        m_ActiveWindow = OfficeWindow::g_ActiveWindow;
    }

    activateWindow();
    setFocus(Qt::PopupFocusReason);

    // Fades in the tooltip.
    m_Opacity = 0.0;
    m_OpacAnim->setStartValue(0.0);
    m_OpacAnim->setEndValue(1.0);
    m_OpacAnim->start();
}


void
OfficeTooltip::hideEvent(QHideEvent*)
{
    if (m_ActiveWindow != nullptr)
        m_ActiveWindow->m_IsTooltipShown = false;

    m_Timer->stop();
    m_Opacity = 0.0;
    m_IsLinkHovered = false;
    disconnect(m_OpacAnim, SIGNAL(finished()), this, SLOT(hideTooltip()));
}


void
OfficeTooltip::leaveEvent(QEvent*)
{
    m_Timer->setInterval(400);
    m_Timer->start();
}


void
OfficeTooltip::beginHideTooltip()
{
    m_OpacAnim->setStartValue(1.0);
    m_OpacAnim->setEndValue(0.0);
    m_OpacAnim->start();
    connect(m_OpacAnim, SIGNAL(finished()), this, SLOT(hideTooltip()));
}


void
OfficeTooltip::hideTooltip()
{
    hide();
}


void
OfficeTooltip::updateRectangles()
{
    QFont boldFont = font();
          boldFont.setBold(true);
    QFontMetrics metrics(font());
    QFontMetrics boldMetrics(boldFont);

    // Specifies the rectangle for the heading.
    int currentX = TOOLTIP_MARGIN;
    int currentY = TOOLTIP_MARGIN;
    if (!m_Heading.isEmpty())
    {
        QRect br = boldMetrics.boundingRect(m_Heading);

        m_HeadingRect.setX(currentX);
        m_HeadingRect.setY(currentY);
        m_HeadingRect.setWidth(br.width());
        m_HeadingRect.setHeight(br.height());

        currentY += br.height();
        currentY += TOOLTIP_BODY_MARGIN;
    }

    // Specifies the rectangle for the body.
    if (!m_BodyText.isEmpty())
    {
        QRect br = metrics.boundingRect(
                    QRect(0, 0, width() - (TOOLTIP_MARGIN * 2), 300),
                    Qt::TextWordWrap,
                    m_BodyText);

        m_BodyRect.setX(currentX);
        m_BodyRect.setY(currentY);
        m_BodyRect.setWidth(br.width());
        m_BodyRect.setHeight(br.height());

        currentY += br.height();
    }

    // Specifies the rectangle for the help area.
    if (!m_HelpText.isEmpty())
    {
        currentY += TOOLTIP_SEPA_MARGIN;
        m_SeparatorRect.setX(currentX);
        m_SeparatorRect.setY(currentY);
        m_SeparatorRect.setWidth(width() - (TOOLTIP_MARGIN * 2));
        m_SeparatorRect.setHeight(1);
        currentY += TOOLTIP_HELP_MARGIN;

        m_HelpIconRect.setX(currentX);
        m_HelpIconRect.setY(currentY);
        m_HelpIconRect.setWidth(16);
        m_HelpIconRect.setHeight(16);
        currentX += m_HelpIcon.width();
        currentX += TOOLTIP_ICON_PADDING;

        m_HelpTextRect.setX(currentX);
        m_HelpTextRect.setY(currentY);
        m_HelpTextRect.setWidth(boldMetrics.width(m_HelpText));
        m_HelpTextRect.setHeight(boldMetrics.height());
        currentY += m_HelpTextRect.height();
    }

    // Changes the height of the widget.
    currentY += TOOLTIP_MARGIN;
    resize(width(), currentY);

    // Specifies the client rectangle.
    m_ClientRect.setX(TOOLTIP_DROP_SHADOW);
    m_ClientRect.setY(TOOLTIP_DROP_SHADOW);
    m_ClientRect.setWidth(width() - TOOLTIP_DROP_SHADOW * 2);
    m_ClientRect.setHeight(height() - TOOLTIP_DROP_SHADOW * 2);

    // Specifies the border rectangle.
    m_BorderRect = m_ClientRect.adjusted(0, 0, -1, -1);

    generateDropShadow();
}


void
OfficeTooltip::generateDropShadow()
{
    // Creates a new pixmap that fills the entire widget.
    m_DropShadow = QPixmap(size());
    m_DropShadow.fill(Qt::transparent);

    QPainter painter(&m_DropShadow);

    // Defines the rectangle.
    QRectF rect(
            TOOLTIP_DROP_SHADOW,
            TOOLTIP_DROP_SHADOW,
            width()  - TOOLTIP_DROP_SHADOW * 2,
            height() - TOOLTIP_DROP_SHADOW * 2);

    // Renders the rectangle.
    painter.fillRect(rect, Qt::darkGray);

    // Prepares the pixmap for blurring.
    QGraphicsScene scene;
    QGraphicsPixmapItem item(m_DropShadow);
    QGraphicsDropShadowEffect shadow;

    shadow.setBlurRadius(TOOLTIP_DROP_SHADOW * 2);
    shadow.setColor(Qt::gray);
    shadow.setOffset(TOOLTIP_DROP_SHADOW_B, TOOLTIP_DROP_SHADOW_B);

    // Blurs the rectangle and renders it to the pixmap.
    item.setGraphicsEffect(&shadow);
    scene.addItem(&item);
    scene.render(&painter);
    painter.end();
}
