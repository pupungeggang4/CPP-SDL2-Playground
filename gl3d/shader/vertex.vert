#version 410 core
uniform vec3 u_p_pos;
uniform vec3 u_p_size;
uniform vec3 u_p_rot;
uniform vec3 u_m_pos;
uniform vec3 u_m_size;
uniform vec3 u_m_rot;
uniform vec3 u_c_pos;
uniform vec3 u_c_rot;
uniform vec4 u_c_proj;
uniform int u_mode_v; // 0: HUD, 1: Whole model, 2: Part
in vec4 a_position;
in vec2 a_texcoord;
in vec3 a_normal;
out vec2 p_texcoord;
out vec3 p_normal;

void main() {
    if (u_mode_v == 0) {
        gl_Position = a_position;
        p_normal = a_normal;
    } else {
        vec4 pos = a_position;
        mat4 m_p_pos = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            u_p_pos.x, u_p_pos.y, u_p_pos.z, 1.0
        );
        mat4 m_p_size = mat4(
            u_p_size.x, 0.0, 0.0, 0.0,
            0.0, u_p_size.y, 0.0, 0.0,
            0.0, 0.0, u_p_size.z, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_p_rot_x = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, cos(u_p_rot.x), sin(u_p_rot.x), 0.0,
            0.0, -sin(u_p_rot.x), cos(u_p_rot.x), 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_p_rot_y = mat4(
            cos(u_p_rot.y), 0.0, -sin(u_p_rot.y), 0.0,
            0.0, 1.0, 0.0, 0.0,
            sin(u_p_rot.y), 0.0, cos(u_p_rot.y), 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_p_rot_z = mat4(
            cos(u_p_rot.z), sin(u_p_rot.z), 0.0, 0.0,
            -sin(u_p_rot.z), cos(u_p_rot.z), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_m_pos = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            u_m_pos.x, u_m_pos.y, u_m_pos.z, 1.0
        );
        mat4 m_m_size = mat4(
            u_m_size.x, 0.0, 0.0, 0.0,
            0.0, u_m_size.y, 0.0, 0.0,
            0.0, 0.0, u_m_size.z, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_m_rot_x = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, cos(u_m_rot.x), sin(u_m_rot.x), 0.0,
            0.0, -sin(u_m_rot.x), cos(u_m_rot.x), 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_m_rot_y = mat4(
            cos(u_m_rot.y), 0.0, -sin(u_m_rot.y), 0.0,
            0.0, 1.0, 0.0, 0.0,
            sin(u_m_rot.y), 0.0, cos(u_m_rot.y), 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_m_rot_z = mat4(
            cos(u_m_rot.z), sin(u_m_rot.z), 0.0, 0.0,
            -sin(u_m_rot.z), cos(u_m_rot.z), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_z_inv = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, -1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_c_pos = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            -u_c_pos.x, -u_c_pos.y, -u_c_pos.z, 1.0
        );
        mat4 m_c_rot_x = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, cos(-u_c_rot.x), sin(-u_c_rot.x), 0.0,
            0.0, -sin(-u_c_rot.x), cos(-u_c_rot.x), 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_c_rot_y = mat4(
            cos(-u_c_rot.y), 0.0, -sin(-u_c_rot.y), 0.0,
            0.0, 1.0, 0.0, 0.0,
            sin(-u_c_rot.y), 0.0, cos(-u_c_rot.y), 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 m_c_rot_z = mat4(
            cos(-u_c_rot.z), sin(-u_c_rot.z), 0.0, 0.0,
            -sin(-u_c_rot.z), cos(-u_c_rot.z), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        float asp = u_c_proj.x;
        float fov = u_c_proj.y;
        float near = u_c_proj.z;
        float far = u_c_proj.w;
        mat4 m_cam_proj = mat4(
            1.0 / (asp * tan(fov / 2.0)), 0.0, 0.0, 0.0,
            0.0, 1.0 / tan(fov / 2.0), 0.0, 0.0,
            0.0, 0.0, (near + far) / (near - far), -1.0,
            0.0, 0.0, (2.0 * near * far) / (near - far), 0.0
        );

        if (u_mode_v == 1) {
            pos = m_m_size * pos;
            pos = m_m_rot_z * m_m_rot_y * m_m_rot_x * pos;
            pos = m_m_pos * pos;
        } else if (u_mode_v == 2) {
            pos = m_p_size * pos;
            pos = m_p_pos * pos;
            pos = m_p_rot_z * m_p_rot_y * m_p_rot_x * pos;
            pos = m_m_size * pos;
            pos = m_m_rot_z * m_m_rot_y * m_m_rot_x * pos;
            pos = m_m_pos * pos;
        }

        pos = m_c_pos * pos;
        pos = m_z_inv * pos;
        pos = m_c_rot_z * m_c_rot_y * m_c_rot_x * pos;
        pos = m_cam_proj * pos;
        gl_Position = pos;

        vec4 normal = vec4(normalize(a_normal), 1.0);

        if (u_mode_v == 1) {
            normal = m_m_rot_z * m_m_rot_y * m_m_rot_x * normal;
        }
        if (u_mode_v == 2) {
            normal = m_p_rot_z * m_p_rot_y * m_p_rot_x * normal;
            normal = m_m_rot_z * m_m_rot_y * m_m_rot_x * normal;
        }
        vec3 normal_3 = vec3(normal.x, normal.y, normal.z);
        p_normal = normalize(normal_3);
    }
    p_texcoord = a_texcoord;
}
