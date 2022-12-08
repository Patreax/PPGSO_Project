#version 330

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) in vec3 Normal;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

out vec2 texCoord;

out vec4 normal;

out vec4 currentPosition;

void main() {
    texCoord = TexCoord;

    normal = normalize(ModelMatrix * vec4(Normal, 0.0f));

    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(Position, 1.0);
    currentPosition = ModelMatrix * vec4(Position, 1.0f);

}
