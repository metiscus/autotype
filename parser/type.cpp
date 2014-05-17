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

namespace parser
{
    std::map<std::string, cType::CreationFunction> cType::sTypeMap;

    cType::cType( const std::string& name, bool isList, bool isVector, const char* objectName, CreationFunction objectCreator ) 
        : mName ( name )
        , mIsListType( isList )
        , mIsVectorType( isVector ) 
    {
        sTypeMap[objectName] = objectCreator;
    }

    cType::~cType()
    {

    }

    cType* cType::CreateFromXml(rapidxml::xml_node<>* node)
    {
        cType *ret = nullptr;

        StringDict values; 
        extractNodeAttributes( node, values );
        auto funcItr = sTypeMap.find(values["name"]);
        if( funcItr != sTypeMap.end() )
        {
            ret = funcItr->second(node);
        }

        return ret;
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