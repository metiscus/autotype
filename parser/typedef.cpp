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

#include "typedef.h"

namespace parser
{
    cTypedef::cTypedef( std::string type, std::string name, bool isList, bool isVector ) 
        : cType( name, isList, isVector, "typedef", cTypedef::CreateFromXml )
        , mType( type ) 
    {

    }

    const std::string& cTypedef::getType() const 
    { 
        return mType; 
    }

    cType* cTypedef::CreateFromXml(rapidxml::xml_node<>* node)
    {
        // scoop up typedef info
        StringDict dict;
        extractNodeAttributes( node, dict );

        bool isList   = dict["listType"] == "list";
        bool isVector = dict["listType"] == "vector";
        return new cTypedef( dict["type"], dict["name"], isList, isVector );
    }
}