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

#define MAX_LIGHTS 6 

struct Light
{
  vec4 position;
  vec3 Ld;
  vec3 La;
  vec3 Ls;
};

Light lights[MAX_LIGHTS];
uniform vec4 camera_offset;
vec3 phongModel(vec3 normal, vec3 diffR){
	
	
	lights[0].position = camera_offset + vec4(0.0, 10.0, 0.0, 1.0);
	lights[1].position = camera_offset + vec4(5.0, 0.0, 0.0, 1.0);
	lights[2].position = camera_offset + vec4(-5.0, 0.0, -10.0, 1.0);
	lights[3].position = camera_offset + vec4(-5.0, 5.0, -10.0, 1.0);
	lights[4].position = camera_offset + vec4(5.0, 0.0, -10.0, 1.0);
	lights[5].position = camera_offset + vec4(0.0, 50.0, 0.0, 1.0);
	
	lights[0].Ld = vec3(1.0, 1.0, 1.0);
	lights[0].La = vec3(0.4, 0.4, 0.4);
	lights[0].Ls = vec3(1.0, 1.0, 1.0);

	lights[1].Ld = vec3(0.0, 0.0, 0.9);
	lights[1].La = vec3(0.4, 0.4, 0.4);
	lights[1].Ls = vec3(1.0, 1.0, 1.0);

	lights[2].Ld = vec3(0.0, 0.9, 0.0);
	lights[2].La = vec3(0.4, 0.4, 0.4);
	lights[2].Ls = vec3(1.0, 1.0, 1.0);

	lights[3].Ld = vec3(1.0, 1.0, 0.0);
	lights[3].La = vec3(0.4, 0.4, 0.4);
	lights[3].Ls = vec3(1.0, 1.0, 1.0);

	lights[4].Ld = vec3(0.0, 1.0, 1.0);
	lights[4].La = vec3(0.4, 0.4, 0.4);
	lights[4].Ls = vec3(1.0, 1.0, 1.0);

	lights[5].Ld = vec3(1.0, 0.0, 1.0);
	lights[5].La = vec3(0.4, 0.4, 0.4);
	lights[5].Ls = vec3(1.0, 1.0, 1.0);
	
	
	vec3 Ld = vec3(1.0, 1.0, 1.0);
    vec3 La = vec3(0.4, 0.4, 0.4);
    vec3 Ls = vec3( 1.0, 1.0, 1.0);
	vec3 LightPosition = vec3(0,0,10);
    vec3 Intensity = vec3(0.9,0.9,0.9);
	vec3 ambAndDiff = lights[0].La * Ka;
	vec3 spec = vec3(0.0);
	for(int i = 0; i < MAX_LIGHTS; i++){
		float attenuation = 1.0 / (1.0 + 0.0 * length(lights[i].position - Position) + 0.01 * pow(length(lights[i].position - Position), 2));
		vec3 n = normalize(Normal);
		vec3 s = normalize(vec3(lights[i].position - Position));
		vec3 v = normalize(-Position.xyz);
		vec3 r = reflect(-s, n);
		float sDotN = max( dot(s,Normal), 0.0 );
		vec3 diffuse = attenuation * (lights[i].Ld * Kd * sDotN);
		if( sDotN > 0.0 )
		    spec += attenuation * (lights[i].Ls * Ks * pow( max( dot(r,v), 0.0 ), Shininess ));
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