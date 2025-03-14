#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in int tex;

out vec2 TexCoord;
out float Tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
    TexCoord = texCoord;
    Tex = tex;
}