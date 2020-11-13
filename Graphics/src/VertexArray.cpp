//
//  VertexArray.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#include "VertexArray.h"
#include "Opengl.h"

VertexArray::VertexArray(const VertexBufferLayout& layout)
:_layout(layout), _copy(new unsigned int(0))
{
    GLCALL(glGenVertexArrays(1, &_id));
    GLCALL(glBindVertexArray(_id));
}

VertexArray::VertexArray(const VertexArray& other)
:_id(other._id), _layout(other._layout), _copy(other._copy)
{
    (*_copy)++;
}

void VertexArray::Bind() const
{
    GLCALL(glBindVertexArray(_id));
}

void VertexArray::Unbind() const
{
    GLCALL(glBindVertexArray(0));
}

void VertexArray::SetLayout(const VertexBufferLayout &layout)
{
    _layout = layout;
}

void VertexArray::EnableAttributes() const
{
    const auto& elements = _layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); ++i)
    {
        const auto& element = elements[i];
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, _layout.GetStride(), (const void*)offset));
        GLCALL(glEnableVertexAttribArray(i));
        offset += element.count * VertexBufferElements::GetSizeOfType(element.type);
    }
}

VertexArray::~VertexArray()
{
    if(*_copy == 0)
    {
        GLCALL(glDeleteVertexArrays(1, &_id));
        delete _copy;
    }
    else
        (*_copy)--;
}
