#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec4 ourPos;
out vec2 TexCoord;

uniform float horizontalOffset;
uniform mat4 transform;

void main() {
    //gl_Position = vec4(aPos.x + horizontalOffset, aPos.y, aPos.z, 1.0);
    gl_Position = transform * vec4(aPos, 1.0f) + vec4(horizontalOffset, 0, 0, 0.0);
    ourColor = aColor;
    ourPos = gl_Position;
    TexCoord = aTexCoord;
}