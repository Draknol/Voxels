#version 330

layout(location = 0) in uvec3 aPosition;

uniform mat4 projView;
uniform uvec3 chunkOffset;

void main() {
    gl_Position = projView * vec4(aPosition + chunkOffset, 1.0);
}