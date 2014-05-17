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

#include "parser/type.h"
#include "utility.h"
#include <vector>

/*! \brief Contains all logic and classes for parsing syntax files */
namespace parser
{
    /*! \class cTypedef
        \brief Represents a 'typedef' in c/c++.
        \verbatim
        <typedef name='U32' type='int'/>
        \endverbatim
    */
    class cTypedef : public cType
    {
    public:
        static cType* CreateFromXml(rapidxml::xml_node<>* node);
        const std::string& getType() const;

    private:
        cTypedef( std::string type, std::string name, bool isList, bool isVector );
        std::string mType;
    };
}