#version 330

layout(location = 0) in uint aData;

uniform mat4 projView;
uniform uvec3 chunkOffset;
uniform uint colorPalette[16];

vec3 unpackPosition(uint data);
uint unpackColorID(uint data);
vec4 hexToColor(uint hex);

out vec4 vColor;

void main() {
    uint hex = colorPalette[unpackColorID(aData)];
    vColor = hexToColor(hex);
    gl_Position = projView * vec4(unpackPosition(aData) + chunkOffset, 1.0);
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

vec4 hexToColor(uint hex) {
    return vec4(
        float((hex >> 24u) & 0xFFu),
        float((hex >> 16u) & 0xFFu),
        float((hex >> 8u) & 0xFFu),
        float((hex >> 0u) & 0xFFu)
    ) / 255.0;
}