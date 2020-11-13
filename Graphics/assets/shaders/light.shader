#SHADER VERTEX
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position =  u_projection * u_view * u_model * vec4(position.x, position.y, position.z, 1.0);
}

#SHADER FRAGMENT
#version 330 core

layout (location = 0) out vec4 color;

uniform vec3 u_color;
void main()
{
    color = vec4(u_color, 1.0);
}
