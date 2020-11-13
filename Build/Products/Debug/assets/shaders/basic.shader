#SHADER VERTEX
#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 v_TexCoord;
uniform mat4 u_transform;

void main()
{
    gl_Position = u_transform * vec4(position.x, position.y, 1.0, 1.0);
    v_TexCoord = texCoords;
}

#SHADER FRAGMENT
#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
}
