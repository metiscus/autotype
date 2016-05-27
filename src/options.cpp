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
#include "options.h"


Options::Options()
{
    Set("use_multifile", false);
    Set("use_old_style_guards", true);
    Set("old_style_sep", std::string("_"));
    Set("old_style_postfix", std::string("INCLUDED"));
}

void Options::Set(const std::string& name, const char* value)
{
    option_strings_[name] = std::string(value);
}

void Options::Set(const std::string& name, const std::string& value)
{
    option_strings_[name] = value;
}

void Options::Set(const std::string& name, const bool& value)
{
    option_bools_[name] = value;
}

const bool& Options::GetOptionValue(const std::string& name, identity<bool>)
{
    return option_bools_[name];
}

const std::string& Options::GetOptionValue(const std::string& name, identity<std::string>)
{
    return option_strings_[name];
}