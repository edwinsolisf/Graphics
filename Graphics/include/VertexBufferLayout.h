//
//  VertexBufferLayout.h
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#ifndef VertexBufferLayout_h
#define VertexBufferLayout_h

#include <vector>
#include "Opengl.h"

struct VertexBufferElements
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    
    VertexBufferElements(unsigned int _type, unsigned int _count, unsigned char _normalized)
    {
        type = _type;
        count = _count;
        normalized = _normalized;
    }

    static unsigned int GetSizeOfType(unsigned int _type)
    {
        switch(_type)
        {
            case GL_FLOAT:
                return sizeof(GLfloat);
            case GL_UNSIGNED_INT:
                return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:
                return sizeof(GLubyte);
            default:
                assert(false);
                return 0;
        }
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
    :_stride(0)
    {
    }
    
    template<typename T>
    void Push(unsigned int count)
    {
        //static_assert(false, "Not a valid Element");
    }
    
    template<>
    void Push<float>(unsigned int count)
    {
        _elements.emplace_back(GL_FLOAT, count, false);
        _stride += count * VertexBufferElements::GetSizeOfType(GL_FLOAT);
    }
    
    template<>
    void Push<unsigned int>(unsigned int count)
    {
        _elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
        _stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_INT);
    }
    
    template<>
    void Push<unsigned char>(unsigned int count)
    {
        _elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
        _stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
    
    inline unsigned int GetStride() const { return _stride; }
    inline const std::vector<VertexBufferElements>& GetElements() const { return _elements; }
    
private:
    std::vector<VertexBufferElements> _elements;
    unsigned int _stride;
};
#endif /* VertexBufferLayout_h */
