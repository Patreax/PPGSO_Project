#version 330

out vec4 FragmentColor;

in vec2 texCoord;

uniform vec4 LightColor;

uniform sampler2D Texture;

uniform float Transparency;

uniform vec2 TextureOffset;

void main() {
    FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * LightColor;
    FragmentColor.a = Transparency;
}