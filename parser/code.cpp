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

#include "code.h"

namespace parser
{
    cType* cCode::CreateFromXml(rapidxml::xml_node<>* node)
    {
        return new cCode(node->value());
    }

    std::string cCode::GenerateCode() const
    {
        return mCodeText;
    }

    const std::string& cCode::getCodeText() const
    {
        return mCodeText;
    }

    cCode::cCode( const std::string& text )
        : cType( "", false, false )
        , mCodeText(text)
    {
        ;
    }
}