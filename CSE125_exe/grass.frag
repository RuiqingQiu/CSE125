varying vec3 vDiffuse;
varying vec2 vTexCoords;
uniform sampler2D tex;

void main()
{	
   vec4 texColor = texture2D(tex, vTexCoords);

   gl_FragColor  = texColor;//vec4(vDiffuse.xyz,1); 
}
