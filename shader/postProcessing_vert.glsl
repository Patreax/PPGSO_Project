#version 330

layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 TexCoords;

out vec2 texCoords;

void main()
{
    gl_Position = vec4(Position.x, Position.y, 0.0, 1.0);
    texCoords = TexCoords;
}