#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D ScreenTexture;

const float contrast = 0.8;

void main()
{
    FragColor = texture(ScreenTexture, texCoords);
    FragColor = (FragColor - 0.5) * (1.0 + contrast) + 0.5;
    FragColor = clamp(FragColor, 0.0, 1.0);
}