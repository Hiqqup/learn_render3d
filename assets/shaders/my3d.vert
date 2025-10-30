#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 transform;
uniform mat4 normalTransform;
out vec3 normal;
void main() {
    gl_Position =transform*vec4(aPos, 1.0f);
    normal = vec3( normalTransform*vec4(aNormal, 0.0f));
}
