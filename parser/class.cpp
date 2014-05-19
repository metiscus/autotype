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
#include <sstream>

namespace parser
{
    //// cMember
    cClass::cMember::cMember( const std::string& name, const std::string& type, bool isList, bool isVector ) 
        : cType(name, isList, isVector)
        , mTypeName( type )
    {

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

    std::string cClass::cMember::GenerateCode() const
    {
        std::string spacer = "\t\tm";
        std::string lineEnd = ";\n";
        if( !getIsListType() && !getIsVectorType() )
        {
            return getTypeName() + spacer + getName() + lineEnd;
        }
        else if ( getIsListType() )
        {
            return "\tstd::list<" + getTypeName() + ">" + spacer + getName() + lineEnd;
        }
        else if ( getIsVectorType() )
        {
            return "\tstd::vector<" + getTypeName() + ">" + spacer + getName() + lineEnd;
        }

        return "";
    }

    const std::string& cClass::cMember::getTypeName() const 
    { 
        return mTypeName; 
    }


    //// cInterface
    cClass::cInterface::cInterface ( const std::string& returnType, const std::string& name, const MemberList& params )
        : mReturnType( returnType )
        , mParams( params )
        , cType( name, false, false ) 
    {

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

    std::string cClass::cInterface::GenerateCode() const
    {
        std::string ifText = "virtual " + mReturnType + " " + getName() + "( ";
        bool hasParams = false;
        
        // now process any params
        for( auto i=0U; mParams.size() > 0 && i<mParams.size() - 1; ++i )
        {
            ifText += mParams[i]->GenerateCode() + ", ";
        }
        
        ifText += mParams[mParams.size() - 1]->GenerateCode() + " ";

        // end the function
        ifText += " ) = 0;";

        return ifText;
    }

    //// cClass
    cClass::cClass( const std::string& name, const TypeList& members, const TypeList& interfaces, const StringList& bases) 
        : cType(name, false, false)
        , mMembers( members )
        , mInterfaces( interfaces )
        , mBaseClasses( bases ) 
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

    std::string cClass::GenerateCode() const
    {
        std::stringstream file;
        file<<"class " << getName();
        const StringList& baseClasses = getBaseClasses();
        bool isDerived = !baseClasses.empty();
        if( isDerived )
        {
            file<<": ";
            for(int ii=0; ii<baseClasses.size(); ++ii)
            {
                file<<"public "<<baseClasses[ii];
                if( ii<baseClasses.size()-1 )
                {
                    file<<", ";
                }
            }
            file<<"\n";
        }
        file<<"{\n";
        file<<"private:\n";

        // generate members (and accessors ;))
        std::vector<std::string> accessorTexts;

        const TypeList& memberList = getMembers();
        for( auto memberItr = memberList.begin(); memberItr!=memberList.end(); ++memberItr )
        {
            // write actual member out
            file<<"\t"<<(*memberItr)->GenerateCode();

            // write accessors
            std::string getFunc, getFuncConst;
            
            std::string fullType = "";
            cMember* pMember = dynamic_cast<cMember*>((*memberItr).get());
            if( pMember )
            {
                fullType = pMember->getTypeName();
            }
            else
            {
                //ERROR!!!
            }

            if ( (*memberItr)->getIsListType() )
            {
                fullType = "std::list<" + fullType + ">";
            }
            else if ( (*memberItr)->getIsVectorType() )
            {
                fullType = "std::vector<" + fullType + ">";
            }

            getFunc = fullType + "& Get" + (*memberItr)->getName() + "( ) { return m" + (*memberItr)->getName() + ";" + " }\n";            
            getFuncConst = "const " + fullType + "& Get" + (*memberItr)->getName() + "( ) const { return m" + (*memberItr)->getName() + ";" + " }\n";
            accessorTexts.push_back( getFunc );
            accessorTexts.push_back( getFuncConst );

            std::string setFunc;
            setFunc = "void Set" + (*memberItr)->getName() + "(const " + fullType + "& in ) { m" + (*memberItr)->getName() + " = in; }\n";
            accessorTexts.push_back( setFunc );
        }


        file<<"\n";
        file<<"public:\n";
        for( int ii=0; ii<accessorTexts.size(); ++ii )
        {
            file<<"\t"<<accessorTexts[ii];
        }

        auto ifList = getInterfaces();
        // write out interfaces
        for( int ii=0; ii<ifList.size(); ++ii  )
        {
            file<<"\t"<<ifList[ii]->GenerateCode()<<"\n";
        }

        file<<"};\n\n";
        return file.str();
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