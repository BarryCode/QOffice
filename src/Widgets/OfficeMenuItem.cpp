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
#include <QOffice/Widgets/OfficeMenuItem.hpp>


QOFFICE_USING_NAMESPACE


OfficeMenuItem::OfficeMenuItem(OfficeMenuPanel *parent)
    : QWidget(parent)
    , m_Timer(new QTimer(this))
    , m_ParentPanel(parent)
    , m_Tooltip(new OfficeTooltip(this))
{
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    m_Timer->setInterval(1000);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(showTooltip()));
    connect(m_Tooltip, SIGNAL(helpRequested()), this, SLOT(onHelpRequested()));
}


OfficeMenuItem::~OfficeMenuItem()
{
}


const QString&
OfficeMenuItem::identifier() const
{
    return m_Identifier;
}


const QString&
OfficeMenuItem::text() const
{
    return m_Text;
}


const QString&
OfficeMenuItem::tooltipText() const
{
    return m_TooltipText;
}


void
OfficeMenuItem::setIdentifier(const QString& id)
{
    m_Identifier = id;
}


void
OfficeMenuItem::setText(const QString& text)
{
    m_Text = text;
}


void
OfficeMenuItem::setTooltipText(const QString& text)
{
    m_TooltipText = text;
}


void
OfficeMenuItem::enterEvent(QEvent*)
{
    m_Timer->start();
}


void
OfficeMenuItem::leaveEvent(QEvent*)
{
    m_Timer->stop();
    m_Tooltip->hide();
}


void
OfficeMenuItem::onHelpRequested()
{
    emit helpRequested();
}


void
OfficeMenuItem::showTooltip()
{
    QPoint pos = mapToGlobal(QCursor::pos());
    QSize size(200, 200);

    m_Tooltip->setGeometry(QRect(pos, size));
    m_Tooltip->setHeading(m_Text);
    m_Tooltip->setText(m_TooltipText);
    m_Tooltip->show();
    m_Timer->stop();
}
