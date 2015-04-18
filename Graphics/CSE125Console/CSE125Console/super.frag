uniform sampler2D textureMap;
uniform sampler2D normalMap;
uniform sampler2D roughMap;
uniform sampler2D metalMap;

uniform vec3 CAMERA_POSITION;
varying vec3 position;
varying vec3 lightvec;
varying vec3 WORLD_NORMAL; 
varying vec3 WORD_POSITION;

#define REFLECTION_CAPTURE_ROUGHEST_MIP 1
#define REFLECTION_CAPTURE_ROUGHNESS_MIP_SCALE 1.2 
/**
float ComputeReflectionCaptureMipFromRoughness(float Roughness)
{
	// Heuristic that maps roughness to mip level
	// This is done in a way such that a certain mip level will always have the same roughness, regardless of how many mips are in the texture
	// Using more mips in the cubemap just allows sharper reflections to be supported
	float LevelFrom1x1 = REFLECTION_CAPTURE_ROUGHEST_MIP - REFLECTION_CAPTURE_ROUGHNESS_MIP_SCALE * log2(Roughness);
	// Note: must match GReflectionCaptureSize
	float HardcodedNumCaptureArrayMips = 7;
	return HardcodedNumCaptureArrayMips - 1 - LevelFrom1x1;
}

vec3 RGBMDecode( MaterialFloat4 rgbm, float MaxValue )
{
	return rgbm.rgb * (rgbm.a * MaxValue);
}

**/
vec3 GetImageBasedReflectionLighting(float Roughness)
{

	vec3 SpecularIBL = vec3(2,2,2);//RGBMDecode(ReflectionCubemap.SampleLevel(ReflectionCubemapSampler, ProjectedCaptureVector, AbsoluteSpecularMip), 16.0f);
	SpecularIBL *= SpecularIBL;

	return SpecularIBL;
}


void main()
{
 vec3 norm = texture2D(normalMap, gl_TexCoord[0].st).rgb * 2.0 - 1.0;
 vec3 BaseColor = texture2D(textureMap, gl_TexCoord[0].st).rgb;
 float Metallic = texture2D(metalMap, gl_TexCoord[0].st).r;
 float Roughness  = texture2D(roughMap, gl_TexCoord[0].st).r;
 // float Metallic = (0.2126*metalColor.r + 0.7152*metalColor.g + 0.0722*metalColor.b);

 float Specular = Roughness;

 //Metal
 float DielectricSpecular = 0.08 * Specular;
 vec3 DiffuseColor = BaseColor - BaseColor * Metallic;
 vec3 SpecularColor =  BaseColor * (Metallic) + (DielectricSpecular - DielectricSpecular * (Metallic));

 float NoV = max( dot( WORLD_NORMAL, (WORD_POSITION - CAMERA_POSITION)), 0 );


 /***********************envBRDFfunction***********************************/
   vec4 c0 =vec4 ( -1, -0.0275, -0.572, 0.022 );
	vec4 c1 = vec4( 1, 0.0425, 1.04, -0.04 );
	vec4 r = Roughness * c0 + c1;
	float a004 = min( r.x * r.x, exp2( -9.28 * NoV ) ) * r.x + r.y;
	vec2 AB = vec2( -1.04, 1.04 ) * a004 + r.zw;

	SpecularColor = 2*SpecularColor*AB.x + AB.y;

 /*************************END_OF_FUNC********************************/
 vec3 lightcolor = vec3(0.8,0.8,0.8);

 vec3 Color = 0;
 float IndirectIrradiance = 0;

 //not material masked
 vec3 PointIndirectLighting = vec3(0.29,0.24,0.24); //inidirect coefficients
 vec3 DiffuseGI = PointIndirectLighting;

 IndirectIrradiance =  dot( DiffuseGI, vec3( 0.3, 0.59, 0.11 ));
 Color += DiffuseColor * DiffuseGI;
 Color += lightcolor * DiffuseColor;


 float NoL = max(0, dot(WORLD_NORMAL, lightvec));
 float RoL = max(0, dot(norm, lightvec));

 /**********************phongApprox****************************************/
 float a = Roughness * Roughness;			// 1 mul
 float a2 = a * a;						// 1 mul
 float rcp_a2 = exp2( -6.88886882 * Roughness + 6.88886882 );
 float c = 0.72134752 * rcp_a2 + 0.39674113;	// 1 mad
 float phongResult = rcp_a2 * exp2( c * RoL - c );		// 2 mad, 1 exp2, 1 m
 /**********************************END**************************************/
 Color += (0.7 * NoL)* lightcolor * (DiffuseColor + SpecularColor * phongResult);

//if not fully rough
 //vec3 SpecularIBL = GetImageBasedReflectionLighting(Roughness);

// Environment map has been prenormalized, scale by lightmap luminance
 Color += 1 * IndirectIrradiance * SpecularColor;

 vec4 VertexFog = vec4(0, 0, 0, 1);
 //Color = lerp(Color, DiffuseColor + SpecularColor, 1);


 Color = mix(Color, DiffuseColor + SpecularColor, 0.1);

 gl_FragColor = vec4(Color.rgb,1.0);

 /*
  float dist = length(lightvec);

 vec3 lightVector = normalize(lightvec);
 float nxDir = max(0.0, dot(norm, lightVector));
 vec4 diffuse = vec4(1,1,1,1.0) * nxDir;

 float specularPower = 0;
 if(nxDir != 0.0)
 {
 vec3 cameraVector = normalize(CAMERA_POSITION - WORD_POSITION);
 vec3 halfVector = normalize(lightVector + cameraVector);
 float nxHalf = max(0.0,dot(norm, halfVector));
 specularPower = pow(nxHalf, 64);
 }
 vec4 specular = vec4(0.9,0.9,0.9,1.0) * specularPower;

 gl_FragColor = vec4(0.12,0.12,0.12,1) +
 (diffuse * vec4(baseColor.rgb,1.0)) +
 specular; 
 */
 //gl_FragColor = vec4(BaseColor.rgb,1.0);

}