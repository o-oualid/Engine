#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

flat struct Material{
    vec4 color;
    uint useColor;
};

layout(std430, push_constant) uniform PushConstants {
    mat4 MVP;
    Material material;

} constants;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec4 pos;
layout(location =3) out vec3 normal;

layout(location =4) out Material material;


void main() {
    pos = ubo.proj * ubo.view * constants.MVP * vec4(inPosition, 1.0);
    fragColor = vec4(inColor, 1.0f);
    fragTexCoord = inTexCoord;
    material=constants.material;
    normal=inNormal;
    gl_Position=pos;
}