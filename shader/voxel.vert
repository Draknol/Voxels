#version 330

layout(location = 0) in uint aData;

uniform mat4 projView;
uniform uvec3 chunkOffset;
uniform uint materialColors[16];

vec3 unpackPosition(uint data);
uint unpackColorID(uint data);
vec3 unpackNormal(uint data);
vec4 hexToColor(uint hex);

out vec4 vColor;
out vec3 vNorm;

void main() {
    uint hex = materialColors[unpackColorID(aData)];
    vColor = hexToColor(hex);
    gl_Position = projView * vec4(unpackPosition(aData) + chunkOffset, 1.0);
    vNorm = unpackNormal(aData);
}

vec3 unpackPosition(uint data) {
    uint x = (data >> 27u) & 0x1Fu;
    uint y = (data >> 22u) & 0x1Fu;
    uint z = (data >> 17u) & 0x1Fu;
    return vec3(uvec3(x, y, z));
}

uint unpackColorID(uint data) {
    return clamp(data & 0xFu, 0u, 15u);
}

vec3 unpackNormal(uint data) {
    uint id = clamp((data >> 14u) & 0x7u, 0u, 6u);
    if (id == 0u) return vec3(-1,  0,  0);
    if (id == 1u) return vec3( 1,  0,  0);
    if (id == 2u) return vec3( 0, -1,  0);
    if (id == 3u) return vec3( 0,  1,  0);
    if (id == 4u) return vec3( 0,  0, -1);
    if (id == 5u) return vec3( 0,  0,  1);
    return vec3(0, 0, 0);
}

vec4 hexToColor(uint hex) {
    return vec4(
        float((hex >> 24u) & 0xFFu),
        float((hex >> 16u) & 0xFFu),
        float((hex >> 8u) & 0xFFu),
        float((hex >> 0u) & 0xFFu)
    ) / 255.0;
}