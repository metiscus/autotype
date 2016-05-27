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

#include <string>
#include <map>

template<typename T>
struct identity { typedef T type; };

class Options
{
    std::map<std::string, bool> option_bools_;
    std::map<std::string, std::string> option_strings_;

public:
    Options();
    ~Options() = default;

    template <typename T>
    const T& Get(const std::string& name)
    {
        return GetOptionValue(name, identity<T>());
    }

    template <typename T>
    const T& Get(const char* name)
    {
        return GetOptionValue(std::string(name), identity<T>());
    }

    void Set(const std::string& name, const char* value);
    void Set(const std::string& name, const std::string& value);
    void Set(const std::string& name, const bool& value);

private:
    const bool& GetOptionValue(const std::string& name, identity<bool>);
    const std::string& GetOptionValue(const std::string& name, identity<std::string>);
};