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

#include "type.h"
#include "utility.h"
#include <vector>

/*! \brief Contains all logic and classes for parsing syntax files */
namespace parser
{
    /*! \class cClass
    \brief Represents a 'class' in c/c++.
    \verbatim
    <class name='MyClass' base='BaseClass'>
        <member name='MyIntMember' type='int'/>
        <member name='MyFloatMember' type='float'/>
        <interface name='Serialize' return='bool'>
            <param name='sql' type='SqlPtr'/>
        </interface>
    </class>
    \endverbatim
    */
    class cClass : public cType
    {
    public:

        /*! \class cMember
        \brief Represents a member variable of a class in c/c++
        This can be either a naked type, another class, a typedef or an enum type.
        It is also used as parameters to an interface function.
        */
        class cMember : public cType
        {
        public:
            static cType* CreateFromXml(rapidxml::xml_node<>* node);
            const std::string& getTypeName() const;
            virtual std::string GenerateCode() const;

        private:
            cMember( const std::string& name, const std::string& type, bool isList, bool isVector );
            std::string mTypeName;
        };

        typedef std::vector<std::shared_ptr<cMember> > MemberList;

        /*! \class cInterface
        \brief Represents a member function, most often used for interface classes
        */
        class cInterface : public cType
        {
        public:
            static cType* CreateFromXml(rapidxml::xml_node<>* node);
            virtual std::string GenerateCode() const;

        private:
            cInterface ( const std::string& returnType, const std::string& name, const MemberList& params );

            std::string mReturnType;
            MemberList  mParams;
        };

        static cType* CreateFromXml(rapidxml::xml_node<>* node);
        virtual std::string GenerateCode() const;

        const TypeList& getMembers() const;
        const TypeList& getInterfaces() const;
        const StringList& getBaseClasses() const;

    private:
        cClass( const std::string& name, const TypeList& members, const TypeList& interfaces, const StringList& bases);

        TypeList mMembers;
        TypeList mInterfaces;
        StringList mBaseClasses;
    };
}
