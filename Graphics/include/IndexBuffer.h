//
//  IndexBuffer.h
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#ifndef IndexBuffer_h
#define IndexBuffer_h

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    IndexBuffer(const IndexBuffer& other);
    
    ~IndexBuffer();
    
    void Bind() const;
    void Unbind() const;
    
    inline const unsigned int GetCount() const { return _count;}
private:
    unsigned int _id;
    unsigned int _count;
    
    unsigned int* _copy;
};

#endif /* IndexBuffer_h */
