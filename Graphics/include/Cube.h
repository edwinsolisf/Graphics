//
//  Cube.h
//  Graphics
//
//  Created by Edwin Solis on 10/6/20.
//

#ifndef Cube_h
#define Cube_h

#include <vector>
#include "vector.h"
#include "matrix.h"
#include "Texture.h"
#include <Mesh.h>

class Cube
{
public:
    Cube(float length, const stml::vec3f position, const std::vector<Texture>& texture);
    //stml::vector<float, 40 + 20> GenVertexBuffer() const;
    //stml::vector<unsigned int, 36> GenIndexBuffer() const;
    stml::matrix<float, 8 * 3, 8> GenVertexData() const;
    stml::vector<unsigned int, 36> GenIndexData() const;
    Mesh GenMesh() const;
private:
    float _length;
    stml::vec3f _position;
    std::vector<Texture> _textures;
};

#endif /* Cube_h */
