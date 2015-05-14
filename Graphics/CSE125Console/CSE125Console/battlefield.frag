uniform sampler2D tex;
uniform sampler2D norm;
uniform sampler2D gloss;
uniform sampler2D metallic;
varying vec4 Position;
varying vec3 Normal;
varying vec2 TexCoords;

varying vec3 Tangent;

varying vec3[3] LightDir;
varying vec3 ViewDir;
varying float height_pass;

//Fog Attributes
float maxDist = 150.0;
float minDist = 10.0;

vec3 Kd = vec3(0.64, 0.64, 0.64);
vec3 Ld = vec3(1.0, 1.0, 1.0);
vec3 Ka = vec3(0.0, 0.0, 0.0);
vec3 La = vec3(0.4, 0.4, 0.4);
vec3 Ks = vec3(0.5, 0.5, 0.5);
vec3 Ls = vec3( 1.0, 1.0, 1.0);
float Shininess = 100.0;
vec3 Intensity = vec3(0.9,0.9,0.9);
    
vec3 phongModel(vec3 normal, vec3 diffR){
	vec3 spec = vec3(0.0);
	vec3 ambAndDiff = vec3(0.0);
	for(int i = 0; i < 3; i++){
		vec3 r = reflect(-LightDir[i], normal);
		vec3 ambient = Intensity * Ka;
		float sDotN = max(dot(LightDir[i], normal), 0.0);
    
		vec3 diffuse = Intensity * diffR * sDotN;
    
		if(sDotN > 0.0){
			spec += Intensity * Ks * pow(max(dot(r, ViewDir), 0.0), Shininess);
		}
		ambAndDiff += ambient + diffuse;
	}
    return spec + ambAndDiff;
}

void main() {
    vec4 normal = 2.0 * texture2D(norm, TexCoords) - 1.0;
    vec4 texColor = texture2D(tex, TexCoords);
    vec3 ambAndDiff, spec;
    vec4 shadeColor = vec4(phongModel(normal.xyz, texColor.rgb), 1.0);
	gl_FragColor = shadeColor;
}