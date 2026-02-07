#version 330 core

// ==========================================================
// CONFIG
// ==========================================================
#define MAX_DIR_LIGHTS   10
#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS  10

out vec4 FragColor;

// ==========================================================
// INPUTS FROM VERTEX SHADER
// ==========================================================
in vec3 vWorldPos;
in vec3 vNormal;
in vec2 vUV;

// ==========================================================
// MATERIAL
// ==========================================================
uniform vec3  uAlbedo;
uniform float uMetallic;
uniform float uRoughness;
uniform float uAO;

// ==========================================================
// CAMERA
// ==========================================================
uniform vec3 uCamPos;

// ==========================================================
// LIGHT UBO (std140 aligned)
// ==========================================================
layout(std140) uniform LightBlock
{
    int  uDirLightCount;
    int  uPointLightCount;
    int  uSpotLightCount;
    float _pad0; // std140 alignment

    vec4 uDirLightDirections[MAX_DIR_LIGHTS]; // xyz = direction
    vec4 uDirLightColors[MAX_DIR_LIGHTS];     // rgb = color * intensity

    vec4 uSpotLightPositions[MAX_SPOT_LIGHTS];   // xyz = position
    vec4 uSpotLightDirections[MAX_SPOT_LIGHTS];  // xyz = direction
    vec4 uSpotLightColors[MAX_SPOT_LIGHTS];      // rgb = color * intensity
    vec4 uSpotLightParams[MAX_SPOT_LIGHTS];      

    // ---- Reserved for future ----
    // vec4 uPointLightPositions[MAX_POINT_LIGHTS];
    // vec4 uPointLightColors[MAX_POINT_LIGHTS];
    // vec4 uSpotLightData[MAX_SPOT_LIGHTS];
};

// ==========================================================
// CONSTANTS
// ==========================================================
const float PI = 3.14159265359;

// ==========================================================
// PBR FUNCTIONS
// ==========================================================

// GGX Normal Distribution
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a  = roughness * roughness;
    float a2 = a * a;

    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    return a2 / (PI * denom * denom);
}

// Schlick-GGX Geometry
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}

// Smith Geometry
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);

    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

// Fresnel (Schlick)
vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// ==========================================================
// MAIN
// ==========================================================
void main()
{
    vec3 N = normalize(vNormal);
    vec3 V = normalize(uCamPos - vWorldPos);

    float roughness = clamp(uRoughness, 0.04, 1.0);
    float metallic  = clamp(uMetallic, 0.0, 1.0);

    vec3 F0 = mix(vec3(0.04), uAlbedo, metallic);

    vec3 Lo = vec3(0.0);

    // ======================================================
    // DIRECTIONAL LIGHTS (UBO-driven)
    // ======================================================
    for (int i = 0; i < uDirLightCount; ++i)
    {
        vec3 L = normalize(-uDirLightDirections[i].xyz);
        vec3 H = normalize(V + L);

        vec3 lightColor = uDirLightColors[i].xyz;

        float NDF = DistributionGGX(N, H, roughness);
        float G   = GeometrySmith(N, V, L, roughness);
        vec3  F   = FresnelSchlick(max(dot(H, V), 0.0), F0);

        vec3 numerator = NDF * G * F;
        float denom =
            4.0 * max(dot(N, V), 0.0) *
            max(dot(N, L), 0.0) + 0.001;

        vec3 specular = numerator / denom;

        vec3 kS = F;
        vec3 kD = (vec3(1.0) - kS) * (1.0 - metallic);

        float NdotL = max(dot(N, L), 0.0);

        Lo += (kD * uAlbedo / PI + specular) *
              lightColor * NdotL;
    }

    // ======================================================
    // SPOT LIGHTS
    // ======================================================
    for (int i = 0; i < uSpotLightCount; ++i)
    {
        vec3 lightPos   = uSpotLightPositions[i].xyz;
        vec3 lightDir   = normalize(uSpotLightDirections[i].xyz);
        vec3 lightColor = uSpotLightColors[i].xyz;

        float innerCut  = uSpotLightParams[i].x;
        float outerCut  = uSpotLightParams[i].y;
        float range     = uSpotLightParams[i].z;

        vec3 L = lightPos - vWorldPos;
        float distance = length(L);

        if (distance > range)
            continue;

        L = normalize(L);

        // ---- Angular attenuation ----
        float theta = dot(L, normalize(-lightDir));
        float epsilon = innerCut - outerCut;
        float intensity = clamp((theta - outerCut) / epsilon, 0.0, 1.0);

        // ---- Distance attenuation ----
        float attenuation = 1.0 / (distance * distance);

        vec3 H = normalize(V + L);

        float NDF = DistributionGGX(N, H, roughness);
        float G   = GeometrySmith(N, V, L, roughness);
        vec3  F   = FresnelSchlick(max(dot(H, V), 0.0), F0);

        vec3 numerator = NDF * G * F;
        float denom =
            4.0 * max(dot(N, V), 0.0) *
            max(dot(N, L), 0.0) + 0.001;

        vec3 specular = numerator / denom;

        vec3 kS = F;
        vec3 kD = (vec3(1.0) - kS) * (1.0 - metallic);

        float NdotL = max(dot(N, L), 0.0);

        Lo += (kD * uAlbedo / PI + specular) *
              lightColor *
              NdotL *
              attenuation *
              intensity;
    }

    // ======================================================
    // AMBIENT
    // ======================================================
    vec3 ambient = vec3(0.03) * uAlbedo * uAO;

    vec3 color = ambient + Lo;

    // ======================================================
    // TONE MAPPING + GAMMA
    // ======================================================
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0 / 2.2));

    FragColor = vec4(color, 1.0);
}
