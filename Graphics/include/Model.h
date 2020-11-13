//
//  Model.h
//  Graphics
//
//  Created by Edwin Solis on 11/4/20.
//

#ifndef Model_h
#define Model_h

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model(const std::string& filePath);
    const std::vector<Mesh>& GetMeshes() const { return _meshes; }
    ~Model();
    
private:
    std::vector<Mesh> _meshes;
    std::vector<Texture> _loadedTextures;
    std::string _directory;
    
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
};

#endif /* Model_h */
