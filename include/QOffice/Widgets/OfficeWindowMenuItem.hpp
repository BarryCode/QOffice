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

#pragma once
#ifndef QOFFICE_WIDGETS_OFFICEWINDOWMENUITEM_HPP
#define QOFFICE_WIDGETS_OFFICEWINDOWMENUITEM_HPP

#include <QOffice/Config.hpp>
#include <QWidget>

class OfficeWindowMenu;

namespace priv
{
class WindowItem : public QWidget
{
public:

    WindowItem(
        OfficeWindowMenu* parent,
        int type,
        int id,
        const QString& text,
        const QPixmap& image = QPixmap(),
        const QString& tooltip = QString()
        );

    OffDefaultDtor(WindowItem)
    OffDisableCopy(WindowItem)
    OffDisableMove(WindowItem)

    int id() const;
    const QString& text() const;
    const QPixmap& image() const;
    const QString& tooltipText() const;

    void setText(const QString& text);
    void setImage(const QPixmap& img);
    void setTooltipText(const QString& text);

    QSize sizeHint() const override;

signals:

    void clicked(WindowItem*);
    void tooltipShowRequested(WindowItem*);
    void tooltipHideRequested(WindowItem*);

protected:

    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private:

    int               m_type;      ///< Defines the type of the parent menu.
    int               m_id;        ///< Defines the unique item identifier.
    bool              m_isHovered; ///< Determines whether the item is hovered.
    bool              m_isPressed; ///< Determines whether the item is pressed.
    QString           m_text;      ///< Defines the displayed item text.
    QPixmap           m_image;     ///< Defines the displayed item image.
    QString           m_tooltip;   ///< Defines the tooltip text.
    OfficeWindowMenu* m_parent;    ///< Defines the parent window menu.

    Q_OBJECT
};
}

#endif
