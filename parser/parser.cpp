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

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

/*! \brief Contains all logic and classes for parsing syntax files */
namespace parser
{
    const std::string VersionString = "1.1";


    void cParser::ParseXmlFile( const char* filename )
    {
        rapidxml::file<> xmlFile(filename); // Default template is char
        rapidxml::xml_document<> doc;
        doc.parse<0>(xmlFile.data());

        // todo: version check here
        rapidxml::xml_node<> *pNode = doc.first_node("typecc");
        for( rapidxml::xml_node<> *child = pNode->first_node(); child; child = child->next_sibling() )
        {
            std::shared_ptr<cType> typeData;
            typeData.reset(cType::CreateFromXml(child));
            if( typeData.get() != nullptr )
            {
                // todo: this could allow duplicate definitions
                mSymbolTable[typeData->getName()] = typeData;
            }
            // todo: check that we made something or print diagnostics
        }
    }

}