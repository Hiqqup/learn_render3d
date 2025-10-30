#version 460 core
in vec3 normal;
out vec4 fragColor;
uniform vec4 color;
uniform vec3 lightDireciton = vec3(0.0f,1.0f,0.0f);
void main() {
    vec3 normalizedNormal = normalize(normal);
    vec3 normalizedLightDirection = normalize(lightDireciton);
    float dotProduct = dot(normalizedNormal,normalizedLightDirection);
    fragColor =max( color * dotProduct, 0.f);
    //fragColor = vec4(vec3(dotProduct), 1.0f);
    //fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
