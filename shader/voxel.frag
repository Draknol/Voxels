#version 330 core

in vec4 vColor;
in vec3 vFragPos;
in vec3 vNorm;
out vec4 FragColor;

uniform vec3 viewPos;

void main() {

    vec4 lightColor = vec4(1f, 1f, 0.98f, 1f) * 0.45f;
    vec3 viewDir = normalize(viewPos - vFragPos);
    vec3 lightDir = normalize(vec3(-1.3f, 1.5f, -1.0f));
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float ambient = 1.0f;
    float diffuse = max(dot(vNorm, lightDir), 0.0f);
    float specular = 0.23f * pow(max(dot(vNorm, halfwayDir), 0.0), 16.0f);

    FragColor = vColor * lightColor * (ambient + diffuse + specular);
}