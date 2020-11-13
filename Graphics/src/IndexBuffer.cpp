//
//  IndexBuffer.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#include "IndexBuffer.h"
#include "Opengl.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
:_count(count), _copy(new unsigned int(0))
{
    GLCALL(glGenBuffers(1, &_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(const IndexBuffer& other)
:_id(other._id), _count(other._count), _copy(other._copy)
{
    (*_copy)++;
}

void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void IndexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer()
{
    if(*_copy == 0)
    {
        GLCALL(glDeleteBuffers(1, &_id));
        delete _copy;
    }
    else
        (*_copy)--;
}
