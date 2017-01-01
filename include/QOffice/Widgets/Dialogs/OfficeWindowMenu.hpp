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


#ifndef QOFFICE_OFFICEWINDOWMENU_HPP
#define QOFFICE_OFFICEWINDOWMENU_HPP


// QOffice headers
#include <QOffice/Widgets/Enums/OfficeWindowEnums.hpp>
#include <QOffice/Widgets/OfficeTooltip.hpp>

// Qt headers
#include <QWidget>
#include <QTimer>


QOFFICE_BEGIN_NAMESPACE


class OfficeWindow;
class OfficeWindowMenuItem;


/**
 * This class defines a menu widget on the window title bar.
 * It is not intended to be used outside this library.
 *
 * @class OfficeWindowMenu
 * @author Nicolas Kogler
 * @date December 29th, 2016
 *
 */
class OfficeWindowMenu : public QWidget
{
public:

    /**
     * Initializes a new instance of OfficeWindowMenu.
     *
     * @param parent The parent office window.
     *
     */
    explicit OfficeWindowMenu(OfficeWindow* parent = nullptr);

    /**
     * Disposes of all menu items.
     *
     */
    virtual ~OfficeWindowMenu();


    /**
     * Retrieves all the menu items on the menu.
     *
     * @returns a list of item references.
     *
     */
    const QList<OfficeWindowMenuItem*>& items() const;

    /**
     * Specifies all the menu items on the menu.
     *
     * @param items
     */
    void setItems(const QList<OfficeWindowMenuItem*>& items);


    /**
     * Retrieves the perfect size for this widget.
     *
     * @returns the perfect menu size.
     *
     */
    QSize sizeHint() const;


protected:

    /**
     * Paints all the items on this menu.
     *
     * @param event Holds nothing we need.
     *
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * Changes the hover states of the items.
     *
     * @param event Holds the mouse position.
     *
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * Changes the press states of the items.
     *
     * @param event Holds the pressed button.
     *
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * Changes the press states of the items.
     *
     * @param event Holds the released button.
     *
     */
    void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * Puts the state of all items to normal.
     *
     * @param event Holds nothing we need.
     *
     */
    void leaveEvent(QEvent* event) override;


signals:

    /**
     * Is emitted if the user clicks a menu item.
     *
     * @param index Index of the item that was clicked.
     *
     */
    void menuItemClicked(int index);

    /**
     * Is emitted if help was requested in a tooltip
     * of a menu item.
     *
     * @param index Index of the item that requested help.
     *
     */
    void helpRequested(int index);


private slots:

    void showTooltip();
    void onHelpRequested();


private:

    // Members
    QList<OfficeWindowMenuItem*> m_Items;
    OfficeWindowMenuItem* m_HoveredItem;
    OfficeWindow*         m_Parent;
    OfficeTooltip*        m_Tooltip;
    QTimer*               m_Timer;

    // Metadata
    Q_OBJECT
};


/**
 * Defines one item on the window menu. Does only
 * consist of an icon, which is either enabled or disabled
 * and can show a tooltip when hovered for a specific time span.
 *
 * @class OfficeWindowMenuItem
 * @author Nicolas Kogler
 * @date December 29th, 2016
 *
 */
class QOFFICE_EXPORT OfficeWindowMenuItem
{
public:

    /**
     * Initializes a new instance of OfficeWindowMenuItem.
     *
     * @param menu The menu that holds this menu item.
     *
     */
    OfficeWindowMenuItem();


    /**
     * Retrieves the icon of this menu item.
     *
     * @returns the current item icon.
     *
     */
    const QPixmap& icon() const;

    /**
     * Retrieves the tooltip string.
     * Empty string means no tooltip.
     *
     * @returns the tooltip.
     *
     */
    const QString& tooltip() const;

    /**
     * Determines whether this item is enabled.
     *
     * @returns true if this item is enabled.
     *
     */
    bool isEnabled() const;


    /**
     * Specifies the icon to display as item.
     *
     * @param img Preferrably a fully white icon.
     *
     */
    void setIcon(const QPixmap& img);

    /**
     * Specifies the tooltip string. If one passes an
     * empty string, no tooltip is being shown.
     *
     * @param str Informative text to display.
     *
     */
    void setTooltip(const QString& str);

    /**
     * Declares this item as either enabled or disabled.
     *
     * @param enabled False in order to disable item.
     *
     */
    void setEnabled(bool enabled);


private:

    // Members
    QPixmap m_Icon;
    QString m_Tooltip;
    QRect   m_Bounds;
    bool    m_IsEnabled;

    OfficeWindowMenu* m_Parent;
    WinButtonState    m_State;

    // Friends
    friend class OfficeWindowMenu;
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEWINDOWMENU_HPP
