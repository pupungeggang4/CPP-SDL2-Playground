#version 330 core
precision highp float;
in vec3 p_color;
out vec4 outColor;
void main() {
    outColor = vec4(p_color, 1.0);
}