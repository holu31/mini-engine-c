#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vUV;
layout (location = 2) in vec3 vNormal;

uniform mat4 uView;
uniform mat4 uProj;
uniform mat4 uModel;

out vec3 fPos;
out vec2 fUV;
out vec3 fNormal;

void main() {
	gl_Position = uProj * uView * uModel * vec4(vPos, 1.0);

	fPos = vPos;
	fUV = vUV;
	fNormal = vNormal;
}