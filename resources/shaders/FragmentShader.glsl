#version 330 core
out vec4 color;

smooth in float frag_Depth;
in vec3 frag_Position;
in vec3 frag_Normal;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform mat4 u_FragModel;
uniform mat4 u_FragRotate;
uniform vec3 u_Color;

float near = 0.1;
float far = -100.0;

float linearizeDepth(float depth) {
    return depth;
}

void main() {

    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    mat3 normalMatrix = transpose(inverse(mat3(u_FragRotate * u_FragModel)));

    vec3 position = frag_Position;

    //Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    //Diffuse
    vec3 normal = normalize(frag_Normal);
    vec3 lightDir = normalize(u_LightPos - position);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - position);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * u_Color;
    color = vec4(result, 1.f);

}
