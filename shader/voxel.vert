#version 330

uniform vec3 cubePos;
uniform mat4 projView;

vec3 Vertices[8] = vec3[](
    vec3( 0.5,  0.5,  0.5),
    vec3( 0.5,  0.5, -0.5),
    vec3( 0.5, -0.5,  0.5),
    vec3( 0.5, -0.5, -0.5),
    vec3(-0.5,  0.5,  0.5),
    vec3(-0.5,  0.5, -0.5),
    vec3(-0.5, -0.5,  0.5),
    vec3(-0.5, -0.5, -0.5)
);

int Elements[36] = int[](
    1, 5, 4, 1, 4, 0,
    2, 0, 4, 2, 4, 6,
    6, 4, 5, 6, 5, 3,
    7, 3, 2, 7, 2, 6,
    3, 1, 0, 3, 0, 2,
    7, 5, 1, 7, 1, 3
);

void main() {
    vec3 pos = Vertices[Elements[gl_VertexID]] + cubePos;
    gl_Position = projView * vec4(pos, 1.0);
}