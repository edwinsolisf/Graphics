#SHADER VERTEX
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_Position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position =  u_projection * u_view * u_model * vec4(position.x, position.y, position.z, 1.0);
    v_TexCoord = texCoords;
    v_Normal = normalize(vec3(u_model * vec4(normal.xyz, 0.0)));
    v_Position = vec3(u_model * vec4(position.x, position.y, position.z, 1.0f));
}

#SHADER FRAGMENT
#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_Position;

uniform vec3 u_ViewPos;
uniform float u_specularStrength;

//uniform sampler2D u_MaterialDiffuseTexture;
//uniform sampler2D u_MaterialSpecularTexture;
//uniform float u_MaterialShininess;

//uniform vec3 u_LightPosition;
//uniform vec3 u_LightAmbientColor;
//uniform vec3 u_LightDiffuseColor;
//uniform vec3 u_LightSpecularColor;
//uniform float u_LightConstant;
//uniform float u_LightLinear;
//uniform float u_LightQuadratic;

struct Material
{
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    float shininess;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

uniform Material u_Material;
uniform PointLight u_PointLight;
uniform DirectionalLight u_DirLight;
uniform SpotLight u_SpotLight;

vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    vec3 diffTextureColor = vec3(texture(u_Material.diffuseTexture, v_TexCoord));
    vec3 specTextureColor = vec3(texture(u_Material.specularTexture, v_TexCoord));
    
    vec3 DirlightDir = normalize(-light.direction);
    vec3 DirReflectDir = reflect(DirlightDir, normal);
    vec3 dirAmbient = light.ambient * diffTextureColor;
    vec3 dirDiffuse = light.diffuse * diffTextureColor * max(dot(normal, DirlightDir), 0.0);
    vec3 dirSpecular = pow(max(dot(viewDirection, DirReflectDir), 0.0), u_Material.shininess) * u_DirLight.specular * specTextureColor;
    vec3 dirColorFactor = dirAmbient + dirDiffuse + dirSpecular;
    return dirColorFactor;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDirection)
{
    vec3 diffTextureColor = vec3(texture(u_Material.diffuseTexture, v_TexCoord));
    vec3 specTextureColor = vec3(texture(u_Material.specularTexture, v_TexCoord));
    
    float pointDistance = length(light.position - position);
    vec3 pointLightDir = normalize(light.position - position);
    vec3 pointReflectDir = reflect(-pointLightDir, normal);
    vec3 pointAmbient = light.ambient * diffTextureColor;
    vec3 pointDiffuse = max(dot(normal, pointLightDir), 0.0) * light.diffuse * diffTextureColor;
    vec3 pointSpecular = pow(max(dot(viewDirection, pointReflectDir), 0.0), u_Material.shininess) * light.specular * specTextureColor;
    float pointAttenuation = 1.0f / (light.constant + (light.linear * pointDistance) + (light.quadratic * pointDistance * pointDistance));
    vec3 pointColorFactor = (pointAmbient + pointDiffuse + pointSpecular) * pointAttenuation;
    return pointColorFactor;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 position, vec3 viewDirection)
{
    vec3 diffTextureColor = vec3(texture(u_Material.diffuseTexture, v_TexCoord));
    vec3 specTextureColor = vec3(texture(u_Material.specularTexture, v_TexCoord));
    
    float spotDistance = length(light.position - position);
    vec3 spotLightDir = normalize(light.position - position);
    float theta = dot(normalize(-light.direction), spotLightDir);
    float epsilon = -u_SpotLight.cutOff + u_SpotLight.outerCutOff;
    float spotLightIntensity = clamp((theta - u_SpotLight.outerCutOff)/epsilon, 0.0, 1.0);
    float spotAttenuation = 1.0f / (light.constant + (light.linear * spotDistance) + (light.quadratic * spotDistance * spotDistance));
    vec3 spotLightReflectDir = reflect(-spotLightDir, normal);
    vec3 spotAmbient = light.ambient * diffTextureColor;
    vec3 spotDiffuse = max(dot(normal, spotLightDir), 0.0) * light.diffuse * diffTextureColor;
    vec3 spotSpecular = pow(max(dot(viewDirection, spotLightReflectDir), 0.0), u_Material.shininess) * light.specular * specTextureColor;
    vec3 spotColorFactor = (spotAmbient + spotDiffuse + spotSpecular) * spotLightIntensity * spotAttenuation;
    return spotColorFactor;
}

