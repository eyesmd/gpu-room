#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec4 ourPos;

void main() {
    FragColor = vec4(ourPos.x, 0.0, 0.0, 1.0);
}