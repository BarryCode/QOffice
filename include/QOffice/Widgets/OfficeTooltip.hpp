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

#pragma once
#ifndef QOFFICE_WIDGETS_OFFICETOOLTIP_HPP
#define QOFFICE_WIDGETS_OFFICETOOLTIP_HPP

#include <QOffice/Config.hpp>
#include <QWidget>

class OfficeWindow;

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeTooltip
/// \ingroup Widget
///
/// \brief Defines an office-style tooltip.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 30, 2017
///
/// This class shows modern tooltips and allows one to customize the title, the
/// body text and the help text along with the help icon and help trigger key. A
/// default help icon is already provided, but it can be changed, if desired.
/// One should use it as follows:
///
/// \code
/// m_tooltip->connect(m_tooltip, &OfficeTooltip::helpRequested, this, [...]);
/// m_tooltip->setTitle("Open");
/// m_tooltip->setText("Opens an existing file with read-write access.");
/// m_tooltip->setHelpText("Press F1 to receive help.");
/// m_tooltip->setHelpKey(Qt::Key_F1);
/// m_tooltip->setHelpEnabled(true);
/// m_tooltip->setDuration(5000); // in msec
/// m_tooltip->show();
/// \endcode
///
/// The helpRequested signal is emitted once the help key was pressed or the
/// help text (that acts as a hyperlink) was clicked.
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeTooltip : public QWidget
{
public:

    OffDeclareCtor(OfficeTooltip)
    OffDefaultDtor(OfficeTooltip)
    OffDisableCopy(OfficeTooltip)
    OffDisableMove(OfficeTooltip)

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the title of this tooltip.
    ///
    /// \return The title of this tooltip.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& title() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the text of this tooltip.
    ///
    /// \return The text of this tooltip.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& text() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether the help section is enabled.
    ///
    /// \return True if help is enabled, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool isHelpEnabled() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the help text of this tooltip.
    ///
    /// \return The help text of this tooltip.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& helpText() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the help icon of this tooltip.
    ///
    /// \return The help icon of this tooltip.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QPixmap& helpIcon() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the key that triggers the helpRequested signal.
    ///
    /// \return The triggering key for help.
    ///
    ////////////////////////////////////////////////////////////////////////////
    Qt::Key helpKey() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the duration this tooltip is shown.
    ///
    /// \return The display duration.
    ///
    ////////////////////////////////////////////////////////////////////////////
    int duration() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Defines the period to wait before the tooltip is actually shown.
    ///
    /// \return The wait period upon showing the tooltip.
    ///
    ////////////////////////////////////////////////////////////////////////////
    int waitPeriod() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the title of this tooltip.
    ///
    /// \param[in] title The new title.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setTitle(const QString& title);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the text of this tooltip.
    ///
    /// \param[in] text The new text.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setText(const QString& text);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies whether the help section should be enabled.
    ///
    /// \param[in] enabled True to enable the help section, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setHelpEnabled(bool enabled);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the help text of this tooltip.
    ///
    /// \param[in] text The new help text.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setHelpText(const QString& text);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the help icon of this tooltip.
    ///
    /// \param[in] icon The new help icon.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setHelpIcon(const QPixmap& icon);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the triggering key for help.
    ///
    /// \param[in] trigger The key that triggers the helpRequested signal.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setHelpKey(Qt::Key trigger);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the duration this tooltip is shown.
    ///
    /// \param[in] milliseconds The new display duration, in milliseconds.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setDuration(int milliseconds);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the wait period before this tooltip is shown.
    ///
    /// \param[in] milliseconds The new wait period, in milliseconds.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setWaitPeriod(int milliseconds);

protected:

    virtual void paintEvent(QPaintEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void keyPressEvent(QKeyEvent*) override;
    virtual void showEvent(QShowEvent*) override;
    virtual void hideEvent(QHideEvent*) override;
    virtual void leaveEvent(QEvent*) override;

signals:

    void tooltipShown();
    void tooltipHidden();
    void helpRequested();

public slots:

    void beginHideTooltip();
    void emitTooltipHidden();
    void fadeInTooltip();

private:

    void updateRectangles();
    void generateDropShadow();
    qreal opacity() const;
    void setOpacity(qreal opacity);

    QTimer*             m_timer;
    QTimer*             m_waitTimer;
    QPropertyAnimation* m_showAnimation;
    QPropertyAnimation* m_hideAnimation;
    OfficeWindow*       m_activeWindow;
    QString             m_heading;
    QString             m_bodyText;
    QString             m_helpText;
    QPixmap             m_helpIcon;
    qint32              m_duration;
    qint32              m_waitPeriod;
    Qt::Key             m_helpKey;
    QPixmap             m_dropShadow;
    QRect               m_clientRectangle;
    QRect               m_borderRectangle;
    QRect               m_headingRectangle;
    QRect               m_bodyRectangle;
    QRect               m_iconRectangle;
    QRect               m_helpRectangle;
    QRect               m_sepaRectangle;
    qreal               m_opacity;
    bool                m_isHelpEnabled;
    bool                m_isLinkHovered;

    Q_OBJECT
    Q_PROPERTY(qreal Opacity READ opacity WRITE setOpacity)
};

#endif

