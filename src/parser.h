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

#include <list>
#include <string>

#include "utility.h"
#include "type.h"

/*! \brief Contains all logic and classes for parsing syntax files */
namespace parser
{
    class cParser
    {
    public:
        cParser() = default;
        ~cParser() = default;
        void ParseXmlFile( const char* filename );
        void GenerateFile( const char* filename );

        typedef std::list<std::shared_ptr<cType> > TypeList;

    private:
        TypeList mTypes;
    };
}
