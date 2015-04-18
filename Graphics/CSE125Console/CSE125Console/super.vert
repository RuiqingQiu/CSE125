// Used for shadow lookup

//uniform mat4 model_view_projection_matrix;

attribute vec3 tangent;
attribute vec3 binormal;
varying vec3 lightvec; 
varying vec3 WORLD_NORMAL; 
varying vec3 WORD_POSITION; 

void main()
{

 gl_Position =   ftransform() ;
 gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
 
 WORD_POSITION = (gl_ModelViewMatrix  *gl_Vertex).xyz;
 WORLD_NORMAL = normalize(gl_NormalMatrix * gl_Normal);

 mat3 TBNMatrix = mat3(tangent, binormal, WORLD_NORMAL);
 lightvec =  WORD_POSITION-vec3(5,5,2);
 lightvec *= TBNMatrix; 
 
}
