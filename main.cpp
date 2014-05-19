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

#include <cstdio>
#include <map>
#include <string>

#include "parser/parser.h"

int main ( int argc, char** argv )
{
    if( argc != 3 )
    {
        printf("autotype (input.xml) (output.h)\nPlease see the documentation for more details.\n");
        return 1;
    }
  
    // parse the xml file into nodes
    parser::cParser xmlParser;
    xmlParser.ParseXmlFile(argv[1]);
    xmlParser.GenerateFile(argv[2]);

    return 0;
}
