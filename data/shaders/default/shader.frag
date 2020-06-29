#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 1) uniform sampler texSampler;
layout(set = 0, binding = 2) uniform texture2D textures[3];

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec4 pos;
layout(location = 3) flat in uint textureId;

layout(location = 0) out vec4 outColor;


void main() {
    vec3 light=vec3(1.0f);
    outColor = fragColor;//;texture(fragColor/*sampler2D(textures[textureId]*/, texSampler), fragTexCoord);
}