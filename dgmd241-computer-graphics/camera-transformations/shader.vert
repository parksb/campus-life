#version 410 core

layout(location=0) in vec3 in_Position;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(void) {
  vec4 p = vec4(in_Position.xyz, 1);
  p = projMat * viewMat * modelMat * p;
	gl_Position= p;
}

