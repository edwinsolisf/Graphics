//
//  VertexBuffer.h
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#ifndef VertexBuffer_h
#define VertexBuffer_h

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(const VertexBuffer& other);
    
    ~VertexBuffer();
    
    void Bind() const;
    void Unbind() const;
    
private:
    unsigned int _id;
    unsigned int* _copy;
};

#endif /* VertexBuffer_h */
