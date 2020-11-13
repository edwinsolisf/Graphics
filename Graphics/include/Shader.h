//
//  Shader.h
//  OpenGL
//
//  Created by Edwin Solis on 10/5/20.
//

#ifndef Shader_h
#define Shader_h

#include <string>
#include <unordered_map>
#include "matrix.h"
#include "vector.h"
#include "Material.h"
#include "Light.h"

class Shader
{
public:
    Shader(const char* source);
    Shader(const Shader& other);
    ~Shader();
    
    void Bind() const;
    void Unbind() const;
    
    int GetUniformLocation(const std::string& uniform) const;
    
    void SetUniform1i(const char* uniform, int value) const;
    void SetUniform1b(const std::string& uniform, bool value);
    void SetUniform1f(const char* uniform, float value);
    void SetUniform3f(const char* uniform, const stml::vec3f& value);
    void SetUniform4f(const char* uniform, const stml::vec4f& value);
    
    void SetUniformMat4f(const char* uniform, const stml::mat4f& value);
    
    void SetUniformMaterial(const std::string& uniform, const Material& material);
    void SetUniformMaterialMap(const std::string& uniform, const Material& material);
    
    void SetUniformPointLight(const std::string& uniform, const PointLight& light);
    void SetUniformDirectionalLight(const std::string& uniform, const DirectionalLight& light);
    void SetUniformSpotLight(const std::string& uniform, const SpotLight& light);
    
    bool ShaderCompileSuccess(unsigned int shader) const;
    
private:
    unsigned int _id;
    std::string _filePath;
    unsigned int* _copy;
    mutable std::unordered_map<std::string, int> _uniformLocationCache;
    
};

#endif /* Shader_h */
