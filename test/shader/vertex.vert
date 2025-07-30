#version 330 core
in vec4 a_position;
in vec3 a_color;
uniform vec3 u_rotate;
uniform mat4 u_mat;
out vec3 p_color;

void getRotate(in vec3 rot, out mat4 rotation_mat) {
    float sx = sin(rot.x);
    float sy = sin(rot.y);
    float sz = sin(rot.z);
    float cx = cos(rot.x);
    float cy = cos(rot.y);
    float cz = cos(rot.z);

    mat4 rot_x = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cx, -sx, 0.0,
        0.0, sx, cx, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    mat4 rot_y = mat4(
        cy, 0.0, sy, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sy, 0.0, cy, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    mat4 rot_z = mat4(
        cz, -sz, 0.0, 0.0,
        sz, cz, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    rotation_mat = rot_z * rot_y * rot_x * mat4(1.0);
}

void main() {
    mat4 rotation_mat = mat4(1.0);
    getRotate(u_rotate, rotation_mat);
    gl_Position = rotation_mat * a_position;
    p_color = a_color;
}