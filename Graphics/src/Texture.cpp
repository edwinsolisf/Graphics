//
//  Texture.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/6/20.
//

#include <Texture.h>
#include "stb_image.h"
#include <Opengl.h>

Texture::Texture(const char* filePath, const std::string& type)
:_filePath(filePath), _type(type), _buffer(nullptr), _copy(new unsigned int(0))
{
    GLCALL(glGenTextures(1, &_id));
    GLCALL(glBindTexture(GL_TEXTURE_2D, _id));
    
    stbi_set_flip_vertically_on_load(1);
    _buffer = stbi_load(filePath, &_width, &_height, &_bpp, 4);

    GLenum format;
    if (_bpp == 1)
        format = GL_RED;
    else if (_bpp == 3)
        format = GL_RGB8;
    else if (_bpp == 4)
        format = GL_RGBA8;
    
    //GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    //GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    //GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    //GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _buffer));
    
    GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
    //GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    
    if(_buffer)
    {
        stbi_image_free(_buffer);
        _buffer = nullptr;
    }
}

Texture::Texture(const Texture& texture)
:_filePath(texture._filePath), _type(texture._type), _id(texture._id), _buffer(texture._buffer), _width(texture._width), _height(texture._height), _bpp(texture._bpp), _copy(texture._copy)
{
    (*_copy)++;
}

void Texture::Bind(unsigned int slot) const
{
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, _id));
} 

void Texture::Unbind() const
{
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
    if(*_copy == 0)
    {
        GLCALL(glDeleteTextures(1, &_id));
        delete _copy;
        delete _buffer;
    }
    else
        (*_copy)--;
}
