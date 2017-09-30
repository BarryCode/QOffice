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
/// \brief OfficeTooltipdesc
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 30, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeTooltip : public QWidget
{
public:

    OffDefaultDtor(OfficeTooltip)
    OffDisableCopy(OfficeTooltip)
    OffDisableMove(OfficeTooltip)

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of OfficeTooltip and specifies the given
    /// \p parent as widget the tooltip is shown on.
    ///
    /// \param parent The widget to show this tooltip on.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeTooltip(QWidget* parent = nullptr);

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

protected:

    virtual void paintEvent(QPaintEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void keyPressEvent(QKeyEvent*) override;
    virtual void showEvent(QShowEvent*) override;
    virtual void hideEvent(QHideEvent*) override;
    virtual void leaveEvent(QEvent*) override;

signals:

    void helpRequested();

public slots:

    void beginHideTooltip();
    void finishHideTooltip();

private:

    ////////////////////////////////////////////////////////////////////////////
    // Functions
    //
    ////////////////////////////////////////////////////////////////////////////
    void updateRectangles();
    void generateDropShadow();
    qreal opacity() const;
    void setOpacity(qreal opacity);

    ////////////////////////////////////////////////////////////////////////////
    // Members 1
    //
    ////////////////////////////////////////////////////////////////////////////
    QTimer*             m_timer;
    QPropertyAnimation* m_animation;
    OfficeWindow*       m_activeWindow;
    QString             m_heading;
    QString             m_bodyText;
    QString             m_helpText;
    QPixmap             m_helpIcon;
    qint32              m_duration;
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

    ////////////////////////////////////////////////////////////////////////////
    // Metadata
    //
    ////////////////////////////////////////////////////////////////////////////
    Q_OBJECT
    Q_PROPERTY(qreal Opacity READ opacity WRITE setOpacity)
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeTooltip
/// \ingroup Widget
///
/// $Detailedclassdesc
///
/// \code
/// <example_code>
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
