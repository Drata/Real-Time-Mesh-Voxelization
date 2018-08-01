struct Light {
	vec3 color;
	vec4 vec;
	float att;
};

varying vec2 ftex;
varying vec4 fpositionobs;
varying vec3 fnormal;

uniform sampler2D sampler;
uniform int isTexture;
uniform vec4 diffuse;
uniform int nLights;
uniform int shininess;
uniform vec3 ambient;
uniform Light lights[8];

void main() {
	
	vec3 H, L, N = normalize(fnormal);
	vec3 diffuseC = vec3(0.0, 0.0, 0.0);
	vec3 specularC = vec3(0.0, 0.0, 0.0);
	float NdotL, NdotH, att;
		
	for(int i = 0; i < nLights; i++) {
		L = lights[i].vec.xyz;
		att = 1.0;
		
		if(lights[i].vec.w == 1.0) {
			L = L - fpositionobs.xyz;
			att = 1.0 / (1.0 + (lights[i].att * length(L)));
		}
		
		L = normalize(L);
		
		NdotL = max(dot(N, L), 0.0);
		diffuseC += NdotL * lights[i].color * att;
		
		if((shininess > 0) && (NdotL > 0.0)) {
			H = normalize(L - normalize(fpositionobs).xyz);
			NdotH = max(dot(N, H), 0.0);
			specularC += pow(NdotH, shininess) * att;
		}
	}
	
	if(nLights > 0) {
		if(isTexture == 1) {
			gl_FragColor = (texture2D(sampler, ftex) * diffuse * vec4(diffuseC, 1.0) * vec4(ambient, 1.0)) + vec4(specularC, 0.0);
		} else {
			gl_FragColor = (diffuse * vec4(diffuseC, 1.0)) + vec4(ambient, 1.0) + vec4(specularC, 0.0);
		}
	} else {
		if(isTexture == 1) {
			gl_FragColor = texture2D(sampler, ftex) * diffuse;
		} else {
			gl_FragColor = diffuse;
		}
	}
}
