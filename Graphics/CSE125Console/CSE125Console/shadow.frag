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




/*
varying vec3 N;
varying vec3 v;    
void main (void)  
{  
   vec3 L = normalize(gl_LightSource[0].position.xyz - v);   
   vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)  
   vec3 R = normalize(-reflect(L,N));  
 
   //calculate Ambient Term:  
   vec4 Iamb = gl_FrontLightProduct[0].ambient;    

   //calculate Diffuse Term:  
   vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);
   Idiff = clamp(Idiff, 0.0, 1.0);     
   
   // calculate Specular Term:
   vec4 Ispec = gl_FrontLightProduct[0].specular 
                * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
   Ispec = clamp(Ispec, 0.0, 1.0); 
   // write Total Color:  
   gl_FragColor = gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec;     
}
*/          

		  


/*
precision highp float;
uniform float time;
uniform vec2 resolution;
varying vec3 fPosition;
varying vec3 fNormal;


varying vec3 Color;
varying vec2 Texcoord;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;

void main()
{
    vec4 colKitten = texture(texKitten, 0.5,0);
    vec4 colPuppy = texture(texPuppy, 0.5,0);
	gl_FragColor = colKitten;
    //gl_FragColor = vec4(1, 0, 0 , 1);
	//gl_FragColor = mix(colKitten, colPuppy, 0.5);
}
*/

/*
uniform sampler2D tex;

varying vec3 Normal;

varying vec3 camera;
varying vec3 position;
void main()
{
  gl_FragColor = texture(tex, Texcoord) * vec4(Color, 1.0);
  //gl_FragColor = vec4(1,0,0, 1.0);
  //gl_FragColor =  textureCube(cube, position.xyz);

}
*/