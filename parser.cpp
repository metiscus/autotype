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

#include "parser.h"

#include <iostream>
#include <map>

using namespace rapidxml;

parser::ParserFactory::~ParserFactory()
{
    clearTypes();
}

void parser::ParserFactory::parseFile( const std::string& filename )
{
    std::string strFileText = readFile( filename );
    const size_t fileTextLength = strFileText.length() + 1;
    char *fileText = (char*)malloc( fileTextLength );
    if( fileText )
    {
        strncpy( fileText, strFileText.c_str(), fileTextLength );

        // parse the document
        xml_document<> doc;
        doc.parse<0>(fileText);

        xml_node<> *root = doc.first_node("typecc");

        if(root)
        {
            xml_node<> *child = root->first_node();
            while( child )
            {
                processNode(child);
                child = child->next_sibling();
            }
        }
    }

    delete [] fileText;
}

void  parser::ParserFactory::processNode( rapidxml::xml_node<>* node )
{
    assert(node);

    std::string name = node->name();

    StringDict dict;
    extractNodeAttributes( node, dict ); 

    if( dict.count("name") > 0 )
    {
        if( name == "typedef" )
        {
            StringDict dict;
            extractNodeAttributes( node, dict );            
            processTypedefNode( dict );
        }
        else if ( name == "class" )
        {
            processClassNode( node );
        }
        else if ( name == "enum" )
        {
            processEnumNode( node );
        }
        else
        {
            printf("Unknown node type: %s\n", node->name());
        }            
    }
}

parser::cClass::p_member* parser::ParserFactory::processClassMemberNode( StringDict& dict )
{
    //TODO: This needs to be changed to hande case sensitivity
    bool isList = false, isVector = false;
    if ( dict.count( "listType" ) > 0 )
    {
        isList = (dict["listType"] == "list");
        isVector  = (dict["listType"] == "vector");
    }

    return new cClass::p_member( dict["name"], dict["type"], isList, isVector );
}

void  parser::ParserFactory::processClassNode( rapidxml::xml_node<>* node )
{
    StringDict dict;
    extractNodeAttributes( node, dict );  
    std::string name = dict["name"];

    // scoop up base classes
    StringList baseClassList;
    if( dict["base"].length() > 0 )
    {        
        const std::string& baseClassStr = dict["base"];
        baseClassList = splitStringList( baseClassStr );
    }

    TypeList memberList;

    // scoop up members
    StringDict members;
    for( xml_node<> *child = node->first_node("member"); child; child = child->next_sibling("member") )
    {
        StringDict memberAttrs;
        extractNodeAttributes( child, memberAttrs );
        if( memberAttrs["name"].length()>0 && memberAttrs["type"].length()>0 )
        {
            memberList.push_back( processClassMemberNode( memberAttrs ) );
        }
    }

    // scoop up interfaces
    StringList interfaces;
    for( xml_node<> *child = node->first_node("interface"); child; child = child->next_sibling("interface") )
    {
        // extract interface params
        StringDict ifAttrs;
        extractNodeAttributes( child, ifAttrs );

        // slurp in one interface
        if( ifAttrs["name"].length()>0 && ifAttrs["return"].length()>0 )
        {
            std::string ifText = "virtual " + ifAttrs["return"] + " " + ifAttrs["name"] + "(";
            bool hasParams = false;
            // now process any params
            for( xml_node<> *param = child->first_node("param"); param; param = param->next_sibling("param") )
            {
                StringDict paramAttrs;
                extractNodeAttributes( param, paramAttrs );
                if( paramAttrs["name"].length()>0 && paramAttrs["type"].length()>0 )
                {
                    ifText += " " + paramAttrs["type"] + " " + paramAttrs["name"] + ",";
                    hasParams = true;
                }
            }
            if( hasParams )
            {
                ifText = ifText.substr( 0, ifText.length() - 1 ); // trim final ,
            }

            // end the function
            ifText += " )";

            // save text of interface
            interfaces.push_back(ifText);
        }
    }

    // handle making the destructor virtual (this is needed)
    if( interfaces.size() > 0 )
    {
        std::string vdtor = "virtual ~" + name + "( ) { }";
        interfaces.push_back( vdtor );
    }
    mTypes.push_back( new cClass( name, false, false, memberList, interfaces, baseClassList ) );
}

void  parser::ParserFactory::processTypedefNode( StringDict& dict )
{
    //
    bool isList = false, isVector = false;
    std::string startName, startTypeName;
    startName     = dict["name"];
    startTypeName = dict["type"];

    if ( dict.count( "listType" ) > 0 )
    {
        isList = (dict["listType"] == "list");
        isVector  = (dict["listType"] == "vector");
    }

    p_type *startType = NULL;

    // lookup
    bool hasChanged = false;
    for( ; ; )
    {    
        hasChanged = false;
        for( int ii=0; ii<mTypes.size(); ++ii )
        {
            if( mTypes[ii]->getName() == startTypeName )
            {
                // we found an existing type of the same name
                startType = mTypes[ii];

                // if it is a typedef, we need to recurse further
                cTypedef *pTypedef = dynamic_cast<cTypedef*>(startType);
                if ( pTypedef )
                {
                    hasChanged = true; // continue iterating until we run out
                    startTypeName = pTypedef->getType().getName();                    
                }
            }
        }
        if( hasChanged == false )
            break;
    }

    if( startType == NULL )
    {
        p_type baseType( startTypeName, isList, isVector );
        cTypedef *pTypedef = new cTypedef( baseType, startName );
        mTypes.push_back( pTypedef );
    }
    else
    {
        p_type baseType( startTypeName, false, false );
        cTypedef *pTypedef = new cTypedef( baseType, startName );        
        mTypes.push_back( pTypedef );
    }
}
