#version 330 core

uniform vec3  uAlbedo;
uniform float uMetallic;
uniform float uRoughness;
uniform float uAO;
uniform int   uShadingModel;

out vec4 FragColor;

void main()
{
    // Temporary visualization (no lights yet)
    // Roughness darkens, metallic tints
    vec3 color = uAlbedo;

    color *= mix(1.0, 0.5, uRoughness);
    color = mix(color, vec3(0.04), uMetallic);

    FragColor = vec4(color * uAO, 1.0);
}
