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

#include "utility.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace rapidxml;

std::string readFile( const std::string& filename )
{
    std::ifstream inFile ( filename.c_str() );
    std::string ret;
    if( inFile.is_open() )
    {
        while( !inFile.eof() )
        {
            std::string line;
            std::getline( inFile, line );
            ret = ret + line + "\n";
        }
    }

    return ret;
}

void extractNodeAttributes( rapidxml::xml_node<>* node, StringDict& dict )
{
    assert( node );
    for( xml_attribute<> *attr = node->first_attribute(); attr!=NULL; attr = attr->next_attribute() )
    {
        dict[attr->name()] = attr->value();
    }
}

StringList splitStringList( const std::string& longstring, const char sep )
{
    StringList ret;
    std::istringstream is (longstring);
    std::string token;
    while( std::getline(is, token, sep) )
    {
        ret.push_back( chompStr(token) );
    }

    return ret;
}

std::string chompStr( const std::string& string )
{
    if( string.empty() )
    {
        return "";
    }

    if( string == " " )
    {
        return "";
    }

    std::string::size_type beg = string.find_first_not_of( " " );
    if( beg == std::string::npos )
    {
        return "";
    }

    std::string::size_type end = string.find_last_not_of( " " );


    return string.substr( beg, end-beg+1 );
}

std::string stringToUpper( const std::string& string )
{
    std::string upper = string;
    std::transform(upper.begin(), upper.end(), upper.begin(), toupper);
    return upper;
}

void explodePath(const std::string& fullpath, std::string& path, std::string& file, std::string& extension)
{
#ifdef WIN32
    const std::string PathSepChar = "\\";
#else
    const std::string PathSepChar = "/";
#endif
    std::string path_in = fullpath;
    size_t itr = path_in.rfind(PathSepChar);
    if(itr != std::string::npos)
    {
        path = path_in.substr(0, itr);
        path_in = path_in.substr(itr + 1, path_in.length() - itr - 1);
    }

    itr = path_in.rfind(".");
    if(itr != std::string::npos)
    {
        file = path_in.substr(0, itr);
        extension = path_in.substr(itr + 1, path_in.length() - itr - 1);
    }
    else
    {
        file = path_in;
    }
}
