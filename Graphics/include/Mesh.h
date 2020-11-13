//
//  Mesh.h
//  Graphics
//
//  Created by Edwin Solis on 11/3/20.
//

#ifndef Mesh_h
#define Mesh_h

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "vector.h"

struct Vertex
{
    stml::vec3f position;
    stml::vec3f normal;
    stml::vec2f texCoords;
    
    Vertex(const stml::vec3f& pos, const stml::vec3f& norm, const stml::vec2f& texcoords)
    :position(pos), normal(norm), texCoords(texcoords)
    {
    }
};

using Index = unsigned int;

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const std::vector<Texture>& textures);
    
    void SetUpMesh() const;
    unsigned int GetIndexCount() const { return _ibo.GetCount(); }
    unsigned int GetTextureCount() const { return _textures.size(); }
    const std::vector<Texture>& GetTextures() const { return _textures; }
    
private:
    VertexArray _vao;
    VertexBuffer _vbo;
    IndexBuffer _ibo;
    
    std::vector<Vertex> _vertices;
    std::vector<Index> _indices;
    std::vector<Texture> _textures;
    static VertexBufferLayout _meshLayout;
};

#endif /* Mesh_h */
