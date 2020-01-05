#version 330 core
out vec4 color;

smooth in float frag_Depth;
in vec3 frag_Position;
in vec3 frag_Normal;
in vec4 frag_Color;
in vec2 frag_Texture;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform mat4 u_FragModel;
uniform vec3 u_Color;
uniform sampler2D u_Texture;

float near = 0.1;
float far = 100.0;

float linearizeDepth(float depth) {
    return (depth - 1.f) / (13.f - 1.f);
}

void main() {

    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    mat3 normalMatrix = transpose(inverse(mat3(u_FragModel)));

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
    vec4 colorLight = vec4(result, 1.f);
    vec4 colTex = texture(u_Texture, frag_Texture);
    vec4 colorTexture = vec4(colTex.r * colorLight.r,
               colTex.g * colorLight.g,
               colTex.b * colorLight.b,
               1.0);
    color = colorTexture;
    if(u_Color == vec3(1.f, 0.f, 1.f)) {
        gl_FragDepth = gl_FragCoord.z;
    } else {
        gl_FragDepth = gl_FragCoord.z + (frag_Depth / 1000.f);
    }
}
