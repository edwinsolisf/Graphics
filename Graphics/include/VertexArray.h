//
//  VertexArray.h
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#ifndef VertexArray_h
#define VertexArray_h

#include <vector>
#include <tuple>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
    VertexArray(const VertexBufferLayout& layout);
    VertexArray(const VertexArray& other);
    
    ~VertexArray();
    
    void Bind() const;
    void Unbind() const;
    
    void SetLayout(const VertexBufferLayout& layout);
    void EnableAttributes() const;
    
    
private:
    VertexBufferLayout _layout;
    unsigned int _id;

    unsigned int* _copy;
};

#endif /* VertexArray_h */
