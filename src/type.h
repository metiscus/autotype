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

#include <cstdlib>
#include <map>
#include <memory>
#include <rapidxml/rapidxml.hpp>
#include <string>
#include "utility.h"

/*! \brief Contains all logic and classes for parsing syntax files */
namespace parser
{
    template<typename T>
    struct identity { typedef T type; };

    class cTypeOptions
    {
        std::map<std::string, bool> mOptionBools;
        std::map<std::string, std::string> mOptionStrings;
    public:
        cTypeOptions();
        ~cTypeOptions() = default;

        template <typename T>
        const T& Get(const std::string& name)
        {
            return GetOptionValue<T>(name, identity<T>());
        }

        template <typename T>
        const T& Get(const char* name)
        {
            return GetOptionValue<T>(std::string(name), identity<T>());
        }

        void Set(const std::string& name, const std::string& value);
        void Set(const std::string& name, const bool& value);
    private:
        template <typename T>
        const T& GetOptionValue(const std::string&, identity<T>)
        {
            return T();
        }

        const bool& GetOptionValue(const std::string& name, identity<bool>)
        {
            return mOptionBools[name];
        }

        const std::string& GetOptionValue(const std::string& name, identity<std::string>)
        {
            return mOptionStrings[name];
        }
    };

    class cType;
    /*! \brief A typedef for a list of cType pointers */
    typedef std::vector<std::shared_ptr<cType> > TypeList;

    /*! \class cType
        \brief A basic type, represents a naked type in c/c++
        \details This class is used to represent any type that does not require
        special handling of some kind. E.g. int, float.
    */
    class cType
    {
        static cTypeOptions mOptions;

    public:
        virtual ~cType();
        const std::string& getName( ) const;
        bool getIsListType( ) const;
        bool getIsVectorType( ) const;

        static cType* CreateFromXml (rapidxml::xml_node<>* node);

        virtual std::string GenerateCode() const = 0;

        static cTypeOptions& GetOptions() { return mOptions; }

    protected:
        cType( const std::string& name, bool isList, bool isVector );

        std::string mName;
        bool mIsVectorType;
        bool mIsListType;

    };
}
