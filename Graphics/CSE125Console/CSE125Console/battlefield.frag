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

varying vec3 ReflectDir;


#define MAX_LIGHTS 4 

struct Light
{
  vec4 position;
  vec3 Ld;
  vec3 La;
  vec3 Ls;
};

uniform Light lights[MAX_LIGHTS];
uniform vec4 camera_offset;
uniform vec3 camera_rot;
uniform mat4 CamRotMatrix;

mat4 skyred= mat4(
 0.187801 ,-0.034054, -0.031252 ,-0.028169 ,

-0.034054 ,-0.187801 , 0.057621, -0.346192 ,

-0.031252 , 0.057621 , 0.082221 , 0.141670 ,

-0.028169 ,-0.346192,  0.141670 , 2.068047 
);


mat4 skygreen= mat4(
0.171103, -0.041203 ,-0.030414 ,-0.052998 ,

-0.041203, -0.171103 , 0.099270 ,-0.380704 ,

-0.030414,  0.099270 , 0.096393 , 0.095560, 

-0.052998, -0.380704 , 0.095560 , 2.170781 
);

mat4 skyblue= mat4(
 0.150290 ,-0.034794 ,-0.018080 ,-0.121960 ,

-0.034794, -0.150290 , 0.125244 ,-0.441708 ,

-0.018080,  0.125244 , 0.073867 , 0.050861, 

-0.121960 ,-0.441708 , 0.050861  ,2.283642 
);

float irradmat (mat4 M, vec3 aaa)
{
    vec4 p = vec4( aaa.xyz, 1 );
	//mat4 M2 = M;
	vec4 temp = p*M;
	return dot(p,temp);
}


mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

vec4 rotationGO(vec4 reflectd4 , mat4 rx, mat4 ry, mat4 rz)
{
	vec4 reflectd4z = rz*reflectd4;
	vec4 reflectd4y = ry*reflectd4z;
	vec4 reflectd4x = rx*reflectd4y;
	return reflectd4x;
}

vec3 phongModel(vec3 normal, vec3 diffR){

	//mat4 rotationx = rotationMatrix(vec3(1,0,0), -camera_rot.x*0.0174532925);
	//mat4 rotationy = rotationMatrix(vec3(0,1,0), -camera_rot.y*0.0174532925);
	//mat4 rotationz = rotationMatrix(vec3(0,0,1), -camera_rot.z*0.0174532925);

	lights[0].position = CamRotMatrix*(camera_offset + lights[0].position);
	lights[1].position = CamRotMatrix*(camera_offset + lights[1].position);
	lights[2].position = CamRotMatrix*(camera_offset + lights[2].position);
	lights[3].position = CamRotMatrix*(camera_offset + lights[3].position);
	//lights[4].position = CamRotMatrix*(camera_offset + lights[4].position);
	//lights[5].position = CamRotMatrix*(camera_offset + lights[5].position);
	
	//lights[0].position.y = lights[0].position.y + 10;
	//lights[1].position.y = lights[0].position.y + 10;
	//lights[2].position.y = lights[0].position.y + 10;
	//lights[3].position.y = lights[0].position.y + 10;
	//lights[4].position.y = lights[0].position.y + 10;
	//lights[5].position.y = lights[0].position.y + 10;

	
	vec3 ambAndDiff = lights[0].La * Ka;
	vec3 spec = vec3(0.0);
	for(int i = 0; i < MAX_LIGHTS; i++){
		float attenuation =1.0 /( 1.0 + 0.001* pow(length(lights[i].position - Position), 2) );
		vec3 LightDir = normalize(toObjectLocal * (lights[i].position - Position.xyz));
		vec3 ViewDir = toObjectLocal * normalize(Position.xyz);
		vec3 r = reflect(-LightDir, normal);
		float sDotN = max(dot(LightDir, normal), 0.0);
    
		vec3 diffuse =  attenuation * (lights[i].Ld * diffR * sDotN);
    
		if(sDotN > 0.0){
			Ks = texture2D(gloss, TexCoords).xyz;
			spec += attenuation * (lights[i].Ls * Ks * pow(max(dot(r, ViewDir), 0.0), Shininess));
		}
		ambAndDiff += diffuse;
	}
    return ambAndDiff + spec;

}

void main() {
    vec4 normal = 2.0 * texture2D(norm, TexCoords) - 1.0;
    vec4 texColor = texture2D(tex, TexCoords);
    vec4 shadeColor = vec4(phongModel(normal.xyz, texColor.rgb), 1.0);

	vec3 ViewDir = toObjectLocal * normalize(Position.xyz);
	vec3 reflectdir2 = reflect(ViewDir,normal);
	vec3 reflectd = inverse(toObjectLocal)*reflectdir2; 

	vec4 reflectd4 = vec4(reflectd.xyz,1.0);
	vec4 reflectd4x = inverse(CamRotMatrix)*reflectd4;
	vec4 cubeMapColor = textureCube(cubeMap, reflectd4x);


	 float albedo = 0.1f;

	vec3 n = -normalize(toObjectLocal*normal.xyz);
	  
    vec3 shadeColor2 = vec3 (

	   albedo*abs(irradmat (skyred,  n)),
	   albedo*abs(irradmat (skygreen, n)), 
	   albedo*abs(irradmat (skyblue,  n))
	   ) ;
	//shadeColor2 = normalize(shadeColor2);

    gl_FragColor = vec4(shadeColor2,1) + cubeMapColor*0.02*vec4(Kd.xyz,1) + shadeColor;

    //gl_FragColor = cubeMapColor*0.2*vec4(Kd.xyz,1)+ shadeColor + vec4(0.1,0.1,0.1,1);

}