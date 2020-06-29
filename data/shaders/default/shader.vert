#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(std430, push_constant) uniform PushConstants {
    mat4 MVP;
    int textueId;
} constants;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec4 pos;
layout(location = 3) out uint textureId;


void main() {
    pos = ubo.proj * ubo.view * constants.MVP * vec4(inPosition, 1.0);
    fragColor = vec4(inColor,1.0f);
    fragTexCoord = inTexCoord;
    gl_Position=pos;
    textureId=constants.textueId;
}