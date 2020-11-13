//
//  Model.cpp
//  Graphics
//
//  Created by Edwin Solis on 11/4/20.
//

#include <Model.h>

Model::Model(const std::string& filePath)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    _directory = filePath.substr(0, filePath.find_last_of('/') + 1);
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(ProcessMesh(mesh, scene));
    }
    
    for(unsigned int i = 0; i < node->mNumChildren; ++i)
        ProcessNode(node->mChildren[i], scene);
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
    std::vector<Texture> textures;
    
    for(unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        stml::vec2f texcoords(0.0f);
        if(mesh->mTextureCoords[0])
        {
            texcoords.x = mesh->mTextureCoords[0][i].x;
            texcoords.y = mesh->mTextureCoords[0][i].y;
        }
        
        vertices.emplace_back(stml::vec3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
                              stml::vec3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z),
                              texcoords);
    }
    
    for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }
    
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        
    }
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *material, aiTextureType type, const std::string &typeName)
{
    std::vector<Texture> textures;
    bool loaded = false;
    for(unsigned int i = 0; i < material->GetTextureCount(type); ++i)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        
        for(unsigned int j = 0; j < _loadedTextures.size(); j++)
        {
            if(_loadedTextures[j].GetFilePath() == std::string(_directory + str.C_Str()))
            {
                textures.push_back(_loadedTextures[j]);
                loaded = true;
                break;
            }
        }
        
        if(!loaded)
        {
            textures.emplace_back((_directory + str.C_Str()).c_str(), typeName);
            _loadedTextures.emplace_back((_directory + str.C_Str()).c_str(), typeName);
        }
    }
    return textures;
}

Model::~Model()
{
}
