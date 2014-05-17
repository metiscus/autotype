#pragma once
/*
    This file is part of AutoType

    AutoType is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    AutoType is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AutoType.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <map>
#include "rapidxml.hpp"
#include "utility.h"

/*! \brief Contains all logic and classes for parsing syntax files */
namespace parser
{
    class cType;
    /*! \brief A typedef for a list of cType pointers */
    typedef std::vector<std::shared_ptr<cType> > TypeList;

    /*! \class cType
        \brief A basic type, represents a naked type in c/c++
        \details This class is used to represent any type that does not require
        special handling of some kind. E.g. int, float.
    */
    class cType 
    { 
    public:
        typedef cType* (*CreationFunction)(rapidxml::xml_node<>* node);
        
        virtual ~cType();
        const std::string& getName( ) const;
        bool getIsListType( ) const;
        bool getIsVectorType( ) const;

        static cType* CreateFromXml (rapidxml::xml_node<>* node);

    protected:
        cType( const std::string& name, bool isList, bool isVector, const char* objectName, CreationFunction objectCreator = nullptr );

        std::string mName;
        bool mIsVectorType;
        bool mIsListType;

        static std::map<std::string, CreationFunction> sTypeMap;
    };
}