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
#include <QOffice/Widgets/OfficeDropDown.hpp>
#include <QOffice/Widgets/Enums/OfficeMenuEnums.hpp>

// Qt headers
#include <QWidget>
#include <QTimer>


QOFFICE_BEGIN_NAMESPACE


class OfficeMenu;
class OfficeMenuPanel;
class OfficeMenuItemGroup;


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
     * Initializes a new instance of OfficeMenuItem.
     *
     * @param parent The parent as menu panel.
     *
     */
    OfficeMenuItem(OfficeMenuPanel* parent = nullptr);

    /**
     * Frees all resources used by this menu item.
     *
     */
    virtual ~OfficeMenuItem() = 0;


    /**
     * Retrieves the perfect size for this widget.
     *
     * @returns the perfect item size.
     *
     */
    virtual QSize sizeHint() const = 0;

    /**
     * Retrieves the optimal height for this widget,
     * but not the perfect one. The item group or the
     * textbox for example do not fill the entire panel
     * height-wise.
     *
     * @returns the optimal height for this item.
     *
     */
    virtual int heightHint() const = 0;


    /**
     * Retrieves the parent office menu.
     *
     * @returns the parent office menu.
     *
     */
    OfficeMenu* parentMenu();

    /**
     * Retrieves the parent menu panel.
     *
     * @returns the parent menu panel.
     *
     */
    OfficeMenuPanel* parentPanel();


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
     * Retrieves the tooltip help text.
     *
     * @returns the tooltip help text.
     */
    const QString& tooltipHelpText() const;


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

    /**
     * Specifies the tooltip help text.
     *
     * @param text The tooltip help text.
     */
    void setTooltipHelpText(const QString& text);


signals:

    /**
     * This signal is emitted if the user requested
     * help from the tooltip that is assigned to this item.
     *
     */
    void helpRequested();

    /**
     * A visible property of the item changed and thus
     * requests a resize to its parent panel.
     *
     */
    void requestResize(OfficeMenuItem* item);


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
    QRect               m_Bounds;
    QRect               m_TightBounds;
    QString             m_Identifier;
    QString             m_Text;
    QTimer*             m_Timer;
    OfficeTooltip*      m_Tooltip;
    OfficeMenuPanel*    m_ParentPanel;
    QString             m_TooltipText;
    QString             m_TooltipHelpText;


private slots:

    void onHelpRequested();
    void showTooltip();


private:

    // Metadata
    Q_OBJECT

    // Friends
    friend class OfficeMenu;
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
     * Initializes a new instance of OfficeMenuButtonItem.
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
     * Retrieves the perfect size for this widget.
     *
     * @returns the perfect item size.
     *
     */
    QSize sizeHint() const;

    /**
     * Returns the optimal height for this button item.
     *
     * @returns merely the MENU_ITEM_HEIGHT.
     *
     */
    int heightHint() const;


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

    /**
     * Specifies the parental group or nullptr.
     *
     * @param group The parent group.
     *
     */
    void setGroup(OfficeMenuItemGroup* group);


signals:

    void clicked();


protected:

    /**
     * Paints the button icon and text.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void paintEvent(QPaintEvent* event) override;

    /**
     * Hovers the item on entering the widget.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void enterEvent(QEvent* event) override;

    /**
     * Dehovers the item on leaving the widget.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void leaveEvent(QEvent* event) override;

    /**
     * Puts the item into pressed state.
     *
     * @param event Holds the pressed button.
     *
     */
    virtual void mousePressEvent(QMouseEvent* event) override;

    /**
     * Puts the item into hovered state, or no state
     * if the mouse pointer does not hover the item.
     *
     * @param event Holds the released button.
     *
     */
    virtual void mouseReleaseEvent(QMouseEvent* event) override;


private:

    // Members
    QPixmap m_Icon;
    QPixmap m_DisabledIcon;
    MenuButtonState m_State;
    OfficeMenuItemGroup* m_ParentGroup; ///< Can be also part of a group.

    // Metadata
    Q_OBJECT
};


/**
 * This class defines a separator between items.
 *
 * @class OfficeMenuSeparatorItem
 * @author Nicolas Kogler
 * @date January 4th, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenuSeparatorItem : public OfficeMenuItem
{
public:

    /**
     * Initializes a new instance of OfficeMenuSeparatorItem.
     *
     * @param parent The parent as menu panel.
     *
     */
    OfficeMenuSeparatorItem(OfficeMenuPanel* parent = nullptr);

    /**
     * Frees all resources used by this menu item.
     *
     */
    ~OfficeMenuSeparatorItem();


    /**
     * Retrieves the perfect size for this widget.
     *
     * @returns the perfect item size.
     *
     */
    QSize sizeHint() const override;

    /**
     * Retrieves the optimal height for this widget,
     * but not the perfect one.
     *
     * @returns the optimal height for this item.
     *
     */
    int heightHint() const override;


protected:

    /**
     * Paints the button icon and text.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void paintEvent(QPaintEvent* event) override;


private:

    // Metadata
    Q_OBJECT
};


/**
 * This class defines a button with drop-down items.
 *
 * @class OfficeMenuDropDownButtonItem
 * @author Nicolas Kogler
 * @date January 8th, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenuDropDownButtonItem : public OfficeMenuButtonItem
{
public:

    /**
     * Initializes a new instance of OfficeMenuDropDownButtonItem.
     *
     * @param parent The parent as menu panel.
     *
     */
    OfficeMenuDropDownButtonItem(OfficeMenuPanel* parent = nullptr);

    /**
     * Frees all resources used by this menu item.
     *
     */
    ~OfficeMenuDropDownButtonItem();


    /**
     * Adds one drop-down menu entry.
     *
     * @param str Text of the entry.
     *
     */
    void addItem(const QString& str);

    /**
     * Removes one drop-down menu entry.
     *
     * @param str Text entry to remove.
     *
     */
    void removeItem(const QString& str);

    /**
     * Removes all drop-down menu entries.
     *
     */
    void removeAll();


protected:

    /**
     * Paints the button icon and text.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void paintEvent(QPaintEvent* event) override;

    /**
     * Hovers the item on entering the widget.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void enterEvent(QEvent* event) override;

    /**
     * Dehovers the item on leaving the widget.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void leaveEvent(QEvent* event) override;

    /**
     * Puts the item into pressed state and shows the drop-down menu.
     *
     * @param event Holds the pressed button.
     *
     */
    virtual void mousePressEvent(QMouseEvent* event) override;

    /**
     * Puts the item into hovered state, or no state
     * if the mouse pointer does not hover the item.
     * Also hides the drop-down menu if previously shown.
     *
     * @param event Holds the released button.
     *
     */
    virtual void mouseReleaseEvent(QMouseEvent* event) override;


private:

    // Members
    OfficeDropDown* m_DropDown;

    // Metadata
    Q_OBJECT
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEMENUITEM_HPP
