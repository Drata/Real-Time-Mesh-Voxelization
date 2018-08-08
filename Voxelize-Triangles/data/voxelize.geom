#version 150

layout ( points ) in;
layout ( triangle_strip, max_vertices = 24) out;

uniform mat4 mvp;

const float size = 0.1;
const vec3 lightDirection = normalize(vec3(0.4, -1.0, 0.8));

out vec3 finalColor;

void createVertex(vec3 offset, vec3 faceNormal) {
	vec4 actualOffset = vec4(offset * size, 0.0);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	float brightness = max(dot(-lightDirection, faceNormal), 0.3);
	finalColor = vec3(1.0, 1.0, 1.0) * brightness;
	gl_Position = mvp * worldPosition;
	EmitVertex();
}

void main(void) {
	vec3 faceNormal = vec3(0.0, 0.0, 1.0);
	createVertex(vec3(-1.0, 1.0, 1.0), faceNormal);
	createVertex(vec3(-1.0, -1.0, 1.0), faceNormal);
	createVertex(vec3(1.0, 1.0, 1.0), faceNormal);
	createVertex(vec3(1.0, -1.0, 1.0), faceNormal);
	
	EndPrimitive();
	
	faceNormal = vec3(1.0, 0.0, 0.0);
	createVertex(vec3(1.0, 1.0, 1.0), faceNormal);
	createVertex(vec3(1.0, -1.0, 1.0), faceNormal);
	createVertex(vec3(1.0, 1.0, -1.0), faceNormal);
	createVertex(vec3(1.0, -1.0, -1.0), faceNormal);
	
	EndPrimitive();
	
	faceNormal = vec3(0.0, 0.0, -1.0);
	createVertex(vec3(1.0, 1.0, -1.0), faceNormal);
	createVertex(vec3(1.0, -1.0, -1.0), faceNormal);
	createVertex(vec3(-1.0, 1.0, -1.0), faceNormal);
	createVertex(vec3(-1.0, -1.0, -1.0), faceNormal);
	
	EndPrimitive();
	
	faceNormal = vec3(-1.0, 0.0, 0.0);
	createVertex(vec3(-1.0, 1.0, -1.0), faceNormal);
	createVertex(vec3(-1.0, -1.0, -1.0), faceNormal);
	createVertex(vec3(-1.0, 1.0, 1.0), faceNormal);
	createVertex(vec3(-1.0, -1.0, 1.0), faceNormal);
	
	EndPrimitive();
	
	faceNormal = vec3(0.0, 1.0, 0.0);
	createVertex(vec3(1.0, 1.0, 1.0), faceNormal);
	createVertex(vec3(1.0, 1.0, -1.0), faceNormal);
	createVertex(vec3(-1.0, 1.0, 1.0), faceNormal);
	createVertex(vec3(-1.0, 1.0, -1.0), faceNormal);
	
	EndPrimitive();
	
	faceNormal = vec3(0.0, -1.0, 0.0);
	createVertex(vec3(-1.0, -1.0, 1.0), faceNormal);
	createVertex(vec3(-1.0, -1.0, -1.0), faceNormal);
	createVertex(vec3(1.0, -1.0, 1.0), faceNormal);
	createVertex(vec3(1.0, -1.0, -1.0), faceNormal);
	
	EndPrimitive();
}