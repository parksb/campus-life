#version 150 core

in vec3 normal;
in vec3 worldPosition;

uniform vec4 color;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float shininess;
uniform vec3 cameraPosition;
uniform vec3 ambientLight;

out vec4 out_Color;

void main(void) {
  vec3 l = lightPosition - worldPosition;
  vec3 L = normalize(l);
  vec3 N = normalize(normal);
  vec3 V = normalize(cameraPosition - worldPosition);
  vec3 R = 2 * dot(L, N) * N - L;
  vec3 I = lightColor / dot(l, l);
  vec3 c = color.rgb * max(0, dot(L, N)) * I + color.rgb * ambientLight;
  c += pow(max(0, dot(R, V)), shininess) * I;

  out_Color = vec4(pow(c, vec3(1 / 2.2)), 1);
}

