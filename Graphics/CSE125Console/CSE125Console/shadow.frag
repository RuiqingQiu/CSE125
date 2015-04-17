uniform sampler2D tex;
uniform sampler2D norm;
uniform sampler2D gloss;

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
