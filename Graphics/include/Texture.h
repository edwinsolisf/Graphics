//
//  Texture.h
//  Graphics
//
//  Created by Edwin Solis on 10/6/20.
//

#ifndef Texture_h
#define Texture_h
#include <string>

class Texture
{
public:
    Texture(const char* filePath, const std::string& type = std::string());
    Texture(const Texture& texture);

    ~Texture();
    
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    
    inline const std::string& GetFilePath() const { return _filePath; }
    inline const std::string& GetType() const { return _type; }
    inline unsigned int GetWidth() const { return  _width;}
    inline unsigned int GetHeight() const { return  _height;}
private:
    std::string _filePath;
    std::string _type;
    
    unsigned int* _copy;
    unsigned int _id;
    unsigned char* _buffer;
    int _width, _height, _bpp;
};
#endif /* Texture_h */
