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
#include <map>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "utility.h"

/*! \brief Contains all logic and classes for parsing syntax files */
namespace parser
{
    /*! \class ParserFactory
        \brief Parses a file and returns a list of types described by the file
        \details Currently the error handling in this class is quite bad. It really does not perform
        any at all. Error checking should be added asap.
    */
    class ParserFactory
    {
    public:
        ~ParserFactory();
        void parseFile( const std::string& filename );
        const TypeList& getTypes() const { return mTypes; }
        void clearTypes() { for( size_t i=0; i<mTypes.size(); ++i ) { delete mTypes[i]; } mTypes.clear(); }
    private:
        void processNode( rapidxml::xml_node<>* node );
        void processClassNode( rapidxml::xml_node<>* node );
        cClass::p_member* processClassMemberNode( StringDict& dict );
        void processTypedefNode( StringDict& dict );
        void processEnumNode( rapidxml::xml_node<>* node );

        TypeList mTypes;
    };
};