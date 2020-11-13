//
//  Light.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/18/20.
//

#include <Light.h>

PointLight::PointLight(const stml::vec3f& position, const stml::vec3f& ambient, const stml::vec3f& diffuse, const stml::vec3f& specular, const stml::vec3f& attenuation)
:_position(position), _ambientColor(ambient), _diffuseColor(diffuse), _specularColor(specular), _constantAttenuation(attenuation.x), _linearAttenuation(attenuation.y), _quadraticAttenuation(attenuation.z)
{
}

DirectionalLight::DirectionalLight(const stml::vec3f& direction, const stml::vec3f& ambient, const stml::vec3f& diffuse, const stml::vec3f& specular)
:_direction(direction), _ambientColor(ambient), _diffuseColor(diffuse), _specularColor(specular)
{
}

SpotLight::SpotLight(const stml::vec3f& position, const stml::vec3f& direction, float cutOff, float outerCutOff, const stml::vec3f& ambient, const stml::vec3f& diffuse, const stml::vec3f& specular, const stml::vec3f& attenuation)
:_position(position), _direction(direction), _cutOff(cutOff), _outerCutOff(outerCutOff), _ambientColor(ambient), _diffuseColor(diffuse), _specularColor(specular), _constantAttenuation(attenuation.x), _linearAttenuation(attenuation.y), _quadraticAttenuation(attenuation.z)
{
}
