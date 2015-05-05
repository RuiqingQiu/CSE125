
varying vec3 vDiffuse;
varying vec2 vTexCoords;

uniform vec3 vLight;
uniform vec3 vClusterTranslation;

void main()
{
	vec2 TexCoords= vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
    vec3 Normal = normalize( gl_NormalMatrix * gl_Normal);
    vec3 Position =  gl_Vertex.xyz;

	 vec3 vPosition = Position.xyz;
	 vec3 vNormal = Normal.xyz;
    if (TexCoords.y >=0.5) {
    vPosition = Position + vClusterTranslation;
    vNormal = normalize(Normal * 2.0 +
                           vClusterTranslation);  
   }

  // Output stuff
  gl_Position  = gl_ModelViewProjectionMatrix * vec4(vPosition.xyz,1);

  vDiffuse = dot(vLight, vNormal);
  vTexCoords = TexCoords;
}