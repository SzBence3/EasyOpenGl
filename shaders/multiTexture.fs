#version 450 core

in vec2 texCoord;
in float TexIndex;

uniform sampler2D textures[32];

out vec4 fragColor;

void main()
{
    //fragColor = texture(textures[int(TexIndex)], texCoord);
    fragColor = vec4(1,1,1,1);
}