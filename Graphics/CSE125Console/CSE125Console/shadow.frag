uniform sampler2D tex;
uniform sampler2D norm;
uniform sampler2D gloss;
uniform sampler2D metallic;

uniform vec3 scaleBias;
varying vec3 eyeVec;
uniform vec3 CAMERA_POSITION; 

varying vec3 position;
varying vec3 lightvec;
varying vec3 mode;

varying vec3 vN;
varying vec3 v;


float PhongApprox( float Roughness, float RoL )
{
	float a = Roughness * Roughness;			// 1 mul
	float a2 = a * a;						// 1 mul
	//float rcp_a2 = rcp(a2);					// 1 rcp
	float rcp_a2 = exp2( -6.88886882 * Roughness + 6.88886882 );

	// Spherical Gaussian approximation: pow( x, n ) ~= exp( (n + 0.775) * (x - 1) )
	// Phong: n = 0.5 / a2 - 0.5
	// 0.5 / ln(2), 0.275 / ln(2)
	float c = 0.72134752 * rcp_a2 + 0.39674113;	// 1 mad
	return rcp_a2 * exp2( c * RoL - c );		// 2 mad, 1 exp2, 1 mul
	// Total 7 instr
}

vec3 EnvBRDFApprox( vec3 SpecularColor, float Roughness, float NoV )
{
	// [ Lazarov 2013, "Getting More Physical in Call of Duty: Black Ops II" ]
	// Adaptation to fit our G term.
	const vec4 c0 = { -1, -0.0275, -0.572, 0.022 };
	const vec4 c1 = { 1, 0.0425, 1.04, -0.04 };
	vec4 r = Roughness * c0 + c1;
	float a004 = min( r.x * r.x, exp2( -9.28 * NoV ) ) * r.x + r.y;
	vec2 AB = vec2( -1.04, 1.04 ) * a004 + r.zw;
	return SpecularColor * AB.x + AB.y;
}



void main (void) 
{ 
	
	float specular = texture2D(gloss, gl_TexCoord[0].st).r;
	float metallic = texture2D(metallic, gl_TexCoord[0].st).r;
	vec3 baseColor = texture2D(tex, gl_TexCoord[0].st).rgb;
	vec3 norm1 = texture2D(norm, gl_TexCoord[0].st).rgb * 2.0 - 1.0;


	vec3 diffuse_color;
	vec3 specular_color;
	
	float DielectricSpecular = 0.08 * specular;
	diffuse_color = baseColor - baseColor * metallic;
	specular_color = (DielectricSpecular - DielectricSpecular * metallic) + baseColor * metallic;
	vec3 cameraVector = normalize(CAMERA_POSITION - position.xyz);
	float NoV = max(dot(norm1, cameraVector), 0);
	
	specular_color = EnvBRDFApprox(specular_color, specular, NoV);
	//specular_color = EnvBRDFApproxNonmetal( specular, NoV );
	vec3 color = 0;
	float IndirectIrradiance = 0;
		
	vec3 lightVector = normalize(lightvec);

	float nxDir = max(0.0, dot(norm1, lightVector));
	vec4 light_diffuse = gl_LightSource[0].diffuse * nxDir;
	light_diffuse = clamp(light_diffuse, 0.0, 1.0);
	   
	float specularPower = 0.0;
	if(nxDir != 0.0)
	{
		 vec3 cameraVector = normalize(CAMERA_POSITION - position.xyz);
		 vec3 halfVector = normalize(lightVector + cameraVector);
		 float nxHalf = max(0.0,dot(norm1, halfVector));
		 specularPower = pow(nxHalf, gl_FrontMaterial.shininess);
	}
	vec4 finalColor = vec4(0,0,0,0);
    vec4 light_specular = gl_LightSource[0].specular * specularPower;
    light_specular = clamp(light_specular, 0.0, 1.0); 
	finalColor = gl_LightSource[0].ambient +light_diffuse + light_specular;
	color += finalColor.rgb * diffuse_color;
	IndirectIrradiance = finalColor.a;
	
	float NoL = max(0, dot(vN, lightVector));

	vec3 tmp = normalize(position.xyz - CAMERA_POSITION);
	vec3 reflection = normalize(reflect(vN.xyz, normalize(tmp)));
	float RoL = max(0, dot(reflection, lightVector));
	float roughness = specular;
	color += NoL * finalColor.rgb * (diffuse_color + specular_color * PhongApprox(roughness, RoL));

	
	vec4 color_without_light = vec4(mix(color, diffuse_color + specular_color, 0.7), 1);
	

	gl_FragColor = color_without_light;
	//gl_FragColor = color_without_light + finalColor;
	//gl_FragColor = vec4(lightvec, 1);
}


