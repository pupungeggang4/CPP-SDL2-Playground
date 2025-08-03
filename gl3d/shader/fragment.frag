#version 410 core
precision highp float;
uniform sampler2D u_sampler;
uniform vec3 u_light_d;
uniform vec3 u_color;
uniform int u_mode_f; // 0: HUD, 1: NoTexture, 2: Texture, 3: NoTexture with light, 4: Texture with light
in vec2 p_texcoord;
in vec3 p_normal;
out vec4 o_color;

void main() {
    if (u_mode_f == 0 || u_mode_f == 2) {
        o_color = texture(u_sampler, p_texcoord);
    } else if (u_mode_f == 1) {
        o_color = vec4(u_color, 1.0);
    } else if (u_mode_f == 3) {
        float brightness = max(dot(p_normal, normalize(-u_light_d)), 0.2);
        vec3 color = brightness * u_color;
        o_color = vec4(color, 1.0);
    } else if (u_mode_f == 4) {
        float brightness = max(dot(p_normal, normalize(-u_light_d)), 0.2);
        vec4 color = texture(u_sampler, p_texcoord);
        color.x *= brightness;
        color.y *= brightness;
        color.z *= brightness;
        o_color = color;
    }
}