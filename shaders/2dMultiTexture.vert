#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) in float tex;

out vec2 texCoord;
out float TexIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
    texCoord = TexCoord;
    TexIndex = float(tex);
}