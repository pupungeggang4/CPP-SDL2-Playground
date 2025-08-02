#version 410 core
uniform int u_mode_v; // 0: HUD, 1: Single object, 2: Object with parts.
uniform vec3 u_m_pos;
uniform vec3 u_m_size;
uniform vec3 u_m_rot;

in vec4 a_position;

void main() {
    gl_Position = a_position;
}
