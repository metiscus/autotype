#pragma once
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

#include "utility.h"
#include "parser/type.h"

/*! \brief Contains all logic and classes for parsing syntax files */
namespace parser
{
    class cParser
    {
    public:
        void ParseXmlFile( const char* filename );
         
        typedef std::map<std::string, std::shared_ptr<cType> > SymbolTable;

    private:
        SymbolTable mSymbolTable;
    };
}