uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 normalMat;
uniform bool isAnimation;
uniform mat4 animMat[64];

attribute vec3 vpos;
attribute vec2 vtex;
attribute vec3 vnormal;
attribute vec4 vboneIndices;
attribute vec4 vboneWeights;

varying vec2 ftex;
varying vec4 fpositionobs;
varying vec3 fnormal;

void main() {
	vec4 vpos4 = vec4(vpos, 1);
	
	if(isAnimation) {
		mat4 boneTransform = mat4(1);
		
		for (int i = 0; i < 4; ++i) {
			int index = int(vboneIndices[i]);
			if(index > -1) 
			{
				boneTransform += animMat[index] * vboneWeights[i];
			}
		}
		
		vpos4 = boneTransform * vec4(vpos, 1);
	}
		
	gl_Position = mvp * vpos4;
	fnormal = (normalMat * vec4(vnormal, 1.0)).xyz;
	ftex = vtex;
	fpositionobs = mv * vec4(vpos, 1);
}