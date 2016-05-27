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

#include <cstdint>
#include <memory>
#include <string>
#include "utility.h"
#include <vector>

class AST;
typedef std::shared_ptr<AST> ASTPtr;

class ASTVisitor
{
private:
    uint32_t depth_;

protected:
    uint32_t GetDepth() const;
public:
    ASTVisitor();

    virtual void EnterNode(AST* node);
    virtual void VisitNode(AST* node);
    virtual void ExitNode(AST* node);
};


class AST
{
public:
    enum Type
    {
        Type_None,
        Type_Class,
        Type_Enum,
        Type_EnumValue,
        Type_Member,
        Type_Struct,
        Type_Typedef,
        Type_Code
    };

private:
    std::string name_;
    Type type_;
    
    std::vector<ASTPtr> children_;
    StringDict attributes_;

public:
    AST(Type type, const std::string& name);
    
    Type GetType() const;
    void AddChild(ASTPtr child);
    uint32_t GetNumChildren() const;
    ASTPtr GetChild(uint32_t idx);
    const std::string& GetName() const;
    StringDict& GetAttributes();
    void SetAttributes(const StringDict& dict);
    
    void Apply(ASTVisitor& visitor);
};