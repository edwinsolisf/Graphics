//
//  Shader.cpp
//  OpenGL
//
//  Created by Edwin Solis on 10/5/20.
//

#include "../include/Shader.h"
#include "../include/Opengl.h"
#include <fstream>
#include <iostream>
#include "utilities.h"


enum class ShaderType
{
  NONE = -1, VERTEX, FRAGMENT
};

Shader::Shader(const char* source)
:_filePath(source), _copy(new unsigned int(0))
{
    std::ifstream file(_filePath);
    if(!file.is_open())
        std::cout << "Could not open file: " << _filePath << std::endl;
    std::string vsource, fsource;
    ShaderType state = ShaderType::NONE;
    
    while(!file.eof())
    {
        char temp[256];
        file.getline(temp, 256);
        
        if(std::string(temp).find("#SHADER") != std::string::npos)
        {
            if(!strcmp(temp, "#SHADER VERTEX"))
                state = ShaderType::VERTEX;
            else if (!strcmp(temp, "#SHADER FRAGMENT"))
                state = ShaderType::FRAGMENT;
            else
                break;
        }
        else
        {
            if(state == ShaderType::VERTEX)
            {
                vsource += temp;
                vsource += "\n";
            }
            else if(state == ShaderType::FRAGMENT)
            {
                fsource += temp;
                fsource += "\n";
            }
            else
                break;
        }
    }
    
    GLuint vshader, fshader;
    vshader = glCreateShader(GL_VERTEX_SHADER);
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char* temp = vsource.c_str();
    GLCALL(glShaderSource(vshader, 1, &temp, nullptr));
    temp = fsource.c_str();
    GLCALL(glShaderSource(fshader, 1, &temp, nullptr));
    
    GLCALL(glCompileShader(vshader));
    ShaderCompileSuccess(vshader);
    GLCALL(glCompileShader(fshader));
    ShaderCompileSuccess(fshader);
    
    _id = glCreateProgram();
    GLCALL(glAttachShader(_id, vshader));
    GLCALL(glAttachShader(_id, fshader));
    GLCALL(glLinkProgram(_id));
    
    GLCALL(glDeleteShader(vshader));
    GLCALL(glDeleteShader(fshader));
}

Shader::Shader(const Shader& other)
:_id(other._id), _filePath(other._filePath), _uniformLocationCache(other._uniformLocationCache)
{
    (*_copy)++;
}

void Shader::Bind() const
{
    GLCALL(glUseProgram(_id));
}

void Shader::Unbind() const
{
    GLCALL(glUseProgram(0));
}

bool Shader::ShaderCompileSuccess(unsigned int shader) const
{
    int success;
    GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if(!success)
    {
        char infoLog[512];
        GLCALL(glGetShaderInfoLog(shader, 512, 0, infoLog));
        std::cout << "[SHADER COMPILE ERROR]: " << infoLog << std::endl;
    }
    return success;
}

int Shader::GetUniformLocation(const std::string& uniform) const
{
    const auto& iter = _uniformLocationCache.find(uniform);
    if(iter != _uniformLocationCache.end())
        return iter->second;
    int location = glGetUniformLocation(_id, uniform.c_str());
    _uniformLocationCache[uniform] = location;
    return location;
}

void Shader::SetUniform1f(const char *uniform, float value)
{
    GLCALL(glUniform1f(GetUniformLocation(uniform), value));
}

void Shader::SetUniform3f(const char* uniform, const stml::vec3f& value)
{
    GLCALL(glUniform3f(GetUniformLocation(uniform), value[0], value[1], value[2]));
}

void Shader::SetUniform4f(const char* uniform, const stml::vec4f& value)
{
    GLCALL(glUniform4f(GetUniformLocation(uniform), value[0], value[1], value[2], value[3]));
}

void Shader::SetUniform1i(const char *uniform, int value) const
{
    GLCALL(glUniform1i(GetUniformLocation(uniform), value));
}

void Shader::SetUniformMat4f(const char* uniform, const stml::mat4f& value)
{
    GLCALL(glUniformMatrix4fv(GetUniformLocation(uniform), 1, GL_TRUE, value.GetData()));
}

