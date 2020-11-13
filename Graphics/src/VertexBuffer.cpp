//
//  VertexBuffer.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#include "VertexBuffer.h"
#include "Opengl.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    :_copy(new unsigned int(0))
{
    GLCALL(glGenBuffers(1, &_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, _id));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const VertexBuffer& other)
:_id(other._id), _copy(other._copy)
{
    (*_copy)++;
}
void VertexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, _id));
}

void VertexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
    if(*_copy == 0)
    {
        GLCALL(glDeleteBuffers(1, &_id));
        delete _copy;
    }
    else
        (*_copy)--;
}