void main()
{
    vec3 diffTextureColor = vec3(texture(u_Material.diffuseTexture, v_TexCoord));
    vec3 specTextureColor = vec3(texture(u_Material.specularTexture, v_TexCoord));
    vec3 viewDir = normalize(u_ViewPos - v_Position);
    
    //PointLight
    //float pointDistance = length(u_PointLight.position - v_Position);
    //vec3 pointLightDir = normalize(u_PointLight.position - v_Position);
    //vec3 pointReflectDir = reflect(-pointLightDir, v_Normal);
    //vec3 pointAmbient = u_PointLight.ambient * diffTextureColor;
    //vec3 pointDiffuse = max(dot(v_Normal, pointLightDir), 0.0) * u_PointLight.diffuse * diffTextureColor;
    //vec3 pointSpecular = pow(max(dot(viewDir, pointReflectDir), 0.0), u_Material.shininess) * u_PointLight.specular * specTextureColor;
    //float pointAttenuation = 1.0f / (u_PointLight.constant + (u_PointLight.linear * pointDistance) + (u_PointLight.quadratic * pointDistance * pointDistance));
    //vec3 pointColorFactor = (pointAmbient + pointDiffuse + pointSpecular) * pointAttenuation;
    
    //vec3 lightDir = normalize(u_LightPosition - v_Position);
    //vec3 reflectDir = reflect(-lightDir, v_Normal);
    //vec3 pointAmbient = u_LightAmbientColor * diffTextureColor;
    //float pointAttenuation = 1.0f / (u_LightConstant + (u_LightLinear * distance) + (u_LightQuadratic * distance * distance));
    //vec3 pointDiffuse = max(dot(v_Normal, lightDir), 0.0) * u_LightDiffuseColor * diffTextureColor;
    //vec3 pointSpecular = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess) * u_LightSpecularColor * specTextureColor;
    //vec3 pointColorFactor = (pointAmbient + pointDiffuse + pointSpecular) * pointAttenuation;
    
    //DirectionalLight
    //vec3 DirlightDir = normalize(-u_DirLight.direction);
    //vec3 DirReflectDir = reflect(DirlightDir, v_Normal);
    //vec3 dirAmbient = u_DirLight.ambient * diffTextureColor;
    //vec3 dirDiffuse = u_DirLight.diffuse * diffTextureColor * max(dot(v_Normal, DirlightDir), 0.0);
    //vec3 dirSpecular = pow(max(dot(viewDir, DirReflectDir), 0.0), u_Material.shininess) * u_DirLight.specular * specTextureColor;
    //vec3 dirColorFactor = dirAmbient + dirDiffuse + dirSpecular;
    
    //SpotLight
    //float spotDistance = length(u_SpotLight.position - v_Position);
    //vec3 spotLightDir = normalize(u_SpotLight.position - v_Position);
    //float theta = dot(normalize(-u_SpotLight.direction), spotLightDir);
    //float epsilon = -u_SpotLight.cutOff + u_SpotLight.outerCutOff;
    //float spotLightIntensity = clamp((theta - u_SpotLight.outerCutOff)/epsilon, 0.0, 1.0);

    //float spotAttenuation = 1.0f / (u_SpotLight.constant + (u_SpotLight.linear * spotDistance) + (u_SpotLight.quadratic * spotDistance * spotDistance));
    //vec3 spotLightReflectDir = reflect(-spotLightDir, v_Normal);
    //vec3 spotAmbient = u_SpotLight.ambient * diffTextureColor;
    //vec3 spotDiffuse = max(dot(v_Normal, spotLightDir), 0.0) * u_SpotLight.diffuse * diffTextureColor;
    //vec3 spotSpecular = pow(max(dot(viewDir, spotLightReflectDir), 0.0), u_Material.shininess) * u_SpotLight.specular * specTextureColor;
    //vec3 spotColorFactor = (spotAmbient + spotDiffuse + spotSpecular) * spotLightIntensity * spotAttenuation;
    
    vec3 pointColorFactor = CalculatePointLight(u_PointLight, v_Normal, v_Position, viewDir);
    vec3 dirColorFactor = CalculateDirLight(u_DirLight, v_Normal, viewDir);
    vec3 spotColorFactor = CalculateSpotLight(u_SpotLight, v_Normal, v_Position, viewDir);
    
    vec3 colorFactor = spotColorFactor + dirColorFactor + pointColorFactor;
    
    color = vec4(colorFactor.x, colorFactor.y, colorFactor.z, 1.0);
     
}
