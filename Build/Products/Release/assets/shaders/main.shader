#SHADER VERTEX
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

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

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
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
uniform PointLight u_PointLight[4];
uniform DirectionalLight u_DirLight;
uniform SpotLight u_SpotLight;
uniform bool u_Draw;

vec4 diffTextureColor = texture(u_Material.texture_diffuse1, v_TexCoord);
vec4 specTextureColor = texture(u_Material.texture_specular1, v_TexCoord);

vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    vec3 DirlightDir = normalize(-light.direction);
    vec3 DirReflectDir = reflect(DirlightDir, normal);
    vec3 dirAmbient = light.ambient * vec3(diffTextureColor);
    vec3 dirDiffuse = light.diffuse * vec3(diffTextureColor) * max(dot(normal, DirlightDir), 0.0);
    vec3 dirSpecular = pow(max(dot(viewDirection, DirReflectDir), 0.0), u_Material.shininess) * u_DirLight.specular * vec3(specTextureColor);
    vec3 dirColorFactor = dirAmbient + dirDiffuse + dirSpecular;
    return dirColorFactor;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDirection)
{
    float pointDistance = length(light.position - position);
    vec3 pointLightDir = normalize(light.position - position);
    vec3 pointReflectDir = reflect(-pointLightDir, normal);
    vec3 pointAmbient = light.ambient * vec3(diffTextureColor);
    vec3 pointDiffuse = max(dot(normal, pointLightDir), 0.0) * light.diffuse * vec3(diffTextureColor);
    vec3 pointSpecular = pow(max(dot(viewDirection, pointReflectDir), 0.0), u_Material.shininess) * light.specular * vec3(specTextureColor);
    float pointAttenuation = 1.0f / (light.constant + (light.linear * pointDistance) + (light.quadratic * pointDistance * pointDistance));
    vec3 pointColorFactor = (pointAmbient + pointDiffuse + pointSpecular) * pointAttenuation;
    return pointColorFactor;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 position, vec3 viewDirection)
{
    float spotDistance = length(light.position - position);
    vec3 spotLightDir = normalize(light.position - position);
    float theta = dot(normalize(-light.direction), spotLightDir);
    float epsilon = u_SpotLight.cutOff - u_SpotLight.outerCutOff;
    float spotLightIntensity = clamp((theta - u_SpotLight.outerCutOff)/epsilon, 0.0, 1.0);
    float spotAttenuation = 1.0f / (light.constant + (light.linear * spotDistance) + (light.quadratic * spotDistance * spotDistance));
    vec3 spotLightReflectDir = reflect(-spotLightDir, normal);
    vec3 spotAmbient = light.ambient * vec3(diffTextureColor);
    vec3 spotDiffuse = max(dot(normal, spotLightDir), 0.0) * light.diffuse * vec3(diffTextureColor);
    vec3 spotSpecular = pow(max(dot(viewDirection, spotLightReflectDir), 0.0), u_Material.shininess) * light.specular * vec3(specTextureColor);
    vec3 spotColorFactor = (spotAmbient + spotDiffuse + spotSpecular) * spotLightIntensity * spotAttenuation;
    return spotColorFactor;
}

void main()
{
    vec3 viewDir = normalize(u_ViewPos - v_Position);
    vec3 pointColorFactor;
    for(int i = 0; i < 4; ++i)
        pointColorFactor += CalculatePointLight(u_PointLight[i], v_Normal, v_Position, viewDir);
    vec3 dirColorFactor = CalculateDirLight(u_DirLight, v_Normal, viewDir);
    vec3 spotColorFactor = CalculateSpotLight(u_SpotLight, v_Normal, v_Position, viewDir);
    
    vec3 colorFactor = spotColorFactor + dirColorFactor + pointColorFactor;
    
    if(u_Draw)
        color = vec4(colorFactor.x, colorFactor.y, colorFactor.z, 1.0);
    else
        color = vec4(1.0, 1.0, 1.0, 1.0);
    //color = diffTextureColor;
    
    //float depth = gl_FragCoord.z;
    //float near = 0.1;
    //float far = 100.0;
    //float z = depth * 2.0 - 1.0; // Back to NDC
    //float _depth = (2.0 * near) / (far + near - z * (far - near));

    //color = vec4(vec3(_depth), 1.0);
}

