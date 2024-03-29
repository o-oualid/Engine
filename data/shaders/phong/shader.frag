#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 1) uniform sampler texSampler;
layout(set = 0, binding = 2) uniform texture2D textures[3];

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec4 pos;
layout(location = 3) in vec3 inNormal;

flat struct Material{
    vec4 color;
    uint useColor;
};

layout(location = 4)  in flat Material material;

layout(location = 0) out vec4 outColor;


void main() {
    if (material.useColor==0){
        vec3 color=vec3(material.color);
        vec3 normal=normalize(inNormal);
        vec3 light=normalize(vec3(0.0f, -1.0f, 2.0f));
        vec3 lightColor=vec3(1.0f, 1.0f, 0.9f);
        float cosTheta = clamp(dot(normal, light), 0.05, 1);

        outColor =vec4(lightColor*color*cosTheta, 1.0f);
    }
    else outColor = texture(sampler2D(textures[material.useColor-1], texSampler), fragTexCoord);

}