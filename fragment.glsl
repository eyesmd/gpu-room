#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec4 ourPos;
in vec2 TexCoord;

uniform sampler2D boxSampler;
uniform sampler2D smileSampler;

void main() {
    FragColor = mix(texture(boxSampler, TexCoord), texture(smileSampler, TexCoord), 0.2);
}