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
#include "ast.h"



ASTVisitor::ASTVisitor()
    : depth_(0)
{
}

uint32_t ASTVisitor::GetDepth() const
{
    return depth_;
}

void ASTVisitor::EnterNode(AST* node)
{
    ++depth_;
}

void ASTVisitor::VisitNode(AST* node)
{
    
}

void ASTVisitor::ExitNode(AST* node)
{
    --depth_;
}


////////////////////
AST::AST(Type type, const std::string& name)
    : name_(name)
    , type_(type)
{
}        

AST::Type AST::GetType() const
{
    return type_;
}

void AST::AddChild(ASTPtr child)
{
    children_.push_back(child);
}

uint32_t AST::GetNumChildren() const
{
    return children_.size();
}

ASTPtr AST::GetChild(uint32_t idx)
{
    return children_.at(idx);
}

const std::string& AST::GetName() const
{
    return name_;
}

StringDict& AST::GetAttributes()
{
    return attributes_;
}

void AST::SetAttributes(const StringDict& dict)
{
    attributes_ = dict;
}

void AST::Apply(ASTVisitor& visitor)
{
    visitor.EnterNode(this);
    visitor.VisitNode(this);
    for(auto child : children_)
    {
        child->Apply(visitor);
    }
    visitor.ExitNode(this);
}