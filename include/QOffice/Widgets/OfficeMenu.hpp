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


#ifndef QOFFICE_OFFICEMENU_HPP
#define QOFFICE_OFFICEMENU_HPP


// QOffice headers
#include <QOffice/Interfaces/IOfficeWidget.hpp>
#include <QOffice/Widgets/OfficeMenuTopItem.hpp>

// Qt headers
#include <QWidget>
#include <QtXml/QDomElement>


QOFFICE_BEGIN_NAMESPACE


class OfficeMenuEventArgs;


/**
 * Displays a ribbon-like menu, with panels and their items.
 *
 * @class OfficeMenu
 * @author Nicolas Kogler
 * @date January 1st, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenu : public QWidget, public IOfficeWidget
{
public:

    /**
     * Initializes a new instance of OfficeMenu.
     *
     * @param parent The parent widget.
     *
     */
    explicit OfficeMenu(QWidget* parent = nullptr);

    /**
     * Frees all resources used by OfficeMenu.
     *
     */
    ~OfficeMenu();


    /**
     * Returns the perfect size for this menu.
     *
     * @returns the perfect menu size.
     *
     */
    QSize sizeHint() const override;


    /**
     * Retrieves the item XML.
     *
     * @returns the item XML.
     *
     */
    QString itemXml() const;

    /**
     * Loads all the panels and items from an XML file. The
     * docs on the XML tree structure can be found on github.
     *
     * @param xml The XML string to parse.
     * @returns true on success.
     *
     */
    bool loadFromXml(const QString& xml);


    /**
     * Expands the menu and increases its height.
     *
     */
    void expand(OfficeMenuTopItem* itemToExpand);

    /**
     * Collapses the menu and decreases its height.
     *
     */
    void collapse();


    /**
     * Reimplemented pure virtual function from IOfficeWidget.
     * Retrieves the accent color for this office widget.
     *
     * @returns the current accent color.
     *
     */
    Accent accent() const override;

    /**
     * Reimplmented pure virtual function from IOfficeWidget.
     * Specifies the new accent color for this office widget.
     * Should never be called manually by the programmer, except
     * within the top-level OfficeWindow instance.
     *
     * @param accent New accent color of the office widget.
     *
     */
    void setAccent(Accent accent) override;


    /**
     * Adds one item to the menu items.
     *
     * @param item Item to append.
     *
     */
    void addItem(OfficeMenuTopItem* item);

    /**
     * Inserts one item at the given position.
     *
     * @param pos Position to insert item to.
     * @param item Item to insert.
     *
     */
    void insertItem(int pos, OfficeMenuTopItem* item);

    /**
     * Removes the item at the given index.
     *
     * @param index Index of the item to remove.
     *
     */
    void removeItem(int index);

    /**
     * Removes the given item.
     *
     * @param item Item to remove.
     *
     */
    void removeItem(OfficeMenuTopItem* item);


    /**
     * Retrieves a menu item by its identifier. The identifier
     * must be unique across the entire menu. If there happen to
     * be multiple items with the same identifier, the first one
     * is returned.
     *
     * Equivalent to 'item = officeMenu["identifier"];'
     *
     * @param identifier Unique identifier of the item to get.
     * @returns the first item with the given identifier.
     *
     */
    OfficeMenuItem* menuItemById(const QString& identifier);


    /**
     * Equivalent to 'item = officeMenu.meuItemById("identifier");'
     * Note: Office menu must be given as reference or object, the
     * subscript operator for pointer types is used instead otherwise.
     *
     * @param identifier Unique identifier of the item to get.
     * @returns the first item with the given identifier.
     *
     */
    OfficeMenuItem* operator[](const QString& identifier);


signals:

    /**
     * Is emitted if the user interacts with a menu item.
     * That can be entering text in a textbox, clicking a
     * button or choosing a drop-down menu item.
     *
     * @param eventArgs Contains useful data for identifying
     *        the event type and the item which was interacted with.
     *        It is recommended to carefully read the documentation
     *        about the OfficeMenuEventArgs members.
     */
    void itemEvent(OfficeMenuEventArgs* eventArgs);


protected:

    /**
     * Renders the menu bar background in the accent color.
     *
     * @param event Holds nothing we need.
     *
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * Resizes the sub-menu with the menu.
     *
     * @param event Holds nothing we need.
     *
     */
    void resizeEvent(QResizeEvent* event) override;

    /**
     * Recalculates all item locations of all panels
     * and all sub-menus upon showing the menu.
     *
     * @param event Holds nothing we need.
     *
     */
    void showEvent(QShowEvent* event) override;


private:

    // Members
    QMap<QString, OfficeMenuItem*> m_IdMap;
    QList<OfficeMenuTopItem*> m_Items;
    QString m_ItemXml;
    bool m_IsExpanded;

    // Metadata
    Q_OBJECT
    Q_PROPERTY(QString ItemXml READ itemXml WRITE loadFromXml)

    // Helpers
    OfficeMenuItem* xmlGetItem(QDomElement* itemElem);
};


/**
 * Holds information about an office menu item event.
 *
 * @class OfficeMenuEventArgs
 * @author Nicolas Kogler
 * @date January 4th, 2016
 *
 */
class QOFFICE_EXPORT OfficeMenuEventArgs
{
public:

    /** Type of the occured event. */
    enum Type
    {
        ButtonClick,
        DropdownItemClicked,
        TextboxTextChanged
    };


    /**
     * Creates a new event args instance with the given information.
     *
     * @param iid Identifier of the item in question.
     * @param data Miscellaneous data.
     * @param type Type of the event.
     *
     */
    OfficeMenuEventArgs(const QString& iid, const QString& data, Type type);


    /**
     * Retrieves the identifier of the interacted item.
     *
     * @returns the item identifier
     *
     */
    const QString& itemId() const;

    /**
     * Retrieves the type of the occured event.
     *
     * @returns the event type.
     *
     */
    Type type() const;

    /**
     * Retrieves the miscellaneous data of the event.
     * The data depends on the type of the item and the event:
     * ButtonClick: Data is empty as not needed.
     * DropdownItemClicked: Name of the item that was clicked.
     * TextboxTextChanged: Current text of the textbox.
     * GroupButtonClicked: Identifier of the clicked group-button.
     *
     * @returns the miscellaneous data.
     *
     */
    const QString& data() const;


private:

    // Members
    QString m_ItemId;
    QString m_Data;
    Type    m_Type;
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEMENU_HPP
