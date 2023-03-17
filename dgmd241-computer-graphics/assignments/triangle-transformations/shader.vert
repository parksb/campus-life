#version 410 core

layout(location=0) in vec3 in_Position;
uniform mat3 transformMatrix;

void main(void) {
  vec3 p2 = vec3(in_Position.xy, 1) * transformMatrix;
	gl_Position= vec4(p2.xy, 0, 1.0);
}

