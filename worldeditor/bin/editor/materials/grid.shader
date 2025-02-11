<Shader>
    <Properties>
        <Property name="scale" type="float"/>
        <Property name="width" type="float"/>
        <Property name="ortho" type="bool"/>
    </Properties>
    <Fragment>
<![CDATA[
#version 450 core

#include "ShaderLayout.h"

layout(location = 0) in vec4 _vertex;
layout(location = 1) in vec2 _uv0;

layout(location = 0) out vec4 rgb;

const float subItems = 10.0;
const float cellSize = 10.0;

layout(binding = UNIFORM) uniform Uniforms {
    float scale;
    float width;
    bool ortho;
} uni;

void main() {
    vec3 pos = _vertex.xyz / _vertex.w;
    float fog = 1.0;
    if(!uni.ortho) {
        fog = clamp(l.color.w * 100.0 * (1.0 - pos.z), 0.0, 1.0);
    }

    float cell = uni.scale / subItems / cellSize;
    float w = cell * 0.2 * uni.width;

    vec2 offset = _uv0 * subItems * uni.scale;
    if(mod(offset.x, cell) < w || mod(offset.y, cell) < w) {
        rgb = vec4(1.0, 0.0, 0.0, fog);
        if(mod(offset.x, cell * subItems) < w || mod(offset.y, cell * subItems) < w) {
            rgb = vec4(l.color.xyz, fog);
        } else {
            rgb = vec4(l.color.xyz, fog * 0.5 * (1.0 - uni.width));
        }
    } else {
        discard;
    }
}
]]>
    </Fragment>
    <Pass type="Surface" blendMode="Translucent" lightModel="Unlit" depthTest="true" depthWrite="false" twoSided="true"/>
</Shader>
