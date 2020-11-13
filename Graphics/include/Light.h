//
//  Light.h
//  Graphics
//
//  Created by Edwin Solis on 10/18/20.
//

#ifndef Light_h
#define Light_h

#include "vector.h"

class PointLight
{
public:
    
    PointLight(const stml::vec3f& position, const stml::vec3f& ambient, const stml::vec3f& diffuse, const stml::vec3f& specular, const stml::vec3f& attenuation);
    
    inline const stml::vec3f& GetPosition() const { return _position; }
    inline const stml::vec3f& GetAmbientColor() const { return _ambientColor; }
    inline const stml::vec3f& GetDiffuseColor() const { return _diffuseColor; }
    inline const stml::vec3f& GetSpecularColor() const { return _specularColor; }
    inline float GetConstantAttenuationValue() const { return _constantAttenuation; }
    inline float GetLinearAttenuationValue() const { return _linearAttenuation; }
    inline float GetQuadraticAttenuationValue() const { return _quadraticAttenuation; }
    
    
private:
    stml::vec3f _position;
    
    stml::vec3f _ambientColor;
    stml::vec3f _diffuseColor;
    stml::vec3f _specularColor;
    
    float _constantAttenuation;
    float _linearAttenuation;
    float _quadraticAttenuation;
};


class DirectionalLight
{
public:
    DirectionalLight(const stml::vec3f& direction, const stml::vec3f& ambient, const stml::vec3f& diffuse, const stml::vec3f& specular);
       
    inline const stml::vec3f& GetDirection() const { return _direction; }
    inline const stml::vec3f& GetAmbientColor() const { return _ambientColor; }
    inline const stml::vec3f& GetDiffuseColor() const { return _diffuseColor; }
    inline const stml::vec3f& GetSpecularColor() const { return _specularColor; }
    
private:
    stml::vec3f _direction;
    
    stml::vec3f _ambientColor;
    stml::vec3f _diffuseColor;
    stml::vec3f _specularColor;
};

class SpotLight
{
public:
    SpotLight(const stml::vec3f& position, const stml::vec3f& direction, float cutOff, float outerCutOff, const stml::vec3f& ambient, const stml::vec3f& diffuse, const stml::vec3f& specular, const stml::vec3f& attenuation);
    
    inline const stml::vec3f& GetPosition() const { return _position; }
    inline const stml::vec3f& GetDirection() const { return _direction; }
    inline float GetCutOff() const { return _cutOff; }
    inline float GetOuterCutOff() const { return _outerCutOff; }
    inline const stml::vec3f& GetAmbientColor() const { return _ambientColor; }
    inline const stml::vec3f& GetDiffuseColor() const { return _diffuseColor; }
    inline const stml::vec3f& GetSpecularColor() const { return _specularColor; }
    inline float GetConstantAttenuationValue() const { return _constantAttenuation; }
    inline float GetLinearAttenuationValue() const { return _linearAttenuation; }
    inline float GetQuadraticAttenuationValue() const { return _quadraticAttenuation; }
private:
    stml::vec3f _position;
    stml::vec3f _direction;
    float _cutOff;
    float _outerCutOff;
    
    stml::vec3f _ambientColor;
    stml::vec3f _diffuseColor;
    stml::vec3f _specularColor;
    
    float _constantAttenuation;
    float _linearAttenuation;
    float _quadraticAttenuation;
};
#endif /* Light_h */
 
