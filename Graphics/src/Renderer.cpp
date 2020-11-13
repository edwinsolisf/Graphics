//
//  Renderer.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/6/20.
//

#include "Renderer.h"
#include "Opengl.h"
#include <sstream>
Renderer::Renderer()
{
    
}

void Renderer::PushToQueue(const Mesh& mesh, const Shader& shader)
{
    _queue.emplace_back(mesh, &shader);
}

/*
void Renderer::Draw() const
{
    for(unsigned int i = 0; i < _queue.size(); ++i)
    {
        const auto& vao = _queue[i].first;
        const auto& shader = _queue[i].second;
        
        shader->Bind();
        vao->Bind();
        for(unsigned int i = 0; i < vao->GetIndexBuffers().size(); ++i)
        {
            //const auto& vbo = bufferPair.first;
            //const auto& ibo = bufferPair.second;
            const auto& vbo = vao->GetVertexBuffers()[i];
            const auto& ibo = vao->GetIndexBuffers()[i];
            
            vbo->Bind();
            ibo->Bind();
            vao->EnableAttributes();
            
            GLCALL(glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, 0));
        }
    }
}
*/

void Renderer::Draw() const
{
    for(unsigned int i = 0; i < _queue.size(); ++i)
    {
        const auto& mesh = _queue[i].first;
        auto& shader = _queue[i].second;
        
        mesh.SetUpMesh();
        shader->Bind();
        
        unsigned int diffuse = 1;
        unsigned int specular = 1;
        
        for(unsigned int j = 0; j < mesh.GetTextureCount(); ++j)
        {
            const Texture& texture = mesh.GetTextures()[j];
            texture.Bind(j);
            std::stringstream ss;
            std::string number;
            std::string name = texture.GetType();
            
            if(name == std::string("texture_diffuse"))
                ss << diffuse++;
            else if(name == std::string("texture_specular"))
                ss << specular++;
            number = ss.str();
            shader->SetUniform1i(("u_Material." + name + number).c_str(), j);
        }
        glActiveTexture(GL_TEXTURE0);
        GLCALL(glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0));
    }
}
Renderer::~Renderer()
{
    for(const auto& pair : _queue)
    {
        //delete pair.first;
        //delete pair.second;
    }
}
