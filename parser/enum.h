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
    /*! \class cEnum
        \brief Represents an 'enum' type in c/c++.
        \verbatim
        <enum name='myenum'>
            <enum_value name='ENUM_0', value='0' />
            <enum_value name='ENUM_1' />
        </enum>
        \endverbatim
    */
    class cEnum : public cType
    {
    public:
        static cType* CreateFromXml(rapidxml::xml_node<>* node);
        const StringList& getMembers() const;

    private:
        cEnum( std::string name, StringList members );

        StringList mMembers;
    };
}