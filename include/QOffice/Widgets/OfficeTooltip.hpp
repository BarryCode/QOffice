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


#ifndef QOFFICE_OFFICETOOLTIP_HPP
#define QOFFICE_OFFICETOOLTIP_HPP


// QOffice headers
#include <QOffice/Config.hpp>

// Qt headers
#include <QWidget>


QOFFICE_BEGIN_NAMESPACE


/**
 * This is the description of the class.
 *
 * @class OfficeTooltip
 * @author Nicolas Kogler
 * @date January 1st, 2016
 *
 */
class QOFFICE_EXPORT OfficeTooltip : public QWidget
{
public:

    /**
     * Initializes a new instance of OfficeTooltip.
     *
     * @param parent The widget to show this tooltip on.
     *
     */
    OfficeTooltip(QWidget* parent = nullptr);

    /**
     * Cleans up all resources used by this tooltip.
     *
     */
    ~OfficeTooltip();


    /**
     * Specifies the heading (in bold) of the tooltip.
     *
     * @param heading The heading string.
     *
     */
    void setHeading(const QString& heading);

    /**
     * Specifies the body text of the tooltip.
     *
     * @param text Descriptive body text.
     *
     */
    void setText(const QString& text);

    /**
     * Specifies the text written next to the help icon.
     * A help text is either clickable or it's signal can
     * be also triggered through an F1 key press. If this
     * string is empty, no help section will be shown.
     *
     * @param text Text next to the help icon.
     *
     */
    void setHelpText(const QString& text);

    /**
     * Specifies the image of the help icon.
     *
     * @param icon Help icon. If null, default will be used.
     *
     */
    void setHelpIcon(const QPixmap& icon);

    /**
     * Specifies the display duration of the tooltip.
     *
     * @param milliseconds The amount of time to display the toolip.
     *
     */
    void setDisplayDuration(int milliseconds);


protected:

    /**
     * Paints the tooltip.
     *
     * @param event Holds nothing we need.
     *
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * If the "help text" link is hovered, it should be
     * marked as a link through displaying an underline.
     *
     * @param event Holds the mouse pointer position.
     *
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * If the "help text" link is pressed, it should
     * trigger a signal that hides the tooltip and
     * shows a help dialog or something of that kind.
     *
     * @param event Holds the pressed mouse button.
     *
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * If the F1 key is pressed, help will be requested.
     *
     * @param event Holds the pressed key.
     *
     */
    void keyPressEvent(QKeyEvent* event) override;

    /**
     * Starts the display duration timer on show.
     *
     * @param event Holds nothing we need.
     *
     */
    void showEvent(QShowEvent* event) override;
    /**
     * Resets the timer if the widget is entered again.
     *
     * @param event Holds nothing we need.
     *
     */
    void enterEvent(QEvent* event) override;

    /**
     * Hides the tooltip after some time when it was left.
     *
     * @param event Holds nothing we need.
     *
     */
    void leaveEvent(QEvent* event) override;


signals:

    /**
     * Is emitted if F1 or the help link is pressed.
     *
     */
    void helpRequested();


private slots:

    void hideTooltip();


private:

    // Members
    QString m_Heading;
    QString m_BodyText;
    QString m_HelpText;
    QPixmap m_HelpIcon;
    int32_t m_Duration;
    QTimer* m_Timer;
    QPixmap m_DropShadow;
    QRect   m_ClientRect;
    QRect   m_BorderRect;
    QRect   m_HeadingRect;
    QRect   m_BodyRect;
    QRect   m_HelpIconRect;
    QRect   m_HelpTextRect;
    QRect   m_SeparatorRect;
    bool    m_IsLinkHovered;

    // Helpers
    void updateRectangles();
    void generateDropShadow();

    // Metadata
    Q_OBJECT
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICETOOLTIP_HPP
