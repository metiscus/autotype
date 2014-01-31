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
    class p_type;
    /*! \brief A typedef for a list of p_type pointers */
    typedef std::vector<p_type*> TypeList;

    /*! \class p_type
        \brief A basic type, represents a naked type in c/c++
        \details This class is used to represent any type that does not require
        special handling of some kind. E.g. int, float.
    */
    class p_type 
    { 
    public:
        p_type( const std::string& name, bool isList, bool isVector ) : mName ( name ), mIsListType( isList ), mIsVectorType( isVector ) { }
        virtual ~p_type() { };
        const std::string& getName( ) const { return mName; }
        bool getIsListType( ) const { return mIsListType; }
        bool getIsVectorType( ) const { return mIsVectorType; }

    protected:
        std::string mName;
        bool mIsVectorType;
        bool mIsListType;
    };

    /*! \class p_class
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
    class p_class : public p_type
    {
    public:
        /*! \class p_member
            \brief Represents a member variable of a class in c/c++
            This can be either a naked type, another class, a typedef or an enum type.
            It is also used as parameters to an interface function.
        */
        class p_member : public p_type 
        {
        public:
            p_member( const std::string& name, const std::string& type, bool isList, bool isVector ) :
              p_type(name, isList, isVector), mTypeName( type ) { };
              const std::string& getTypeName() const { return mTypeName; }
        private:
            std::string mTypeName;
        };

        typedef std::vector<p_member> MemberList;

        /*! \class p_interface
            \brief Represents a member function, most often used for interface classes
        */
        class p_interface : public p_type
        {
        public:
            p_interface ( const std::string& ret_type, const std::string& name, const MemberList& params ):
              mReturnType( ret_type ), mParams( params ), p_type( name, false, false ) { }
        
        private:
            std::string mReturnType;
            MemberList  mParams;
        };

        p_class( const std::string& name, 
                 bool isList, 
                 bool isVector, 
                 const TypeList& members, 
                 const StringList& interfaces,
                 const StringList& bases) : 
            p_type(name, isList, isVector), mMembers( members ), mInterfaces( interfaces ), mBaseClasses( bases ) { }
        virtual ~p_class( ) { for( size_t i=0; i<mMembers.size(); ++i ) { delete mMembers[i]; } mMembers.clear(); }
        const TypeList& getMembers() const { return mMembers; }
        const StringList& getInterfaces() const { return mInterfaces; }
        const StringList& getBaseClasses() const { return mBaseClasses; }
    private:
        TypeList   mMembers;
        StringList mInterfaces;
        StringList mBaseClasses;
    };

    /*! \class p_typedef
        \brief Represents a 'typedef' in c/c++.
        \verbatim
        <typedef name='myenum' type='int'/>
        \endverbatim
    */
    class p_typedef : public p_type
    {
    public:
        p_typedef( p_type type, std::string name ) : p_type( name, false, false ), mType( type ) { }
        const p_type& getType() const { return mType; }
    private:
        p_type mType;
    };

    /*! \class p_enum
        \brief Represents an 'enum' type in c/c++.
        \verbatim
        <enum name='myenum'>
            <enum_value name='ENUM_0', value='0' />
            <enum_value name='ENUM_1' />
        </enum>
        \endverbatim
    */
    class p_enum : public p_type
    {
    public:
        p_enum( std::string name, StringList members ) : p_type( name, false, false ), mMembers( members ) { }
        const StringList& getMembers() const { return mMembers; }
    private:
        StringList mMembers;
    };

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
        p_class::p_member* processClassMemberNode( StringDict& dict );
        void processTypedefNode( StringDict& dict );
        void processEnumNode( rapidxml::xml_node<>* node );

        TypeList mTypes;
    };
};