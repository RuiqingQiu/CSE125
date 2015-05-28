uniform sampler2D tex;
uniform sampler2D norm;
uniform sampler2D gloss;
uniform sampler2D metallic;
uniform samplerCube cubeMap;

varying vec4 Position;
varying vec3 Normal;
varying vec2 TexCoords;

varying vec3 Tangent;

varying vec3 LightDir;
varying vec3 ViewDir;

//Fog Attributes
float maxDist = 150.0;
float minDist = 10.0;
vec4 color = vec4(0.5, 0.5, 0.5, 1.0);

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shininess;
varying mat3 toObjectLocal;

#define MAX_LIGHTS 6 

struct Light
{
  vec4 position;
  vec3 Ld;
  vec3 La;
  vec3 Ls;
};

uniform Light lights[MAX_LIGHTS];
uniform vec4 camera_offset;
vec3 phongModel(vec3 normal, vec3 diffR){

	lights[0].position = camera_offset + lights[0].position;
	lights[1].position = camera_offset + lights[1].position;
	lights[2].position = camera_offset + lights[2].position;
	lights[3].position = camera_offset + lights[3].position;
	lights[4].position = camera_offset + lights[4].position;
	lights[5].position = camera_offset + lights[5].position;
	
	//lights[0].position.y = lights[0].position.y + 10;
	//lights[1].position.y = lights[0].position.y + 10;
	//lights[2].position.y = lights[0].position.y + 10;
	//lights[3].position.y = lights[0].position.y + 10;
	//lights[4].position.y = lights[0].position.y + 10;
	//lights[5].position.y = lights[0].position.y + 10;

	
	vec3 ambAndDiff = lights[0].La * Ka;
	vec3 spec = vec3(0.0);
	for(int i = 0; i < MAX_LIGHTS; i++){
		float attenuation = 1.0 / (1.0 + 0.0 * length(lights[i].position - Position) + 0.001 * pow(length(lights[i].position - Position), 2));
		vec3 LightDir = normalize(toObjectLocal * (lights[i].position - Position.xyz));
		vec3 ViewDir = toObjectLocal * normalize(-Position.xyz);
		vec3 r = reflect(-LightDir, normal);
		float sDotN = max(dot(LightDir, normal), 0.0);
    
		vec3 diffuse = attenuation * (lights[i].Ld * diffR * sDotN);
    
		if(sDotN > 0.0){
			//Ks = texture2D(gloss, TexCoords).xyz;
			//spec += attenuation * (lights[i].Ls * Ks * pow(max(dot(r, ViewDir), 0.0), Shininess));
		}
		ambAndDiff += diffuse;
	}
    return ambAndDiff + spec;

}

void main() {
    vec4 normal = 2.0 * texture2D(norm, TexCoords) - 1.0;
	/*
	vec3 incident_eye = normalize(Position.xyz);
	vec3 reflected = reflect(incident_eye, normal.xyz);
	//reflected = vec3(ViewMatrix * vec4(reflected, 0.0));
	vec4 cubeMapColor = textureCube(cubeMap, reflected);
	//gl_FragColor = cubeMapColor;
	*/
    vec4 texColor = texture2D(tex, TexCoords);
    vec4 shadeColor = vec4(phongModel(normal.xyz, texColor.rgb), 1.0);
    gl_FragColor = pow(shadeColor,vec4(1.0/2.2));
}