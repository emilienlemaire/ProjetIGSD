#version 330 core

layout( location = 0 ) in vec3 in_Position;
layout( location = 1 ) in vec3 in_Normal;
layout( location = 2 ) in float in_Depth;
layout( location = 3 ) in vec2 in_Texture;


uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
uniform mat4 u_Translate;
uniform mat4 u_Scale;

out float frag_Depth;
out vec3 frag_Position;
out vec3 frag_Normal;
out vec4 frag_Color;
out vec2 frag_Texture;

void main() {

    frag_Position = vec3(u_Model * vec4(in_Position, 1.f));
    frag_Normal = mat3(transpose(inverse(u_Model))) * in_Normal;
    frag_Color = vec4(1.0f, 0.f, 0.f, 1.f);
    frag_Texture = in_Texture;
    frag_Depth = in_Depth;

    gl_Position = u_ViewProjection * u_Translate * u_Scale * vec4(in_Position, 1.f);

}
