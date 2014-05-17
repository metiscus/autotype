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

#include "enum.h"

namespace parser
{
    cEnum::cEnum( std::string name, StringList members ) 
        : cType( name, false, false, "enum", cEnum::CreateFromXml )
        , mMembers( members ) 
    {

    }

    cType* cEnum::CreateFromXml(rapidxml::xml_node<>* node)
    {
        StringDict dict;
        extractNodeAttributes( node, dict );            
        std::string name = dict["name"];

        // parse children
        StringList members;
        int lastEnumValue = 0;
        char buffer[10];
        for( rapidxml::xml_node<> *child = node->first_node("enum_value"); child; child = child->next_sibling("enum_value") )
        {
            StringDict memberAttrs;
            extractNodeAttributes( child, memberAttrs );
            std::string memberName = memberAttrs["name"];
            std::string memberValue;
            if( memberAttrs.count("value") != 1 )
            {
                sprintf( buffer, "%d", lastEnumValue++ );
                memberValue = buffer;
            }
            else
            {
                memberValue = memberAttrs["value"];
                // test to see if there is a valid number in there
                int retVal;
                if( sscanf( memberValue.c_str(), "%d", &retVal ) == 1 ) // sscanf found a number of some kind
                {
                    lastEnumValue = retVal;
                }
                else
                {
                    assert(false); // this is not good really
                    ++lastEnumValue;
                }
            }

            members.push_back( memberName + " = " + memberValue + "," );
        }

        return new cEnum( name, members );        
    }

    const StringList& cEnum::getMembers() const 
    { 
        return mMembers; 
    }
}