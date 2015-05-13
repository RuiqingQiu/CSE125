uniform sampler2D tex;
uniform sampler2D norm;
uniform sampler2D gloss;
uniform sampler2D metallic;
varying vec4 Position;
varying vec3 Normal;
varying vec2 TexCoords;

varying vec3 Tangent;

varying vec3 LightDir;
varying vec3 ViewDir;
varying float height_pass;

//Fog Attributes
float maxDist = 150.0;
float minDist = 10.0;
vec4 color = vec4(0.5, 0.5, 0.5, 1.0);

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shininess;

vec4 lights[5];
vec3 phongModel(vec3 normal, vec3 diffR){
	
	lights[0] = vec4(0.0, 10.0, 20.0, 1.0);
	lights[1] = vec4(5.0, 0.0, 0.0, 1.0);
	lights[2] = vec4(-5.0, 0.0, -10.0, 1.0);
	lights[3] = vec4(-5.0, 5.0, -10.0, 1.0);
	lights[4] = vec4(-5.0, -5.0, -10.0, 1.0);



	vec3 Ld = vec3(1.0, 1.0, 1.0);
    vec3 La = vec3(0.4, 0.4, 0.4);
    vec3 Ls = vec3( 1.0, 1.0, 1.0);
	vec3 LightPosition = vec3(0,0,10);
    vec3 Intensity = vec3(0.9,0.9,0.9);
	vec3 ambAndDiff = La * Ka;
	vec3 spec = vec3(0.0);
	for(int i = 0; i < 5; i++){
		vec3 n = normalize(Normal);
		vec3 s = normalize(vec3(lights[i] - Position));
		vec3 v = normalize(-Position.xyz);
		vec3 r = reflect(-s, n);
		float sDotN = max( dot(s,Normal), 0.0 );
		vec3 diffuse = Ld * Kd * sDotN;
		if( sDotN > 0.0 )
		    spec += Ls * Ks * pow( max( dot(r,v), 0.0 ), Shininess );
		ambAndDiff += diffuse;
	}
	return ambAndDiff + spec;
}

void main() {
 
    vec4 normal = 2.0 * texture2D(norm, TexCoords) - 1.0;
    vec4 texColor = texture2D(tex, TexCoords);
    float dist = length(Position.xyz);
    float fogFactor = (maxDist - dist)/(maxDist-minDist);
    fogFactor = clamp(fogFactor, 0.0, 1.0);
    vec4 shadeColor = vec4(phongModel(normal.xyz, texColor.rgb), 1.0);
    gl_FragColor = shadeColor;
	//gl_FragColor = mix(color, shadeColor, fogFactor);
}