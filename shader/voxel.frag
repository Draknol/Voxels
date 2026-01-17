#version 330 core

in vec4 vColor;
in vec3 vNorm;
out vec4 FragColor;

void main() {
    FragColor = vColor * vec4(1f, 1f, 0.98f, 1f) * (0.25f + max(dot(vNorm, normalize(vec3(-1.3f, 1.5f, -1f))), 0f));
}