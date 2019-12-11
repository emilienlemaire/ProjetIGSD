#version 330 core

layout( location = 0 ) in vec3 in_Position;
layout( location = 1 ) in vec3 in_Normal;


uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Rotate;

out float frag_Depth;
out vec3 frag_Position;
out vec3 frag_Normal;

void main() {

    frag_Position = vec3(u_Rotate * u_Model * vec4(in_Position, 1.f));
    frag_Normal = mat3(transpose(inverse(u_Model))) * in_Normal;

    gl_Position = u_Projection * u_View * u_Rotate * u_Model * vec4(in_Position, 1.f);
    frag_Depth = gl_Position.z;
}
