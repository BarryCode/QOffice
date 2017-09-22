////////////////////////////////////////////////////////////////////////////////
//
// QOffice - The office framework for Qt
// Copyright (C) 2016-2018 Nicolas Kogler
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

////////////////////////////////////////////////////////////////////////////////
/// \file Config.hpp
/// \brief This header provides useful macroes for the QOffice framework.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef QOFFICE_CONFIG_HPP
#define QOFFICE_CONFIG_HPP

#include <QtCore>

#if defined(QOFFICE_BUILD_STATIC)
    // If you want to statically link against QOffice, contact a lawyer to
    // retrieve information about the LGPL and what you can do or can not do.
    #define QOFFICE_CORE_API
    #define QOFFICE_DESIGN_API
    #define QOFFICE_WIDGET_API
    #define QOFFICE_PLUGIN_API
#else
    #if defined(QOFFICE_BUILD_SHARED)
        // Export symbols to shared library.
        #define QOFFICE_CORE_API    Q_DECL_EXPORT
        #define QOFFICE_DESIGN_API  Q_DECL_EXPORT
        #define QOFFICE_WIDGET_API  Q_DECL_EXPORT
        #define QOFFICE_PLUGIN_API  Q_DECL_EXPORT
    #else
        // Import symbols to link symbols.
        #define QOFFICE_CORE_API    Q_DECL_IMPORT
        #define QOFFICE_DESIGN_API  Q_DECL_IMPORT
        #define QOFFICE_WIDGET_API  Q_DECL_IMPORT
        #define QOFFICE_PLUGIN_API  Q_DECL_IMPORT
    #endif
#endif

#if defined(Q_CC_MSVC)
    // MSVC is missing some C++11 keywords.
    #define QOFFICE_NOEXCEPT
    #define QOFFICE_CONSTEXPR const
#else
    #define QOFFICE_NOEXCEPT noexcept
    #define QOFFICE_CONSTEXPR constexpr
#endif

// Bitwise operators for strong- and weak-type enums.
#define OffEnumOperators(flags) \
    inline flags operator |  (flags l,flags r) { return (flags) (static_cast<int>(l) | static_cast<int>(r)); } \
    inline flags operator &  (flags l,flags r) { return (flags) (static_cast<int>(l) & static_cast<int>(r)); } \
    inline flags operator ^  (flags l,flags r) { return (flags) (static_cast<int>(l) ^ static_cast<int>(r)); } \
    inline flags operator ~  (flags f)         { return (flags) (static_cast<int>(f)); } \
    inline void  operator |= (flags& l,flags r) { l = l | r; } \
    inline void  operator &= (flags& l,flags r) { l = l & r; } \
    inline void  operator ^= (flags& l,flags r) { l = l ^ r; }

#define OffHasFlag(value,flag)    (value & flag) != 0
#define OffAddFlag(value,flag)    (value |= flag)
#define OffRemoveFlag(value,flag) (value &= ~flag)

// Easy to use constructor macroes.
#define OffDeclareCtor(type) type();
#define OffDeclareDtor(type) virtual ~type();
#define OffDeclareCopy(type) type(const type& t); type& operator =(const type& t);
#define OffDefaultCtor(type) type() = default;
#define OffDefaultDtor(type) virtual ~type() = default;
#define OffDefaultCopy(type) type(const type& t) = default; type& operator =(const type& t) = default;
#define OffDisableCopy(type) type(const type& t) = delete; type& operator =(const type& t) = delete;
#define OffDeclareMove(type) type(type&& t); type& operator=(type&& t);

#if !defined(Q_CC_MSVC)
    #define OffDefaultMove(type) type(type&& t) = default; type& operator=(type&& t) = default;
    #define OffDisableMove(type) type(type&& t) = delete;  type& operator=(type&& t) = delete;
#else
    // MSVC does not support defaulted and disabled move constructors.
    #define OffDefaultMove(type)
    #define OffDisableMove(type)
#endif

inline QString QOfficeGetFunc(const QString& func)
{
    QString output(func);
    int32_t whitespace = func.indexOf(' ');

    if (whitespace != -1)
    {
        output.remove(0, whitespace + 1);
        whitespace = output.indexOf('(');
        output.remove(whitespace, -1);
        whitespace = output.indexOf(' ');
        output.remove(0, whitespace + 1);
    }

    return output;
}

inline QString QOfficeGetClass(const QString& func)
{
    QString output(func);
    int32_t nspace = func.lastIndexOf("::");

    return output.remove(nspace - 1, -1);
}

#if defined(Q_CC_MSVC)
    #define OffCurrentFunc QOfficeGetFunc(__FUNCTION__)
#elif defined(Q_CC_GNU) || defined(Q_CC_CLANG)
    #define OffCurrentFunc QOfficeGetFunc(__PRETTY_FUNCTION__)
#else
    // Use standard C99 __func__ macro as fallback.
    #define OffCurrentFunc QOfficeGetFunc(__func__)
#endif

#define OffCurrentClass QOfficeGetClass(OffCurrentFunc)

#endif

////////////////////////////////////////////////////////////////////////////////
/// \def OffEnumOperators
/// Defines bitwise operators for strong- and weak-type enumerators.
///
/// \def OffHasFlag
/// Determines whether a bitfield contains a specific enum flag.
///
/// \def OffAddFlag
/// Adds a specific enum flag to a bitfield.
///
/// \def OffRemoveFlag
/// Removes a specific enum flag from a bitfield.
///
/// \def OffDeclareCtor
/// Declares a default constructor. Implementation is done in the source file.
///
/// \def OffDeclareDtor
/// Declares a virtual destructor. Implementation is done in the source file.
///
/// \def OffDeclareCopy
/// Declares a copy constructor. Implementation is done in the source file.
///
/// \def OffDeclareMove
/// Declares a move constructor. Implementation is done in the source file.
///
/// \def OffDefaultCtor
/// Generates default code for a default constructor.
///
/// \def OffDefaultDtor
/// Generates default code for a default destructor.
///
/// \def OffDefaultCopy
/// Generates default code for a copy constructor and copy assignment operator.
///
/// \def OffDefaultMove
/// Generates default code for a move constructor and move assignment operator.
///
/// \def OffDisableCopy
/// Prevents the programmer to copy a class instance.
///
/// \def OffDisableMove
/// Prevents the compiler to move a class instance.
///
/// \def OffCurrentFunc
/// Retrieves the beautified name of the current function.
///
/// \def OffCurrentClass
/// Retrieves the beautified name of the current class.
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// \defgroup Core Core
/// \brief Contains all core-related classes.
/// \details Defines the core functionality within the framework.
///
/// \defgroup Design Design
/// \brief Contains all design-related classes.
/// \details Defines reusable and standardized design functionality.
///
/// \defgroup Widget Widget
/// \brief Contains all widget-related classes.
/// \details Defines flat-styled widgets, dialogs and components.
///
/// \defgroup Plugin Plugin
/// \brief Contains all plugin-related classes.
/// \details Defines plugin classes written for the Qt designer.
///
////////////////////////////////////////////////////////////////////////////////
