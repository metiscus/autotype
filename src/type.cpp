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

#include "type.h"
#include "enum.h"
#include "code.h"
#include "class.h"
#include "typedef.h"

#include <cstdio>

namespace parser
{
    cTypeOptions cType::mOptions;

    cTypeOptions::cTypeOptions()
    {
        Set("use_multifile", false);
        Set("use_old_style_guards", true);
        Set("old_style_sep", std::string("_"));
        Set("old_style_postfix", std::string("INCLUDED"));
    }

    void cTypeOptions::Set(const std::string& name, const char* value)
    {
        mOptionStrings[name] = std::string(value);
    }

    void cTypeOptions::Set(const std::string& name, const std::string& value)
    {
        mOptionStrings[name] = value;
    }

    void cTypeOptions::Set(const std::string& name, const bool& value)
    {
        mOptionBools[name] = value;
    }

    cType::cType( const std::string& name, bool isList, bool isVector )
        : mName ( name )
        , mIsListType( isList )
        , mIsVectorType( isVector )
    {
    }

    cType::~cType()
    {

    }

    cType* cType::CreateFromXml(rapidxml::xml_node<>* node)
    {
        std::string name = node->name();
        if( name == "class" )
        {
            return cClass::CreateFromXml(node);
        }
        else if( name == "enum" )
        {
            return cEnum::CreateFromXml(node);
        }
        else if( name == "typedef" )
        {
            return cTypedef::CreateFromXml(node);
        }
        else if( name == "code" )
        {
            return cCode::CreateFromXml(node);
        }
        else
        {
            return nullptr;
        }
    }

    const std::string& cType::getName( ) const
    {
        return mName;
    }

    bool cType::getIsListType( ) const
    {
        return mIsListType;
    }

    bool cType::getIsVectorType( ) const
    {
        return mIsVectorType;
    }
}
