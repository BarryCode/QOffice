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


#ifndef QOFFICE_OFFICEMENUITEM_HPP
#define QOFFICE_OFFICEMENUITEM_HPP


// QOffice headers
#include <QOffice/Widgets/OfficeTooltip.hpp>
#include <QOffice/Widgets/Enums/OfficeMenuEnums.hpp>

// Qt headers
#include <QWidget>
#include <QTimer>


QOFFICE_BEGIN_NAMESPACE


class OfficeMenuPanel;


/**
 * This class is the base for all menu item types.
 *
 * @class OfficeMenuItem
 * @author Nicolas Kogler
 * @date January 2nd, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenuItem : public QWidget
{
public:

    /**
     * Initializes a new instance of OfficeMenuPanel.
     *
     * @param parent The parent as menu panel.
     *
     */
    OfficeMenuItem(OfficeMenuPanel* parent);

    /**
     * Frees all resources used by this menu item.
     *
     */
    virtual ~OfficeMenuItem();


    /**
     * Retrieves the perfect size for this widget.
     *
     * @returns the perfect item size.
     *
     */
    QSize sizeHint() const;


    /**
     * Retrieves the bounding rectangle of this item.
     * The height is the same for all menu items.
     *
     * @returns the bounding rectangle.
     *
     */
    const QRect& bounds() const;

    /**
     * Retrieves the unique ID of this item.
     *
     * @returns the unique identifier.
     *
     */
    const QString& identifier() const;

    /**
     * Retrieves the text of this item.
     *
     * @returns the item text.
     *
     */
    const QString& text() const;

    /**
     * Retrieves the tooltip text.
     *
     * @returns the tooltip text.
     *
     */
    const QString& tooltipText() const;


    /**
     * Specifies the unique identifier.
     *
     * @param id The unique identifier.
     *
     */
    void setIdentifier(const QString& id);

    /**
     * Specifies the item text.
     *
     * @param text The item text.
     *
     */
    void setText(const QString& text);

    /**
     * Specifies the tooltip text.
     *
     * @param text The tooltip text.
     *
     */
    void setTooltipText(const QString& text);


signals:

    /**
     * This signal is emitted if the user requested
     * help from the tooltip that is assigned to this item.
     *
     */
    void helpRequested();


protected:

    /**
     * Paints the menu item. The default implementation
     * is empty and renders nothing.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void paintEvent(QPaintEvent* event) = 0;

    /**
     * Provides the tooltip logic for all menu items.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void enterEvent(QEvent* event) override;

    /**
     * Provides the tooltip logic for all menu items.
     * Hides the tooltip, if any, on leaving the item.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void leaveEvent(QEvent* event) override;


    // Protected members
    QRect m_Bounds;
    QRect m_TightBounds;
    QString m_Identifier;
    QString  m_Text;


private slots:

    void onHelpRequested();
    void showTooltip();


private:

    // Members
    QTimer*             m_Timer;
    OfficeMenuPanel*    m_ParentPanel;
    OfficeTooltip*      m_Tooltip;
    QString             m_TooltipText;

    // Metadata
    Q_OBJECT

    // Friends
    friend class OfficeMenuPanel;
};


/**
 * This class defines a simple, clickable button.
 *
 * @class OfficeMenuButtonItem
 * @author Nicolas Kogler
 * @date January 2nd, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenuButtonItem : public OfficeMenuItem
{
public:

    /**
     * Initializes a new instance of OfficeMenuPanel.
     *
     * @param parent The parent as menu panel.
     *
     */
    OfficeMenuButtonItem(OfficeMenuPanel* parent = nullptr);

    /**
     * Frees all resources used by this menu item.
     *
     */
    ~OfficeMenuButtonItem();


    /**
     * Retrieves the button icon.
     *
     * @returns the button icon.
     *
     */
    const QPixmap& icon() const;

    /**
     * Specifies the button icon.
     *
     * @param pm The button icon.
     *
     */
    void setIcon(const QPixmap& pm);


protected:

    /**
     * Paints the button icon and text.
     *
     * @param event Holds nothing we need.
     *
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * Hovers the item on entering the widget.
     *
     * @param event Holds nothing we need.
     *
     */
    void enterEvent(QEvent* event) override;

    /**
     * Dehovers the item on leaving the widget.
     *
     * @param event Holds nothing we need.
     *
     */
    void leaveEvent(QEvent* event) override;

    /**
     * Puts the item into pressed state.
     *
     * @param event Holds the pressed button.
     *
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * Puts the item into hovered state, or no state
     * if the mouse pointer does not hover the item.
     *
     * @param event Holds the released button.
     *
     */
    void mouseReleaseEvent(QMouseEvent* event) override;


private:

    // Members
    QPixmap m_Icon;
    MenuButtonState m_State;


    // Metadata
    Q_OBJECT

    // Friends
    friend class OfficeMenuPanel;
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEMENUITEM_HPP