/* Working version with normal texture and gloss */
/*
uniform sampler2D tex;
uniform sampler2D norm;
uniform sampler2D gloss;
uniform sampler2D metallic;

uniform vec3 scaleBias;
varying vec3 eyeVec;
uniform vec3 CAMERA_POSITION; 

varying vec3 position;
varying vec3 lightvec;
varying vec3 mode;

void main (void) 
{ 
	   vec3 norm1 = texture2D(norm, gl_TexCoord[0].st).rgb * 2.0 - 1.0;
	   vec3 baseColor = texture2D(tex, gl_TexCoord[0].st).rgb;

	   vec4 glossColor = texture2D(gloss, gl_TexCoord[0].st);
	   
	   vec4 finalColor = vec4(0,0,0,0);
	   float dist = length(lightvec);

	   vec3 lightVector = normalize(lightvec);

	   float nxDir = max(0.0, dot(norm1, lightVector));
	   vec4 diffuse = gl_LightSource[0].diffuse * nxDir;
	   diffuse = clamp(diffuse, 0.0, 1.0);
	   
	   float specularPower = 0.0;
	   if(nxDir != 0.0)
	   {
		 vec3 cameraVector = normalize(CAMERA_POSITION - position.xyz);
		 vec3 halfVector = normalize(lightVector + cameraVector);
		 float nxHalf = max(0.0,dot(norm1, halfVector));
		 specularPower = pow(nxHalf, gl_FrontMaterial.shininess);
	   }
		vec4 specular = gl_LightSource[0].specular * specularPower;
		specular = clamp(specular, 0.0, 1.0); 
		finalColor = gl_LightSource[0].ambient +diffuse + vec4(specular.rgb * glossColor.r, 1.0);
		gl_FragColor = vec4(baseColor.rgb, 1.0) + finalColor;
}
*/

/* Working version of a shader with normal and texture */

/*
uniform sampler2D tex;
uniform sampler2D norm;
uniform vec3 CAMERA_POSITION; 

varying vec3 position;
varying vec3 lightvec;
varying vec3 mode;


varying vec3 vN;
varying vec3 v; 
#define MAX_LIGHTS 3 

void main (void) 
{ 

	   vec3 norm1 = texture2D(norm, gl_TexCoord[0].st).rgb * 2.0 - 1.0;
	   vec3 baseColor = texture2D(tex, gl_TexCoord[0].st).rgb;
	   vec4 finalColor = vec4(0,0,0,0);
	   float dist = length(lightvec);

	   vec3 lightVector = normalize(lightvec);
	   float nxDir = max(0.0, dot(norm1, lightVector));
	   vec4 diffuse = gl_LightSource[0].diffuse * nxDir;
	   diffuse = clamp(diffuse, 0.0, 1.0);
	   float specularPower = 0.0;
	   if(nxDir != 0.0)
	   {
		 vec3 cameraVector = normalize(CAMERA_POSITION - position.xyz);
		 vec3 halfVector = normalize(lightVector + cameraVector);
		 float nxHalf = max(0.0,dot(norm1, halfVector));
		 specularPower = pow(nxHalf, gl_FrontMaterial.shininess);
	   }
		vec4 specular = gl_LightSource[0].specular * specularPower;
		//vec4 specular = gl_FrontLightProduct[0].specular * specularPower;
		specular = clamp(specular, 0.0, 1.0); 
		//gl_FragColor = vec4(norm1, 1);
		//gl_FragColor = vec4(baseColor, 1);

		finalColor = gl_LightSource[0].ambient +diffuse + specular;
		//gl_FragColor = vec4(baseColor, 1.0) + gl_FrontLightModelProduct.sceneColor + finalColor;
		gl_FragColor = vec4(baseColor, 1.0)  + finalColor;
}
*/
























/* Working fragment shader */
/*
varying vec3 vN;
varying vec3 v; 
#define MAX_LIGHTS 3 

uniform sampler2D tex;
uniform sampler2D norm;
void main (void) 
{ 
   vec3 N = normalize(vN);
   vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
   
   for (int i=0;i<MAX_LIGHTS;i++)
   {
      vec3 L = normalize(gl_LightSource[i].position.xyz - v); 
      vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0) 
      vec3 R = normalize(-reflect(L,N)); 
   
      //calculate Ambient Term: 
      vec4 Iamb = gl_FrontLightProduct[i].ambient; 
      //calculate Diffuse Term: 
      vec4 Idiff = gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0);
      Idiff = clamp(Idiff, 0.0, 1.0); 
   
      // calculate Specular Term:
      vec4 Ispec = gl_FrontLightProduct[i].specular 
             * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
      Ispec = clamp(Ispec, 0.0, 1.0); 
   
      finalColor += Iamb + Idiff + Ispec;
   }
   
   // write Total Color: 
   //gl_FragColor = gl_FrontLightModelProduct.sceneColor + finalColor; 

   vec4 color = texture2D(tex, gl_TexCoord[0].st);
   vec4 color2 = texture2D(norm, gl_TexCoord[0].st);
   //gl_FragColor = color*color2;
   gl_FragColor = color + gl_FrontLightModelProduct.sceneColor + finalColor;
   //gl_FragColor = vec4(vN, 1);
}
*/