void Shader::SetUniformMaterial(const std::string& uniform, const Material& material)
{
    GLCALL(glUniform3f(GetUniformLocation((uniform + "AmbientColor").c_str()), material.GetAmbient()[0], material.GetAmbient()[1], material.GetAmbient()[2]));
    GLCALL(glUniform3f(GetUniformLocation((uniform + "SpecularColor").c_str()), material.GetSpecular()[0], material.GetSpecular()[1], material.GetSpecular()[2]));
    GLCALL(glUniform3f(GetUniformLocation((uniform + "DiffuseColor").c_str()), material.GetDiffuse().x, material.GetDiffuse().y, material.GetDiffuse().z));
    GLCALL(glUniform1f(GetUniformLocation((uniform + "Shininess").c_str()), material.GetShininess()));
}

void Shader::SetUniformMaterialMap(const std::string& uniform, const Material& material)
{
    //GLCALL(glUniform1i(GetUniformLocation(uniform + ".diffuseTexture"), 1));
    //GLCALL(glUniform1i(GetUniformLocation(uniform + ".specularTexture"), 2));
    GLCALL(glUniform1f(GetUniformLocation(uniform + ".shininess"), material.GetShininess()));
}

void Shader::SetUniformPointLight(const std::string& uniform, const PointLight& light)
{
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".position"), 1, light.GetPosition().GetData()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".ambient"), 1, light.GetAmbientColor().GetData()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".diffuse"), 1, light.GetDiffuseColor().GetData()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".specular"), 1, light.GetSpecularColor().GetData()));
    GLCALL(glUniform1f(GetUniformLocation(uniform + ".constant"), light.GetConstantAttenuationValue()));
    GLCALL(glUniform1f(GetUniformLocation(uniform + ".linear"), light.GetLinearAttenuationValue()));
    GLCALL(glUniform1f(GetUniformLocation(uniform + ".quadratic"), light.GetQuadraticAttenuationValue()));
}

void Shader::SetUniformDirectionalLight(const std::string& uniform, const DirectionalLight& light)
{
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".direction"), 1, light.GetDirection().GetData()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".ambient"), 1, light.GetAmbientColor().GetData()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".diffuse"), 1, light.GetDiffuseColor().GetData()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".specular"), 1, light.GetSpecularColor().GetData()));
}

void Shader::SetUniformSpotLight(const std::string& uniform, const SpotLight& light)
{
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".position"), 1, light.GetPosition().GetData()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".direction"), 1, light.GetDirection().GetData()));
    GLCALL(glUniform1f (GetUniformLocation(uniform + ".cutOff"), light.GetCutOff()));
    GLCALL(glUniform1f (GetUniformLocation(uniform + ".outerCutOff"), light.GetOuterCutOff()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".ambient"), 1, light.GetAmbientColor().GetData()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".diffuse"), 1, light.GetDiffuseColor().GetData()));
    GLCALL(glUniform3fv(GetUniformLocation(uniform + ".specular"), 1, light.GetSpecularColor().GetData()));
    GLCALL(glUniform1f(GetUniformLocation(uniform + ".constant"), light.GetConstantAttenuationValue()));
    GLCALL(glUniform1f(GetUniformLocation(uniform + ".linear"), light.GetLinearAttenuationValue()));
    GLCALL(glUniform1f(GetUniformLocation(uniform + ".quadratic"), light.GetQuadraticAttenuationValue()));
    
    /*
    stml::vec3f temp;
    glGetUniformfv(_id, GetUniformLocation(uniform + ".position"), temp.GetData());
    stml::Print(temp);
    glGetUniformfv(_id, GetUniformLocation(uniform + ".direction"), temp.GetData());
    stml::Print(temp);
    glGetUniformfv(_id, GetUniformLocation(uniform + ".cutOff"), temp.GetData());
    stml::Print(temp);
    glGetUniformfv(_id, GetUniformLocation(uniform + ".outerCutOff"), temp.GetData());
    stml::Print(temp);
    glGetUniformfv(_id, GetUniformLocation(uniform + ".ambient"), temp.GetData());
    stml::Print(temp);
    glGetUniformfv(_id, GetUniformLocation(uniform + ".diffuse"), temp.GetData());
    stml::Print(temp);
    glGetUniformfv(_id, GetUniformLocation(uniform + ".specular"), temp.GetData());
    stml::Print(temp);
    std::cout << "-------------\n";
    */
}

void Shader::SetUniform1b(const std::string& uniform, bool value)
{
    GLCALL(glUniform1i(GetUniformLocation(uniform), value));
}

Shader::~Shader()
{
    if(*_copy == 0)
    {
        GLCALL(glDeleteProgram(_id));
        delete _copy;
    }
    else
        (*_copy)--;
}
