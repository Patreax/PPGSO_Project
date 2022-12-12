#version 330
layout (location = 0) in vec3 Position;

uniform mat4 lightProjection;
uniform mat4 model;

void main()
{
    gl_Position = lightProjection * model * vec4(Position, 1.0);
}