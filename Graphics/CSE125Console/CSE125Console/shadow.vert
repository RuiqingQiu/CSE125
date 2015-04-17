varying vec3 vN;
varying vec3 v;
void main(void)  
{     
   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   vN = normalize(gl_NormalMatrix * gl_Normal);
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
   gl_TexCoord[0] = gl_MultiTexCoord0;
   gl_Position = ftransform();


}
       



/*
varying vec3 Normal;
uniform vec3 LightPosition;
uniform vec3 cameraPosition;

varying vec3 camera;
varying vec3 position;


varying vec2 texcoord;

varying vec3 Color;
varying vec2 Texcoord;
void main()
{
	Normal = gl_NormalMatrix * gl_Normal;
	camera = cameraPosition;
	position = vec3(gl_ModelViewProjectionMatrix * gl_Vertex);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
			//gl_Position = ftransform();
			//v_position = gl_Position;
	Texcoord = texcoord;
}
*/
/*
void main()
{
    Texcoord = texcoord;
}
*/

					
/*	
precision highp float;
attribute vec3 position;
attribute vec3 normal;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
varying vec3 fNormal;
varying vec3 fPosition;

void main()
{
  fNormal = normalize(normalMatrix * normal);
  vec4 pos = modelViewMatrix * vec4(position, 1.0);
  fPosition = pos.xyz;
  gl_Position = projectionMatrix * pos;
}
*/