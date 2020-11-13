//
//  Material.h
//  Graphics
//
//  Created by Edwin Solis on 10/16/20.
//

#ifndef Material_h
#define Material_h

#include "vector.h"

class Material
{
public:
    Material(const stml::vec3f& ambientColor, const stml::vec3f& diffuseColor, const stml::vec3f& specularColor, float shininess);
    inline const stml::vec3f& GetAmbient() const { return _ambientColor; }
    inline const stml::vec3f& GetDiffuse() const { return _diffuseColor; }
    inline const stml::vec3f& GetSpecular() const { return _specularColor; }
    inline float GetShininess() const { return _shininess; }
private:
    stml::vec3f _ambientColor;
    stml::vec3f _diffuseColor;
    stml::vec3f _specularColor;
    float _shininess;
};



const Material material_white(stml::vec3f(1.0f), stml::vec3f(1.0f), stml::vec3f(1.0f), 32.0f);
const Material material_emerald(stml::vec3f(0.0215f, 0.1745f, 0.0215f), stml::vec3f(0.07568f, 0.61424f, 0.07568f), stml::vec3f(0.633f, 0.727811f, 0.633f), 0.6f * 128.0f);
const Material material_diamond(stml::vec3f(0.0215f, 0.1745f, 0.0215f), stml::vec3f(0.07568f, 0.61424f, 0.07568f), stml::vec3f(0.633f, 0.727811f, 0.633f), 0.6f);
const Material material_earth(stml::vec3f(1.0f, 0.5f, 0.31f), stml::vec3f(1.0f, 0.5f, 0.31f), stml::vec3f(0.5f), 32.0f);
const Material material_wood(stml::vec3f(1.0f), stml::vec3f(0.0f), stml::vec3f(0.5f), 4.0f);


 

#endif /* Material_h */
