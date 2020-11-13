//
//  Material.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/16/20.
//

#include <Material.h>

Material::Material(const stml::vec3f& ambientColor, const stml::vec3f& diffuseColor, const stml::vec3f& specularColor, float shininess)
:_ambientColor(ambientColor), _diffuseColor(diffuseColor), _specularColor(specularColor), _shininess(shininess)
{
}

