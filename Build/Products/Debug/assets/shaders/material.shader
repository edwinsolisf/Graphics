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

uniform sampler2D u_Texture;
uniform vec3 u_ViewPos;
uniform float u_specularStrength;


uniform vec3 u_MaterialAmbientColor;
uniform vec3 u_MaterialDiffuseColor;
uniform vec3 u_MaterialSpecularColor;
uniform float u_MaterialShininess;

uniform vec3 u_LightPosition;
uniform vec3 u_LightAmbientColor;
uniform vec3 u_LightDiffuseColor;
uniform vec3 u_LightSpecularColor;

void main()
{

    vec4 texColor = texture(u_Texture, v_TexCoord);
    vec3 ambient = u_LightAmbientColor * u_MaterialAmbientColor;
    
    vec3 lightDir = normalize(u_LightPosition - v_Position);
    vec3 diffuse = u_LightDiffuseColor * (max(dot(v_Normal, lightDir), 0.0) * u_MaterialDiffuseColor);
    
    vec3 viewDir = normalize(u_ViewPos - v_Position);
    vec3 reflectDir = reflect(-lightDir, v_Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_MaterialShininess);
    vec3 specular = u_LightSpecularColor * (spec * u_MaterialSpecularColor);
    
    vec3 colorFactor = ambient + diffuse + specular;
    color = texColor * vec4(colorFactor.x, colorFactor.y, colorFactor.z, 1.0);
     
}
