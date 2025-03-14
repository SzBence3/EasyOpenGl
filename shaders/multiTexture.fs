#version 450 core

in vec2 texCoord;
in float texIndex;

uniform sampler2D texs[32];

out vec4 fragColor;

void main()
{
    fragColor = texture(texs[(int)texIndex], texCoord);
}