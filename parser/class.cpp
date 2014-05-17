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

#include "class.h"

namespace parser
{
    //// cMember
    cClass::cMember::cMember( const std::string& name, const std::string& type, bool isList, bool isVector ) 
        : cType(name, isList, isVector, "member", cClass::cMember::CreateFromXml)
        , mTypeName( type )
    {
        ;
    }

    cType* cClass::cMember::CreateFromXml(rapidxml::xml_node<>* node)
    {
        cType *ret = nullptr;

        StringDict values; 
        extractNodeAttributes( node, values );

        bool isList = false, isVector = false;
        if ( values.count( "listType" ) > 0 )
        {
            isList    = (values["listType"] == "list");
            isVector  = (values["listType"] == "vector");
        }

        return new cClass::cMember( values["name"], values["type"], isList, isVector );
    }

    const std::string& cClass::cMember::getTypeName() const 
    { 
        return mTypeName; 
    }


    //// cInterface
    cClass::cInterface::cInterface ( const std::string& returnType, const std::string& name, const MemberList& params )
        : mReturnType( returnType )
        , mParams( params )
        , cType( name, false, false, "interface", cClass::cInterface::CreateFromXml ) 
    {
        ;
    }

    cType* cClass::cInterface::CreateFromXml(rapidxml::xml_node<>* node)
    {
        cType *ret = nullptr;

        // extract interface params
        StringDict ifAttrs;
        extractNodeAttributes( node, ifAttrs );

        MemberList members;
        // slurp in one interface
        if( ifAttrs["name"].length()>0 && ifAttrs["return"].length()>0 )
        {
            for( rapidxml::xml_node<> *param = node->first_node("param"); param; param = param->next_sibling("param") )
            {
                cType *type = cMember::CreateFromXml(param);
                if( type )
                {
                    std::shared_ptr<cMember> memberPtr;
                    memberPtr.reset( dynamic_cast<cMember*>(type) );
                    if (memberPtr.get() != nullptr)
                    {
                        members.push_back(memberPtr);
                    }
                }
            }

            ret = new cClass::cInterface(ifAttrs["return"], ifAttrs["name"], members);
        }

        return ret;
    }

    //// cClass
    cClass::cClass( const std::string& name, const TypeList& members, const TypeList& interfaces, const StringList& bases) 
        : cType(name, false, false, "class", cClass::CreateFromXml)
        , mMembers( members )
        , mInterfaces( interfaces )
        , mBaseClasses( bases ) 
    {
        ;
    }

    cClass::~cClass( ) 
    { 
    }

    cType* cClass::CreateFromXml(rapidxml::xml_node<>* node)
    {      
        // scoop up class info
        StringDict dict;
        extractNodeAttributes( node, dict );  

        // scoop up base classes
        StringList baseClassList;
        if( dict["base"].length() > 0 )
        {        
            const std::string& baseClassStr = dict["base"];
            baseClassList = splitStringList( baseClassStr );
        }

        // scoop up members
        TypeList members;
        for( rapidxml::xml_node<> *child = node->first_node("member"); child; child = child->next_sibling("member") )
        {
            std::shared_ptr<cType> memberPtr;
            memberPtr.reset(cMember::CreateFromXml(child));
            if( memberPtr != nullptr )
            {
                members.push_back(memberPtr);
            }
        }

        // scoop up interfaces
        TypeList interfaces;
        for( rapidxml::xml_node<> *child = node->first_node("interface"); child; child = child->next_sibling("interface") )
        {
            std::shared_ptr<cType> interfacePtr;
            interfacePtr.reset(cInterface::CreateFromXml(child));
            if( interfacePtr != nullptr )
            {
                interfaces.push_back(interfacePtr);
            }
        }

        return new cClass( dict["name"], members, interfaces, baseClassList );
    }

    const TypeList& cClass::getMembers() const 
    { 
        return mMembers; 
    }

    const TypeList& cClass::getInterfaces() const 
    { 
        return mInterfaces; 
    }

    const StringList& cClass::getBaseClasses() const 
    { 
        return mBaseClasses; 
    }
}