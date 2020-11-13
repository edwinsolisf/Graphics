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
uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_AmbientColor;
uniform vec3 u_ViewPos;
uniform float u_specularStrength;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    vec3 lightDir = normalize(u_LightPos - v_Position);
    vec3 diffuse = u_LightColor * max(dot(v_Normal, lightDir), 0.0);
    vec3 viewDir = normalize(u_ViewPos - v_Position);
    vec3 reflectDir = reflect(-lightDir, v_Normal);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = u_specularStrength * spec * u_LightColor;
    
    vec3 colorFactor = u_AmbientColor + diffuse + specular;
    color = texColor * vec4(colorFactor.x, colorFactor.y, colorFactor.z, 1.0);
}
