//
//  Mesh.cpp
//  Graphics
//
//  Created by Edwin Solis on 11/3/20.
//

#include <Mesh.h>

VertexBufferLayout Mesh::_meshLayout;
static bool layoutInit = false;

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const std::vector<Texture>& textures)
    :_vbo(vertices.data(), vertices.size() * sizeof(Vertex)), _ibo(indices.data(), indices.size()), _vao(_meshLayout), _vertices(vertices), _indices(indices), _textures(textures)
{
    if(!layoutInit)
    {
        _meshLayout.Push<float>(3);
        _meshLayout.Push<float>(3);
        _meshLayout.Push<float>(2);
        layoutInit = true;
        _vao.SetLayout(_meshLayout);
    }
    
    //_vao.AddBuffer(_vbo, _ibo);
    SetUpMesh();
}

void Mesh::SetUpMesh() const
{
    _vao.Bind();
    _vbo.Bind();
    _ibo.Bind();
    _vao.EnableAttributes();
}
