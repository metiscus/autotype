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

#pragma once

#include <map>
#include <string>
#include <vector>

#include "rapidxml.hpp"

/*! \brief A list of strings */
typedef std::vector<std::string> StringList;

/*! \brief A string to string dictionary */
typedef std::map<std::string, std::string> StringDict;

/*!  \brief Reads the contents of a file into a string.
    \param[in] filename The name of the file to open and read.
    \return The contents of the file as a string.
*/
std::string readFile( const std::string& filename );

/*! \brief Extracts the attributes from a rapidxml node, results placed in string dictionary.
    \param[in] node The xml node to extract from.
    \param[in,out] dict The string dictionary to return results with.
*/
void extractNodeAttributes( rapidxml::xml_node<>* node, StringDict& dict );

/*! \brief Splits a string using the separator character.
    \param[in] longstring The main string to split.
    \param[in] sep The chacacter to split.
    \return The list longstring split using , with leading and trailing spaces removed
*/
StringList splitStringList( const std::string& longstring, const char sep = ',' );

/*! \brief Removes leading and trailing whitespace from a string
    \param[in] string 
    \return string without leading or trailing spaces
*/
std::string chompStr( const std::string& string );