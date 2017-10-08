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
#ifndef QOFFICE_WIDGET_OFFICEMENUHEADER_HPP
#define QOFFICE_WIDGET_OFFICEMENUHEADER_HPP

#include <QOffice/Config.hpp>
#include <QWidget>

class OfficeMenu;
class OfficeMenuPanel;
class QGraphicsOpacityEffect;
class QHBoxLayout;
namespace priv { class PanelBar; }

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuHeader
/// \brief OfficeMenuHeaderdesc
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date September 30, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QOFFICE_WIDGET_API OfficeMenuHeader : public QWidget
{
public:

    OffDefaultDtor(OfficeMenuHeader)
    OffDisableCopy(OfficeMenuHeader)
    OffDisableMove(OfficeMenuHeader)

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new instance of OfficeMenuHeader and specifies the \p
    /// parent of this header.
    ///
    /// \param[in] parent The ::OfficeMenu this header belongs to.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuHeader(OfficeMenu* parent);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the unique identifier of this object.
    ///
    /// \return The unique identifier.
    ///
    ////////////////////////////////////////////////////////////////////////////
    int id() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether this item is selected and expanded.
    ///
    /// \return True if this item is selected, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool isSelected() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the displayed text of this header.
    ///
    /// \return The text of this header.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& text() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the parent menu of this header.
    ///
    /// \return The parent menu.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenu* menu() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the panel that has the specified \p id.
    ///
    /// \param[in] id The id of the panel to fetch.
    /// \return The pointer to the panel with the given \p id.
    ///
    /// \remarks Yields nullptr if the given \p id is invalid.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuPanel* panelById(int id) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the panel that has the specified \p id. Is equivalent to
    /// calling OfficeMenuHeader::panelById(id).
    ///
    /// \param[in] id The id of the panel to fetch.
    /// \return The pointer to the panel with the given \p id.
    ///
    /// \remarks Yields nullptr if the given \p id is invalid.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuPanel* operator [](int id) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the unique identifier of this object.
    ///
    /// \param[in] id The new unique identifier.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setId(int id);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the displayed text of this header.
    ///
    /// \param[in] text New displayed text.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setText(const QString& text);

    ////////////////////////////////////////////////////////////////////////////
    /// Appends a new panel to this header item.
    ///
    /// \param[in] id The unique identifier of the new panel.
    /// \param[in] text The displayed text of the new panel.
    ///
    /// \return The pointer to the newly created ::OfficeMenuPanel.
    ///
    /// \remarks If the given \p id already exists, nullptr is returned.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuPanel* appendPanel(int id, const QString& text);

    ////////////////////////////////////////////////////////////////////////////
    /// Inserts a new panel into this header item. If the given position is
    /// invalid, this is equivalent to calling OfficeMenuHeader::appendPanel.
    ///
    /// \param[in] pos The position to insert the new panel to.
    /// \param[in] id The unique identifier of the new panel.
    /// \param[in] text The displayed text of the new panel.
    ///
    /// \return The pointer to the newly created ::OfficeMenuPanel.
    ///
    /// \remarks If the given \p id already exists, nullptr is returned.
    ///
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenuPanel* insertPanel(int pos, int id, const QString& text);

    ////////////////////////////////////////////////////////////////////////////
    /// Removes the panel with the specified \p id.
    ///
    /// \param[in] id The id of the panel to remove.
    /// \return True if successfully removed, false otherwise.
    ///
    /// \remarks Yields false if the given \p id is invalid.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool removePanel(int id);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the preferred size for this header.
    ///
    /// \return The preferred widget size.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QSize sizeHint() const override;

signals:

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted once this header is expanded.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void headerExpanded();

    ////////////////////////////////////////////////////////////////////////////
    /// This signal is emitted once this header is collapsed.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void headerCollapsed();

protected:

    virtual void paintEvent(QPaintEvent*) override;
    virtual void enterEvent(QEvent*) override;
    virtual void leaveEvent(QEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;

private slots:

    void animationInFinished();
    void animationOutFinished();

private:

    ////////////////////////////////////////////////////////////////////////////
    // Functions
    ////////////////////////////////////////////////////////////////////////////
    void expand(QHBoxLayout*,bool);
    void collapse(QHBoxLayout*,bool);

    ////////////////////////////////////////////////////////////////////////////
    // Members
    ////////////////////////////////////////////////////////////////////////////
    OfficeMenu*             m_parent;       ///< Defines the parent office menu.
    priv::PanelBar*         m_panelBar;     ///< Defines the panel bar widget.
    QHBoxLayout*            m_panelLayout;  ///< Defines the panel layout.
    QGraphicsOpacityEffect* m_effectIn;     ///< Defines the fade in opac effect.
    QPropertyAnimation*     m_animationIn;  ///< Defines the fade in animation.
    QPropertyAnimation*     m_animationOut; ///< Defines the fade out animation.
    QList<OfficeMenuPanel*> m_panels;       ///< Holds all panels of this header.
    QString                 m_text;         ///< Defines the displayed header text.
    bool                    m_isHovered;    ///< Determines whether its hovered.
    bool                    m_isSelected;   ///< Determines whether its selected.
    int                     m_id;           ///< Defines the unique ID.

    ////////////////////////////////////////////////////////////////////////////
    // Metadata
    ////////////////////////////////////////////////////////////////////////////
    Q_OBJECT

    friend class OfficeMenu;
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class OfficeMenuHeader
/// \ingroup Widget
///
/// $Detailedclassdesc
///
/// \code
/// <example_code>
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
