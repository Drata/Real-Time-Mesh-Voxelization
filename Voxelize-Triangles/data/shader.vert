attribute vec3 vpos;

void main() {
	gl_Position = vec4(vpos, 1);
}